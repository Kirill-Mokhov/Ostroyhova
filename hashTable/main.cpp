#include <iostream>
#include <string>

using namespace std;

const int ERROR_HASHTABLE_FULL = -1;
const int ERROR_RECORD_NOT_FOUND = -2;
const int ERROR_KEY_IS_NOT_UNIQUE = -3;
const int ERROR_TABLE_IS_EMPTY = -4;

struct Record {
	unsigned int key;
    string fullName;
};

class HashTable {
	unsigned int size, countOfElem;
	bool* status;
	Record* table;

public:
    
	HashTable(unsigned int N) {
		size = N;
		countOfElem = 0;
		table = new struct Record[size];
		status = new bool[size];
		for (int i = 0; i < size; i++) {
			status[i] = 0;
		}
	}

	~HashTable() {
		delete[] table;
		delete[] status;
	}

	int hashFunction1(unsigned int key) {
        int address = 0;
        while (key != 0) {
            address = address + (key % 10);
            key = key / 10;
        }
        address = address % size;
        return address;
	}

	int hashFunction2(int LastHash) {
		int address = LastHash;
		address = (address + 1) % size;
		return address;
	}

	void print() {
	    cout << "-----------------------------------------------" << endl;
		for (size_t i = 0; i < size; i++) {
			if (status[i] == 1) {
				cout << " | " << i << " | " << table[i].key << " | " << table[i].fullName << " | "<< endl;
			}
		}
        cout << "-----------------------------------------------" << endl;
		cout << "Элементов в таблице: \"" << countOfElem << "\" из \"" << size << "\"" << endl;
	}

	int add(Record record) {

        if (countOfElem == size) {
            cout << "Нельзя добвить данную запись: \"" << record.key << " | " << record.fullName << "\"" << endl;
            cout << "Таблица полная! Освободите ячейку, чтобы добавить новую запись!" << endl;
            return ERROR_HASHTABLE_FULL;
        }

        bool canAdd = true;
        size_t i = 0;
        while ((canAdd == true) && (i < size)) {
            if ((status[i] == 1) && (record.key == table[i].key)) {
                canAdd = false;
                cout << "Нельзя добавить данную запись : \"" << record.key << " | " << record.fullName << "\"" << endl;
                cout << "Ключ \"" << record.key << "\" не уникальный! В записи под номером \"" << i << "\" находится абсолютно идентичный ключ \"" << table[i].key << "\"" << endl;
                return ERROR_KEY_IS_NOT_UNIQUE;
            }
            i++;
        }

        if (canAdd == true) {
            int address = hashFunction1(record.key);
            if (status[address] == 1) {
                size_t steps = 0;
                while (steps <= size) {
                    if (status[address] == 0) {
                        table[address].key = record.key;
                        table[address].fullName = record.fullName;
                        status[address] = 1;
                        countOfElem++;
                        return 0;
                    }
                    address = hashFunction2(address);
                    steps++;
                }
            }
            else {
                table[address].fullName = record.fullName;
                table[address].key = record.key;
                status[address] = 1;
                countOfElem++;
                return 0;
            }
        }
    }

	int search(Record record) {
	    if (countOfElem == 0){
	        cout << "Невозможно найти данную запись : \"" << record.key << " | " << record.fullName << "\"" << endl;
	        cout << "Таблица пустая" << endl;
            return ERROR_TABLE_IS_EMPTY;
	    }
		size_t count = 1;
		int address = hashFunction1(record.key);
		if ((table[address].fullName == record.fullName) && (table[address].key == record.key) && (status[address] == 1)) {
			return address;
		}
		else {
			while (count <= countOfElem) {
				address = hashFunction2(address);
				if ((table[address].fullName == record.fullName) && (table[address].key == record.key) && (status[address] == 1)) {
					return address;
				}
				if (status[address] == 1)
                    count++;
			}
			return ERROR_RECORD_NOT_FOUND;
		}
	}

	int deleteRecord(Record record) {
		int address = search(record);
		if (address == ERROR_RECORD_NOT_FOUND) {
		    cout << "Неудалось удалить. Данная запись не найдена : \"" << record.key << " | " << record.fullName << "\"" << endl;
			return ERROR_RECORD_NOT_FOUND;
		}
		table[address].key = 0;
        table[address].fullName = "";
		status[address] = 0;
		countOfElem--;
		rehashTable();
        return 0;
	}

	void rehashTable(){
	    Record record;
	    size_t count = 0;
        while(count <= size){
            if(status[count] == 1){
                record.key = table[count].key;
                record.fullName = table[count].fullName;
                table[count].key = 0;
                table[count].fullName = "";
                status[count] = 0;
                countOfElem--;
                add(record);
            }
            count++;
        }
    }
};



int main(){
	HashTable table(30);
	Record record;

    record.key = 1009;
    record.fullName = "Kirill Mokhovichenko10";

    for (int i=0;i<8;i++){

        table.add(record);
        record.key = record.key+1000-1;
        record.fullName[0] += 1;

    }


 table.print();



    for (int i=0;i<8;i++){


        table.deleteRecord(record);
        record.key = record.key-2000+2;
        record.fullName[0] -= 2;

    }




    table.print();


    record.key = 1119;
    record.fullName = "Kirill Mokhovichenko10";

    for (int i=0;i<10;i++){

        table.add(record);
        record.key = record.key+1000-1;
        record.fullName[0] += 1;

    }


    table.print();


    record.key = 1009;
    record.fullName = "Kirill Mokhovichenko10";

    for (int i=0;i<8;i++){

        table.add(record);
        record.key = record.key+1000-1;
        record.fullName[0] += 1;

    }


    table.print();



    for (int i=0;i<8;i++){
       cout<<"del "<<record.fullName<<" "<<record.key<<endl;

        table.deleteRecord(record);
        record.key = record.key-1000+1;
        record.fullName[0] -= 1;

    }




    table.print();





record.key = 1109;
record.fullName = "Kirill";

for (int i=0;i<8;i++){

table.add(record);
record.key = record.key+1000-1;
record.fullName[0] += 1;

}


table.print();
}
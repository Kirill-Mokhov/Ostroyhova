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
	    int address = 0, a = 0, b = 0;
	    a = key / 1000;
		for(size_t i = 0; i <= 3; i++){
		    key = key % 10;
		}
		b = key;
		address = (a + b) / 2;
		return address;
	}

	int hashFunction2(int LastHash) {
		int address = LastHash;
		address += 1;
		if (address >= size)
		    address -= size;
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
				count++;
				if ((table[address].fullName == record.fullName) && (table[address].key == record.key) && (status[address] == 1)) {
					return address;
				}
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
		status[address] = 0;
		countOfElem--;
        return 0;
	}
};

int main(){
	HashTable table(10);
	Record record;
	record.key = 1000;
	record.fullName = "Kirill Mokhovichenko1";
    table.add(record);
    record.key = 1010;
    record.fullName = "Kirill Mokhovichenko2";
    table.add(record);
    record.key = 1020;
    record.fullName = "Kirill Mokhovichenko3";
    table.add(record);
    record.key = 1030;
    record.fullName = "Kirill Mokhovichenko4";
    table.add(record);
    record.key = 1040;
    record.fullName = "Kirill Mokhovichenko5";
    table.add(record);
    record.key = 1050;
    record.fullName = "Kirill Mokhovichenko6";
    table.add(record);
    record.key = 1060;
    record.fullName = "Kirill Mokhovichenko7";
    table.add(record);
    record.key = 1070;
    record.fullName = "Kirill Mokhovichenko8";
    table.add(record);
    record.key = 1080;
    record.fullName = "Kirill Mokhovichenko9";
    table.add(record);
    record.key = 1090;
    record.fullName = "Kirill Mokhovichenko10";
    table.add(record);

    record.key = 9139;
    record.fullName = "Таблица полная";
    table.add(record);

    table.print();


    record.key = 9099;
    record.fullName = "Kirill Mokhovichenko10";
    table.deleteRecord(record);

    table.print();

    record.key = 9069;
    record.fullName = "Ключ не уникльный";
    table.add(record);

    record.key = 9059;
    record.fullName = "Kirill Mokhovichenko6";
    table.deleteRecord(record);

    table.print();

}

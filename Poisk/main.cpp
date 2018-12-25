#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int interpolatingSearch(int a[], int arraySize, int key) {
    int low = 0;  //Наало массива
    int high = arraySize - 1; //Конец массива
    int mid;
    while (a[low] < key && a[high] >= key) {  //цикл интерполирующего поиска
        mid = low + ((key - a[low]) * (high - low)) / (a[high] - a[low]);
        if (a[mid] < key)
            low = mid + 1;
        else if (a[mid] > key)
            high = mid - 1;
        else
            return mid;
    }
}

int lineinioySearch(int a[], int arraySize, int key) {
    for (int i = 0; i < arraySize; i++){
        if ( a[i] == key );
        return i;
    }
}

int main() {
    unsigned int n;
    cout << "Vvedite razmernost matrizi : ";
    cin >> n;
    int matrisa[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrisa[i][j] = rand() % 10;
            cout << matrisa[i][j] << " ";
        }
    cout << endl;
    }

    cout << "Vvektora (diagonali parallelnie pobochnoi)" << endl;

    int key;
    cout << endl << endl << "Vvedite clytch : ";
    cin >> key;



    int new_n = 0;
    while (new_n <= n) {
        for (int i = 0; i < new_n; i++)
            for (int j = 0; j < new_n; j++)
                if (i == new_n - j - 1)
                    cout << matrisa[i][j];
        cout << endl;
        new_n++;
        //cout << "Klytch \"" << key << "\" nahoditsia v pozisii " << lineinioySearch(numbSearch, n, key) << " (Lineinii poisk)" << endl;
        //cout << "Klytch \"" << key << "\" nahoditsia v pozisii " << interpolatingSearch(numbSearch, n, key) << " (Interpoliasionnii poisk)";
    }


    new_n = 0;
    while (new_n <= n + 1) {
        for (int i = n - 1; i > 0; i--)
            for (int j = n - 1; j > 0; j--)
                if (i == new_n - j - 1)
                    cout << matrisa[n - i][n - j];
        cout << endl;
        new_n++;
        //cout << "Klytch \"" << key << "\" nahoditsia v pozisii " << lineinioySearch(numbSearch, n, key) << " (Lineinii poisk)" << endl;
        //cout << "Klytch \"" << key << "\" nahoditsia v pozisii " << interpolatingSearch(numbSearch, n, key) << " (Interpoliasionnii poisk)";
    }

}
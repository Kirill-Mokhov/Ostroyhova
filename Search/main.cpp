#include <iostream>
#include <time.h>
#include <windows.h>
#include <ctime>
#include <math.h>

using namespace std;

int i, j, n, count;

void Shell_sort(int *A, int n) { //сортировка Шелла
    size_t swap = 0;
    size_t cmp = 0 ;
    int graniza = n / 2;
    while ( graniza > 0) {
        for (i = 0; i < n - graniza; i++) {
            j = i;
            cmp++;
            while (j >= 0 && A[j] > A[j + graniza]){
                count = A[j];
                A[j] = A[j + graniza];
                A[j + graniza] = count;
                j--;
                if (j >= 0)
                    cmp++;
                swap++;
            }
        }
        graniza = graniza / 2;
    }
    for (i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
    cout << "Kolvo swapow : \"" << swap << "\"" << endl;
    cout << "Kolichestvo sravnenii : \"" << cmp << "\"" << endl;
}

int howRazr(int A) {
    int cislo, n = 1;
    cislo = A;
    while (cislo > 9) {
        cislo /= 10;
        n++;
    }
    return n;
}

int razriadChisla(int A , int numbDel) {
    int cislo;
    cislo = A;
    cislo = cislo % (int)pow(10,numbDel);
    if (cislo > 9) {
        while (cislo > 9) {
            cislo /= 10;
        }
    }
    return cislo;
}



void Radix_sort(int *A, int n) { //Поразрядная сортировка

    int **matrixSort = new int *[10];
    for (size_t i = 0; i < 10; i++)
        matrixSort[i] = new int[n];

    cout << "Not sorted vector: ";
    for (size_t i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;

    /**Удаление нулей из вектора, чтобы работала поразрядная сортировка**/
    int errO(0);
    for (size_t i = 0; i < n; i++){
        if (A[i] == 0){
            errO++;
        }
    }
    if (errO > 0){
        int A1[n-errO];
        size_t j(0);
        for (size_t i = 0; i < n; i++){
            if (A[i] != 0){
                A1[j] = A[i];
                j++;
            }
        }
        n = n - errO;
        for (size_t i = 0; i < n; i++)
            A[i] = A1[i];
    }

    int maxRazriadCisla(0);
    for (size_t i = 0; i < n; i++) {
        if (howRazr(A[i]) > maxRazriadCisla)
            maxRazriadCisla = howRazr(A[i]);
    }
    cout << "Maximum number of digits in numbers : " << maxRazriadCisla << endl;

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < n; j++) {
            matrixSort[i][j] = 0;
        }
    }
    int cmp(0);

    for (int k = 1; k <= maxRazriadCisla; k++) {

        for (size_t j = 0; j < n; j++) {
            bool write = false;
            bool dontWrite = false;
            if (howRazr(A[j])>= k) {
                for (size_t q = 0; q < n; q++) {
                    if ((write == false) && (matrixSort[razriadChisla(A[j], k)][q] == 0)) {
                        matrixSort[razriadChisla(A[j], k)][q] = A[j];
                        write = true;
                        cmp++;
                    }
                }
            }
            else {
                write = false;
                for (size_t q = 0; q < n; q++) {
                    if ((write == false) && (matrixSort[0][q] == 0)){
                        matrixSort[0][q] = A[j];
                        write = true;
                    }
                }
            }
        }


        /**
        cout << "Rearrangement of elements " << k << " steps :" << endl;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                cout << matrixSort[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        **/
        int numb(0);
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                bool write = false;
                if ((howRazr(matrixSort[i][j]) == k) && (matrixSort[i][j] != 0)) {
                    for (size_t k = 0; k < n; k++){
                        if ((write == false) && (matrixSort[0][k] == 0)) {
                            matrixSort[0][k] = matrixSort[i][j];
                            matrixSort[i][j] = 0;
                            write = true;
                        }
                    }
                }
            }
        }
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                if (matrixSort[i][j] != 0) {
                    A[numb] = matrixSort[i][j];
                    numb++;
                    cmp++;
                }
            }
        }

        /**
        cout << "Assembly " << k << " steps :" << endl;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                cout << matrixSort[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "Vector after assembly " << k << " steps :"  << endl;
        for (size_t i = 0; i < n; i++)
            cout << A[i] << " ";
        cout << endl << "****************" << endl;
        **/

        for (size_t i = 0; i < 10; i++){
            for (size_t j = 0; j < n; j++){
                matrixSort[i][j] = 0;
            }
        }
    }

    cout << "Radix sorting result :" << endl;
    for (size_t i = 0; i < errO; i++)
        cout << "0 ";
    for (size_t i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
    cout << "cmp = " << cmp << endl;
}




int main(){
    cout << "Enter array size: ";
    cin >> n;
    if (n != 0) {
        int *vectorSearchShella = new int[n];
        for (i = 0; i < n; i++) {
            cout << "Enter the " << i + 1 << " element of the array:";
            cin >> vectorSearchShella[i];
        }

        cout << "The resulting vector:" << endl;
        for (i = 0; i < n; i++)
            cout << vectorSearchShella[i] << " ";

        int *vectorSearchForRadix = new int[n];
        for (i = 0; i < n; i++)
            vectorSearchForRadix[i] = vectorSearchShella[i];

        double t1, t2, t3, t4, t_shell, t_radix;
        bool trueVectorSort = true, equalVectorSort = true;

        for (size_t i = 0; i < n - 1; i++) {
            if (vectorSearchShella[i] > vectorSearchShella[i + 1]) {
                trueVectorSort = false;
            }
        }

        if (trueVectorSort == false) {
            cout << endl << "****************************************************" << "Shell sort: " << endl;
            t1 = (double) GetTickCount();
            Shell_sort(vectorSearchShella, n);
            t2 = (double) GetTickCount();
            t_shell = t2 - t1;
            cout << "Time Shell sort: " << t_shell << endl;
            cout << "****************************************************" << endl;


            cout << endl << "****************************************************" << "Radix sort: " << endl;
            t3 = (double) GetTickCount();
            Radix_sort(vectorSearchForRadix, n);
            t4 = (double) GetTickCount();
            t_radix = t4 - t3;
            cout << "Time Radix sort: " << t_radix << endl;
            cout << "****************************************************" << endl;
        } else {
            for (size_t i = 0; i < n - 1; i++) {
                if (vectorSearchShella[i] < vectorSearchShella[i + 1]) {
                    equalVectorSort = false;
                }
            }
            if (equalVectorSort == true) {
                cout << endl << "Notice: All elements of the vector are equal!" << endl;
            } else {
                cout << endl << "Notice: Vector already sorted!" << endl;
            }
        }
    }else{
        cout << "Error: Your vector is ZERO!";
    }
}
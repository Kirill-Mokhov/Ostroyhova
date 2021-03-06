#include <iostream>
#include <time.h>
#include <windows.h>
#include <ctime>
#include <math.h>

using namespace std;

int i, j, n, count, RandVector, errO(0);

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
    cout << "Number of swaps: \"" << swap << "\"" << endl;
    cout << "Number of comparisons: \"" << cmp << "\"" << endl;
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
    int cislo ,delTEN(10);
    cislo = A;
    for (size_t i = 1; i < numbDel; i++)
        delTEN *= 10;
    cislo = cislo % delTEN;
    if (cislo > 9) {
        while (cislo > 9) {
            cislo /= 10;
        }
    }
    return cislo;
}


int razmer(){
    int razmernost(0);
    cout << "To create a vector with your elements values\"1\" and press \"Enter\"." << endl;
    cout << "To create a vector with random elements values\"2\" and press \"Enter\"." << endl;
    cin >> RandVector;
    cout << endl;
    if (RandVector == 1){
        cout << "Enter vector size: ";
        cin >> razmernost;
    }
    if (RandVector >= 2){
        cout << "Enter the size of the random vector: ";
        cin >> razmernost;
    }
    return razmernost;
}

void delZiro(int *A, int n) {
/**Удаление нулей из вектора, чтобы работала поразрядная сортировка**/
    for (size_t i = 0; i < n; i++) {
        if (A[i] == 0) {
            errO++;
        }
    }
    if (errO > 0) {
        int A1[n - errO];
        size_t j(0);
        for (size_t i = 0; i < n; i++) {
            if (A[i] != 0) {
                A1[j] = A[i];
                j++;
            }
        }
        n = n - errO;
        for (size_t i = 0; i < n; i++)
            A[i] = A1[i];
    }
}



void Radix_sort(int *A, int n) { //Поразрядная сортировка

    int **matrixSort = new int *[10];
    for (size_t i = 0; i < 10; i++)
        matrixSort[i] = new int[n];

    int maxRazriadCisla(0);
    for (size_t i = 0; i < n; i++) {
        if (howRazr(A[i]) > maxRazriadCisla)
            maxRazriadCisla = howRazr(A[i]);
    }
    cout << "Maximum number of digits in numbers: " << maxRazriadCisla << endl;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < n; j++) {
            matrixSort[i][j] = 0;
        }
    }
    int swap(0);

    for (int k = 1; k <= maxRazriadCisla; k++) {

        for (size_t j = 0; j < n; j++) {
            bool write = false;
            if (howRazr(A[j])>= k) {
                for (size_t q = 0; q < n; q++) {
                    if ((write == false) && (matrixSort[razriadChisla(A[j], k)][q] == 0)) {
                        matrixSort[razriadChisla(A[j], k)][q] = A[j];
                        write = true;
                        swap++;
                    }
                }
            }
            else {
                write = false;
                for (size_t q = 0; q < n; q++) {
                    if ((write == false) && (matrixSort[0][q] == 0)){
                        matrixSort[0][q] = A[j];
                        write = true;
                        swap++;
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
                    swap++;
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
    cout << "Number of swaps: \"" << swap << "\"" << endl;
}




int main(){
    n = razmer();
    int *vectorSearchShella = new int[n];
    int *vectorSearchForRadix = new int[n];
    if (RandVector == 1){
        for (i = 0; i < n; i++) {
            cout << "Enter the " << i + 1 << " element of the array: ";
            cin >> vectorSearchShella[i];
        }
    }
    if (RandVector == 2){
        for(size_t i = 0; i < n; i++)
            vectorSearchShella[i] = rand() % 100 + 1;
    }

    if (n != 0) {
        cout << "The resulting vector: " << endl;
        for (i = 0; i < n; i++)
            cout << vectorSearchShella[i] << " ";

        //int *vectorSearchForRadix = new int[n];
        for (i = 0; i < n; i++)
            vectorSearchForRadix[i] = vectorSearchShella[i];

        double time1, time2, time3, time4, t_shell, t_radix;
        bool trueVectorSort = true, equalVectorSort = true;

        for (size_t i = 0; i < n - 1; i++) {
            if (vectorSearchShella[i] > vectorSearchShella[i + 1]) {
                trueVectorSort = false;
            }
        }

        if (trueVectorSort == false) {
            cout << endl << "*************************Shell sort*************************" <<  endl;
            cout << "Not sorted vector: ";
            for (i = 0; i < n; i++)
                cout << vectorSearchShella[i] << " ";
            cout << endl;
            time1 = clock() / 10000.0;
            Shell_sort(vectorSearchShella, n);
            time2 = clock() / 10000.0;
            t_shell = time2 - time1;
            cout << "Shell sorting result: ";
            for (i = 0; i < n; i++)
                cout << vectorSearchShella[i] << " ";
            cout << endl;
            printf("Time Shell sort: = %.4f",t_shell);
            cout << endl;
            cout << "************************************************************" << endl;


            cout << endl << "*************************Radix sort*************************" << endl;
            cout << "Not sorted vector: ";
            for (size_t i = 0; i < n; i++)
                cout << vectorSearchForRadix[i] << " ";
            cout << endl;
            delZiro(vectorSearchForRadix, n);
            time3 = clock() / 1000.0;
            Radix_sort(vectorSearchForRadix, n);
            time4 = clock() / 1000.0;
            t_radix = time4 - time3;
            cout << "Radix sorting result: ";
            for (size_t i = 0; i < errO; i++)
                cout << "0 ";
            for (size_t i = 0; i < n; i++)
                cout << vectorSearchForRadix[i] << " ";
            cout << endl;
            printf("Time Radix sort: = %.4f",t_radix);
            cout << endl;
            cout << "************************************************************" << endl;
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
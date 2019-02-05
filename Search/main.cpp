#include <iostream>
#include <time.h>
#include <windows.h>
#include <ctime>
#include <math.h>

using namespace std;

int i, j, n, count;

void Shell(int *A, int n) { //сортировка Шелла
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



void porazriadniaiaSearch(int *A, int n) { //Поразрядная сортировка
    int **matrixSearch = new int *[10];
    for (size_t i = 0; i < 10; i++)
        matrixSearch[i] = new int[n];

    cout << "Pervonachalnii vector: ";
    for (size_t i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;

    int maxRazriadCisla(0);
    for (size_t i = 0; i < n; i++) {
        if (howRazr(A[i]) > maxRazriadCisla)
            maxRazriadCisla = howRazr(A[i]);
    }
    cout << "maxRazr : " << maxRazriadCisla << endl;

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < n; j++) {
            matrixSearch[i][j] = 0;
        }
    }
    int cmp(0);

    for (int k = 1; k <= maxRazriadCisla; k++) {

        for (size_t j = 0; j < n; j++) {
            bool write = false;
            bool dontWrite = false;
            for (size_t q = 0; q < n; q++) {
                if ((write == false) && (matrixSearch[razriadChisla(A[j], k)][q] == 0)) {
                    for (size_t i = 0; i < n; i++) {
                        if (matrixSearch[0][i] == A[j]){
                            dontWrite = true;
                        }
                    }
                    if (dontWrite == false) {
                        matrixSearch[razriadChisla(A[j], k)][q] = A[j];
                        write = true;
                        cmp++;
                    }
                }
            }
        }
        ///**
        cout << "Peregrypirovka " << k << " SHaga :" << endl;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                cout << matrixSearch[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        //**/
        int numb(0);
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                bool write = false;

                if(matrixSearch[i][j] != 0){
                    A[numb] = matrixSearch[i][j];
                    numb++;
                    cmp++;
                }
                if ((howRazr(matrixSearch[i][j]) == k) && (matrixSearch[i][j] != 0)) {
                    for (size_t k = 0; k < n; k++) {
                        if ((write == false) && (matrixSearch[0][k] == 0)) {
                            matrixSearch[0][k] = matrixSearch[i][j];
                            matrixSearch[i][j] = 0;
                            write = true;
                        }
                    }
                }
            }
        }
        cout << "Massiv posle " << "k" << " shaga."  << endl;
        for (size_t i = 0; i < n; i++)
            cout << A[i] << " ";
        cout << endl << "****************" << endl;


        ///**
        cout << "Sborka " << k << " SHaga :" << endl;
        for (size_t i = 0; i < 10; i++) {
            for (size_t j = 0; j < n; j++) {
                cout << matrixSearch[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
         //**/

        for (size_t i = 0; i < 10; i++){
            for (size_t j = 0; j < n; j++){
                matrixSearch[i][j] = 0;
            }
        }
    }

    cout << "Rezyltat porazriadnoi search: " << endl;
    for (size_t i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
    cout << "cmp = " << cmp << endl;
}




int main(){
    cout << "Razmer massiva : ";
    cin >> n;
    int *vectorSearchShella = new int[n];
    for (i=0; i<n; i++){
        cout << i + 1 << " Zapolnite chislami ";
        cin >> vectorSearchShella[i];
    }
    cout << "Vash vector:" << endl;
    for (i=0; i<n; i++)
        cout << vectorSearchShella[i] << " ";
    cout << endl <<"Rezyltat " << endl;
    int *vectorSearchForPoraz = new int[n];
    for (i=0; i<n; i++)
        vectorSearchForPoraz[i] = vectorSearchShella[i];
    double t1, t2, t3, t4, t_shell, t_poraz;

    cout << endl <<"Search Shella: " << endl;
    t1 = (double)GetTickCount();
    Shell(vectorSearchShella, n);
    t2 = (double)GetTickCount();
    t_shell = t2 - t1;
    cout << "Time Shell sort: " << t_shell << endl;

    cout << endl <<"Search Porazriadnaiaia: " << endl;
    t3 = (double)GetTickCount();
    porazriadniaiaSearch(vectorSearchForPoraz, n);
    t4 = (double)GetTickCount();
    t_poraz = t4 - t3;
    cout << "Time Porazriadnaia sort: " << t_poraz << endl;
}
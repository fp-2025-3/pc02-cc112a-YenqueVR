#include<iostream>
using namespace std;

const int F=4;
const int C=5;

int sumaSubmatriz(int (*i)[C], int FILAS, int COL, int *pos1, int *pos2);

int main(){
    
    int A[F][C]={
        {-2, 1,-3, 4,-1},
        { 2, 3,-2, 1,-5},
        {-1, 4, 2,-3, 2},
        { 1,-2, 3, 4,-1}
    };
    int (*inicio)[C]=A;

    return 0;
}

int sumaSubmatriz(int (*i)[C], int FILAS, int COL, int *pos1, int *pos2){

}
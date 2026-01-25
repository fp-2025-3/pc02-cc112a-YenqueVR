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

int sumaSubmatriz(int (*inicio)[C], int FILAS, int COL, int *pos1, int *pos2){
    int (*f1)[COL]=inicio, (*f2)[COL]=inicio;
    int *c1=*inicio, *c2=*inicio;

    //hallar la posicion exacta en la matriz de las posiciones 
    for(int (*i)[COL]=inicio; i<inicio+FILAS; i++){
        for(int *j=*i; j<*i+COL; j++){
            if(j==pos1) f1=i; c1=j; //se hallo la posicion exacta de pos1 (i1, j1)
            if(j==pos2) f2=i; c2=j; //se hallo la posicion exacta de pos2 (i2, j2)
        }
    }

    //calcular la suma de elementos de la submatriz delimitada
    int suma=0;
    for(int (*i)[COL]=f1; i<=f2; i++){  //desde la fila f1 hasta la fila f2
        for(int *j=*(i+(c1-*i)); j<*(i+(c2-*i)); j++){  //*(i+(c1-*i)): Pos del elemento en la fila i, c1-*i= #columna
            suma+= *j;
        }
    }

    return suma;    //retorna la suma de los elementos de la submatriz
}
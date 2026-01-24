#include<iostream>
using namespace std;

const int F=4;
const int C=5;

void imprimirMatrizYpicos(int (*inicio)[C], int (*fin)[C]);
int *posicionPico(int (*inicio)[C], int (*fin)[C], int (*i)[C], int *j);

int main(){

    int A[F][C]={
        {3,3,3,3,3},
        {3,4,4,2,3},
        {3,4,5,4,3},
        {3,3,3,3,3}
    };

    int (*inicio)[C]=A; //primera fila
    int (*fin)[C]=A+F;  //la fila inmediatamente despues de la ultima fila del arreglo

    imprimirMatrizYpicos(inicio,fin);

    return 0;
}

int *posicionPico(int (*inicio)[C], int (*fin)[C], int (*i)[C], int *j){
    bool alMenosMayor=false;    //al menos a uno debe ser mayor de sus vecino
    bool mayorOigual=true;  //debe ser mayor o igual que sus vecinos
    //comparar arriba
    if(i-1>=inicio && *(*(i-1)+(j-*i))<=*j){    //i-1: fila anterior, j-*i: posicion columna desde el comienzo de fila i 
        alMenosMayor=true;
    }else if(i!=inicio) mayorOigual=false;  //no modifica nada si esta en la fila = inicio
    //abajo
    if(i+1<fin && *(*(i+1)+(j-*i))<=*j){ 
        alMenosMayor=true;
    }else if(i!=fin-1) mayorOigual=false;   //no modifica nada si esta en la fila = fin-1
    //izquierda
    
}

void imprimirMatrizYpicos(int (*inicio)[C], int (*fin)[C]){
    //imprimir la matriz A
    cout<<"\nMatriz A["<<F<<"]["<<C<<"]:  ";
    for(int (*i)[C]=inicio; i<fin; i++){    //desde la primera fila hasta la ultima
        if(i!=inicio) cout<<"                 ";
        for(int *j=*i; j<*i+C; j++){    //*i = A[*][C], *j = A[F][C]
            cout<<*j<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    int (*i)[C]=inicio+1;
    int *j=*i+1;
    cout<<*(*(i-1)+(j-*i))<<endl;
}
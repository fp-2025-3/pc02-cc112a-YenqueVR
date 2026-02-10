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

int* posicionPico(int (*inicio)[C], int (*fin)[C], int (*i)[C], int *j){    //int (*i)[C]: fila i, int *j: pos en fila i
    bool alMenosMayor=false;    //al menos a uno debe ser mayor de sus vecinos
    bool mayorOigual=true;  //debe ser mayor o igual que sus vecinos

    //comparar arriba
    if(i-1>=inicio && *(*(i-1)+(j-*i))<*j){    //i-1: fila anterior, j-*i: posicion columna desde el comienzo de fila i 
        alMenosMayor=true;
    }else if(i!=inicio && *(*(i-1)+(j-*i))>*j) mayorOigual=false;  //no modifica nada si esta en la fila = inicio

    //abajo
    if(i+1<fin && *(*(i+1)+(j-*i))<*j){ 
        alMenosMayor=true;
    }else if(i!=fin-1 && *(*(i+1)+(j-*i))>*j) mayorOigual=false;   //no modifica nada si esta en la fila = fin-1

    //izquierda
    if(j-1>=*i && *(j-1)<*j){  //j-1: elemento anterior, *(j-1): valor del elemento anterior
        alMenosMayor=true;
    }else if(j!=*i && *(j-1)>*j) mayorOigual=false;  //no modifica nada si esta en la columna = *i

    //derecha
    if(j+1<*i+C && *(j+1)<*j){
        alMenosMayor=true;
    }else if(j!=*i+C-1 && *(j+1)>*j) mayorOigual=false;  //no modifica nada si esta en la columna = *i

    if(alMenosMayor && mayorOigual) return j;   //si cumple, retorna la direccion o posicion del elemento pico
    else return *fin;   //si no cumple, retorna la direccion *fin = *(A+F) o *(inicio+F)
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

    cout<<"Elementos pico:\n";
    for(int (*i)[C]=inicio; i<fin; i++){
        for(int *j=*i; j<*i+C; j++){
            int *elemPico=posicionPico(inicio,fin,i,j);
            if(elemPico!=*fin){
                cout<<"Pico en ("<<i-inicio<<", "<<j-*i<<"): "<<*elemPico<<" ; Pos: "<<elemPico;
                cout<<endl;
            }
        }
    }
    cout<<endl;
}
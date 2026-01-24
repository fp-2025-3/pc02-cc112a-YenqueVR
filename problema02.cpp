#include<iostream>
using namespace std;

void imprimirArreglo(int *inicio, int *fin);
int* buscar(int *inicio, int *fin, bool (*equivale)(int,int), int clave);
bool igual(int a, int b);
bool mismaParidad(int a, int b);
bool divideA(int a, int b);
bool mismaCantidadDigitos(int a, int b);
bool mismoResiduoMod5(int a, int b);

int main(){

    int arr[]={-1,21,2,-2,8,13,25};
    int N=sizeof(arr)/sizeof(arr[0]);
    int *inicio=arr;
    int *fin=arr+N;
    int clave=13;

    return 0;
}

void imprimirArreglo(int *inicio, int *fin){

}

int* buscar(int *inicio, int *fin, bool (*equivale)(int,int), int clave){
    
}
bool igual(int a, int b){
    return a==b;
}
bool mismaParidad(int a, int b){
    return ((a%2==0 && b%2==0)||(a%2==1 && b%2==1));
}
bool divideA(int a, int b){
    return b%a==0;
}
bool mismaCantidadDigitos(int a, int b){
    if(a<0) a*=-1;
    if(b<0) b*=-1;

    int digA=0, digB=0;

    if(a==0) digA++;
    else{
        while(a>0){
            digA++;
            a/=10;
        }
    }

    if(b==0) digB++;
    else{
        while(b>0){
            digB++;
            b/=10;
        }
    }

    return digA==digB;
}
bool mismoResiduoMod5(int a, int b){
    return (a%5)==(b%5);
}
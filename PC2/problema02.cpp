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

    cout<<"\nA[] = ";
    imprimirArreglo(inicio,fin); //imprimir arreglo A[]
    cout<<"\nClave: "<<clave<<endl; //imprimir clave

    //lista de nociones
    bool (*eq)(int,int)=igual;
    int *ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nIgualdad exacta: ";
    if(ptr!=fin) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"No encontrado";

    eq=mismaParidad;
    ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nMisma paridad: ";
    if(ptr!=fin) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"No encontrado";

    eq=divideA;
    ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nDivide a: ";
    if(ptr!=fin) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"No encontrado";

    eq=mismaCantidadDigitos;
    ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nMisma cantidad de digitos: ";
    if(ptr!=fin) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"No encontrado";

    eq=mismoResiduoMod5;
    ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nMismo residuo modulo 5: ";
    if(ptr!=fin) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"No encontrado";

    cout<<endl;
    return 0;
}

void imprimirArreglo(int *inicio, int *fin){
    for(int *i=inicio; i<fin; i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}

int* buscar(int *inicio, int *fin, bool (*equivale)(int,int), int clave){
    for(int *i=inicio; i<fin; i++){
        if(equivale(*i, clave)) return i;   //si sale verdadero, retorna la posicion
    }
    return fin; //caso contrario si no lo encuentra, devuelve fin
}
bool igual(int a, int b){
    return a==b;
}
bool mismaParidad(int a, int b){
    if(a<0) a*=-1;  //vuelve positivo para comparar correctamente
    if(b<0) b*=-1;
    return ((a%2==0 && b%2==0)||(a%2==1 && b%2==1));    //ambos pares o impares
}
bool divideA(int a, int b){
    return b%a==0;  //si su division es exacta
}
bool mismaCantidadDigitos(int a, int b){
    if(a<0) a*=-1;  //lso vuelve positivo para comparar mejor
    if(b<0) b*=-1;

    int digA=0, digB=0; //los digitos de a y b

    if(a==0) digA++;    //0 es de un digito
    else{
        while(a>0){ //mientras a no este en 0<=a<1, ~a=0
            digA++; //sumamos un digito para a
            a/=10;  //dividimos para obtener el siguiente digito
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
    return (a%5)==(b%5);    //verdadero cuando sus residuos de dividir con 5 son iguales
}
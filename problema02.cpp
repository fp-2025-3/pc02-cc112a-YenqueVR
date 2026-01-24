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
    if(ptr!=nullptr) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"\nNo encontrado";

    eq=mismaParidad;
    int *ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nMisma paridad: ";
    if(ptr!=nullptr) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"\nNo encontrado";

    eq=divideA;
    int *ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nDivide a: ";
    if(ptr!=nullptr) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"\nNo encontrado";

    eq=mismaCantidadDigitos;
    int *ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nMisma cantidad de digitos: ";
    if(ptr!=nullptr) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"\nNo encontrado";

    eq=mismoResiduoMod5;
    int *ptr=buscar(inicio,fin,eq,clave);
    cout<<"\nMismo residuo modulo 5: ";
    if(ptr!=nullptr) cout<<"encontrado valor: "<<*ptr<<" Pos: "<<ptr;
    else cout<<"\nNo encontrado";

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
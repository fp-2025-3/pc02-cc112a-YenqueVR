#include<iostream>
using namespace std;

int costoMaximoPosible(int arr[], int n, int pos);
void imprimirArreglo(int arr[], int n);
void registroDeLlamadas(int pos, int resultado);

int main(){
    
    int arr[]={2,1,3};
    int n=sizeof(arr)/sizeof(arr[0]);
    int costoMaximo=costoMaximoPosible(arr,n,0);    //inicia en la posicion 0

    cout<<"\n\nArreglo: ";
    imprimirArreglo(arr,n);
    cout<<"Costo Maximo: "<<costoMaximo<<endl;
    return 0;
}

int costoMaximoPosible(int arr[], int n, int pos){
    //caso base
    if(pos==n){
        registroDeLlamadas(pos,0);
        return 0;    //devuelve 0 por que esta fuera de limites arr[n]
    }
    //caso recursivo
    int maxPosible=0;   //trabajando con enteros positivos
    int producto=1; //producto de la multiplicacion

    for(int i=pos; i<n; i++){
        producto*=*(arr+i);
        int costo=costoMaximoPosible(arr,n,i+1);
        if(producto+costo>maxPosible) maxPosible=producto+costo;    //actualizamos si el costo es mas grande
    }

    registroDeLlamadas(pos,maxPosible);     //puesto aqui para obtener el valor que retorna 
    return maxPosible;  //retornamos el costo maximo
}

void imprimirArreglo(int arr[], int n){
    for(int *i=arr; i<arr+n; i++){
        cout<<*i<<" ";
    }
    cout<<endl;
}

void registroDeLlamadas(int pos, int resultado){
    cout<<"\n=== Llamada a la funcion costoMaximoPosible(int,int,int) ===";
    cout<<"\nPosicion actual: "<<pos;
    cout<<" ; Valor Retornado: "<<resultado;
}
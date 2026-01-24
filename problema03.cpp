#include<iostream>
using namespace std;

const int F=4;
const int C=5;

void imprimirMatrizYpicos(int (*inicio)[C], int (*fin)[C]);

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

void imprimirMatrizYpicos(int (*inicio)[C], int (*fin)[C]){
    cout<<"\nMatriz A["<<F<<"]["<<C<<"]:  ";
    for(int (*i)[C]=inicio; i<fin; i++){    //desde la primera fila hasta la ultima
        if(i!=inicio) cout<<"                 ";
        for(int *j=*i; j<*i+C; j++){    //*i = A[*][C], *j = A[F][C]
            cout<<*j<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
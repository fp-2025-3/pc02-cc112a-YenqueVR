#include<iostream>
using namespace std;

const int F=4;
const int C=5;

int sumaSubmatriz(int (*i)[C], int *pos1, int *pos2);
void sumaSubmatrizMaxima(int (*inicio)[C]);

int main(){
    
    int A[F][C]={
        {-2, 1,-3, 4,-1},
        { 2, 3,-2, 1,-5},
        {-1, 4, 2,-3, 2},
        { 1,-2, 3, 4,-1}
    };
    int (*inicio)[C]=A;
    int *pos1=*inicio;
    int *pos2=(*(inicio+F-1))+C-1;

    cout<<"\nSuma de submatriz: "<<sumaSubmatriz(inicio,pos1,pos2)<<endl;
    return 0;
}

void imprimirMatriz(int (*inicio)[C], int (*fin)[C]){
    for(int (*i)[C]=inicio; i<fin; i++){
        cout<<" ";
        for(int *j=*i; j<*i+C; i++){
            if(*j>=0){
                cout<<" "<<*j<<" ";
            }else{
                cout<<*j<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

int sumaSubmatriz(int (*inicio)[C], int *pos1, int *pos2){
    int (*f1)[C]=inicio, (*f2)[C]=inicio;
    int *c1=*inicio, *c2=*inicio;

    //hallar la posicion exacta en la matriz de las posiciones 
    for(int (*i)[C]=inicio; i<inicio+F; i++){
        for(int *j=*i; j<*i+C; j++){
            if(j==pos1){
                f1=i;
                c1=j; //se hallo la posicion exacta de pos1 (i1, j1)
            }
            if(j==pos2){
                f2=i;
                c2=j; //se hallo la posicion exacta de pos2 (i2, j2)
            }
        }
    }

    //calcular la suma de elementos de la submatriz delimitada
    int suma=0;
    for(int (*i)[C]=f1; i<=f2; i++){  //desde la fila f1 hasta la fila f2
        for(int *j=*i+(c1-*f1); j<=*i+(c2-*f2); j++){  //*i+(c1-*f1): Pos del elemento en la fila i, c1-*f1= #columna
            suma+= *j;
        }
    }

    return suma;    //retorna la suma de los elementos de la submatriz
}

void sumaSubmatrizMaxima(int (*inicio)[C]){
    int sumaSubMmaxima=**inicio;
    int (*MAX_f1)[C]=inicio, (*MAX_f2)[C]=inicio;   //inicializamos
    int *MAX_c1=*inicio, *MAX_c2=*inicio;

    for(int (*f1)[C]=inicio; f1<inicio+F; f1++){
        for(int *c1=*f1; c1<*f1+C; c1++){
            for(int (*f2)[C]=f1; f2<inicio+F; f2++){
                for(int *c2=*f2; c2<*f2+C; c2++){
                    int sumaSubM=sumaSubmatriz(inicio,c1,c2);
                    if(sumaSubM>sumaSubMmaxima){    //si la suma actual es mayor que la maxima
                        sumaSubMmaxima=sumaSubM;    //actualizamos la suma maxima con la actual
                        MAX_f1=f1; MAX_c1=c1;       //y actualizamos los punteros de los limitantes
                        MAX_f2=f2; MAX_c2=c2;       //de la subMatriz
                    }
                }
            }
        }
    }
}
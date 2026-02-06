#include<iostream>
#include<cstring>
using namespace std;

void registrarCorredores(char **nombres, int *tiempo, int n);

int main(){
    int n;
    cout<<"\nCuanto corredores desea registrar? (1-30): ";
    cin>>n;
    if(n<1 && n>30){
        cout<<"\nEl numero esta fuera del rango permitido.\n";
        return 0;
    }

    char **nombres=new char*[n];
    int *tiempo=new int[n];
    
    registrarCorredores(nombres,tiempo,n);

    return 0;
}

void registrarCorredores(char **nombres, int *tiempo, int n){
    for(int i=0; i<n; i++){
        char *temp;

        cout<<"Nombre del corredor "<<i<<": ";
        cin.getline(temp,20);   //obtenemos el nombre

        int tam=strlen(temp);   //obtenemos el tamaño del nombre
        *(nombres+i)=new char[tam+1];   //creamos espacio de memoria

        for(char *p=temp; p<temp+tam; p++){ //copiamos el nombre del corredor en nombres
            *(*(nombres+i)+(p-temp))=*p;
        }
        *(*(nombres+i)+tam)='\0';

        int t;
        cout<<"Tiempo (en segundos): ";
        cin>>t; //obtenemos el tiempo del corredor
        *(tiempo+i)=t;

        cout<<endl;
    }
}

void ordenarRanking(char **nombres, int *tiempo, int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(*(tiempo+j)>*(tiempo+(j+1))){

            }
        }
    }
}
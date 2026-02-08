#include<iostream>
#include<cstring>
using namespace std;

char *leerFrase();
char *normalizarFrase(char *frase);
int contadorPalabras(char *frase);
char **arregloPalabras(char *frase, int n);
void mostrarPalabras(char **palabras, int n);
int tamañoPalabra(char *p);
void imprimir(char *p);
void liberarMemoriaSimple(char *&arr);
void liberarMemoriaDoble(char **&arr, int n);

int main(){

    char *frase=leerFrase();
    char *normalizada=normalizarFrase(frase);
    int numPalabras=contadorPalabras(frase);
    char **palabras=arregloPalabras(normalizada,numPalabras);

    cout<<"\nFrase Normalizada: ";
    imprimir(normalizada);
    cout<<"La frase tiene "<<numPalabras<<" palabras\n";
    cout<<"\nLas palabras de la frase son:\n\n";
    mostrarPalabras(palabras,numPalabras);

    liberarMemoriaSimple(frase);
    liberarMemoriaSimple(normalizada);
    liberarMemoriaDoble(palabras,numPalabras);
    
    return 0;
}

char *leerFrase(){
    char temp[100];
    cout<<"\nIngrese una frase: ";
    cin.getline(temp,100);

    int len=strlen(temp);   //tamaño de la frase sin '\0'
    char *frase=new char[len+1];    //tamaño de la frase incluido el '\0'
    for(char *p=temp; p<=temp+len; p++){
        *(frase+(p-temp))=*p;   //copiamos toda la frase, incluido el '\0'
    }
    
    return frase;   //retornamos la direccion del bloque de memoria con la frase
}

char *normalizarFrase(char *frase){
    char temp[100]; //memoria adicional
    int lenTemp=0;

    for(char *p=frase; *p!='\0'; p++){ //recorremos toda la frase
        if(*p==' ' && (p==frase || *(p-1)==' ')) continue;  //salta los espacios hasta antes de la palabra final
        if(*p>='A' && *p<='Z') *(temp+lenTemp)=*p+32;   //convierte a minuscula si son mayusculas
        else *(temp+lenTemp)=*p;
        lenTemp++;
    }
    //si hubiera espacio despues de la palabra final, registrara una como la final
    if(*(temp+lenTemp-1)==' '){
        *(temp+lenTemp-1)='\0';     //pone el caracter nulo en donde habia espacio
        --lenTemp;
    } else *(temp+lenTemp)='\0';    //pone el caracter nulo normalmente

    char *normalizada=new char[lenTemp+1];

    for(char *p=temp; p<=temp+lenTemp; p++){
        *(normalizada+(p-temp))=*p;     //se copia con el caracter nulo
    }

    return normalizada;
}

int contadorPalabras(char *frase){
    int numPalabras=0;
    for(char *p=frase; *p!='\0'; p++){
        if(*p!=' ' && (p==frase || *(p-1)==' ')){
            numPalabras++;
        }
    }
    return numPalabras;
}

char **arregloPalabras(char *frase, int n){
    char **palabras=new char*[n];   //arreglo de punteros de cada palabra
    int posPalabra=0;

    for(char *p=frase; *p!='\0'; p++){  //recorre toda la frase
        if(*p!=' ' && (p==frase || *(p-1)==' ')){   //encuentra el inicio de una palabra
            int n=tamañoPalabra(p);
            *(palabras+posPalabra)=new char[n+1];     //espacio de memoria para la palabra y caracter nulo

            for(char *i=p; i<p+n; i++){
                *(*(palabras+posPalabra)+(i-p))=*i;      //se copia la palabra
            }

            *(*(palabras+posPalabra)+n)='\0'; //pone el caracter nulo
            posPalabra++;   //avanza para almacenar el siguiente puntero
        }
    }
    
    return palabras;
}

void mostrarPalabras(char **palabras, int n){
    for(char **p=palabras; p<palabras+n; p++){
        cout<<*p<<"\t\t; Longitud: "<<strlen(*p);
        cout<<endl;
    }
    cout<<endl;
}

int tamañoPalabra(char *p){
    int tam=0;
    for(; *p!=' ' && *p!='\0'; p++) tam++;
    return tam;
}

void imprimir(char *p){
    for(; *p!='\0'; p++){
        cout<<*p;
    }
    cout<<endl;
}

void liberarMemoriaSimple(char *&arr){
    delete[] arr;
    arr=nullptr;
}

void liberarMemoriaDoble(char **&arr, int n){
    for(int i=0; i<n; i++){
        delete[] *(arr+i);
        *(arr+i)=nullptr;
    }
    delete[] arr;
    arr=nullptr;
}
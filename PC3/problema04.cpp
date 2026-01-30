#include<iostream>
using namespace std;

void intercambiar(char *&a, char *&b);
int guardaDirecciones(char *texto, char **indice);
int comparar(const char *a, const char *b);
int ordenarIndice(char **indice, int n);
void imprimir(char *texto, char **indice, int n);

int main(){
    char texto[]="los punteros no se copian se referencian y se ordenan";   //texto en minuscula
    char *indice[50];   //espacio suficiente

    int n=guardaDirecciones(texto,indice);
    ordenarIndice(indice,n);
    imprimir(texto,indice,n);

    return 0;
}

int guardaDirecciones(char *texto, char **indice){
    int contadorPalabras=0;
    for(char *p=texto; *p!='\0'; p++){
        if(*p!=' ' && (p==texto || *(p-1)==' ')){   //nos lleva al incio de cada palabra
            *indice=p;
            indice++;
            contadorPalabras++;
        }
    }
    return contadorPalabras;
}

int comparar(const char *a, const char *b){     //no adaptado para mayusculas (considera mayuscules menor que minusculas)
    for(; *a!='\0' && *a!=' ' && *b!='\0' && *b!=' '; a++, b++){
        if(*a!=*b){
            return *a-*b;   //comparacion antes del primer caracter nulo o espacio
        }
    }
    if((*a=='\0' && (*b==' ' || *b=='\0')) || (*a==' ' && (*b==' ' || *b=='\0'))){ //terminan al mismo tiempo de distintas formas o iguales
        return 0;   //las palabras son iguales, del mismo tamaño
    }
    return *a-*b;   //comparacion con al menos uno de ello con caracter nulo o espacio
}

int ordenarIndice(char **indice, int n){
    for(char **i=indice; i<indice+n-1; i++){
        for(char **j=indice; j<indice+n-(i-indice)-1; j++){
            if(comparar(*j,*(j+1))>0){
                intercambiar(*j, *(j+1));
            }
        }
    }
    return 1;
}

void intercambiar(char *&a, char *&b){
    char *temp=a;
    a=b;
    b=temp;
}

void imprimir(char *texto, char **indice, int n){
    for(char **p=indice; p<indice+n; p++){
        char *pos=*p;
        for(char *i=*p; *i!='\0' && *i!=' '; i++){
            cout<<*i;
        }
        cout<<"\t\t\t(Posicion "<<pos-texto<<")"<<endl;
    }
}
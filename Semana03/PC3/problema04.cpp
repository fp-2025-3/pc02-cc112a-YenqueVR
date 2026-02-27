#include<iostream>
using namespace std;

void intercambiar(char *&a, char *&b);
int guardaDirecciones(char *texto, char **indice);
int comparar(const char *a, const char *b);
void ordenarIndice(char **indice, int n);
void imprimir(char *texto, char **indice, int n);

int main(){
    char texto[]="los punteros no se copian se referencian y se ordenan";   //texto en minuscula
    char *indice[50];   //espacio suficiente

    int n=guardaDirecciones(texto,indice);
    ordenarIndice(indice,n);
    cout<<"\nTexto: "<<texto<<endl;
    imprimir(texto,indice,n);

    return 0;
}

int guardaDirecciones(char *texto, char **indice){
    int contadorPalabras=0;
    for(char *p=texto; *p!='\0'; p++){
        if(*p!=' ' && (p==texto || *(p-1)==' ')){   //nos lleva al incio de cada palabra
            *indice=p;  //se copia la direccion del inicio de la palabra
            indice++;   //se avanza para registrar el proximo puntero
            contadorPalabras++; //aumneta el numero de palabras del texto
        }
    }
    return contadorPalabras;
}

int comparar(const char *a, const char *b){     //adaptado para comparar mayusculas y minusculas
    char a1, b1;
    for(; *a!='\0' && *a!=' ' && *b!='\0' && *b!=' '; a++, b++){
        a1=*a; b1=*b;
        if(a1>='A' && a1<='Z')  a1+=('a'-'A');  //convierte a minusculas
        if(b1>='A' && b1<='Z')  b1+=('a'-'A');  //convierte a minusculas
        if(a1!=b1){
            return a1-b1;   //comparacion antes del primer caracter nulo o espacio
        }
    }
    if(*a==*b || (*a=='\0' && *b==' ') || (*a==' ' && *b=='\0')){ //terminan al mismo tiempo de distintas formas o iguales
        return 0;   //las palabras son iguales, del mismo tamaño
    }
    return *a-*b;   //comparacion con al menos uno de ello con caracter nulo o espacio
}

void ordenarIndice(char **indice, int n){
    for(char **i=indice; i<indice+n-1; i++){
        for(char **j=indice; j<indice+n-(i-indice)-1; j++){
            if(comparar(*j,*(j+1))>0){
                intercambiar(*j, *(j+1));
            }
        }
    }
}

void intercambiar(char *&a, char *&b){
    char *temp=a;
    a=b;
    b=temp;
}

void imprimir(char *texto,char **indice, int n){
    cout<<endl;
    for(char **p=indice; p<indice+n; p++){
        char *pos=*p;
        for(char *i=*p; *i!='\0' && *i!=' '; i++){
            cout<<*i;
        }
        cout<<"\t\t\t(Posicion "<<pos-texto<<")"<<endl;
    }
}
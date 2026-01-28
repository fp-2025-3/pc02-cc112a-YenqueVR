#include<iostream>
using namespace std;

int separar_palabras(char* texto, char* palabras[]);
int longitud_palabra(const char* p);
void clasificar(char* palabras[], int n, char* cortas[], int& nc, char* largas[], int& nl);
int comparar_palabras(const char* a, const char* b);
void ordenar(char* v[], int n);
void imprimir_grupo(const char* titulo, char* v[], int n);

int main(){
    char texto[300]="Programar en C++ requiere logica C++ exige disciplina";
    char* palabras[60];
    char* cortas[60];
    char* largas[60];



    return 0;
}

int separar_palabras(char* texto, char* palabras[]){
    char *p=texto;  //puntero al primer caracter del texto
    int contPalabras=0;
    for(; *p='\0'; p++){    //hasta terminar el texto
        if(*p!=' ' && (p==texto || *(p-1)!=' ')){
            *palabras=p;    //almacenamos el puntero al primer caracter de la palabra
            palabras++; //avanzamos para almacenar el siguiente puntero
            contPalabras++; //aumentamos el numero de palabras que hay en el texto
        }
    }
    return contPalabras;
}

int longitud_palabra(const char* p){
    const char *inicio=p; //puntero al primer caracter
    for(; *p!='\0' && *p!=' '; p++);   //p avanza hasta el caracter nulo o el primer espacio que encuentre
    return p-inicio;  //la diferencia entre punteros es la longitud
}

int comparar_palabras(const char* a, const char* b){
    for(; *a!='\0' && *b!='\0' && *a!=' ' && *b!=' '; a++, b++){
        if(*a!=*b){
            return *a-*b;   //diferencia antes del caracter nulo o primer espacio
        }
    }
    if(*a!=*b){
        return *a-*b;   //diferencia con al menos uno, o caracter nulo o espacio
    }
    return 0;   //ambos llegaron al mismo tiempo al caracter nulo o al primer espacio, son iguales
}

void clasificar(char* palabras[], int n, char* cortas[], int& nc, char* largas[], int& nl){
    nc=0;
    nl=0;
    for(char **i=palabras; i<palabras+n; i++){
        if(longitud_palabra(*i)>3){
            *(largas+nl)=*i;
            nl++;
        }else{
            *(cortas+nc)=*i;
            nc++;
        }
    }
}

void ordenar(char* v[], int n){
    for(char **i=v; i<v+n-1; i++){
        for(char **j=v; j<v+n-(i-v)-1; j++){
            if(comparar_palabras(*j,*(j+1))>0){
                swap(*j,*(j+1));
            }
        }
    }
}

void imprimir_grupo(const char* titulo, char* v[], int n){
    cout<<"\nPalabras "<<titulo<<endl;
}
#include<iostream>
using namespace std;

int separar_palabras(char* frase, char* palabras[]);
int comparar(const char* a, const char* b);
void ordenar(char* palabras[], int n);
void imprimir(char* palabras[], int n);
void intercambiar(char *&a, char *&b);

int main(){
    char frase[200] = "aprender punteros exige mucha logica y practica";      // arreglo base de caracteres
    char* palabras[50];  // arreglo de punteros a palabras

    int n=separar_palabras(frase,palabras);
    ordenar(palabras,n);
    imprimir(palabras,n);

    return 0;
}

int separar_palabras(char* frase, char* palabras[]){
    char *p=frase;  //puntero al primer caracter del texto
    int contPalabras=0;
    for(; *p!='\0'; p++){    //hasta terminar el texto
        if(*p!=' ' && (p==frase || *(p-1)==' ')){
            *(palabras+contPalabras)=p;    //almacenamos el puntero al primer caracter de la palabra
            contPalabras++; //aumentamos el numero de palabras que hay en el texto
        }
    }
    return contPalabras;
}

int comparar(const char* a, const char* b){
    char a1=*a,b1=*b;   //almacena los caracteres
    for(; *a!='\0' && *b!='\0' && *a!=' ' && *b!=' '; a++, b++){
        a1=*a;
        b1=*b;
        if(a1>='A' && a1<='Z') a1+=('a'-'A');   //para que lo haga alfabeticamente sin importar mayusculas
        if(b1>='A' && b1<='Z') b1+=('a'-'A');
        if(a1!=b1){
            return a1-b1;   //diferencia antes del caracter nulo o primer espacio
        }
    }
    a1=*a;
    b1=*b;
    if(a1>='A' && a1<='Z') a1+=('a'-'A');   //para que lo haga alfabeticamente sin importar mayusculas
    if(b1>='A' && b1<='Z') b1+=('a'-'A');
    if(a1!=b1){
        return a1-b1;   //diferencia con al menos uno, o caracter nulo o espacio
    }
    return 0;   //ambos llegaron al mismo tiempo al caracter nulo o al primer espacio, son iguales
}

void ordenar(char* palabras[], int n){
    for(char **i=palabras; i<palabras+n-1; i++){
        for(char **j=palabras; j<palabras+n-(i-palabras)-1; j++){
            if(comparar(*j,*(j+1))>0){
                intercambiar(*j,*(j+1));
            }
        }
    }
}

void intercambiar(char *&a, char *&b){
    char *temp=a;
    a=b;
    b=temp;
}

void imprimir(char* palabras[], int n){
    cout<<endl;
    for(char **i=palabras; i<palabras+n; i++){
        for(char *j=*i; *j!='\0' && *j!=' '; j++){
            cout<<*j;
        }
        cout<<endl;
    }
}
#include<iostream>
using namespace std;

size_t my_strlen(const char *str);
char* my_strcpy(char *destino, const char *origen);
char* my_strcat(char *destino, const char *origen);


int main(){
    char cadena[]="acido dexosiribonucleico";
    int tamCad=my_strlen(cadena);
    
    cout<<"\nEl tamaño de la cadena '"<<cadena<<"' es:";
    cout<<"\n--> n = "<<tamCad<<endl;
    
    char destino[30];
    my_strcpy(destino,cadena);
    cout<<"\nmy_strcpy(destino,cadena);";
    cout<<"\ndestino: "<<destino<<endl;

    char cadConcatenar[50];
    char cad1[]="NO lo vi venir";
    my_strcpy(cadConcatenar,cadena);
    cout<<"\ncadConcatenar[50]: "<<cadConcatenar;
    cout<<"\ncad1: "<<cad1;
    cout<<"\nmy_strcat(cadConcatenar,cad1)";
    my_strcat(cadConcatenar,cad1);
    cout<<"\ncadConcatenar[50]: "<<cadConcatenar<<endl;

    return 0;
}

size_t my_strlen(const char *str){
    const char *p=str;  //lo hacemos con puro punteros
    for(; *str!='\0'; str++);
    return str-p;
}

char* my_strcpy(char *destino, const char *origen){
    char *ptr=destino;
    for(; *origen!='\0'; origen++, destino++){
        *destino=*origen;
    }
    *destino='\0';  //terminamos la cadena con el caracter nulo
    return ptr;
}

char* my_strcat(char *destino, const char *origen){
    char *ptr=destino;
    for(; *destino!='\0'; destino++);   //llegamos al caracter nulo
    for(; *origen!='\0'; origen++, destino++){
        *destino=*origen;   //copia caracter a caracter
    }
    *destino='\0';  //finalizamos con caracter nulo
    return ptr;
}
#include<iostream>
using namespace std;

char* my_strcpy(char *destino, const char *origen);
int my_strcmp(const char *cad1, const char *cad2);
void ordenarNombres(char (*nombres)[20], int N);

int main(){
    char nombres[][20]={"Lesly","Americo","Xingbeck","William","Julio","Darwin","Kevin"};
    ordenarNombres(nombres,7);
    for(char (*i)[20]=nombres; i<nombres+7; i++){
        cout<<"\n"<<*nombres;
    }
    return 0;
}

void ordenarNombres(char (*nombres)[20], int N){
    for(char (*i)[20]=nombres; i<nombres+N-1; i++){
        for(char (*j)[20]=i+1; j<nombres; j++){
            if(my_strcmp(*i,*j)>0){
                char temp[20];
                my_strcpy(temp,*i);
                my_strcpy(*i,*j);
                my_strcpy(*j,temp);
            }
        }
    }
}

char* my_strcpy(char *destino, const char *origen){
    char *ptr=destino;
    for(; *origen!='\0'; origen++, destino++){
        *destino=*origen;
    }
    *destino='\0';  //terminamos la cadena con el caracter nulo
    return ptr;
}

int my_strcmp(const char *cad1, const char *cad2){
    for(; *cad1!='\0' && *cad2!='\0'; cad1++, cad2++){
        if(*cad1!=*cad2){  
            return *cad1-*cad2; //diferencia antes del primer caracter nulo
        }
    }
    if(*cad1!=*cad2){   //si son diferentes, ambos no son caracteres nulos
        return *cad1-*cad2; //diferencia en el primer caracter nulo
    }
    return 0;   //retorna 0 si al final ambos son caracteres nulos despues de revisar todo
}
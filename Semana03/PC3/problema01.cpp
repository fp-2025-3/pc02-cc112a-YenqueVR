#include<iostream>
using namespace std;

int numerizador(const char *p);
bool existeNumerosQueSumenK(const char *texto, const int k);

int main(){
    char texto[]="1, 2, 4, 7, 11";
    int k=15;

    cout<<"\nTexto: '"<<texto<<"'";
    if(existeNumerosQueSumenK(texto,k)){
        cout<<"\nSI existen 2 numeros con suma "<<k;
    }else{
        cout<<"\nNO existen 2 numeros con suma "<<k;
    }
    cout<<endl;

    return 0;
}

int numerizador(const char *num){
    int suma=0;
    for(; *num!='\0' && *num!=' ' && *num!=','; num++){ //recorre hasta llegar al caracter nulo, espacio o coma
        suma=suma*10 + (*num-'0');    //convertimos en numeros
    }
    return suma;    //devolvemos el numero entero
}

bool existeNumerosQueSumenK(const char *texto, const int k){

    int arregloEnteros[30]; //espacio suficiente para almacenar los numeros del texto
    int nEnteros=0;     //cantidad de numeros enteros en el texto

    for(const char *p=texto; *p!='\0'; p++){
        if(*p>='0' && *p<='9' && (p==texto || *(p-1)==' ' || *(p-1)==',')){ //nos ubica al inicio del numero
            *(arregloEnteros+nEnteros)=numerizador(p);  //extrae el numero del texto hacia el arreglo
            nEnteros++; //aumenta la cantidad de numeros del texto
        }
    }

    int *inicio=arregloEnteros;     //primer numero del arreglo de enteros
    int *fin=arregloEnteros+nEnteros-1;     //ultimo numero del arreglo de enteros

    while(inicio<fin){  //su ordenamiento de forma ascendente facilita 
        if(*inicio+*fin==k) return true;    //encontro los numeros que suman k
        else if(*inicio+*fin>k) fin--;  //fin se mueve a la izquierda para reducir la suma
        else if(*inicio+*fin<k) inicio++;   //inicio se mueve a la derecha para aumentar la suma
    }
    return false;   //no encontro numeros que sumen k
}
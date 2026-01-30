#include<iostream>
using namespace std;

int contarVocales(char *texto);
void imprimirTexto(char *texto);

int main(){
    char texto[]="    Este es    un ejemplo en C++   END";
    int numVocales=contarVocales(texto);

    cout<<"Texto: ";
    imprimirTexto(texto);
    cout<<"Numero de palabras que comienzan con vocal: "<<numVocales<<endl;
    return 0;
}

int contarVocales(char *texto){
    int contadorVocales=0;
    for(char *p=texto; *p!='\0'; p++){  //recorremos el arreglo hasta el caracter nulo
        if(*p!=' ' && (p==texto || *(p-1)==' ')){   //nos ubicamos a inicio de una palabra
            if(*p=='a' || *p=='e' || *p=='i' || *p=='o' || *p=='u') ++contadorVocales;  //vocales minusculas
            if(*p=='A' || *p=='E' || *p=='I' || *p=='O' || *p=='U') ++contadorVocales;  //vocales mayusculas
        }
    }
    return contadorVocales; //devolvemos el numero de palabras que comienzan con vocal
}

void imprimirTexto(char *texto){
    for(; *texto!='\0'; texto++){
        cout<<*texto;
    }
    cout<<endl;
}
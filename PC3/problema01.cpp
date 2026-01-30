#include<iostream>
#include<cstring>
using namespace std;

int numerizador(char *p);
bool existeNumerosQueSumenK(char *texto, int k);

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

int numerizador(char *num){
    int suma=0;
    for(char *p=num; *p!='\0' && *p!=' ' && *p!=','; p++){ //recorre hasta llegar al caracter nulo, espacio o coma
        suma=suma*10 + (*p-'0');    //convertimos en numeros
    }
    return suma;    //devolvemos el numero entero
}

bool existeNumerosQueSumenK(char *texto, int k){
    char *inicio=texto;
    char *fin=texto+strlen(texto);
    int numI, numF;
    bool encontradoNumI=false, encontradoNumF=false;

    while(inicio<fin){
        if(*inicio!=' ' && *inicio!=',' && (inicio==texto || *(inicio-1)==' ')){    //nos ubica al inicio del numero
            numI=numerizador(inicio);
            encontradoNumI=true;
        }else ++inicio;

        if(*fin!=' ' && *fin!=',' && (fin==texto || *(fin-1)==' ')){    //nos ubica al inicio del numero
            numF=numerizador(fin);
            encontradoNumF=true;
        } else --fin;

        if(encontradoNumI && encontradoNumF){
            if(numI+numF>k){    //si la suma es mayor que k
                --fin;          //el puntero de fin pasa al numero de izquierda
                encontradoNumF=false;
                encontradoNumI=false;
            }else if(numI+numF<k){    //si la suma es menor que k
                ++inicio;       //el puntero inicio pasa al numero de la derecha
                encontradoNumF=false;
                encontradoNumI=false;
            }else return true;    //retorna verdadero si la suma es igual a k
        }
    }
    return false;   //no encontro numeros que sumen k
}
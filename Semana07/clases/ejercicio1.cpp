#include<iostream>
#include<fstream>
using namespace std;

void mezclaArchivos(const char *nombre1, const char *nombre2);

int main(){
    char arch1[]="input/archivo1.txt", arch2[]="input/archivo2.txt";
    mezclaArchivos(arch1,arch2);

    return 0;
}

void mezclaArchivos(const char *nombre1, const char *nombre2){
    ifstream archivo1(nombre1);
    ifstream archivo2(nombre2);
    ofstream mezcla("output/nombreM");

    if(!archivo1 || !archivo2 || !mezcla){
        cerr<<"\nNo se abrieron correctamente los archivos.\n";
        return;
    }

    int num1,num2;
    archivo1>>num1; archivo2>>num2;

    while(num1!=-1 || num2!=-1){
        if((num1<=num2 && num1!=-1) || num2==-1){ //cuando num1 es menor a num2 pero num1 no es -1, o num2 es igual a -1
            mezcla<<num1<<endl;
            archivo1>>num1;
        }else if(num2!=-1){  //cuando num2 es menor a num1 pero num2 no es -1, o num1 es igual a -1
            mezcla<<num2<<endl;
            archivo2>>num2;
        }
    }
}
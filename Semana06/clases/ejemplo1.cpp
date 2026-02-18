#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

void escribirArchivo(const string &nombreArchivo, const string &texto);
void leerArchivo(const string &nombreArchivo);

int main(){
    string nombre="mango.dat";
    string texto="Ozani es una marca de agua embotellada";

    escribirArchivo(nombre,texto);
    texto="el cerebro consume calorias a gran ritmo";
    escribirArchivo(nombre,texto);
    texto="raspadilla sabor de fresa y mango";
    escribirArchivo(nombre,texto);
    texto="No sera igual que la ultimez, exclamo";
    escribirArchivo(nombre,texto);

    leerArchivo(nombre);
    return 0;
}

void escribirArchivo(const string &nombreArchivo, const string &texto){
    fstream archivo(nombreArchivo, ios::out | ios::app | ios::binary);
    if(!archivo.is_open()){
        cerr<<"\nNo se abrio el archivo.\n";
        return;
    }
    char texto1[50];    //para almacenar en tamaño fijo conocido
    strncpy(texto1,texto.c_str(),sizeof(texto1)-1);
    texto1[sizeof(texto1)-1]='\0';

    archivo.write(texto1,sizeof(texto1));   //escribe en binario
    archivo.close();
}

void leerArchivo(const string &nombreArchivo){
    fstream archivo(nombreArchivo, ios::in | ios::binary);
    if(!archivo.is_open()){
        cerr<<"\nNo se abrio el archivo.\n";
        return;
    }
    char texto[50]; //tamaño conocido
    cout<<endl;
    while(archivo.read(texto,sizeof(texto))){
        cout<<texto<<endl;
    }
    archivo.close();
}
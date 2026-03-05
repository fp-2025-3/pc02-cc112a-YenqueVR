#include "Vehiculo.h"
#include<iostream>
using namespace std;

int main(){
    Vehiculo *v[4]={
                    new Motocicleta,
                    new Automovil,
                    new Camion,
                    new Camion
    };

    ifstream archivo("mensaje.dat", ios::binary);
    if(!archivo){
        cerr<<"\nNo ingresa.\n";
        return 0;
    }
    archivo.seekg(0,ios::beg);

    //no funciona
    for(int i=0; i<4; i++){
        v[i]->cargar(archivo);
    }

    for(int i=0; i<4; i++){
        v[i]->mostrarInfo();
    }

    for(int i=0; i<4; i++){
        delete v[i];
        v[i]=nullptr;
    }

    return 0;
}
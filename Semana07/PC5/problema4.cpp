#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct Venta {
    int idVenta;
    int idVendedor;
    int Producto;
    int cantidad;
    double precioUnitario;
};

int numeroEmpleadosArchivo(const char *nombre);

int main(){
    char nombre[]="input/ventas.dat";
    generarReporte(nombre,numeroEmpleadosArchivo(nombre));
    return 0;
}

void generarReporte(const char *nombre, int numEmpleados){
    if(numEmpleados==-1) return;

    ofstream ventas(nombre, ios::binary);
    if(!ventas){
        cerr<<"\nNo se abrio correctamente input/ventas.dat.\n";
        return;
    }

    
}

int numeroEmpleadosArchivo(const char *nombre){
    ifstream ventas(nombre, ios::binary);
    if(!ventas){
        cerr<<"\nNo se abrio correctamente input/ventas.dat.\n";
        return -1;
    }

    ventas.seekg(0,ios::end);   //posicionamos el puntero de lectura al final del archivo

    //leemos la posicion del final del archivo y lo dividimos con el tamaño de la estructura, para el numero de empleados
    return (ventas.tellg())/sizeof(Venta);
}

double calcularMontoTotalVendido(const Venta* const v, int n){
    double montoTotal=0;

    for(int i=0; i<n; i++){
        montoTotal += v[i].cantidad * v[i].precioUnitario;
    }

    return montoTotal;
}


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

int numeroRegistrosArchivo(const char *nombre);

int main(){
    char nombre[]="input/ventas.dat";
    generarReporte(nombre,numeroRegistrosArchivo(nombre));
    return 0;
}

void generarReporte(const char *nombre, int numEmpleados){
    if(numEmpleados==-1) return;

    ofstream reporte(nombre, ios::binary);
    if(!reporte){
        cerr<<"\nNo se abrio correctamente input/ventas.dat.\n";
        return;
    }

    reporte<<"=== REPORTE GENERAL DE VENTAS ===\n";
    reporte<<"\nTotal de registros: ";
}

int numeroRegistrosArchivo(const char *nombre){
    ifstream ventas(nombre, ios::binary);
    if(!ventas){
        cerr<<"\nNo se abrio correctamente input/ventas.dat.\n";
        return -1;
    }

    ventas.seekg(0,ios::end);   //posicionamos el puntero de lectura al final del archivo

    //leemos la posicion del final del archivo y lo dividimos con el tamaño de la estructura, para el numero de registros
    return (ventas.tellg())/sizeof(Venta);
}

double calcularMontoTotalVendido(const Venta* const v, int n){
    double montoTotal=0;

    for(int i=0; i<n; i++){
        montoTotal += v[i].cantidad * v[i].precioUnitario;  //monto total de cada registro
    }

    return montoTotal;
}


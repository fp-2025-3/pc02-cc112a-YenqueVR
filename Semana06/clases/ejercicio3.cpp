#include<iostream>
#include<fstream>
using namespace std;

struct Producto {
    int id;             // Identificador único
    char nombre[30];    // Nombre del producto
    double precio;      // Precio unitario
    int stock;          // Cantidad disponible
    bool activo;        // true = activo, false = eliminado lógicamente
};

void registrarProducto(const char* nombreArchivo);
void mostrarProductos(const char* nombreArchivo);
int buscarProductoPorID(const char* nombreArchivo, int idBuscado);
void modificarPrecio(const char* nombreArchivo, int id, double nuevoPrecio);
void eliminarProducto(const char* nombreArchivo, int id);
double calcularValorInventario(const char* nombreArchivo);

int main(){

    return 0;
}

void registrarProducto(const char* nombreArchivo){

}

void mostrarProductos(const char* nombreArchivo){

}

int buscarProductoPorID(const char* nombreArchivo, int idBuscado){

}

void modificarPrecio(const char* nombreArchivo, int id, double nuevoPrecio){

}

void eliminarProducto(const char* nombreArchivo, int id){

}

double calcularValorInventario(const char* nombreArchivo){

}

int menu(int &opc){
    cout<<"\n1. Registrar producto";
    cout<<"\n2. Mostrar productos";
    cout<<"\n3. Buscar producto";
    cout<<"\n4. Modificar precio";
    cout<<"\n5. Eliminar producto";
    cout<<"\n6. Calcular valor total";
    cout<<"\n7. Salir";
    cout<<"\nOpcion --> ";
    cin>>opc;
}
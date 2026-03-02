#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct Venta {
    int idVenta;
    int idVendedor;
    int idProducto;
    int cantidad;
    double precioUnitario;
};

int numeroRegistrosArchivo(const char *nombre);
Venta* extraerRegistrosArchivoBinario(const char *nombre, int n);
void calcularMontoTotalVendido(ofstream &reporte, const Venta *v, int n);
void vendedorMayorRecaudacion(ofstream &reporte, const Venta *v, int n);
void productoMayorVendido(ofstream &reporte, const Venta *v, int n);
void ventasSospechosas(ofstream &reporte, const Venta *v, int n);
void liberarVentas(Venta *&v);
void generarReporte(const char *nombre, int numEmpleados);

int main(){
    char nombre[]="input/ventas.dat";
    generarReporte(nombre,numeroRegistrosArchivo(nombre));

    return 0;
}

void generarReporte(const char *nombre, int numRegistros){
    if(numRegistros==-1) return;

    ofstream reporte("output/reporte.txt");
    if(!reporte){
        cerr<<"\nNo se abrio correctamente output/reporte.txt.\n";
        return;
    }

    Venta *ventas=extraerRegistrosArchivoBinario(nombre,numRegistros);
    if(ventas==nullptr) return;

    cout<<"\nGenerando reporte...\n";

    reporte<<"=== REPORTE GENERAL DE VENTAS ===\n";
    reporte<<"\nTotal de registros: "<<numRegistros<<endl;

    reporte<<fixed<<setprecision(1);
    calcularMontoTotalVendido(reporte,ventas,numRegistros);
    vendedorMayorRecaudacion(reporte,ventas,numRegistros);
    productoMayorVendido(reporte,ventas,numRegistros);
    ventasSospechosas(reporte,ventas,numRegistros);

    reporte.close();
    liberarVentas(ventas);

    cout<<"\nReporte general de ventas creado exitosamente!\n";
}

int numeroRegistrosArchivo(const char *nombre){
    ifstream ventas(nombre, ios::binary);
    if(!ventas){
        cerr<<"\nNo se abrio correctamente input/ventas.dat.\n";
        return -1;
    }

    ventas.seekg(0,ios::end);   //posicionamos el puntero de lectura al final del archivo

    //leemos la posicion del final del archivo y lo dividimos con el tamaño de la estructura, para el numero de registros
    int numRegistros=(ventas.tellg())/sizeof(Venta);

    ventas.close();
    return numRegistros;
}

Venta* extraerRegistrosArchivoBinario(const char *nombre, int n){
    ifstream ventas(nombre, ios::binary);
    if(!ventas){
        cerr<<"\nNo se abrio correctamente input/ventas.dat.\n";
        return nullptr;
    }

    Venta *v = new Venta[n];   //espacio de memoria para almacenar los registros

    cout<<"\nExtrayendo datos del archivo binario...\n";
    ventas.read((char*)v, sizeof(Venta)*n);   //leemos y almacenamos los registros en el arreglo

    ventas.close();
    return v;
}

void calcularMontoTotalVendido(ofstream &reporte, const Venta *v, int n){
    double montoTotal=0;

    //al parecer, los precios unitarios no se mantienen para el mismo producto, cambian en cada registro en el mismo producto
    for(int i=0; i<n; i++){
        montoTotal += v[i].cantidad * v[i].precioUnitario;  //monto total de cada registro
    }

    //escritura en el archivo
    reporte<<"\nMONTO TOTAL VENDIDO:";
    reporte<<"\nS/. "<<montoTotal<<endl;
}

void vendedorMayorRecaudacion(ofstream &reporte, const Venta *v, int n){
    int numVendedores=-1;    //los ID comienzan a partir de 1 hacia adelante
    for(int i=0; i<n; i++){
        if(numVendedores<v[i].idVendedor) numVendedores=v[i].idVendedor;    //el mayor id de un vendedor = numero vendedores
    }

    //espacio de memoria para la recaudcion de cada vendedor iniciado en 0
    double *recaudacionVendedor = new double[numVendedores]{0};

    for(int i=0; i<n; i++){ //completamos la recaudacion de cada vendedor
        recaudacionVendedor[v[i].idVendedor - 1] += (v[i].precioUnitario * v[i].cantidad);
    }

    int idMejorRecaudador=-1;
    double montoMejorRecaudador=-1;

    for(int i=0; i<numVendedores; i++){
        if(montoMejorRecaudador<recaudacionVendedor[i]){
            montoMejorRecaudador=recaudacionVendedor[i];    //actualizar el monto del mejor recaudador
            idMejorRecaudador=i+1;  //actualizar id del mejor recaudador
        }
    }

    delete[] recaudacionVendedor;   //liberar memoria
    recaudacionVendedor=nullptr;

    //escritura en el archivo
    reporte<<"\n-------------------------------------";
    reporte<<"\nVENDEDOR CON MAYOR RECAUDACION:";
    reporte<<"\nID vendedor: "<<idMejorRecaudador;
    reporte<<"\nTotal vendido: S/. "<<montoMejorRecaudador<<endl;
}

void productoMayorVendido(ofstream &reporte, const Venta *v, int n){
    int numProductos=-1;    //los ID comienzan a partir de 1 hacia adelante
    for(int i=0; i<n; i++){
        if(numProductos<v[i].idProducto) numProductos=v[i].idProducto;    //el mayor id de un prducto = numero productos
    }

    //espacio de memoria para las unidades de productos iniciado en 0
    int *unidadesProducto = new int[numProductos]{0};

    for(int i=0; i<n; i++){ //completamos las unidades de cada producto
        unidadesProducto[v[i].idProducto - 1] += v[i].cantidad;
    }

    int idMejorVendido=-1, mayorUnidadesVendidas=-1;

    for(int i=0; i<numProductos; i++){
        if(mayorUnidadesVendidas<unidadesProducto[i]){
            mayorUnidadesVendidas=unidadesProducto[i];    //actualizar las unidades del producto mas vendido
            idMejorVendido=i+1;  //actualizar id del producto mas vendido
        }
    }

    delete[] unidadesProducto;   //liberar memoria
    unidadesProducto=nullptr;

    //escritura en el archivo
    reporte<<"\n-------------------------------------";
    reporte<<"\nPRODUCTO MAS VENDIDO:";
    reporte<<"\nID Producto: "<<idMejorVendido;
    reporte<<"\nTotal unidades: "<<mayorUnidadesVendidas<<endl;
}

void ventasSospechosas(ofstream &reporte, const Venta *v, int n){
    reporte<<"\n-------------------------------------";
    reporte<<"\nVENTAS SOSPECHOSAS (cantidad > 100):\n";

    reporte<<left;
    for(int i=0; i<n; i++){
        if(v[i].cantidad>100){
            reporte<<"\nID Venta: "<<setw(3)<<v[i].idVenta<<" | Vendedor: "<<setw(2)<<v[i].idVendedor;
            reporte<<" | Producto: "<<setw(2)<<v[i].idProducto<<" | Cantidad: "<<v[i].cantidad;
        }
    }
}

void liberarVentas(Venta *&v){
    delete[] v;
    v=nullptr;
}
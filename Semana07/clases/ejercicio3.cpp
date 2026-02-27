#include<iostream>
#include<fstream>
using namespace std;

struct Venta {
    int idVenta;
    int idVendedor;
    int idProducto;
    int cantidad;
    double precioUnitario;
};

Venta *extraerDatos(const char *file, int &n);
void generarReporte(const Venta *ventas, int n);
float montoTotalVendido(const Venta *&ventas, int n);
int numVendedores(const Venta *ventas, int n);
int IDvendedorMayorRecaudacion(const Venta *ventas, int n, float &mayorRecaudacionVendedor);
int numProducto(const Venta *ventas, int n);
int IDproductoMayorVendido(const Venta *ventas, int n, int &maximoProductoVendido);
void liberarVentas(Venta *&ventas);

int main(){
    char file[]="input/ventas.dat";
    int n;

    Venta *ventas=extraerDatos(file,n);
    if(ventas==nullptr) return 1;

    generarReporte(ventas,n);
    liberarVentas(ventas);

    return 0;
}

Venta *extraerDatos(const char *file, int &n){
    ifstream ventas(file, ios::binary);
    if(!ventas){
        cerr<<"\nNo pudo abrirse ventas.dat.\n";
        return nullptr;
    }

    int pos=0;
    ventas.read((char*)&n,sizeof(n));   //extraemos el numero de registros

    Venta *registros=new Venta[n];  //creamos un arreglo de ventas
    for(; ventas.read((char*)&*(registros+pos),sizeof(Venta)); pos++);  //registramos todas la ventas en el arreglo

    ventas.close();
    return registros;
}

void generarReporte(const Venta *ventas, int n){
    ofstream reporte("output/reporte.txt");
    if(!reporte){
        cerr<<"\nNo se pudo abrir el archivo reporte.txt.\n";
        return;
    }

    cout<<"\nGenerando reporte...\n";

    float totalVendido;
    int totalUnidades;

    reporte<<"--- REPORTE GENERAL DE VENTAS ---\n";
    reporte<<"\nTotal de registros: "<<n<<endl;
    reporte<<"\nMONTO TOTAL VENDIDO: "<<montoTotalVendido(ventas,n)<<endl;;
    reporte<<"\n---------------------------------------\n";
    reporte<<"VENDEDOR CON MAYOR RECAUDACION:";
    reporte<<"\nID vendedor: "<<IDvendedorMayorRecaudacion(ventas,n,totalVendido);
    reporte<<"\nTotal vendido: "<<totalVendido<<endl;
    reporte<<"\n---------------------------------------\n";
    reporte<<"PRODUCTO MAS VENDIDO:";
    reporte<<"\nID producto: "<<IDproductoMayorVendido(ventas,n,totalUnidades);
    reporte<<"\nTotal unidades: "<<totalUnidades<<endl;
    reporte<<"\n---------------------------------------\n";
    reporte<<"VENTAS SOSPECHOSAS (cantidad > 100)\n";
    for(const Venta *v=ventas; v<ventas+n; v++){
        if(v->cantidad>100){
            reporte<<"\nID Venta: "<<v->idVenta<<" | Vendedor: "<<v->idVendedor;
            reporte<<" | Producto: "<<v->idProducto<<" | Cantidad: "<<v->cantidad;
        }
    }

    cout<<"\nReporte generado con exito.\n";
    reporte.close();
}

float montoTotalVendido(const Venta *&ventas, int n){
    float montoTotal=0; 
    for(const Venta *v=ventas; v<ventas+n; v++){
        montoTotal+= v->precioUnitario * v->cantidad;   //el costo de cada venta
    }
    return montoTotal;
}

int numVendedores(const Venta *ventas, int n){
    int numV=ventas->idVendedor;
    for(const Venta *v=ventas; v<ventas+n; v++){
        if(v->idVendedor>numV) numV=v->idVendedor;
    }
    return numV;
}

int IDvendedorMayorRecaudacion(const Venta *ventas, int n, float &mayorRecaudacionVendedor){
    int idVendedorMayor=ventas->idVendedor;    //id del vendedor con mayor recaudacion
    int numeroVendedores=numVendedores(ventas,n);   //numero de vendedores (su id comienza en 1)
    float *vendedores=new float[numeroVendedores]{0};  //arreglo de las ventas totales de cada vendedor inicializado en 0

    for(const Venta *v=ventas; v<ventas+n; v++){
        vendedores[v->idVendedor-1]+=(v->cantidad * v->precioUnitario); //asignando las ventas de cada vendedor
    }

    mayorRecaudacionVendedor=-1;
    for(const float *vend=vendedores; vend<vendedores+numeroVendedores; vend++){
        if(mayorRecaudacionVendedor < *vend){
            mayorRecaudacionVendedor=*vend;
            idVendedorMayor= vend-vendedores+1;
        }
    }

    delete[] vendedores;
    vendedores=nullptr;

    return idVendedorMayor;
}

int numProducto(const Venta *ventas, int n){
    int numP=ventas->idProducto;
    for(const Venta *v=ventas; v<ventas+n; v++){
        if(v->idProducto>numP) numP=v->idProducto;
    }
    return numP;
}

int IDproductoMayorVendido(const Venta *ventas, int n, int &maximoProductoVendido){
    int idProductoMayor=ventas->idProducto;    //id del producto mas vendido
    int numeroProductos=numProducto(ventas,n);  //numero de productos (su id comienza en 1)
    int *productos=new int[numeroProductos]{0};    //arreglo de la cantidad de productos vendidos iniciado en 0

    for(const Venta *v=ventas; v<ventas+n; v++){
        productos[v->idProducto-1]+=v->cantidad;
    }

    maximoProductoVendido=-1;
    for(const int *prod=productos; prod<productos+numeroProductos; prod++){
        if(maximoProductoVendido < *prod){
            maximoProductoVendido = *prod;
            idProductoMayor=prod-productos+1;
        }
    }

    delete[] productos;
    productos=nullptr;

    return idProductoMayor;
}

void liberarVentas(Venta *&ventas){
    delete[] ventas;
    ventas=nullptr;
}
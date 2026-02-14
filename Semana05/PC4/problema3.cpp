#include<iostream>
#include<cstring>
using namespace std;

struct Producto {
    int codigo;
    char *nombre;
    double precio;
    int stock;
};

int numeroProductos(int &n);
Producto crearProducto(int codigo, const char* nombre, double precio, int stock);
Producto* crearInventario(int n);
void mostrarProducto(Producto p);
void mostrarInventario(Producto *p, int n);

int main(){
    int n;
    if(numeroProductos(n)==-1) return 0;

    Producto *prod=crearInventario(n);
    mostrarInventario(prod,n);

    int codigoBuscado=102;
    Producto *buscado=buscarProducto(prod,n,codigoBuscado);

    cout<<"\nBuscando producto con codigo "<<codigoBuscado<<"...\n";
    if(buscado!=nullptr){   //si ha encontrado, entonces
        cout<<"Producto encontrado: "<<buscado->nombre;
        cout<<" | Precio: "<<buscado->precio<<endl;
    }else{
        cout<<"Producto no encontrado\n";
    }

    return 0;
}

int numeroProductos(int &n){
    cout<<"\nCuantos productos habra?: ";
    cin>>n;
    if(n<=0){   //n debe ser mayor a cero
        cout<<"Numero no valido.";
        cout<<"\nTerminando programa";
        return -1;  //valor de error
    }
    return n;
}

Producto crearProducto(int codigo, const char* nombre, double precio, int stock){
    char *t=new char[strlen(nombre)+1]; //asignamos memoria dinamica para el nombre con su caracter nulo
    strcpy(t,nombre);   //copiamos correctamente el nombre en t (mismo tamaño en ambos)

    Producto p{codigo,t,precio,stock};  //inicializamos un producto con los datos dispuestos
    return p;   //retornamos el producto
}

Producto* crearInventario(int n){
    Producto *p=new Producto[n];    //reservamos memoria dinamica de los productos
    int codigo=100; //inciamos desde el codigo 100
    cout<<"\nIngrese los datos solicitados:";

    int i=0;
    while(i<n){
        cin.ignore(100,'\n');   //limpiamos despues de cada cin o error

        int stock=0;
        double precio=0;
        char nombre[100];   //espacio suficiente

        cout<<"\nIngrese el nombre del producto "<<i+1<<": ";
        cin.getline(nombre,100);    //recibimos el nombre por teclado

        cout<<"Ingrese el precio de "<<nombre<<" (mayor a 0): ";    //precio
        cin>>precio;

        cout<<"Ingrese el stock de "<<nombre<<" (mayor o igual a 0): "; //stock
        cin>>stock;

        if(cin.fail() || precio<=0 || stock<0){ //si los datos estan mal, 
            cin.clear();
            cout<<"\nError al ingresar datos, intentelo de nuevo\n";
            continue;   //reiniciamos en pedir los datos
        }

        p[i]=crearProducto(codigo,nombre,precio,stock); //creamos al producto con los datos solicitados
        i++; codigo++;   //aumentamos en 1 al i y al codigo
    }
    
    return p;   //retornamos el arreglo dinamico de productos
}

void mostrarInventario(Producto *p, int n){
    cout<<"\n\tINVENTARIO\n";
    for(int i=0; i<n; i++){
        mostrarProducto(p[i]);
    }
}

void mostrarProducto(Producto p){
    cout<<"Codigo: "<<p.codigo<<" | Nombre: "<<p.nombre;
    cout<<" | Precio: "<<p.precio<<" | Stock: "<<p.stock<<endl;
}

Producto* buscarProducto(Producto *inventario, int n, int codigoBuscado){
    for(int i=0; i<n; i++){
        if(inventario[i].codigo==codigoBuscado) return inventario+i;    //retornamos el puntero al producto encontrado
    }

    return nullptr; //retorna nullptr al no encontrarlo;
}
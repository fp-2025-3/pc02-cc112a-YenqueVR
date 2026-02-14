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
void mostrarInventario(Producto *p, int n);

int main(){
    int n;
    if(numeroProductos(n)==-1) return 0;

    Producto *prod=crearInventario(n);
    mostrarInventario(prod,n);

    return 0;
}

int numeroProductos(int &n){
    cout<<"\nCuantos productos habra?: ";
    cin>>n;
    if(n<0){   //n debe ser mayor a cero
        cout<<"Numero no valido.";
        cout<<"\nTerminando programa";
        return -1;  //valor de error
    }
    return n;
}

Producto crearProducto(int codigo, const char* nombre, double precio, int stock){
    char *t=new char[strlen(nombre)+1]; //asignamos memoria dinamica para el nombre con su caracter nulo
    strcpy(t,nombre);   //copiamos el nombre en t (mismo tamaño en ambos)

    Producto p{codigo,t,precio,stock};  //inicializamos un producto con los datos dispuestos
    return p;   //retornamos el producto
}

Producto* crearInventario(int n){
    Producto *p=new Producto[n];    //reservamos memoria dinamica de los productos
    int codigo=100; //inciamos desde el codigo 100
    cout<<"\nIngrese los datos solicitados:\n";

    int i=0;
    while(i<n){
        cin.ignore(50,'\n');   //limpiamos despues de cada cin

        int stock=0;
        double precio=0;
        char nombre[100];   //espacio suficiente

        cout<<"Ingrese el nombre del producto "<<i+1<<": ";
        cin.getline(nombre,100);    //recibimos el nombre por teclado

        cout<<"Ingrese el precio de "<<nombre<<" (mayor a 0): ";    //precio
        cin>>precio;

        cout<<"Ingrese el stock de "<<nombre<<" (mayor o igal a 0): "; //stock
        cin>>stock;

        if(cin.fail() || precio<=0 || stock<0){ //si los datos estan mal, 
            cin.clear();
            cout<<"\nError al ingresar datos, intentelo de nuevo\n\n";
            continue;   //reiniciamos en pedir los datos
        }

        p[i]=crearProducto(codigo,nombre,precio,stock); //creamos al producto con los datos solicitados
        i++; stock++;   //aumentamos en 1 al i y al codigo
    }
    
    return p;   //retornamos el arreglo dinamico de productos
}

void mostrarInventario(Producto *p, int n){
    cout<<"\n\tINVENTARIO";
    for(int i=0; i<n; i++){
        
    }
}
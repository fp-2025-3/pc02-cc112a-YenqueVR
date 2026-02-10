#include<iostream>
using namespace std;

struct Producto {
    int codigo;
    float precio;
    Producto *sig;
};

int main(){
    Producto *cabeza=nullptr;

    //insertar producto al inicio
    for(int i=0; i<2; i++){
        Producto *nuevo=new Producto;

        cout<<"\nCodigo: "; cin>>nuevo->codigo;
        cout<<"Precio: "; cin>>nuevo->precio;
        nuevo->sig=cabeza;   //el puntero de nuevo apunta al primer bloque de inicio
        cabeza=nuevo;   //el puntero cabeza deja de apuntar al bloque inicial y apunta a cabeza, que sera el primer bloque
    }

    for(Producto *a=cabeza; a!=nullptr; a=a->sig){  //inicia en cabeza, mientras a sea distinto de nullptr
        cout<<"\nCodigo: "<<a->codigo;              //a apuntara a la direccion que guarda la variable *sig
        cout<<"\nPrecio: "<<a->precio;
        cout<<endl;
    }

    while(cabeza!=nullptr){ //avanza hasta llegar al final, el que apunta a nullptr
        Producto *temp=cabeza;  //creamos un puntero que apunte al bloque de memoria actual
        cabeza=cabeza->sig; //cabeza avanza al siguiente bloque
        delete temp;    //eliminamos el bloque usando el puntero creado
    }

    return 0;
}
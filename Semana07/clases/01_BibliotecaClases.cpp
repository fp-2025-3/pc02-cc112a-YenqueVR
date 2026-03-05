#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class Libro {
    private:

    int codigo;
    char titulo[50];
    bool prestado;

    public:

    Libro(int c=0, const char *t=""){
        if(c<0){
            cout<<"\nEl codigo no debe ser negativo.\n";
            return;
        }

        if(strlen(t)==0) return;

        codigo=c;
        prestado=false;
        strcpy(titulo,t);
        titulo[49]='\0';    //por si acaso
    }

    ~Libro(){
        cout<<"\nLibro "<<titulo<<" destruido.\n";
    }

    void prestar(){
        if(prestado){
            cout<<"\nEl libro ya ha sido prestado.\n";
            return;
        }

        prestado=true;
        cout<<"\nLibro prestado exitosamente.\n";
    }

    void devolver(){
        if(!prestado){
            cout<<"\nEl libro no puede devolverse, no esta prestado.\n";
            return;
        }

        prestado=false;
        cout<<"\nLibro devuelto exitosamente.\n";
    }

    void mostrar(){
        cout<<"Codigo: "<<codigo<<" | Titulo: "<<titulo<<" | Estado: ";
        if(prestado) cout<<"Prestado";
        else cout<<"Disponible";
        cout<<endl;
    }
};

int main(){
    Libro l1(3,"De junto al cielo a tierra"), l2(6,"Manuel Rojas en Tambillamambo de Boscal"), l3;
    l2.prestar();
    l2.prestar();
    l1.devolver();
    cout<<endl;
    l1.mostrar();
    l2.mostrar();
    l3.mostrar();
    return 0;
}
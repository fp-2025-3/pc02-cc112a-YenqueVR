#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;

struct Seleccion {
    string nombre;
    int puntaje, PG, PE, PP;
    float rend;
};

int numeroSelecciones(int &n);
Seleccion* generarSelecciones(int n, int pj);
void SeleccionMejorRendimiento(Seleccion *s, int n);
void tabla(Seleccion *s, int n);
void liberarMemoria(Seleccion *&s);

int main(){
    int n, partidos=100;
    if(numeroSelecciones(n)==-1) return 0;

    Seleccion *selecciones=generarSelecciones(n,partidos);

    tabla(selecciones,n);
    liberarMemoria(selecciones);

    return 0;
}

int numeroSelecciones(int &n){
    cout<<"\nIngrese el numero de selecciones: ";
    cin>>n;

    if(n<=0){   //no aceptamos numeros menores o iguales a cero
        cout<<"No es un numero valido para registrar.\n";
        return -1;  //numero de error
    }
    return n;   //retorna el numero n valido
}

Seleccion* generarSelecciones(int n, int pj){
    cin.ignore();
    Seleccion *s=new Seleccion[n];

    srand(time(NULL));
    for(int i=0; i<n; i++){
        cout<<"Nombre de la seleccion "<<i+1<<": ";
        getline(cin,s[i].nombre);

        //partidos solo se reduce hasta 0
        int partidos=pj;

        s[i].PG = rand()%(partidos+1);    //de 0 a 100 ganados
        partidos -= s[i].PG;  //partidos sobrantes

        s[i].PE = rand()%(partidos+1);    //de 0 a 100-PG empatados
        partidos -= s[i].PE;

        s[i].PP = partidos;   //de 0 a 100-PG-PE ; los partidos sobrantes

        s[i].puntaje = 3*s[i].PG + s[i].PE;   //calculo del puntaje obtenido

        s[i].rend=100*((float)(s[i].puntaje)/300);   //300 es el puntaje maximo, hallamos el rendimiento
    }
    cout<<endl;

    return s;
}

void SeleccionMejorRendimiento(Seleccion *s, int n){
    Seleccion mejorRend=*s;

    for(int i=0; i<n; i++){
        if(s[i].rend>mejorRend.rend){
            mejorRend=s[i];
        }
    }

    cout<<"\nLa seleccion con mejor rendimiento es: "<<mejorRend.nombre<<"  Rendimiento: "<<mejorRend.rend;
    cout<<endl;
}

void tabla(Seleccion *s, int n){
    cout<<fixed<<setprecision(1);
    cout<<left;

    cout<<setw(18)<<"Seleccion"<<setw(5)<<"PG"<<setw(5)<<"PE"<<setw(5)<<"PP"<<setw(10)<<"Puntaje"<<"Rendimiento";
    for(int i=0; i<n; i++){
        cout<<endl<<setw(18)<<s[i].nombre<<setw(5)<<s[i].PG<<setw(5)<<s[i].PE<<setw(7)<<s[i].PP;
        cout<<setw(12)<<s[i].puntaje<<s[i].rend;
    }
    cout<<endl;

    SeleccionMejorRendimiento(s,n);
}

void liberarMemoria(Seleccion *&s){
    delete[] s;
    s=nullptr;
}
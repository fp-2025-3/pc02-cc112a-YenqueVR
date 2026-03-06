#include<iostream>
#include<cmath>
using namespace std;

struct Punto {
    double x, y;
};

void leerPunto(Punto* p);
double distanciaOrigen(const Punto* p);
Punto* masLejano(Punto* p1, Punto* p2);

int main(){
    Punto *p1=new Punto{0,0}, *p2=new Punto{0,0};   //asignamos memoria dinamica en los puntos iniciados en 0

    cout<<"\nPunto p1:\n";  //leemos el primer punto
    leerPunto(p1);

    cout<<"\nPunto p2:\n";  //leemos el segundo punto
    leerPunto(p2);

    Punto *puntoMasLejano=masLejano(p1,p2); //almacenamos el puntero del punto mas lejano

    if(puntoMasLejano==nullptr){    //si la distancia de los puntos al origen son iguales, entonces...
        cout<<"\nAmbos puntos estan a la misma distancia del origen.\n";
    }else{  //si no, indica el punto mas lejano
        cout<<"\nEl punto mas lejano es:\n";
        if(puntoMasLejano==p1) cout<<"Punto p1: ";  //indicamos el nombre del punto mas lejano
        else cout<<"Punto p2: ";

        cout<<"("<<puntoMasLejano->x<<", "<<puntoMasLejano->y<<")\n\n"; //coordenadas del punto mas lejano
    }

    delete p1;  //liberamos memoria dinamica de los puntos
    delete p2;

    return 0;
}

void leerPunto(Punto* p){
    cout<<"Ingrese la coordenada x: ";
    cin>>p->x;
    cout<<"Ingrese la coordenada y: ";
    cin>>p->y;
}

double distanciaOrigen(const Punto* p){
    return sqrt(pow(p->x,2) + pow(p->y,2)); //raiz de la suma de cuadrados de x y y
}

Punto* masLejano(Punto* p1, Punto* p2){
    double distP1=distanciaOrigen(p1);
    double distP2=distanciaOrigen(p2);

    if(distP1==distP2) return nullptr;  //si las distancias son iguales, retorna nullptr
    if(distP1>distP2) return p1;    //si no al que sea mayor
    else return p2;
}
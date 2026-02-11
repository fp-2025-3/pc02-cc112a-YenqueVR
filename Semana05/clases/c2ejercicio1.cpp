#include<iostream>
#include<cmath>
using namespace std;

struct Punto {
    float x,y,z;
};

void coordenadasPuntos(Punto &a, Punto &b);
void distanciaEntrePuntos(Punto a, Punto b);

int main(){
    Punto a,b;
    coordenadasPuntos(a,b);
    distanciaEntrePuntos(a,b);

    return 0;
}

void coordenadasPuntos(Punto &a, Punto &b){
    cout<<"\nIngrese las coordenadas del primer punto:";
    cout<<"\nX: "; cin>>a.x;
    cout<<"Y: "; cin>>a.y;
    cout<<"Z: "; cin>>a.z;
    cout<<"Ingrese las coordenadas del segundo punto:";
    cout<<"\nX: "; cin>>b.x;
    cout<<"Y: "; cin>>b.y;
    cout<<"Z: "; cin>>b.z;
}

void distanciaEntrePuntos(Punto a, Punto b){
    float distancia=sqrt(pow(a.x-b.x,2) + pow(a.y-b.y,2) + pow(a.z-b.z,2));
    cout<<"La distancia entre los dos puntos es: "<<distancia<<endl;
}
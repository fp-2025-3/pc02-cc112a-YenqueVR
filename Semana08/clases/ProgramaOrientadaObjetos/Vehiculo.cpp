#include "Vehiculo.h"
#include<iostream>
#include<string>
using namespace std;

//CONSTRUCTORES Y DESTRUCTORES DE LAS CLASES

Vehiculo::Vehiculo():placa("Deconocido"),marca("Desconocido"),anio(0),precioBase(0){
    cout<<"Llamando al constructor por defecto de Vehiculo.\n";
}

Vehiculo::Vehiculo(string p, string m, int a, double pb):placa(p),marca(m),anio(a),precioBase(pb){
    cout<<"Llamando al constructor con parametros de Vehiculo.\n";
}

Vehiculo::~Vehiculo(){
    cout<<"Destructor de Vehiculo.\n";
}

Automovil::Automovil():Vehiculo(), numeroPuertas(0){
    cout<<"Llamando al constructor por defecto de Automovil.\n";
}

Automovil::Automovil(string p, string m, int a, double pb, int np):Vehiculo(p,m,a,pb), numeroPuertas(np){
    cout<<"Llamando al constructor con parametros de Automovil.\n";
}

Automovil::~Automovil(){
    cout<<"Destructor de Automovil.\n";
}

Camion::Camion():Vehiculo(), capacidad(0){
    cout<<"Llamando al constructor por defecto de Camion.\n";
}

Camion::Camion(string p, string m, int a, double pb, double cp):Vehiculo(p,m,a,pb), capacidad(cp){
    cout<<"Llamando al constructor con parametros de Camion.\n";
}

Camion::~Camion(){
    cout<<"Destructor de Camion.\n";
}

Motocicleta::Motocicleta():Vehiculo(), potencia(0){
    cout<<"Llamando al constructor por defecto de Motocicleta.\n";
}

Motocicleta::Motocicleta(string p, string m, int a, double pb, double pt):Vehiculo(p,m,a,pb), potencia(pt){
    cout<<"Llamando al constructor con parametros de Motocicleta.\n";
}

Motocicleta::~Motocicleta(){
    cout<<"Destructor de Motocicleta.\n";
}

//FUNCIONES DE LAS CLASES

void Automovil::mostrarInfo() const{
    cout<<"Placa del automovil: "<<placa<<endl;
    cout<<"Marca del automovil: "<<marca<<endl;
    cout<<"Anio del automovil: "<<anio<<endl;
    cout<<"Precio base del automovil: "<<precioBase<<endl;
    cout<<"Numero de puertas del automovil: "<<numeroPuertas<<endl;
}

void Camion::mostrarInfo() const{
    cout<<"Placa del camion: "<<placa<<endl;
    cout<<"Marca del camion: "<<marca<<endl;
    cout<<"Anio del camion: "<<anio<<endl;
    cout<<"Precio base del camion: "<<precioBase<<endl;
    cout<<"Capacidad de carga(Ton) del camion: "<<capacidad<<endl;
}

void Motocicleta::mostrarInfo() const{
    cout<<"Placa de la motocicleta: "<<placa<<endl;
    cout<<"Marca de la motocicleta: "<<marca<<endl;
    cout<<"Anio de la motocicleta: "<<anio<<endl;
    cout<<"Precio base de la motocicleta: "<<precioBase<<endl;
    cout<<"Potencia de la motocicleta: "<<potencia<<endl;
}

double Automovil::calculaPrecioFinal() const{
    return precioBase*1.05;
}

double Camion::calculaPrecioFinal() const{
    return precioBase*1.12;
}

double Motocicleta::calculaPrecioFinal() const{
    return precioBase*1.03;
}

void Automovil::guardar(ofstream &out) const{
    out.write((char*)this,sizeof(Automovil));
}

void Automovil::cargar(ifstream &in){
    in.read((char*)this,sizeof(Automovil));
}

void Camion::guardar(ofstream &out) const{
    out.write((char*)this,sizeof(Camion));
}

void Camion::cargar(ifstream &in){
    in.read((char*)this,sizeof(Camion));
}

void Motocicleta::guardar(ofstream &out) const{
    out.write((char*)this,sizeof(Motocicleta));
}

void Motocicleta::cargar(ifstream &in){
    in.read((char*)this,sizeof(Motocicleta));
}
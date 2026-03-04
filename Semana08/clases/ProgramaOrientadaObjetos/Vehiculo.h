#ifndef VEHICULO_H
#define VEHICULO_H

#include<string>
#include<fstream>

//debe serializarse el string para guaradar correctamente en binario, o en cambio usar char[]
class Vehiculo {
protected:
    std::string placa;
    std::string marca;
    int anio;
    double precioBase;

public:
    Vehiculo(); //Constructor por defecto
    Vehiculo(std::string p, std::string m, int a, double pb);   //Constructor con parametro

    virtual ~Vehiculo();    //Destructor

    //convertimos la clase en una clase abstracta definiendo al menos un metodo virtual puro
    virtual void mostrarInfo() const=0;
    virtual double calculaPrecioFinal() const = 0;
    virtual void guardar(std::ofstream &out) const = 0 ;
    virtual void cargar(std::ifstream &in) = 0;
};

class Automovil : public Vehiculo {
private:
    int numeroPuertas;

public:
    Automovil();    //Constructor por defecto
    Automovil(std::string p, std::string m, int a, double pb, int np);  //Constructor con parametro

    ~Automovil() override;   //Destructor

    void mostrarInfo() const override;
    double calculaPrecioFinal() const override;
    void guardar(std::ofstream &out) const override;
    void cargar(std::ifstream &in) override;
};

class Camion : public Vehiculo {
private:
    double capacidad;

public:
    Camion();   //Constructor por defecto
    Camion(std::string p, std::string m, int a, double pb, double cp); //Constructor con parametro

    ~Camion() override;  //Destructor

    void mostrarInfo() const override;
    double calculaPrecioFinal() const override;
    void guardar(std::ofstream &out) const override;
    void cargar(std::ifstream &in) override;
};

class Motocicleta : public Vehiculo {
private:
    double potencia;

public:
    Motocicleta();  //Constructor por defecto
    Motocicleta(std::string p, std::string m, int a, double pb, double pt); //Constructor con parametro
    
    ~Motocicleta() override; //Destructor

    void mostrarInfo() const override;
    double calculaPrecioFinal() const override;
    void guardar(std::ofstream &out) const override;
    void cargar(std::ifstream &in) override;
};

#endif
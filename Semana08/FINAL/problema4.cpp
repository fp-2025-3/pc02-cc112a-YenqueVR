#include<iostream>
using namespace std;

class Sensor {
    protected:
    string id;
    double* posicion;

    public:
    Sensor(string ID, double x, double y):id(ID){
        posicion=new double[2];
        posicion[0]=x;  //coordenada x
        posicion[1]=y;  //coordenada y
    }

    Sensor(Sensor &otro):id(otro.id){
        posicion=new double[2];
        posicion[0]=otro.posicion[0];  //coordenada x
        posicion[1]=otro.posicion[2];  //coordenada y
    }

    Sensor& operator=(Sensor &otro){
        if(this!=&otro){    //evitar la auto copia
            this->id=otro.id;

            delete[] posicion;
            posicion=new double[2];

            this->posicion[0]=otro.posicion[0];
            this->posicion[1]=otro.posicion[1];
        }

        return *this;   //retornamos el contenido
    }

    virtual ~Sensor(){
        cout<<"Sensor ID: "<<id<<" destruido.\n";
    }
    
    virtual double areaCobertura() const = 0;
    virtual bool detecta(double x, double y) const = 0;
    virtual void imprimir() const = 0;
};

class SensorCircular : public Sensor {
    private:
    double radio;

    public:
    SensorCircular(string id, double x, double y, double r):Sensor(id,x,y){
        if(r<0) r*=-1;
        radio=r;
    }

    SensorCircular(SensorCircular &otro):Sensor(otro.id,otro.posicion[0],otro.posicion[1]),radio(otro.radio){}

    SensorCircular& operator=(SensorCircular &otro){
        if(this!=&otro){    //evitar la auto copia
            this->id=otro.id;
            this->radio=otro.radio;

            delete[] posicion;
            posicion=new double[2];

            this->posicion[0]=otro.posicion[0];
            this->posicion[1]=otro.posicion[1];
        }

        return *this;   //retornamos el contenido
    }

    ~SensorCircular(){
        cout<<"Sensor circular destruido.\n";
    }

    double areaCobertura() const override{
        double pi=3.1416;
        return 2*pi*radio*radio;    //2pi*r^2
    }

    bool detecta(double x, double y) const override{    //centro circulo (h,k)
        double xRelativo=x-posicion[0]; //x-h
        double yRelativo=y-posicion[1]; //y-k

        //(x-h)^2 + (y-k)^2 <= r^2 es verdadero si (x,y) esta en el area del circulo (h,k) con radio r
        return ((xRelativo*xRelativo + yRelativo*yRelativo) <= (radio*radio));
    }

    void imprimir() const override{
        cout<<"\nSensor circular:";
        cout<<"\nCoordenadas: ("<<posicion[0]<<", "<<posicion[1]<<")";
        cout<<"\nRadio: "<<radio;
        cout<<"\nArea cubierta: "<<areaCobertura()<<" u^2"<<endl;
    }
};

class SensorRectangular : public Sensor {
    private:
    double ancho, alto;

    public:
    SensorRectangular(string id, double x, double y, double an, double al):Sensor(id,x,y){
        if(an<0) an*=-1;
        if(al<0) al*=-1;

        ancho=an;
        alto=al;
    }

    SensorRectangular(SensorRectangular &otro):Sensor(otro.id,otro.posicion[0],otro.posicion[1]),ancho(otro.ancho),alto(otro.alto){}

    SensorRectangular& operator=(SensorRectangular &otro){
        if(this!=&otro){    //evitar la auto copia
            this->id=otro.id;
            this->ancho=otro.ancho;
            this->alto=otro.alto;

            delete[] posicion;
            posicion=new double[2];

            this->posicion[0]=otro.posicion[0];
            this->posicion[1]=otro.posicion[1];
        }

        return *this;   //retornamos el contenido
    }

    ~SensorRectangular() override{
        cout<<"Sensor rectangular destruido.\n";
    }

    double areaCobertura() const override{
        return ancho*alto;
    }

    bool detecta(double x, double y) const override{    //centro rectangulo (h,k)
        double xRelativo=x-posicion[0]; //x-h
        double yRelativo=y-posicion[1]; //y-k

        if(xRelativo<0) xRelativo*=-1;  //convertirlo a positivo (valor absoluto)
        if(yRelativo<0) yRelativo*=-1;

        //|x-h|<=ancho/2 && |y-h|<=alto/2
        return (xRelativo<=ancho/2) && (yRelativo<=alto/2);
    }
    
    void imprimir() const override{
        cout<<"\nSensor rectangular:";
        cout<<"\nCoordenadas: ("<<posicion[0]<<", "<<posicion[1]<<")";
        cout<<"\nAncho: "<<ancho<<", Alto: "<<alto;
        cout<<"\nArea cubierta: "<<areaCobertura()<<" u^2"<<endl;
    }
};

class SistemaSensores {
    private:
    Sensor** sensores;
    int cantidad;
    int capacidad;

    public:
    SistemaSensores(int cap):cantidad(0){
        if(cap<0) cap*=-1;
        sensores=new Sensor*[cap];
    }

    ~SistemaSensores(){
        cout<<"\nSistema de sensores destruido.\n";
    }

    void agregarSensor(){}
};

int main(){
    return 0;
}
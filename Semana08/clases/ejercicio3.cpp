#include<iostream>
using namespace std;

class Figura {
    private:
    string nombre;
    double *colorRGB;

    public:
    Figura(string nom, double r, double g, double b):nombre(nom){   //constructor de parametro
        colorRGB=new double[3];
        colorRGB[0]=r;
        colorRGB[1]=g;
        colorRGB[2]=b;
    }

    Figura(Figura &otro):nombre(otro.nombre){   //constructor de copia
        colorRGB=new double[3];
        colorRGB[0]=otro.colorRGB[0];
        colorRGB[1]=otro.colorRGB[1];
        colorRGB[2]=otro.colorRGB[2];
    }

    //Redefinir el operador de asignacion (puntero oculto this)
    Figura& operator=(Figura &otro){
        if(this!=&otro){
            this->nombre=otro.nombre;

            delete[] colorRGB;

            colorRGB=new double[3];

            for(int i=0; i<3; i++){
                colorRGB[i]=otro.colorRGB[i];
            }
        }

        return *this;
    }

    virtual ~Figura(){
        delete[] colorRGB;  //liberar memoria del objeto en colorRGB
        cout<<"Figura "<<nombre<<" destruida.\n";
    }

    virtual double area() const = 0;
    virtual double perimetro() const = 0;
    virtual double imprimir() const = 0;
};

class Circulo : public Figura {
    private:
    double radio;

    public:
    Circulo(string nom, double r, double g, double b, double rd):Figura(nom,r,g,b), radio(rd){}
    Circulo(Circulo &otro):Figura(otro), radio(otro.radio){}

    ~Circulo() override {
        cout<<"Circulo destruido.\n";
    }
};

class Rectangulo {
    private:
    double base, altura;

    public:

};

int main(){
    return 0;
}
#include<iostream>
using namespace std;

struct Polinomio {
    int gradoP;
    float *coef;
};

Polinomio sumarTresPolinomios(Polinomio p1, Polinomio p2, Polinomio p3);
Polinomio multiplicarTresPolinomios(Polinomio p1, Polinomio p2, Polinomio p3);
void mostrarPolinomio(Polinomio p);
void liberarCoefPolinomio(Polinomio &p);

int main(){
    int grado1=2, grado2=1, grado3=2;   //grado de los 3 polinomios
    float *coef1=new float[grado1+1]{1,0,3};    //coeficientes del primer polinomio
    float *coef2=new float[grado2+1]{-4,5};     //coeficientes del segundo polinomio
    float *coef3=new float[grado3+1]{3,0,1};    //coeficientes del tercer polinomio

    Polinomio p1{grado1,coef1}; //inicializando los polinomios en su declaracion
    Polinomio p2{grado2,coef2};
    Polinomio p3{grado3,coef3};

    cout<<"\nPolinomio 1: "; mostrarPolinomio(p1);  //mostramos los 3 polinomios
    cout<<"\nPolinomio 2: "; mostrarPolinomio(p2);
    cout<<"\nPolinomio 3: "; mostrarPolinomio(p3);

    Polinomio suma=sumarTresPolinomios(p1,p2,p3);   //polinomio de la suma
    cout<<"\n\nSuma de los tres polinomios: ";
    mostrarPolinomio(suma);

    Polinomio mult=multiplicarTresPolinomios(p1,p2,p3); //polinomio de la multiplicacion
    cout<<"\n\nProducto de los tres polinomios: ";
    mostrarPolinomio(mult);
    cout<<endl;

    liberarCoefPolinomio(p1);
    liberarCoefPolinomio(p2);
    liberarCoefPolinomio(p3);
    liberarCoefPolinomio(suma);
    liberarCoefPolinomio(mult);

    return 0;
}

Polinomio sumarTresPolinomios(Polinomio p1, Polinomio p2, Polinomio p3){
    Polinomio s;
    s.gradoP=p1.gradoP;
    if(s.gradoP<p2.gradoP) s.gradoP=p2.gradoP;  //buscamos el mayor gradoP de los polinomios
    if(s.gradoP<p3.gradoP) s.gradoP=p3.gradoP;
    
    s.coef=new float[s.gradoP+1]{0};    //inicializados en 0 los coeficientes

    for(int i=0; i<=s.gradoP; i++){
        if(p1.gradoP-i<=p1.gradoP && p1.gradoP-i>=0) s.coef[s.gradoP-i]+=p1.coef[p1.gradoP-i]; //suma con coef de p1 si es posible
        if(p2.gradoP-i<=p2.gradoP && p2.gradoP-i>=0) s.coef[s.gradoP-i]+=p2.coef[p2.gradoP-i]; //suma con coef de p2 si es posible
        if(p3.gradoP-i<=p3.gradoP && p3.gradoP-i>=0) s.coef[s.gradoP-i]+=p3.coef[p3.gradoP-i]; //suma con coef de p3 si es posible
    }

    return s;   //retornamos una copia del polinomio de suma de los 3 polinomios
}

Polinomio multiplicarTresPolinomios(Polinomio p1, Polinomio p2, Polinomio p3){
    Polinomio r;
    r.gradoP=p1.gradoP+p2.gradoP+p3.gradoP; //el grado de la multiplicacion como la suma de los 3 polinomios
    r.coef=new float[r.gradoP+1]{0};    //inicializados en 0 los coeficientes

    for(int i=0; i<=p1.gradoP; i++){
        for(int j=0; j<=p2.gradoP; j++){
            for(int k=0; k<=p3.gradoP; k++){
                r.coef[i+j+k]+=(p1.coef[i] * p2.coef[j] * p3.coef[k]);  //multiplicacion de los miembros de los polinomios
            }
        }
    }

    return r;
}

void mostrarPolinomio(Polinomio p){
    for(int i=0; i<=p.gradoP; i++){
        if(p.coef[i]==0) continue;  //continua al siguiente coeficiente
        if(i!=0) cout<<" + ";    //coloca el operador suma
        if(i!=p.gradoP) cout<<p.coef[i]<<"x^"<<p.gradoP-i;  //muestra el x elevado a la i
        else cout<<p.coef[i];  //muestra solo el coeficiente en x^0
    }
}

void liberarCoefPolinomio(Polinomio &p){
    delete[] p.coef;
    p.coef=nullptr;
}
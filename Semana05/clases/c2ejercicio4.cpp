#include<iostream>
#include<cmath>
using namespace std;

struct Polinomio {
    int gradoP;
    float *coef;
};

int gradoPolinomio();
Polinomio generarPolinomio(int n);
Polinomio sumaPolinomios(Polinomio p1, Polinomio p2);
Polinomio productoPolinomios(Polinomio p1, Polinomio p2);
float evaluarPolinomio(Polinomio p, float x);
void mostrarPolinomio(Polinomio p);

int main(){
    cout<<"\nIngrese el grado del primer polinomio: ";
    Polinomio p1=generarPolinomio(gradoPolinomio());

    cout<<"\nIngrese el grado del segundo polinomio: ";
    Polinomio p2=generarPolinomio(gradoPolinomio());

    cout<<"\nPrimer polinomio: "; mostrarPolinomio(p1);
    cout<<"\nSegundo polinomio: "; mostrarPolinomio(p2);

    Polinomio suma=sumaPolinomios(p1,p2);
    cout<<"\nLa suma de los polinomios es: ";
    mostrarPolinomio(suma);

    Polinomio producto=productoPolinomios(p1,p2);
    cout<<"\nEl producto de los polinomios es: ";
    mostrarPolinomio(producto);

    float x;    //valor de x en el polinomio
    cout<<"\n\nIngrese el valor de x para evaluar el primer polinomio: "; cin>>x;
    float evaluado=evaluarPolinomio(p1,x);
    cout<<"El primer polinomio evaluado en x = "<<x<<" es: "<<evaluado;
    cout<<endl;

    return 0;
}

int gradoPolinomio(){
    int grado;
    while(true){    //repite hasta tener un grado valido
        cin>>grado;
        if(grado<0){
            cout<<"No es un grado valido de polinomio\n";
            continue;   //continua el bucle
        }
        break;  //sale del bucle
    }
    return grado;   //retorna el grado del polinomio
}

Polinomio generarPolinomio(int n){
    Polinomio p;    //creamos un polinomiio
    p.gradoP=n;    //le asignamos su grado de polinomio
    p.coef=new float[n+1];   //creamos un arreglo de sus coeficientes

    for(int i=n; i>=0; i--){
        cout<<"Ingrese el coeficiente de x^"<<i<<": ";
        cin>>p.coef[i];
    }
    return p;   //retorna la direccion del bloque de memoria
}

Polinomio sumaPolinomios(Polinomio p1, Polinomio p2){
    Polinomio r;
    r.gradoP=max(p1.gradoP,p2.gradoP);
    r.coef=new float[r.gradoP+1];   //coeficientes de suma

    for(int i=0; i<=r.gradoP; i++){
        r.coef[i]=0;    //los coeficientes inician en 0
        if(i<=p1.gradoP) r.coef[i]+=p1.coef[i];
        if(i<=p2.gradoP) r.coef[i]+=p2.coef[i];
    }

    return r;
}

Polinomio productoPolinomios(Polinomio p1, Polinomio p2){
    Polinomio r;
    r.gradoP=p1.gradoP+p2.gradoP;
    r.coef=new float[r.gradoP+1]{0};    //iniciamos los coeficientes del producto en 0

    for(int i=0; i<=p1.gradoP; i++){
        for(int j=0; j<=p2.gradoP; j++){
            r.coef[i+j]+=(p1.coef[i] * p2.coef[j]); //multiplicacion de cada miembro de los polinomios
        }
    }

    return r;
}

float evaluarPolinomio(Polinomio p, float x){
    float resultado=0;

    for(int i=0; i<=p.gradoP; i++){
        resultado+=(p.coef[i] * pow(x,i));  //coef * x^i + ...
    }
    
    return resultado;   //retorna el valor del polinomio evaluado en x
}

void mostrarPolinomio(Polinomio p){
    for(int i=p.gradoP; i>=0; i--){
        if(i==p.gradoP) cout<<p.coef[i]<<"x^"<<i;
        else if(i!=0) cout<<" + "<<p.coef[i]<<"x^"<<i;
        else cout<<" + "<<p.coef[i];
    }
}
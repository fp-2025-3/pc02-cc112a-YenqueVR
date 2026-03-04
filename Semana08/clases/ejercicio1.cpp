#include<iostream>
#include<cmath>
using namespace std;

struct Termino {    //coef^exp
    double coeficiente;    //coeficiente del termino
    double exponente;     //exponente del termino
};

struct Polinomio {      //suma de terminos
    Termino *terminos;  //arreglo dinamico de terminos
    int cantidad;       //cantidad de terminos en el arreglo
};

void crearPolinomio(Polinomio &p, int n){
    p.cantidad=n;
    p.terminos=new Termino[n];
}

void leerPolinomio(Polinomio &p){
    cout<<"\nIngrese los coeficientes y exponentes del polinomio:\n";

    for(int i=0; i<p.cantidad; i++){
        cout<<"Coeficiente "<<i+1<<": ";
        cin>>p.terminos[i].coeficiente;
        cout<<"Exponente "<<i+1<<": ";
        cin>>p.terminos[i].exponente;
        cout<<"-----------------------\n";
    }
}

void mostrarPolinomio(const Polinomio &p){
    for(int i=0; i<p.cantidad; i++){
        if(p.terminos[i].coeficiente==0) continue;  //no mostrar coeficientes igual a 0

        if(p.terminos[i].coeficiente>0) cout<<" + ";    //poner el signo de acuerdo al coeficiente
        else cout<<" - ";
        
        //colocar el coeficiente
        if((p.terminos[i].coeficiente!=1 && p.terminos[i].coeficiente!=-1) || p.terminos[i].exponente==0){
            if(p.terminos[i].coeficiente>0) cout<<p.terminos[i].coeficiente;
            else cout<<p.terminos[i].coeficiente * -1;
        }

        if(p.terminos[i].exponente>1) cout<<"x^"<<p.terminos[i].exponente;  //colocar exponente
        else if(p.terminos[i].exponente==1) cout<<"x";
    }
    cout<<endl;
}

double evaluarPolinomio(const Polinomio &p, double x){
    double sumaEvaluada=0;
    for(int i=0; i<p.cantidad; i++){
        sumaEvaluada+=(p.terminos[i].coeficiente * pow(x,p.terminos[i].exponente));
    }
    return sumaEvaluada;
}

void derivarPolinomio(const Polinomio &p, Polinomio &der){
    int numExpNoNulos=0;
    for(int i=0; i<p.cantidad; i++){    //numero de exponentes no nulos
        if(p.terminos[i].exponente!=0) numExpNoNulos++;
    }

    crearPolinomio(der,numExpNoNulos);

    int iDer=0;
    for(int i=0; i<p.cantidad; i++){
        if(p.terminos[i].exponente==0) continue;
        der.terminos[iDer].coeficiente=p.terminos[i].coeficiente * p.terminos[i].exponente;
        der.terminos[iDer].exponente=p.terminos[i].exponente-1;
        iDer++;
    }
}

void liberarPolinomio(Polinomio &p){
    delete[] p.terminos;
    p.terminos=nullptr;
    p.cantidad=0;
}

int main(){
    Polinomio p,der;
    double x=1;
    crearPolinomio(p,4);
    leerPolinomio(p);

    cout<<"\nPolinomio p: ";
    mostrarPolinomio(p);
    cout<<"Polinomio p evaluado en x="<<x<<": "<<evaluarPolinomio(p,x);

    derivarPolinomio(p,der);

    cout<<"\n\nPolinomio der: ";
    mostrarPolinomio(der);
    cout<<"Polinomio der evaluado en x="<<x<<": "<<evaluarPolinomio(der,x)<<endl;
    
    liberarPolinomio(p);
    liberarPolinomio(der);
    return 0;
}
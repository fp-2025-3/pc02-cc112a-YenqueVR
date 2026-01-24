#include<iostream>
using namespace std;

void imprimirPolinomio(const double* p, int grado);
void derivarPol(double arr[], int n, int k);

int main(){
    double coeft[]={2,3,-1,4};
    int grado=sizeof(coeft)/sizeof(coeft[0])-1;

    cout<<"Polinomio original: "<<endl;
    imprimirPolinomio(coeft,grado);

    int k=2;
    derivarPol(coeft,grado,k);
    return 0;
}

void derivadaK(const double* coef ,int grado, int k, double* res, int& gradoRes){
    gradoRes = grado - k;   //grado de la derivada actualizada
    int gradoK=0;   //grado k: exponente del termino del polinomio original (x^k)
    for(const double *i=coef; i<=coef+grado; i++, gradoK++){    //desde x^0 a x^grado
        int gradoDervK=gradoK-k;    //grado k de los terminos de la derivada
        if(gradoDervK>=0){  //se almacena desde el grado 0 de la derivada
            *(res+gradoDervK)= *i;  //copiamos el valor del coeficiente en la derivada
            for(int j=gradoK; j>gradoK-k; j--){ //multiplicamos el coeficiente con el valor de exponentes
                *(res+gradoDervK)*=j;   //si K=2, gradoK=3, "a" coef, a*3*2
            }
        }
        //se descarta del polinomio los terminos con exponente menor a k
        //para hallar la derivada a partir del exponente k del original
    }
}

void imprimirPolinomio(const double* p, int grado){
   for(int gradoK=0; gradoK<=grado; gradoK++){
        //disponemos la presentacion de coeficientes
        if(*(p+gradoK)<0){   //a<0
            cout<<" - ";
            if(-(*(p+gradoK))!=1 || gradoK==0) cout<<-(*(p+gradoK));   //... -a ... else ... - ...
        }
        else if(gradoK>0 && *(p+gradoK)>0){  //a>0 ax^k k>0
            cout<<" + ";
            if(*(p+gradoK)!=1) cout<<*(p+gradoK); //... + a ... else ... + ...
        }
        else if(*(p+gradoK)>0){  //a>0 ax^k k=0
            cout<<*(p+gradoK);  //... a ... else ...  ...
        }

        //disponemos la presentacion de los X
        if(*(p+gradoK)!=0){ //a!=0
            if(gradoK>1) cout<<"x^"<<gradoK;    //ax^k k>1
            else if(gradoK==1) cout<<"x";   //ax k=1 else a k=0
        }
        //a=0 --> 0x^k no se muestra
    }
    cout<<endl;
}
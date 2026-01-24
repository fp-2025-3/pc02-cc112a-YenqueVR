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

void derivarPol(double arr[], int n, int k){
    int i=n-1;
    for(double *p=arr+n-1; p>=arr; --p, i--){
        for(int j=i; j>i-k; --j){
            *p *= j;
        }
    }

    cout<<"\nDerivada de orden "<<k<<":\n";
    for(int i=n-1; i>n-1-k; --i){
        if(i==n-1) cout<<*(arr+i)<<"x^"<<i-k;
        else if(i==n-k) cout<<" + "<<*(arr+i);
        else if(*(arr+i)!=0) cout<<" + "<<*(arr+i)<<"x^"<<i;
    }
    cout<<endl;
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
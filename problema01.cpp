#include<iostream>
using namespace std;

void imprimirPol(double arr[], int n);
void derivarPol(double arr[], int n, int k);

int main(){
    double coeft[]={2,3,-1,4};
    int n=sizeof(coeft)/sizeof(coeft[0]);

    cout<<"Polinomio original: "<<endl;
    imprimirPol(coeft,n);

    int k=2;
    derivarPol(coeft,n,k);
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

void imprimirPol(double arr[], int n){
    for(int i=n-1; i>=0; --i){
        if(i==n-1) cout<<*(arr+i)<<"x^"<<i;
        else if(i==0) cout<<" + "<<*(arr+i);
        else if(*(arr+i)!=0) cout<<" + "<<*(arr+i)<<"x^"<<i;
    }
    cout<<endl;
}
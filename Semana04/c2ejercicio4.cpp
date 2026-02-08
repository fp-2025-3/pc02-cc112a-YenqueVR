#include <iostream>
#include<climits>
using namespace std;


int costoMinimo(int arr[], int n, int pos) {
    //Caso Base
    if(pos==n) return 0;

    // Caso recursivo
    int min=INT_MAX;
    int producto = 1;
    for (int i=pos; i<n; ++i) {
        producto *= arr[i];

        int costo=costoMinimo(arr,n,i+1);
        if(producto+costo<min) min=producto+costo;
    }

    return min;
}


// Graficar el albol de llamadas recursivas
// para [1,2,3]
int main(){

    int arr[]={1,2,3};
    int N=3;
    int n=costoMinimo(arr,N,0);
    cout<<endl<<"es este: "<<n<<endl;
    return 0;
}
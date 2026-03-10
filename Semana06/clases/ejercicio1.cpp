#include<iostream>
#include<fstream>
using namespace std;

bool registrarVentas(int dias);
void realizarResumenVentas(int n);
float *almacenarMontosVentas(int n);
float totalVentas(float *montos, int n);
float promedioVentas(float *montos, int n);
float mayorVenta(float *montos, int n);
float menorVenta(float *montos, int n);

int main(){
    int dias=7;
    if(!registrarVentas(dias)) return 1; //si es falso, termina el programa

    realizarResumenVentas(dias);
    return 0;
}

bool registrarVentas(int dias){
    ofstream ventas("output/ventas.txt");

    if(!ventas){
        cerr<<"\nEl archivo ventas.txt no se abrio correctamente. RegistrarVentas\n";
        return false;
    }

    if(dias<=0){    //para evitar problemas con funciones
        cerr<<"\nDias a registrar no valido\n";
        ventas.close();
        return false;
    }

    float monto;    //se alamacenara los montos de cada dia
    cout<<endl;
    for(int i=0; i<dias; i++){
        cout<<"Ingrese el monto de las ventas del dia "<<i+1<<": ";
        cin>>monto; //del teclado a la variable

        ventas<<monto<<endl;    //de la variable al archivo
    }

    cout<<"\nVentas registradas!\n";
    ventas.close(); //cerramos el archivo
    return true;    //ventas registradas
}

void realizarResumenVentas(int n){
    ofstream ventas("output/ventas.txt", ios::app); //para escribir

    if(!ventas){
        cerr<<"\nEl archivo ventas.txt no se abrio correctamente. RealizarResumen\n";
        return;
    }

    float *montos=almacenarMontosVentas(n);
    
    ventas<<"--------------------\n";
    ventas<<"RESUMEN\n";
    ventas<<"Total: "<<totalVentas(montos,n)<<endl;
    ventas<<"Promedio: "<<promedioVentas(montos,n)<<endl;
    ventas<<"Mayor venta: "<<mayorVenta(montos,n)<<endl;
    ventas<<"Menor venta: "<<menorVenta(montos,n);

    delete[] montos;    //liberamos memoria
    montos=nullptr;
}

float *almacenarMontosVentas(int n){
    ifstream lecturaVentas("output/ventas.txt"); //para leer

    if(!lecturaVentas){
        cerr<<"\nEl archivo ventas.txt no se abrio correctamente. AlmacenarMonto\n";
        return nullptr;
    }

    float *montos=new float[n]; //almacenamos en un arreglo
    for(int i=0; i<n; i++){
        lecturaVentas>>montos[i];
    }

    lecturaVentas.close();
    return montos;
}

float totalVentas(float *montos, int n){
    float suma=0;
    for(int i=0; i<n; i++) suma+=montos[i];
    return suma;
}

float promedioVentas(float *montos, int n){
    return totalVentas(montos,n)/n;
}

float mayorVenta(float *montos, int n){
    float maxVenta=*montos;
    for(int i=1; i<n; i++){
        if(montos[i]>maxVenta){
            maxVenta=montos[i];
        }
    }
    return maxVenta;
}

float menorVenta(float *montos, int n){
    float minVenta=*montos;
    for(int i=1; i<n; i++){
        if(montos[i]<minVenta){
            minVenta=montos[i];
        }
    }
    return minVenta;
}
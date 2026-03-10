#include<iostream>
#include<fstream>
using namespace std;

int totalEstudiantes(ifstream &txt);
float *generarArregloNotas(int &n);
void generarReporte(float *notas, int n);
float promedio(float *notas, int n);
void maxYminNotas(float *notas, int n, float &maxNota, float &minNota);
void estadoEstudiantes(float *notas, int n, int &aprob, int &desaprob);
void liberarNotas(float *&notas);

int main(){
    int n;
    float *notas=generarArregloNotas(n);
    if(notas==nullptr) return 1;    //si no abre, termina programa

    generarReporte(notas,n);    //genera el reporte en reporte.txt

    liberarNotas(notas);    //libera la memoria creada para almacenar notas

    return 0;
}

int totalEstudiantes(ifstream &txt){
    int total=0, n;
    while(txt>>n){  //primera lectura total, puntero lectura al final
        total++;
    }
    return total;   //retorna el numero de estudiantes (numero de notas presentes leidas)
}

float *generarArregloNotas(int &n){
    ifstream txt("input/notas.txt");

    if(!txt){   //si no abre
        cerr<<"\nNo se abrio el archivo notas.txt\n";
        return nullptr;
    }

    n=totalEstudiantes(txt);

    float *notas=new float[n];  //arreglo dinamico de notas

    txt.clear();    //limpiamos el estado del flujo (similar a cin)
    txt.seekg(0);   //reiniciamos el puntero lectura al inicio de nuevo

    for(int i=0; i<n; i++){
        txt>>notas[i];  //alamacenamos en arreglo
    }

    cout<<"\nNotas registradas en el arreglo\n";

    txt.close();    //cerramos archivo utilizado para lectura
    return notas;   //retornamos el arreglo dinamico
}

void generarReporte(float *notas, int n){
    ofstream reporte("output/reporte.txt");

    if(!reporte){
        cerr<<"\nNo se abrio el archivo reporte.txt\n";
        return;
    }

    float maxNota, minNota;
    int aprobados, desaprobados;

    maxYminNotas(notas,n,maxNota,minNota);  //maximo y mininmo actualizados
    estadoEstudiantes(notas,n,aprobados,desaprobados);  //aprobados y desaprobados actualizados

    reporte<<"REPORTE GENERAL"; //contenido de reporte.txt
    reporte<<"\n--------------------";
    reporte<<"\nTotal estudiantes: "<<n;
    reporte<<"\nPromedio: "<<promedio(notas,n);
    reporte<<"\nMayor nota: "<<maxNota;
    reporte<<"\nMenor nota: "<<minNota;
    reporte<<"\nAprobados: "<<aprobados;
    reporte<<"\nDesaprobados: "<<desaprobados;

    cout<<"\nReporte generado!\n";
    reporte.close();    //cerramos archivo utilizado para escribir
}

float promedio(float *notas, int n){
    float suma=0;
    for(int i=0; i<n; i++){
        suma+=notas[i];
    }
    return suma/n;
}

void maxYminNotas(float *notas, int n, float &maxNota, float &minNota){
    maxNota=*notas; minNota=*notas; //actualizamos en su primer elemento
    for(int i=1; i<n; i++){
        if(notas[i]>maxNota) maxNota=notas[i];  //maxima nota hasta nota[i]
        else if(notas[i]<minNota) minNota=notas[i];  //minima nota hasta nota[i]
    }
}

void estadoEstudiantes(float *notas, int n, int &aprob, int &desaprob){
    aprob=0; desaprob=0;
    for(int i=0; i<n; i++){
        if(notas[i]>=10) aprob++;   //los aprobados aumentan
        else desaprob++;    //los desaprobados aumentan, ya que no aprobaron
    }
}

void liberarNotas(float *&notas){
    delete[] notas;
    notas=nullptr;
}
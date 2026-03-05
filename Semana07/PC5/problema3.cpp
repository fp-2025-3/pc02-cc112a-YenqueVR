#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>
using namespace std;

void generarGraficoSin5x(const char *nombre);

int main(){
    char nombre[]="output/grafico.txt";
    generarGraficoSin5x(nombre);
    return 0;
}

void generarGraficoSin5x(const char *nombre){
    ofstream grafico(nombre);
    if(!grafico){
        cerr<<"\nNo se abrio correctamente output/grafico.txt.\n";
        return;
    }

    cout<<"\nGenerando grafico sin(5x)...\n";

    float pi=3.1415;

    for(int fila=10; fila>=-10; fila--){
        float saltoX=(2*pi)/79;    //80 puntos entre 0 y 2*pi, 79 espacios en los 80 puntos

        grafico<<setw(4)<<(float)fila/10<<"  ";
        for(int colum=0; colum<80; colum++){    //recorre las 80 columnas de cada fila
            //multiplicado por 10 para obtener la unidad (1 unidad grafico = 0.1 unidades funcion sin()) y convertido a int para el entero
            if((int)(sin(5*(saltoX*colum)) * 10) == fila) grafico<<"*"; //la curva tiene mayor prioridad
            else if(fila==0) grafico<<"-";
            else if(colum==0) grafico<<"|";
            else grafico<<" ";
        }

        if(fila!=-10) grafico<<endl;    //para no hacer un salto de linea en la ultima linea
    }

    cout<<"\nGrafico de sin(5x) generada con exito!\n";
    grafico.close();
}
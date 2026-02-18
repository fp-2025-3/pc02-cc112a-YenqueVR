#include<iostream>
#include<ctime>
#include<iomanip>
#include<string>
using namespace std;

struct Seleccion {
    string nombre; //nombre de la seleccion
    int PG,PE,PP,GF,GC; //partidos ganados, empatados, perdidos, gole favor y en contra
    int puntaje,DG; //puntaje y diferencia de goles (DG=GF-GC)
    float rend; //rendimiento (rend(%)=100*(puntaje/max_puntaje)
};

Seleccion *generarSelecciones(int n, int pj);   //genera el arreglo de n selecciones
void tabla(Seleccion *s, int n);    //muestra los datos de las selecciones y campeon
void ordenarSeleccion(Seleccion *&s, int n);    //
void seleccionCampeon(Seleccion *s);
void liberarMemoria(Seleccion *&s);

int main(){
    int n=5, pj=100;
    Seleccion *sel=generarSelecciones(n,pj);
    ordenarSeleccion(sel,n);

    tabla(sel,n);
    liberarMemoria(sel);

    return 0;
}

Seleccion *generarSelecciones(int n, int pj){
    srand(time(NULL));
    Seleccion *s=new Seleccion[n];

    cout<<endl;
    for(int i=0; i<n; i++){
        s[i].GF=0; s[i].GC=0;   //goles a favor y en contra en 0
        s[i].PG=0; s[i].PE=0; s[i].PP=0;    //partidos ganados, empatados y perdidos en 0

        cout<<"Nombre de la seleccion "<<i+1<<": ";
        getline(cin,s[i].nombre);

        for(int j=0; j<pj; j++){    //los 100 partidos simulados, pj=100
            //goles a favor y en contra por cada partido
            int gf=rand()%6, gc=rand()%6;   //de 0 a 5 goles cada uno

            s[i].GF+=gf;    //acumulamos los goles a favor y en contra
            s[i].GC+=gc;

            if(gf>gc) s[i].PG++;        //acumulamos los partidos ganados, empatados o perdidos
            else if(gf<gc) s[i].PP++;
            else s[i].PE++;
        }

        s[i].DG=s[i].GF-s[i].GC;    //diferencia de goles
        s[i].puntaje=(s[i].PG*3 + s[i].PE); //puntaje
        s[i].rend=100*((float)(s[i].puntaje)/(pj*3));   //rendimiento

    }

    return s;   //retornamos el arreglo de selecciones
}

void ordenarSeleccion(Seleccion *&s, int n){
    for(int i=0; i<n-1; i++){   //ordenamiento burbuja
        for(int j=0; j<n-i-1; j++){
            if(s[j].puntaje==s[j+1].puntaje){   //si los puntajes son lo mismo, entonces
                if(s[j].DG==s[j+1].DG){ //si incluso la diferencia de goles son iguales
                    if(s[j].GF<s[j+1].GF){
                        swap(s[j],s[j+1]);  //cambio por goles a favor (GF)
                    }
                }else if(s[j].DG<s[j+1].DG){
                    swap(s[j],s[j+1]);  //cambio por diferencia de goles (DG)
                }
            }else if(s[j].puntaje<s[j+1].puntaje){
                swap(s[j],s[j+1]);  //cambio por puntaje
            }
        }
    }
}

void tabla(Seleccion *s, int n){
    cout<<fixed<<setprecision(1);   //precision de 1 decimal
    cout<<left<<endl;

    cout<<setw(20)<<"Seleccion"<<setw(5)<<"PG"<<setw(5)<<"PE"<<setw(5)<<"PP"; //encabezado de la tabla
    cout<<setw(5)<<"GF"<<setw(5)<<"GC"<<setw(5)<<"DG"<<setw(7)<<"Pts"<<"Rend(%)";
    cout<<"\n-----------------------------------------------------------------------\n";

    for(int i=0; i<n; i++){
        cout<<setw(20)<<s[i].nombre<<setw(5)<<s[i].PG<<setw(5)<<s[i].PE<<setw(5)<<s[i].PP;  //datos de la seleccion i
        cout<<setw(5)<<s[i].GF<<setw(5)<<s[i].GC<<setw(5)<<s[i].DG<<setw(7)<<s[i].puntaje<<s[i].rend;
        cout<<endl;
    }

    seleccionCampeon(s);    //mostramos al campeon de las selecciones
}

void seleccionCampeon(Seleccion *s){    //al ordenar, el campeon esta primero, en s[0] o *s
    cout<<"\nCAMPEON: "<<s->nombre<<" | Puntaje: "<<s->puntaje<<" | DG: "<<s->DG<<" | Rendimiento: "<<s->rend<<"%\n";
}
void liberarMemoria(Seleccion *&s){ //libera memoria dinamica del arreglo de selecciones
    delete[] s;
    s=nullptr;
}
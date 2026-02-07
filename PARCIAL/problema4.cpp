#include<iostream>
using namespace std;

void agregarEstudiante(int *&codigos, float *&promedios, int &cap, int &cant, int &cod);
void duplicarCapacidad(int *&codigos, float *&promedios, int &n);
void filtrarEstudiantes(int *&codigos, float *&promedios, int &cap, int &cant);
void mostrarEstudiantes(int *codigos, float *promedios, int cant);

int main(){
    int cap=1;  //capacidad del arreglo
    int cant=0;     //cantidad de alumnos en el arreglo
    int cod=101;    //codigo unico de cada alumno
    int *codigos=new int[cap];      //inicializamos el arreglo
    float *promedios=new float[cap];

    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);

    cout<<"\nEstudiantes registrados:\n";
    mostrarEstudiantes(codigos,promedios,cant);

    filtrarEstudiantes(codigos,promedios,cap,cant);
    cout<<"\nFiltrando estudiantes desaprobados...\n";

    cout<<"\nEstudiantes aprobados:\n";
    mostrarEstudiantes(codigos,promedios,cant);

    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);
    agregarEstudiante(codigos,promedios,cap,cant,cod);

    cout<<"\nEstudiantes registrados:\n";
    mostrarEstudiantes(codigos,promedios,cant);

    filtrarEstudiantes(codigos,promedios,cap,cant);
    cout<<"\nFiltrando estudiantes desaprobados...\n";

    cout<<"\nEstudiantes aprobados:\n";
    mostrarEstudiantes(codigos,promedios,cant);

    delete[] codigos;   //liberando memoria
    delete[] promedios;

    codigos=nullptr;
    promedios=nullptr;

    return 0;
}

void agregarEstudiante(int *&codigos, float *&promedios, int &cap, int &cant, int &cod){
    float prom;
    cout<<"\nAgregar estudiante";
    cout<<"\nCodigo: "<<cod<<" , Promedio: ";
    cin>>prom;

    *(codigos+cant)=cod;
    *(promedios+cant)=prom;

    cant++; //se registro un alumno
    cod++;  //avanzamos el numero del codigo

    if(cant>=cap) duplicarCapacidad(codigos,promedios,cap);  //duplicamos la capacidad si esta lleno
}

void filtrarEstudiantes(int *&codigos, float *&promedios, int &cap, int &cant){
    int aprobados=0;
    for(int i=0; i<cant; i++){
        if(*(promedios+i)>=10) aprobados++;
    }

    int *codigosAprob=new int[aprobados];   //creamos arreglos al tamaño exacto resultante
    float *promediosAprob=new float[aprobados];

    int j=0;
    for(int i=0; i<cant; i++){
        if(*(promedios+i)>=10){
            *(codigosAprob+j)=*(codigos+i);     //copiamos al nuevo bloque de memoria
            *(promediosAprob+j)=*(promedios+i); //los estudiantes que aprobaron
            j++;
        }
    }

    cap=aprobados;    //actualizamos el numero de estudiantes
    cant=aprobados;

    delete[] codigos;   //liberamos memoria original
    delete[] promedios;

    codigos=codigosAprob;   //asignamos la direccion del nuevo bloque de memoria
    promedios=promediosAprob;
}

void duplicarCapacidad(int *&codigos, float *&promedios, int &cap){
    cout<<"\nArreglo lleno ("<<cap<<" de "<<cap<<")";

    int *nuevoCodigo=new int[2*cap];  //codigo al doble de su capacidad
    float *nuevoPromedios=new float[2*cap];   //promedios al doble de su capacidad

    for(int i=0; i<cap; i++){     //copiamos los valores en el nuevo espacio
        *(nuevoCodigo+i)=*(codigos+i);
        *(nuevoPromedios+i)=*(promedios+i);
    }

    cap*=2;   //actualizamos el tamaño de los arreglos

    delete[] codigos;   //liberamos memoria de codigos original
    delete[] promedios;     //liberamos memoria de promedios original

    codigos=nuevoCodigo;    //reasignamos la nueva direccion del bloque redimensionado
    promedios=nuevoPromedios;

    cout<<"\nDuplicando capacidad...";
    cout<<"\nArreglo duplicado. Nueva capacidad de "<<cap<<endl;
}

void mostrarEstudiantes(int *codigos, float *promedios, int cant){
    for(int i=0; i<cant; i++){
        cout<<"Codigo: "<<*(codigos+i)<<" , Promedios: "<<*(promedios+i)<<endl;
    }
}
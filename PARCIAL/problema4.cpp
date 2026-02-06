#include<iostream>
using namespace std;

void agregarEstudiante(int *&codigos, float *&promedios, int &n, int &cod);
void duplicarCapacidad(int *&codigos, float *&promedios, int &n);
void filtrarEstudiantes(int *&codigos, float *&promedios, int &n);
void mostrarEstudiantes(int *codigos, float *promedios, int n, int pos);

int main(){
    int n=1;
    int cod=101;
    int *codigos=new int[n];
    float *promedios=new float[n];

    agregarEstudiante(codigos,promedios,n,cod);
    agregarEstudiante(codigos,promedios,n,cod);
    agregarEstudiante(codigos,promedios,n,cod);
    agregarEstudiante(codigos,promedios,n,cod);
    agregarEstudiante(codigos,promedios,n,cod);

    cout<<"\nEstudiantes registrados:\n";
    mostrarEstudiantes(codigos,promedios,n,cod);

    filtrarEstudiantes(codigos,promedios,n);
    cout<<"\nFiltrando estudiantes desaprobados...\n";

    cout<<"\nEstudiantes aprobados:\n";
    mostrarEstudiantes(codigos,promedios,n,cod);

    delete[] codigos;   //liberando memoria
    delete[] promedios;

    codigos=nullptr;
    promedios=nullptr;

    return 0;
}

void agregarEstudiante(int *&codigos, float *&promedios, int &n, int &cod){
    float prom;
    cout<<"\nAgregar estudiante";
    cout<<"\nCodigo: "<<cod<<" , Promedio: ";
    cin>>prom;

    *(codigos+(cod-100)-1)=cod;
    *(promedios+(cod-100)-1)=prom;

    if(cod-100>=n) duplicarCapacidad(codigos,promedios,n);  //duplicamos la capacidad si esta lleno

    cod++;  //avanzamos el numero del codigo
}

void filtrarEstudiantes(int *&codigos, float *&promedios, int &n){
    int aprobados=0;
    for(int i=0; i<n; i++){
        if(*(promedios+i)>=10) aprobados++;
    }

    int *codigosAprob=new int[aprobados];   //creamos arreglos al tamaño exacto resultante
    float *promediosAprob=new float[aprobados];

    int j=0;
    for(int i=0; i<n; i++){
        if(*(promedios+i)>=10){
            *(codigosAprob+j)=*(codigos+i);     //copiamos al nuevo bloque de memoria
            *(promediosAprob+j)=*(promedios+i); //los estudiantes que aprobaron
            j++;
        }
    }

    n=aprobados;    //actualizamos el numero de estudiantes

    delete[] codigos;   //liberamos memoria original
    delete[] promedios;

    codigos=codigosAprob;   //asignamos la direccion del nuevo bloque de memoria
    promedios=promediosAprob;
}

void duplicarCapacidad(int *&codigos, float *&promedios, int &n){
    cout<<"\nArreglo lleno ("<<n<<" de "<<n<<")";

    int *nuevoCodigo=new int[2*n];  //codigo al doble de su capacidad
    float *nuevoPromedios=new float[2*n];   //promedios al doble de su capacidad

    for(int i=0; i<n; i++){     //copiamos los valores en el nuevo espacio
        *(nuevoCodigo+i)=*(codigos+i);
        *(nuevoPromedios+i)=*(promedios+i);
    }

    n*=2;   //actualizamos el tamaño de los arreglos

    delete[] codigos;   //liberamos memoria de codigos original
    delete[] promedios;     //liberamos memoria de promedios original

    codigos=nuevoCodigo;    //reasignamos la nueva direccion del bloque redimensionado
    promedios=nuevoPromedios;

    cout<<"\nDuplicando capacidad...";
    cout<<"\nArreglo duplicado. Nueva capacidad de "<<n<<endl;
}

void mostrarEstudiantes(int *codigos, float *promedios, int n, int cod){
    int limite;
    if(n<=(cod-100)-1){
        limite=n;
    }else {
        limite=cod-100-1;
    }
    for(int i=0; i<limite; i++){
        cout<<"Codigo: "<<*(codigos+i)<<" , Promedios: "<<*(promedios+i)<<endl;
    }
}
#include<iostream>
using namespace std;

struct Estudiante {
    int codigo;
    float promedio;
    char estado;
};

int cantidadEstudiantes(int &n);
Estudiante *registrarEstudiantes(int n);
Estudiante leerEstudiante(int i);
void mostrarEstudiante(Estudiante a);
void mostrarEstudiantesAprobados(Estudiante *a, int n);
void liberarMemoria(Estudiante *&a);

int main(){
    int n;
    if(cantidadEstudiantes(n)==-1) return 0;

    Estudiante *est=registrarEstudiantes(n);

    mostrarEstudiantesAprobados(est,n);

    liberarMemoria(est);

    return 0;
}

int cantidadEstudiantes(int &n){
    cout<<"\nCuantos estudiantes habra: ";
    cin>>n;
    if(n<=0){   //n debe ser mayor a cero
        cout<<"Numero no valido.";
        cout<<"\nTerminando programa";
        return -1;  //valor de error
    }
    return n;
}

Estudiante *registrarEstudiantes(int n){
    Estudiante *est=new Estudiante[n];  //creamos un arreglo de estudiantes

    for(int i=0; i<n; i++){
        est[i]=leerEstudiante(i);   //leemos los promedios de los estudiantes
    }

    return est;
}

Estudiante leerEstudiante(int i){
    Estudiante a;
    a.codigo=100+i+1;
    cout<<"\nEstudiante "<<i+1<<":";
    cout<<"\nCodigo: "<<a.codigo;

    while(true){    //repite hasta ingresar un promedio valido
        cout<<"\nPromedio: ";
        cin>>a.promedio;    //obtenemos el promedio

        if(a.promedio<0){   //cuando el promedio registrado es menor a 0
            cout<<"\nPromedio no valido, intentelo de nuevo.\n";
            continue;
        }

        cout<<endl;
        
        if(a.promedio>=10) a.estado='A';    //'A': aprobado
        else a.estado='D';  //'D': desaprobado

        break;
    }

    return a;
}

void mostrarEstudiante(Estudiante a){
    cout<<"\nCodigo Estudiante: "<<a.codigo;
    cout<<"\nPromedio: "<<a.promedio;
    cout<<endl;
}

void mostrarEstudiantesAprobados(Estudiante *a, int n){
    cout<<"\n\nEstudiantes aprobados:";
    for(int i=0; i<n; i++){
        if(a[i].estado=='A'){
            mostrarEstudiante(a[i]);
        }
    }
    cout<<endl;
}

void liberarMemoria(Estudiante *&a){
    delete[] a;
    a=nullptr;
}
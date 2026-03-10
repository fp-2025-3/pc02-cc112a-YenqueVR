#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Estudiante {
    int codigo;
    string nombre;
    float promedio;
    bool desaprobadoAcademico;
};

Estudiante *extraerTotalEstudiantes(const char *nombre, int &n);
void generarReporteNotas(const char *nombre);
float promedioGeneral(const Estudiante *e, int n);
void posEstudianteMayorYmenorPromedio(const Estudiante *e, int n, int &posMenor, int &posMayor);
void liberarEstudiantes(Estudiante *&est);

int main(){
    char nombre[]="input/notas.txt";
    generarReporteNotas(nombre);

    return 0;
}

Estudiante *extraerTotalEstudiantes(const char *nombre, int &n){
    ifstream file(nombre);
    if(!file){
        cerr<<"\nNo se abrio correctamente input/notas.txt.\n";
        return nullptr;
    }
   
    n=0;
    for(string linea; getline(file,linea); n++);   //cada linea pasada es un alumno

    file.clear();   //limpiamos  estado
    file.seekg(0,ios::beg); //movemos el puntero de lectura al inicio

    Estudiante *est=new Estudiante[n];  //realizamos un arreglo dinamico de estudiante

    for(int pos=0; pos<n; pos++){
        string cod,nomb,n1,n2,n3;

        getline(file,cod,' ');  //extraer codigo
        getline(file,nomb,' '); //extraer el bombre
        getline(file,n1,' ');   //extraer las notas
        getline(file,n2,' ');
        getline(file,n3);

        est[pos].codigo=stoi(cod);  //asignacion de datos a la estructura
        est[pos].nombre=nomb;

        float nota1=stof(n1),nota2=stof(n2),nota3=stof(n3);
        est[pos].promedio=(nota1+nota2+nota3)/3;

        if(nota1<5 || nota2<5 || nota3<5) est[pos].desaprobadoAcademico=true;
        else est[pos].desaprobadoAcademico=false;
    }

    file.close();
    return est;
}

void generarReporteNotas(const char *nombre){
    ofstream reporte("output/reporteAlumnos.txt");
    if(!reporte){
        cerr<<"\nNo se abrio correctamente output/reporteAlumnos.txt.\n";
        return;
    }

    cout<<"\nGenerando reporte...\n";

    int numEst=0;   //numero de estudiantes del archivo
    Estudiante *est=extraerTotalEstudiantes(nombre,numEst);

    if(est==nullptr) return;    //si no abre notas.txt

    reporte<<"=== REPORTE GENERAL DE ESTUDIANTES ===\n";
    reporte<<"\nTotal de estudiantes: "<<numEst<<endl;
    reporte<<"\nEstudiantes:\n";

    for(int i=0; i<numEst; i++){
        reporte<<"Codigo: "<<est[i].codigo<<" | Nombre: "<<est[i].nombre;
        reporte<<" | Promedio: "<<est[i].promedio<<" | Condicion: ";

        if(est[i].desaprobadoAcademico) reporte<<"DESAPROBADO POR REGLA ACADEMICA";
        else if(est[i].promedio>=10) reporte<<"APROBADO";
        else reporte<<"DESAPROBADO";
        reporte<<endl;
    }

    reporte<<"\n\nPromedio general del curso: "<<promedioGeneral(est,numEst)<<endl;

    int posMenor,posMayor;  //posicion del mayor y menor promedio 
    posEstudianteMayorYmenorPromedio(est,numEst,posMenor,posMayor);

    reporte<<"\nEstudiante con mayor promedio:\n";
    reporte<<"Codigo: "<<est[posMayor].codigo<<" | Nombre: "<<est[posMayor].nombre;
    reporte<<" | Promedio: "<<est[posMayor].promedio;
    reporte<<"\nEstudiante con menor promedio:\n";
    reporte<<"Codigo: "<<est[posMenor].codigo<<" | Nombre: "<<est[posMenor].nombre;
    reporte<<" | Promedio: "<<est[posMenor].promedio;

    cout<<"\nReporte generado exitosamente.\n";

    liberarEstudiantes(est);
    reporte.close();
}

float promedioGeneral(const Estudiante *e, int n){
    float sumaPromedioGeneral=0;
    for(int i=0; i<n; i++){
        sumaPromedioGeneral+=e[i].promedio; //suma los promedios de cada estudiante
    }

    return sumaPromedioGeneral/n;   //retorna el promedio de los promedios de los estudiantes
}

void posEstudianteMayorYmenorPromedio(const Estudiante *e, int n, int &posMenor, int &posMayor){
    posMenor=0; posMayor=0;
    float mayorProm=e->promedio, menorProm=e->promedio;
    for(int i=0; i<n; i++){
        if(mayorProm<e[i].promedio){
            mayorProm=e[i].promedio;
            posMayor=i;
        }else if(menorProm>e[i].promedio){
            menorProm=e[i].promedio;
            posMenor=i;
        }
    }
}

void liberarEstudiantes(Estudiante *&est){
    delete[] est;
    est=nullptr;
}
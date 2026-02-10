#include<iostream>
using namespace std;

void sistema(float *&notas, int &n);
void leerEstudiantes(int &n);
float *reservarMemoria(int n);
void redimensionarArreglo(float *&arr, int &n, int nuevos);
void leerNotas(float *arr, int inicio, int fin);
float calculoPromedioMinMax(float *arr, int n, float &min, float &max);
void mostrarPromedio(float prom, float min, float max);
void liberarMemoria(float *&arr);

int main(){
    int n;
    leerEstudiantes(n); //tamaño inicial del arreglo
    float *notas=reservarMemoria(n);

    if(notas==nullptr){
        cout<<"\nTerminando programa...\n";
        return 0;
    }

    sistema(notas,n);

    return 0;
}

void sistema(float *&notas, int &n){

    leerNotas(notas,0,n);

    float prom, maxNota, minNota;
    int opc;

    do{
        cout<<"\n=== ¿Que desea realizar?\n";
        cout<<"\n1. Agregar estudiantes";
        cout<<"\n2. Ver promedio, maximo y minimo";
        cout<<"\n3. Salir";
        cout<<"\n\nOpc --> "; cin>>opc;

        switch(opc){
            case 1: int k;
            leerEstudiantes(k);
            redimensionarArreglo(notas,n,k);
            break;

            case 2: prom=calculoPromedioMinMax(notas,n,minNota,maxNota);
            mostrarPromedio(prom,minNota,maxNota);
            break;
            
            case 3:
            cout<<"\nTerminando programa...\n";
            break;

            default:
            cout<<"\nOpcion no valida\n";
            break;
        }
    }while(opc!=3);

    liberarMemoria(notas);
}

void leerEstudiantes(int &n){
    cout<<"\nIngrese el numero de estudiantes a agregar: ";
    cin>>n;
}

float *reservarMemoria(int n){
    if(n<=0){
        cout<<"\nNo es un numero valido de estudiantes\n";
        return nullptr;
    }

    return new float[n];
}

void leerNotas(float *arr, int inicio, int fin){
    cout<<"\nIngrese las notas de cada estudiante (0-20):\n";
    for(float *ptr=arr+inicio; ptr<arr+fin; ptr++){
        cout<<"Estudiante "<<(ptr-arr)+1<<": ";
        cin>>*ptr;
    }
}

void redimensionarArreglo(float *&arr, int &n, int nuevos){
    if(nuevos<=0){
        cout<<"\nNo es un numero valido para agregar estudiantes\n";
        return;
    }

    float *newArr=reservarMemoria(n+nuevos);    //asignamos mas memoria al nuevo arreglo

    for(int i=0; i<n; i++){
        *(newArr+i)=*(arr+i);   //copiamos valores al nuevo arreglo
    }
    
    leerNotas(newArr,n,n+nuevos);   //leemos las notas de los nuevos
    n+=nuevos;  //actualizamos el tamaño del arreglo

    liberarMemoria(arr);    //liberamos memoria de arr
    arr=newArr; //asignamos la direccion del nuevo arreglo

    cout<<"\nEstudiantes agregados con exito...\n";
}

float calculoPromedioMinMax(float *arr, int n, float &min, float &max){
    float suma=0;
    min=*arr; max=*arr; //asignamos al min y max

    for(float *p=arr; p<arr+n; p++){
        suma+=*p;
        if(*p>max) max=*p;  //actualizamos max
        if(*p<min) min=*p;  //actualizamos min
    }
    return suma/n;
}

void mostrarPromedio(float prom, float min, float max){
    cout<<"\nNota promedio de estudiantes: "<<prom;
    cout<<"\nLa nota minima es: "<<min;
    cout<<"\nLa nota maxima es: "<<max;
    cout<<endl;
}

void liberarMemoria(float *&arr){
    delete[] arr;
    arr=nullptr;
}
#include<iostream>
using namespace std;

void sistema(int *&codigos, float *&promedios, int &cap);
void agregarEstudiante(int *&codigos, float *&promedios, int &cap, int &cant, int &cod);
void duplicarCapacidad(int *&codigos, float *&promedios, int &n);
void filtrarEstudiantes(int *&codigos, float *&promedios, int &cap, int &cant);
void mostrarEstudiantes(int *codigos, float *promedios, int cant);
int opciones();

int main(){
    int cap=1;  //capacidad del arreglo
    int *codigos=new int[cap];      //inicializamos el arreglo
    float *promedios=new float[cap];

    sistema(codigos,promedios,cap);

    return 0;
}

void sistema(int *&codigos, float *&promedios, int &cap){
    int cant=0;     //cantidad de alumnos en el arreglo
    int cod=101;    //codigo unico de cada alumno
    int opc;

    agregarEstudiante(codigos,promedios,cap,cant,cod);

    do{
        opc=opciones();
        if(cin.fail()){ //para lecturas no validas
            cin.clear();
            cin.ignore(50,'\n');
            opc=-1; //codigo de error
        }

        switch(opc){
            case 1: agregarEstudiante(codigos,promedios,cap,cant,cod);
            break;

            case 2:
            if(cant>0 && cap>1){
                cout<<"\nEstudiantes registrados:\n";
                mostrarEstudiantes(codigos,promedios,cant);
            }else cout<<"\nNo hay estudiantes registrados\n";
            break;

            case 3:
            cout<<"\nFiltrando estudiantes desaprobados...\n";
            filtrarEstudiantes(codigos,promedios,cap,cant);
            if(cant>0){
                cout<<"\nEstudiantes aprobados:\n";
                mostrarEstudiantes(codigos,promedios,cant);
            }
            break;

            case 4:
            cout<<"\nSaliendo...\n";
            break;

            default:
            cout<<"\nOpcion no valida\n";
            break;
        }
    }while(opc!=4);

    delete[] codigos;   //liberando memoria
    delete[] promedios;
    codigos=nullptr;    //evitamos punteros colgantes
    promedios=nullptr;

    cout<<"\nHa salido del programa\n";
}

int opciones(){
    int opc;
    cout<<"\n === Que desea realizar? ===";
    cout<<"\n1. Agregar un estudiante";
    cout<<"\n2. Mostrar estudiantes";
    cout<<"\n3. Filtrar estudiantes";
    cout<<"\n4. Salir";
    cout<<"\nOpcion --> ";
    cin>>opc;
    return opc;
}

void agregarEstudiante(int *&codigos, float *&promedios, int &cap, int &cant, int &cod){
    //lo pongo aqui para evaluar si esta lleno antes de registrarlo
    //usado unicamente despues de un filtrado de estudiantes
    if(cant>=cap) duplicarCapacidad(codigos,promedios,cap);  //duplicamos la capacidad si esta lleno

    while(true){
        float prom;
        cout<<"\nAgregar estudiante";
        cout<<"\nCodigo: "<<cod<<" , Promedio: ";
        cin>>prom;

        if(cin.fail()){ //para lecturas no validas
            cin.clear();
            cin.ignore(50,'\n');
            cout<<"\nNo se ingreso un promedio valido, intentelo de nuevo\n";
            continue;
        }
        if(prom<0){ //para promedios menor a 0
            cout<<"\nNo se ingreso un promedio valido, intentelo de nuevo\n";
            continue;
        }

        *(codigos+cant)=cod;
        *(promedios+cant)=prom;
        break;
    }

    cant++; //se registro un alumno
    cod++;  //avanzamos el numero del codigo

    //usado unicamente despues del registro de un estudiante
    if(cant>=cap) duplicarCapacidad(codigos,promedios,cap);  //duplicamos la capacidad si esta lleno
}

void filtrarEstudiantes(int *&codigos, float *&promedios, int &cap, int &cant){
    int aprobados=0;
    for(int i=0; i<cant; i++){
        if(*(promedios+i)>=10) aprobados++; //aumentamos la cantidad de aprobados
    }

    if(aprobados==0){
        if(cant==0 && cap==1){
            cout<<"No hay estudiantes registrados para filtrar\n";
            return;
        }
        cout<<"No hay estudiantes aprobados\n"; //evita que forme arreglos dinamicos con new int[0]
        cap=1;  //actualizamos la capacidad a 1
        cant=0; //actualizamos la cantidad de estudiantes a 0;

        delete[] codigos;   //liberamos memoria de ls arreglos
        delete[] promedios; //ya que nadie ha aprobado

        codigos=new int[cap];   //asignamos un nuevo bloque de memoria
        promedios=new float[cap];   //donde se pueda registrar un nuevo alumno
        return;
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
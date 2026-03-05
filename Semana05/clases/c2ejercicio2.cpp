#include<iostream>
#include<string>
using namespace std;

struct Estudiante {
    string nombre;
    float nota;
};

int numeroEstudiantes(int &n);
Estudiante *registrarEstudiantes(int n);
void NotaMasAlta(const Estudiante *e, int n);
void liberarMemoria(Estudiante *&e);

int main(){
    int n;
    if(numeroEstudiantes(n)==-1) return 0;

    Estudiante *est=registrarEstudiantes(n);

    NotaMasAlta(est,n);

    liberarMemoria(est);

    return 0;
}

int numeroEstudiantes(int &n){
    cout<<"\nIngrese el numero de estudiantes: ";
    cin>>n;

    if(n<=0){   //no aceptamos numeros menores o iguales a cero
        cout<<"No es numero valido para registrar.\n";
        return -1;  //numero de error
    }
    return n;   //retorna el numero n valido
}

Estudiante *registrarEstudiantes(int n){
    Estudiante *e=new Estudiante[n];

    for(int i=0; i<n; i++){
        cin.ignore();   //despues de registrar el n y las notas
        cout<<"Ingrese el nombre del estudiante "<<i+1<<": ";
        getline(cin,e[i].nombre);

        while(true){    //repite hasta que la nota sea mayor o igual a 0
            cout<<"Ingrese la nota del estudiante "<<i+1<<": ";
            cin>>e[i].nota;

            if(e[i].nota<0){
                cout<<"\nNota no valida. Intentelo de nuevo\n";
                continue;
            }

            cout<<endl;
            break;
        }
    }

    return e;
}

void NotaMasAlta(const Estudiante *e, int n){
    Estudiante mejor=e[0];
    for(int i=0; i<n; i++){
        if(e[i].nota > mejor.nota){
            mejor=e[i];
        }
    }

    cout<<"El estudiante con la mayor nota es:";
    cout<<" "<<mejor.nombre<<" , Nota: "<<mejor.nota<<endl;
}

void liberarMemoria(Estudiante *&e){
    delete[] e;
    e=nullptr;
}
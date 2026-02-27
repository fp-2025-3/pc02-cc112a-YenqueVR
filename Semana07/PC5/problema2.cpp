#include<iostream>
#include<fstream>
using namespace std;

struct Empleado {
    int id;
    char nombre[30];
    double salario;
};

void buscarEmpleadoPorID(const char *archivo, int IDbuscado);
int totalEmpleados(const char *archivo);
void mostrarEmpleado(Empleado e);
bool modificarSalario(Empleado &e);
void mostrarTotalEmpleados(const char *archivo, int n);

int main(){
    int IDbuscado;
    cout<<"\nIngrese ID del empleado: ";
    cin>>IDbuscado;

    char archivo[]="output/empleados.dat";
    buscarEmpleadoPorID(archivo,IDbuscado);

    return 0;
}

void buscarEmpleadoPorID(const char *archivo, int IDbuscado){
    int numEmpleado=totalEmpleados(archivo);
    if(IDbuscado<=0 || IDbuscado>numEmpleado){
        cerr<<"\nNo existe empleado con ese numero de ID.\n";
        return;
    }

    fstream file(archivo, ios::in | ios::out | ios::binary);
    if(!file){
        cerr<<"\nNo se pudo abrir output/empleados.dat";
        return;
    }

    mostrarTotalEmpleados(archivo,numEmpleado);

    file.seekg((IDbuscado-1) * sizeof(Empleado), ios::beg); //posicionamos el puntero de lectura en el empleado buscado

    Empleado empleadoBuscado;
    file.read((char*)&empleadoBuscado, sizeof(Empleado));
    file.clear();

    mostrarEmpleado(empleadoBuscado);   //mostramos al empleado
    if(!modificarSalario(empleadoBuscado)) return;  //modificamos el salario
    
    file.seekp((IDbuscado-1) * sizeof(Empleado), ios::beg); //posicionamos el puntero de escritura en el empleado a modificar
    file.write((char*)&empleadoBuscado, sizeof(Empleado));
    file.close();

    cout<<"\nArchivo modificado exitosamente.\n";

    mostrarTotalEmpleados(archivo,numEmpleado);
}

int totalEmpleados(const char *archivo){
    ifstream file(archivo, ios::binary);
    if(!file){
        cerr<<"\nNo se pudo abrir output/empleados.dat";
        return -1;
    }

    int numEmpleados=0;
    for(Empleado e; file.read((char*)&e, sizeof(e)); numEmpleados++);

    file.close();
    return numEmpleados;
}

void mostrarEmpleado(Empleado e){
    cout<<"\n--- DATOS DEL EMPLEADO ---";
    cout<<"\nID: "<<e.id;
    cout<<"\nNombre: "<<e.nombre;
    cout<<"\nSalario: "<<e.salario<<endl;
}

bool modificarSalario(Empleado &e){
    double nuevoSalario;
    cout<<"\nIngrese nuevo salario: "; cin>>nuevoSalario;

    if(nuevoSalario<0){
        cerr<<"\nEl sb moalario no puede ser negativo. Operacion cancelada.\n";
        return false;
    }

    e.salario=nuevoSalario;
    cout<<"\nSalario actualizado correctamente.\n";

    return true;
}

void mostrarTotalEmpleados(const char *archivo, int n){
    ifstream file(archivo, ios::binary);
    if(!file){
        cerr<<"\nNo se pudo abrir output/empleados.dat";
        return;
    }

    Empleado *e=new Empleado[n];
    file.read((char*)e, sizeof(Empleado)*n);

    cout<<"\nEmpleados:\n";
    for(int i=0; i<n; i++){
        cout<<"ID: "<<e[i].id<<" | Nombre: "<<e[i].nombre<<" | Salario: "<<e[i].salario<<endl;
    }
    cout<<endl;

    file.close();

    delete[] e; //liberamos memoria
    e=nullptr;
}
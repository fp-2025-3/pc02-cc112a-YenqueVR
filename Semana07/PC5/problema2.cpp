#include<iostream>
#include<fstream>
using namespace std;

struct Empleado {
    int id;
    char nombre[30];
    double salario;
};

void buscarEmpleadoPorID(const char *archivo, int IDbuscado);
void mostrarEmpleado(Empleado e);
bool modificarSalario(Empleado &e);
void mostrarTotalEmpleados(const char *archivo);

int main(){
    int IDbuscado;
    cout<<"\nIngrese ID del empleado: ";
    cin>>IDbuscado;

    char archivo[]="output/empleados.dat";
    buscarEmpleadoPorID(archivo,IDbuscado);

    return 0;
}

void buscarEmpleadoPorID(const char *archivo, int IDbuscado){
    if(IDbuscado<=0){
        cerr<<"\nEl ID de los empleados es mayor a 0. Busqueda cancelada.\n";
        return;
    }

    fstream file(archivo, ios::in | ios::out | ios::binary);
    if(!file){
        cerr<<"\nNo se pudo abrir output/empleados.dat";
        return;
    }

    int posicionEmpleado=(IDbuscado-1) * sizeof(Empleado);  //posicion del comienzo de la estructura del empleado buscado

    file.seekg(posicionEmpleado, ios::beg); //posicionamos el puntero de lectura en el empleado buscado

    Empleado empleadoBuscado;   //estructura creada para almacenar al empleado buscado
    file.read((char*)&empleadoBuscado, sizeof(Empleado));

    if(file.eof()){ //si llega al final o mas alla, detectara lectura invalida y saldra de la funcion
        file.clear();
        file.close();  
        cerr<<"\nNo se encontro un empleado con el ID proporcionado.\n";
        return;
    }

    mostrarEmpleado(empleadoBuscado);   //mostramos al empleado
    if(!modificarSalario(empleadoBuscado)) return;  //modificamos el salario
    
    file.seekp(posicionEmpleado, ios::beg); //posicionamos el puntero de escritura en el empleado a modificar
    file.write((char*)&empleadoBuscado, sizeof(Empleado));
    file.close();

    cout<<"\nSalario actualizado correctamente.\n";

    mostrarTotalEmpleados(archivo);     //despues de si es que se modifica el salario
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
        cerr<<"\nEl salario no puede ser negativo. Operacion cancelada.\n";
        return false;
    }else if(nuevoSalario==e.salario){
        cerr<<"\nEl salario no esta modificandose realmente. Operacion cancelada.\n";
        return false;
    }

    e.salario=nuevoSalario; //si es valido, el salario es modificado

    return true;
}

void mostrarTotalEmpleados(const char *archivo){
    ifstream file(archivo, ios::binary);
    if(!file){
        cerr<<"\nNo se pudo abrir output/empleados.dat";
        return;
    }

    cout<<"\nEmpleados:\n";
    for(Empleado e; file.read((char*)&e, sizeof(e));){  //lee cada empleado hasta el final
        cout<<"ID: "<<e.id<<" | Nombre: "<<e.nombre<<" | Salario: "<<e.salario<<endl;
    }
    cout<<endl;

    file.close();
}
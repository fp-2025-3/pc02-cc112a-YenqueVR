#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

void mostrarRegistros(const char *file);

int main(){
    char file[]="input/baseUNI.txt";
    mostrarRegistros(file);
    return 0;
}

void mostrarRegistros(const char *file){
    ifstream base(file);
    if(!base){
        cerr<<"\nNo se pudo abrir el archivo baseUNI.txt.\n";
        return;
    }

    cout<<left<<endl;
    cout<<setw(8)<<"Num"<<setw(16)<<"Apellidos"<<setw(8)<<"Nombre";
    cout<<setw(8)<<"Nota1"<<setw(8)<<"Nota2"<<"Promedio"<<endl;

    float promedioMax=-1;
    string alumnoMaxNombre, alumnoMaxApellido;

    string i,apellido,nombre,n1,n2;
    while(getline(base,i,'.')){
        getline(base,apellido,',');
        getline(base,nombre,'-');
        getline(base,n1,'-');
        getline(base,n2);

        int indice=stoi(i);
        float nota1=stof(n1), nota2=stof(n2);   //asignar notas
        float promedio=(nota1+nota2)/2;

        if(promedio>promedioMax){
            promedioMax=promedio;
            alumnoMaxNombre=nombre;
            alumnoMaxApellido=apellido;
        }

        cout<<setw(8)<<indice<<setw(16)<<apellido<<setw(8)<<nombre;
        cout<<setw(8)<<nota1<<setw(8)<<nota2<<promedio<<endl;
    }

    cout<<"\nEl promedio maximo: "<<promedioMax;
    cout<<"\nAlumno: "<<alumnoMaxNombre<<" "<<alumnoMaxApellido<<endl;
}
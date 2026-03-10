#include<iostream>
#include<fstream>
using namespace std;

const int MAX_LIBROS = 100;

struct Libro {
    int codigo;
    char titulo[50];
    bool prestado;
};

int opciones(int &opc);
void registrarLibro(Libro libros[], int &n);
int buscarLibro(Libro libros[], int n, int codigo);
void prestarLibro(Libro libros[],int n);
void devolverLibro(Libro libros[], int n);
void guardarEnArchivo(Libro libros[], int n);
void cargarDesdeArchivo(Libro libros[], int &n);
void mostrarLibros(Libro libros[], int n);
void presentarLibro(Libro l);

int main(){
    Libro libros[MAX_LIBROS];
    int n=0, opc, codigo, pos;

    do{
        switch(opciones(opc)){
            case 1: registrarLibro(libros,n);
            break;

            case 2:
            cout<<"\nIngrese el codigo del libro: "; cin>>codigo;
            if(codigo<0){
                cout<<"\nEl codigo no debe ser negativo.";
                cout<<"\nBuscar libro cancelado.\n";
                break;
            }
            pos=buscarLibro(libros,n,codigo);
            if(pos==-1){
                cout<<"\nBuscar libro cancelado.\n";
                break;
            }
            cout<<"\nLibro encontrado:\n";
            presentarLibro(libros[pos]);
            break;

            case 3: prestarLibro(libros,n);
            break;

            case 4: devolverLibro(libros,n);
            break;

            case 5: mostrarLibros(libros,n);
            break;

            case 6: guardarEnArchivo(libros,n);
            break;
            
            case 7: cargarDesdeArchivo(libros,n);
            break;

            case 8: cout<<"\nSaliendo...\n";
            break;

            default: cout<<"\nOpcion no valida.\n";
            break;
        }
    }while(opc!=8);

    cout<<"\nHa salido del sistema.\n";
    return 0;
}

int opciones(int &opc){
    cout<<"\n=============================================\n";
    cout<<"\n=== SISTEMA DE BIBLIOTECA ===";
    cout<<"\n1. Registrar libro.";
    cout<<"\n2. Buscar libro.";
    cout<<"\n3. Prestar libro.";
    cout<<"\n4. Devolver libro.";
    cout<<"\n5. Mostrar libros.";
    cout<<"\n6. Guardar en archivo.";
    cout<<"\n7. Cargar desde archivo.";
    cout<<"\n8. SALIR.";
    cout<<"\nOpcion --> ";
    cin>>opc;
    cout<<"\n=============================================\n";
    return opc;
}

void registrarLibro(Libro libros[], int &n){
    //la posicion n es donde se registrara el nuevo libro
    if(n==MAX_LIBROS){
        cout<<"\nSe alcanzo el numero maximo de libros";
        cout<<"\nRegistrar libro cancelado.\n";
        return;
    }

    Libro l;

    cout<<"\nIngrese el codigo del libro: "; cin>>l.codigo;
    if(l.codigo<0){
        cout<<"\nEl codigo no debe ser negativo.";
        cout<<"\nRegistrar libro cancelado.\n";
        return;
    }

    cin.ignore(50,'\n');    //avanzamos buffer
    cout<<"Ingrese el titulo del libro: "; cin.getline(l.titulo,50);

    if(cin.fail()){
        cin.clear();
        cin.ignore(50,'\n');
    }

    l.prestado=false;

    libros[n]=l;    //copiamos la informacion en el arreglo
    n++;    //actualizamos la cantidad de libros

    cout<<"\nLibro registrado exitosamente.\n";
}

int buscarLibro(Libro libros[], int n, int codigo){
    for(int i=0; i<n; i++){
        if(libros[i].codigo==codigo){
            cout<<"\nLibro encontrado exitosamente.\n";
            return i;
        }
    }

    cout<<"\nNo se encuentra un libro con ese codigo.\n";
    return -1;
}

void prestarLibro(Libro libros[],int n){
    int codigo;
    cout<<"\nIngrese el codigo del libro: "; cin>>codigo;
    if(codigo<0){   //verificar que el codigo no sea negativo
        cout<<"\nEl codigo no debe ser negativo.";
        cout<<"\nPrestar libro cancelado.\n";
        return;
    }

    int cod=buscarLibro(libros,n,codigo);
    if(cod==-1){    //verificar que existe el libro con ese codigo
        cout<<"\nPrestar libro cancelado.\n";
        return;
    }

    if(libros[cod].prestado){
        cout<<"\nEl libro ya ha sido prestado.";
        cout<<"\nPrestar libro cancelado.\n";
        return;
    }

    libros[cod].prestado=true;

    cout<<"\nLibro prestado exitosamente.\n";
}

void devolverLibro(Libro libros[], int n){
    int codigo;
    cout<<"\nIngrese el codigo del libro: "; cin>>codigo;
    if(codigo<0){   //verificar que el codigo no sea negativo
        cout<<"\nEl codigo no debe ser negativo.";
        cout<<"\nDevolver libro cancelado.\n";
        return;
    }

    int cod=buscarLibro(libros,n,codigo);
    if(cod==-1){    //verificar que existe el libro con ese codigo
        cout<<"\nDevolver libro cancelado.\n";
        return;
    }

    if(!libros[cod].prestado){
        cout<<"\nEl libro no ha sido prestado.";
        cout<<"\nDevolver libro cancelado.\n";
        return;
    }

    libros[cod].prestado=false;

    cout<<"\nLibro devuelto exitosamente.\n";
}

void mostrarLibros(Libro libros[], int n){
    cout<<"\n=== BIBLIOTECA ===\n";
    for(int i=0; i<n; i++){
        presentarLibro(libros[i]);
    }
}

void presentarLibro(Libro l){
    cout<<"Codigo: "<<l.codigo;
    cout<<" | Titulo: "<<l.titulo<<" | Estado: ";
    if(l.prestado) cout<<"Prestado";
    else cout<<"Disponible";
    cout<<endl;
}

void guardarEnArchivo(Libro libros[], int n){
    ofstream archivo("output/biblioteca.dat", ios::binary);
    if(!archivo){
        cout<<"\nNo se pudo abrir biblioteca.dat";
        cout<<"\nGuardar en archivo cancelado.\n";
        return;
    }

    for(int i=0; i<n; i++){
        archivo.write((char*)&libros[i], sizeof(Libro));
    }

    archivo.close();
    cout<<"\nGuardar en archivo realizado exitosamente.\n";
}

void cargarDesdeArchivo(Libro libros[], int &n){
    ifstream archivo("output/biblioteca.dat", ios::binary);
    if(!archivo){
        cout<<"\nNo se pudo abrir biblioteca.dat";
        cout<<"\nCargar desde archivo cancelado.\n";
        return;
    }

    while(archivo.read((char*)&libros[n], sizeof(Libro))){
        n++;
    }
    
    archivo.close();
    cout<<"\nCargar desde archivo realizado exitosamente.\n";
}
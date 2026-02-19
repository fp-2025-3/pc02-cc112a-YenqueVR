#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

struct Producto {
    int id;             // Identificador único
    char nombre[30];    // Nombre del producto
    double precio;      // Precio unitario
    int stock;          // Cantidad disponible
    bool activo;        // true = activo, false = eliminado lógicamente
};

int ID=100;

void registrarProducto(const char* nombreArchivo);
void mostrarProductos(const char* nombreArchivo);
int buscarProductoPorID(const char* nombreArchivo, int idBuscado);
void modificarPrecio(const char* nombreArchivo, int id, double nuevoPrecio);
void eliminarProducto(const char* nombreArchivo, int id);
double calcularValorInventario(const char* nombreArchivo);
void presentarProducto(Producto p);

int main(){

    return 0;
}

void registrarProducto(const char* nombreArchivo){
    Producto p; //declaramos para almacenar datos
    cin.ignore(50,'\n');    //despues de registrar cin>>opc o cin.fail

    cout<<"\nIngrese el nombre del producto: ";
    cin.getline(p.nombre,30);

    if(cin.fail()){ //si se escribe mas de 30 caracteres, queda sobrante en buffer
        cin.clear();
        cin.ignore(50,'\n');
    }

    if(strlen(p.nombre)==0){    //cuando no se escribio nada y solo enter
        cerr<<"\nNo tiene nombre registrado. No registrado.\n";
        return;
    }

    cout<<"Ingrese el precio del producto (precio>0) ";
    cin>>p.precio;
    cout<<"Ingrese el stock del producto (stock>=0): ";
    cin>>p.stock;

    if(cin.fail() || p.precio<=0 || p.stock<0){ //si falla en registrar o validar
        cerr<<"\nDatos mal ingresados. No registrado.\n";
        cin.clear();    //limpiar estado
        cin.ignore(50,'\n');    //avanzar en buffer, 
        return; //salir de la funcion de registrar
    }

    p.activo=true;  //actualizamos a verdadero
    p.id=ID;    //registramos el numero de id
    ID++;   //aumentamos el ID en uno

    ofstream inv(nombreArchivo, ios::app | ios::binary);    //abrir el archivo y escribir al final
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse.\n";
        return;
    }

    inv.write((char*)&p,sizeof(p)); //escribimos al final del archivo
    inv.close();    //cerrar archivo

    cout<<"\nProducto registrado exitosamente.\n";  //mensaje de producto registrado
}

void mostrarProductos(const char* nombreArchivo){
    ifstream inv(nombreArchivo, ios::binary);
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse.\n";
        return;
    }

    cout<<"\nPRODUCTOS:\n";

    Producto p;
    while(inv.read((char*)&p,sizeof(p))){   //lee todos los productos
        presentarProducto(p);   //muestra el producto
        cout<<" | Pos_Binario: "<<inv.tellg()-sizeof(p);  //posicion del inicio del producto (tellg muestra pos despues de recorrer p actual)
        cout<<endl;
    }

    inv.close();    //cerrar archivo
}

void presentarProducto(Producto p){
    cout<<"ID: "<<p.id<<" | "<<p.nombre<<" | Precio: "<<p.precio<<" | Stock: "<<p.stock;
}

int buscarProductoPorID(const char* nombreArchivo, int idBuscado){
    ifstream inv(nombreArchivo, ios::binary);
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse.\n";
        return;
    }

    Producto p; //declarado para almacenar datos
    while(inv.read((char*)&p,sizeof(p))){
        if(p.id==idBuscado){
            int pos=inv.tellg()-sizeof(p);   //posicion en el archivo
            inv.close();    //cerramos el archivo
            return pos;
        }
    }

    inv.close();    //cerrar archivo
    return -1;  //si no encuentra, devuelve -1
}

void modificarPrecio(const char* nombreArchivo, int id, double nuevoPrecio){
    //encontrar y extraer el producto en el archivo---------------------------------
    fstream inv(nombreArchivo, ios:: in | ios::out | ios::binary);  //leer y escribir en binario
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse.\n";
        return;
    }

    int pos=buscarProductoPorID(nombreArchivo,id);  //usado para encontrar el registro, y leer y escribir

    if(pos==-1){
        cerr<<"\nProducto no encontrado.\n";
        inv.close();    //cerrar archivo
        return;
    }

    Producto p; //Producto que almacenara los datos modificados
    inv.seekg(pos);    //nos posicionamos sobre el registro con acceso aleatorio
    inv.read((char*)&p,sizeof(p));  //leemos el registro donde se modifica el precio

    //modificar el producto en el archivo---------------------------------------
    p.precio=nuevoPrecio;   //modificamos el precio en el registro extraido
    
    inv.seekp(pos);    //nos movemos a la posicion del registro a modificar
    inv.write((char*)&p,sizeof(p));    //modificamos el registro con el precio cambiado
    inv.close();    //cerramos el archivo
}

void eliminarProducto(const char* nombreArchivo, int id){
    fstream inv(nombreArchivo, ios::in | ios::out | ios::binary);   //leer y escribir en binario
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse.\n";
        return;
    }

    int pos=buscarProductoPorID(nombreArchivo,id);  //usado para encontrar el registro, y leer y escribir

    if(pos==-1){
        cerr<<"\nProducto no encontrado. Asegurese de ingresar bien los datos\n";
        inv.close();    //cerrar archivo
        return;
    }

    Producto p; //Producto que almacenara los datos modificados
    inv.seekg(pos);    //nos posicionamos sobre el registro con acceso aleatorio
    inv.read((char*)&p,sizeof(p));  //leemos el registro donde se modifica el activo

    if(!p.activo){
        cout<<"\nEl producto estaba eliminado. Operacion cancelada.\n";
        inv.close();    //cerrar el archivo
        return;
    }

    //modificar el producto en el archivo---------------------------------------
    p.activo=false;   //modificamos el activo a falso en el registro extraido
    
    inv.seekp(pos);    //nos movemos a la posicion del registro a modificar
    inv.write((char*)&p,sizeof(p));    //modificamos el registro con el activo en falso
    inv.close();    //cerramos el archivo

    cout<<"\nProducto eliminado exitosamente.\n";
}

double calcularValorInventario(const char* nombreArchivo){

}

int menu(int &opc){
    cout<<"\n1. Registrar producto";
    cout<<"\n2. Mostrar productos";
    cout<<"\n3. Buscar producto";
    cout<<"\n4. Modificar precio";
    cout<<"\n5. Eliminar producto";
    cout<<"\n6. Calcular valor total";
    cout<<"\n7. Salir";
    cout<<"\nOpcion --> ";
    cin>>opc;
}
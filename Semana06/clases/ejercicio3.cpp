#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

//El sistema hace uso de cin.ignore y validaciones como cin.fail para tratar la contaminacion de otros
//caracteres y evitar caer en bucle por dato mal ingresado, soportado hasta 200 caracteres en cada ingreso

struct Producto {
    int id;             // Identificador único
    char nombre[30];    // Nombre del producto
    double precio;      // Precio unitario
    int stock;          // Cantidad disponible
    bool activo;        // true = activo, false = eliminado lógicamente
};

const int ID=100; //ID base

int asignarID(const char* nombreArchivo);
int menu(int &opc);
void sistema(const char *nombreArchivo);
void registrarProducto(const char* nombreArchivo);
void mostrarProductos(const char* nombreArchivo);
int buscarProductoPorID(const char* nombreArchivo, int idBuscado);
void modificarPrecio(const char* nombreArchivo, int id, double nuevoPrecio);
void eliminarProducto(const char* nombreArchivo, int id);
double calcularValorInventario(const char* nombreArchivo);
void presentarProducto(Producto p, int pos);

int main(){
    char archivo[]="output/inventario.dat";
    sistema(archivo);
    return 0;
}

int menu(int &opc){  //reposicionamiento en codigo de menu
    cout<<"\n========================================\n";
    cout<<"\n1. Registrar producto";
    cout<<"\n2. Mostrar productos";
    cout<<"\n3. Buscar producto";
    cout<<"\n4. Modificar precio";
    cout<<"\n5. Eliminar producto";
    cout<<"\n6. Calcular valor total";
    cout<<"\n7. Salir";
    cout<<"\nOpcion --> ";
    cin>>opc;
    cout<<"\n========================================\n";

    if(cin.fail() || opc<=0 || opc>7){
        cin.clear();
        cin.ignore(200,'\n');
        opc=-1; //numero de fallo
    }

    return opc;
}

void sistema(const char *nombreArchivo){
    int opc, id;
    double nuevoPrecio, valorInv;
    
    do{
        switch(menu(opc)){
            case 1: 
            cin.ignore(200,'\n');    //despues de registrar cin>>opc y borrar sobrantes no detectados
            registrarProducto(nombreArchivo);   //registrar un producto
            break;
            //=======================================================================================================
            case 2: mostrarProductos(nombreArchivo);    //mostrar los productos activos
            break;
            //=======================================================================================================
            case 3: //busqueda por ID
            cin.ignore(200,'\n');    //limpiar buffer si queda sobrantes despues de opc
            cout<<"\nIngrese el ID buscado (ID>=0): "; cin>>id;
            if(cin.fail() || id<0){
                cerr<<"\nDatos mal ingresados. Buscar Producto por ID cancelado.\n";
                cin.clear();    //limpiar estado
                break;  //la funcion menu limpiara el buffer
            }
            if(buscarProductoPorID(nombreArchivo,id)==-1){
                cerr<<"\nBuscar Producto por ID cancelado.\n"; //si no lo encuentra
                break;
            }
            break;
            //===========================================================================================================
            case 4: //modificar precio de un producto
            cin.ignore(200,'\n'); //limpiar buffer
            cout<<"\nIngrese el ID del producto (ID>=0): "; cin>>id;
            cout<<"Ingrese el nuevo precio del producto (precio>0): "; cin>>nuevoPrecio;
            if(cin.fail() || id<0 || nuevoPrecio<=0){
                cerr<<"\nDatos mal ingresados. Modificar precio cancelado.\n";
                cin.clear();    //limpiar estado
                break;  //la funcion menu limpiara el buffer
            }
            modificarPrecio(nombreArchivo,id,nuevoPrecio);
            break;
            //===========================================================================================================
            case 5: //eliminar un producto
            cin.ignore(200,'\n'); //limpiar buffer
            cout<<"\nIngrese el ID del producto a eliminar(ID>=0): "; cin>>id;
            if(cin.fail() || id<0){
                cerr<<"\nDatos mal ingresados. Modificar precio cancelado.\n";
                cin.clear();    //limpiar estado
                break;  //despues de switch limpiara el buffer
            }
            eliminarProducto(nombreArchivo,id);
            break;
            //===========================================================================================================
            case 6: //calcular el valor total de los productos no eliminados
            valorInv=calcularValorInventario(nombreArchivo);
            if(valorInv==-1) break;
            cout<<"\nEl valor total del inventario es: "<<valorInv;
            cout<<endl;
            break;
            //===========================================================================================================
            case 7: cout<<"\nSaliendo...\n";    //salir del programa
            break;
            //===========================================================================================================
            default: cout<<"\nOpcion no valida\n";  //continua en bucle para opc no validos
            break;
        }
        //para evitar doble cin.ignore cuando opc falla o getline solo capta '\n'
        if(opc!=-1 && opc!=1) cin.ignore(200,'\n');    //avanzar en buffer para borrar caracteres sobrantes o erroneos
    }while(opc!=7);
    cout<<"\nHa salido del programa.\n";
}

int asignarID(const char* nombreArchivo){
    ifstream inv(nombreArchivo, ios::binary);
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse. Asignar ID cancelado.\n";
        return -1;
    }

    int i=0;    //contador de estructuras presentes. Utilizado para hacer el ID automatico
    //Producto p: creado para contar el numero de estructuras presentes
    for(Producto p; inv.read((char*)&p,sizeof(p)); i++);    //cuenta las estructuras encontradas

    inv.close();    //cerrar archivo
    return ID+i;   //ID base + el numero de estructuras/ el primer registro el id es 100
}

void registrarProducto(const char* nombreArchivo){
    Producto p; //declaramos para almacenar datos

    cout<<"\nIngrese el nombre del producto: ";
    cin.getline(p.nombre,30);

    if(strlen(p.nombre)==0){    //cuando no se escribio nada y solo enter, no llevara cin.ignore por que lo detiene
        cin.clear();
        cerr<<"\nNo tiene un nombre registrado. Registrar producto cancelado.\n";
        return;
    }

    if(cin.fail()){ //si se escribe mas de 30 caracteres, queda sobrante en buffer
        cin.clear();
        cin.ignore(200,'\n');
    }

    cout<<"Ingrese el precio del producto (precio>0): ";
    cin>>p.precio;
    cout<<"Ingrese el stock del producto (stock>=0): ";
    cin>>p.stock;

    if(cin.fail() || p.precio<=0 || p.stock<0){ //si falla en registrar o validar
        cerr<<"\nDatos mal ingresados. Registrar producto cancelado.\n";
        cin.clear();    //limpiar estado
        cin.ignore(200,'\n');   //no limpiara despues de salir del switch
        return; //salir de la funcion de registrar
    }

    //creamos primero el archivo si no habia para que haya archivo que analizar en asignarID
    ofstream inv(nombreArchivo, ios::app | ios::binary);    //abrir el archivo y escribir al final
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse. Registrar producto cancelado.\n";
        return;
    }

    p.id=asignarID(nombreArchivo);  //asignamos un ID unico al producto
    if(p.id==-1) return;    //si no abrio el archivo, no genera ID y por tanto tampoco producto

    p.activo=true;  //actualizamos a verdadero

    inv.write((char*)&p,sizeof(p)); //escribimos al final del archivo
    inv.close();    //cerrar archivo

    cout<<"\nProducto registrado exitosamente.\n";  //mensaje de producto registrado
}

void mostrarProductos(const char* nombreArchivo){
    ifstream inv(nombreArchivo, ios::binary);
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse. Mostrar producto cancelado.\n";
        return;
    }

    cout<<"\nPRODUCTOS:\n";

    Producto p;
    while(inv.read((char*)&p,sizeof(p))){   //lee todos los productos
        if(p.activo){   //solo si no estan eliminados
            int pos=inv.tellg(); pos-=sizeof(p); //tellg muestra pos despues de recorrer p actual
            presentarProducto(p,pos);   //muestra el producto
        }
    }

    inv.close();    //cerrar archivo
}

void presentarProducto(Producto p, int pos){
    cout<<"ID: "<<p.id<<" | "<<p.nombre<<" | Precio: "<<p.precio<<" | Stock: "<<p.stock;
    cout<<" | Pos_Binario: "<<pos<<endl;  //posicion del inicio del producto
}

int buscarProductoPorID(const char* nombreArchivo, int idBuscado){
    ifstream inv(nombreArchivo, ios::binary);
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse. Operacion cancelada\n";
        return -1;
    }

    Producto p; //declarado para almacenar datos
    while(inv.read((char*)&p,sizeof(p))){
        if(p.id==idBuscado){
            int pos=inv.tellg(); pos-=sizeof(p);   //posicion en el archivo
            cout<<"\nProducto encontrado:\n";
            presentarProducto(p,pos);   //presentamos el producto encontrado
            inv.close();    //cerramos el archivo
            return pos;
        }
    }

    cout<<"\nProducto no encontrado.\n";
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
        cerr<<"\nModificar precio cancelado\n";
        inv.close();    //cerrar archivo
        return;
    }

    Producto p; //Producto que almacenara los datos modificados
    inv.seekg(pos);    //nos posicionamos sobre el registro con acceso aleatorio
    inv.read((char*)&p,sizeof(p));  //leemos el registro donde se modifica el precio

    if(p.precio==nuevoPrecio){
        cerr<<"\nEl producto no esta cambiando de precio realmente. Modificar precio cancelado.\n";
        inv.close();    //cerrar el archivo
        return;
    }

    //modificar el producto en el archivo---------------------------------------
    p.precio=nuevoPrecio;   //modificamos el precio en el registro extraido
    
    inv.seekp(pos);    //nos movemos a la posicion del registro a modificar
    inv.write((char*)&p,sizeof(p));    //modificamos el registro con el precio cambiado
    inv.close();    //cerramos el archivo

    cout<<"\nPrecio del producto ha sido modificado exitosamente.\n";
}

void eliminarProducto(const char* nombreArchivo, int id){
    //encontrar y extraer el producto en el archivo---------------------------------
    fstream inv(nombreArchivo, ios::in | ios::out | ios::binary);   //leer y escribir en binario
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse. Eliminar producto cancelado.\n";
        return;
    }

    int pos=buscarProductoPorID(nombreArchivo,id);  //usado para encontrar el registro, y leer y escribir

    if(pos==-1){
        cerr<<"\nEliminar producto cancelado.\n";
        inv.close();    //cerrar archivo
        return;
    }

    Producto p; //Producto que almacenara los datos modificados
    inv.seekg(pos);    //nos posicionamos sobre el registro con acceso aleatorio
    inv.read((char*)&p,sizeof(p));  //leemos el registro donde se modifica el activo

    if(!p.activo){
        cout<<"\nEl producto estaba eliminado. Eliminar producto cancelado.\n";
        inv.close();    //cerrar el archivo
        return;
    }

    //modificar el producto en el archivo---------------------------------------
    p.activo=false;   //modificamos el activo a falso en el registro extraido
    
    inv.seekp(pos);    //nos movemos a la posicion del registro a modificar
    inv.write((char*)&p,sizeof(p));    //modificamos el registro con el activo en falso
    inv.close();    //cerramos el archivo

    cout<<"\nProducto eliminado exitosamente.\n";   //mensaje de producto eliminado
}

double calcularValorInventario(const char* nombreArchivo){
    ifstream inv(nombreArchivo, ios::binary);   //leer y escribir en binario
    if(!inv){
        cerr<<"\nEl archivo inventario.dat no pudo abrirse. Calcular valor inventario cancelado.\n";
        return -1;
    }

    Producto p; //declarado para almacenar datos
    float suma=0;
    while(inv.read((char*)&p,sizeof(p))){
        if(p.activo){   //para los que no estan eliminados
            suma+=(p.precio * p.stock);
        }
    }

    inv.close();
    return suma;
}
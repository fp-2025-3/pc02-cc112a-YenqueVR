#include<iostream>
#include<cstring>
using namespace std;

struct Item {
    char *descripcion;
    int cantidad;
    double precioUnitario;
};

struct Pedido {
    int numeroPedido;
    char *nombreCliente;
    Item *items;
    int cantidadItems;
};

Item crearItem(const char *descripcion, int cantidad, double precio);
Pedido* crearPedido(int numero, const char *cliente, int cantidadItems);

int main(){
    int num=101, cantItems=3;
    char nombre[]="Carlos Perez";   //espacio suficiente

    Pedido *p1=crearPedido(num,nombre,cantItems);

    return 0;
}

Item crearItem(const char *descripcion, int cantidad, double precio){
    char *desc=new char[strlen(descripcion)+1]; //memoria para el nombre del item
    strcpy(desc,descripcion);   //copia segura de descripcion a desc

    Item p{desc,cantidad,precio};
    return p;   //retornamos un item inicializado
}

Pedido* crearPedido(int numero, const char *cliente, int cantidadItems){
    Pedido *p=new Pedido;   //reservamos memoria dinamica para un pedido

    p->nombreCliente=new char[strlen(cliente)+1];   //memoria para el nombre del cliente
    strcpy(p->nombreCliente,cliente); //copia segura de cliente a nombre

    p->numeroPedido=numero;     //actualizar numero de pedido
    p->cantidadItems=cantidadItems;     //actualizamos la cantidad de items en el pedido
    p->items=new Item[cantidadItems];   //reservamos memoria para los items del pedido

    cout<<"\nIngrese los datos requeridos para su pedido.";

    int i=0;
    while(i<cantidadItems){
        cin.ignore(100,'\n');   //limpiamos despues de cada cin o error

        char desc[100]; //espacio para la descripcion nombre del producto
        int cantItem;   //cantidad del item
        double precio;  //precio unitario del item

        cout<<"\nIngrese la descripcion del item "<<i+1<<": ";
        cin.getline(desc,100);

        cout<<"Ingrese el precio unitario del item "<<i+1<<": ";
        cin>>precio;

        cout<<"Ingrese la cantidad deseada del item "<<i+1<<": ";
        cin>>cantItem;

        if(cin.fail() || cantItem<=0 || precio<=0){     //si los datos estan mal
            cin.clear();
            cout<<"\nError al ingresar datos, intentelo de nuevo.\n";
            continue;
        }

        p->items[i]=crearItem(desc,cantItem,precio);    //inicializamos los item con la funcion
        i++;
    }
}
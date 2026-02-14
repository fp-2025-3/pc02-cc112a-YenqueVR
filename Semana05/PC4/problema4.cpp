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
double calcularTotal(const Pedido *p);
Item *itemMasCaro(Pedido *p);
void mostraPedidoYmas(const Pedido *p);

int main(){
    int num=101, cantItems=3;
    char nombre[]="Carlos Perez";   //espacio suficiente

    Pedido *p1=crearPedido(num,nombre,cantItems);

    return 0;
}

Item crearItem(const char *descripcion, int cantidad, double precio){
    char *desc=new char[strlen(descripcion)+1]; //memoria para el nombre del item
    strcpy(desc,descripcion);   //copia segura de descripcion a desc

    Item p{desc,cantidad,precio};   //inicializamos el item con los parametros
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

        if(cin.fail() || cantItem<=0 || precio<=0){     //si los datos estan mal o fallan
            cin.clear();
            cout<<"\nError al ingresar datos, intentelo de nuevo.\n";
            continue;   //continua al inicio del bucle en el mismo item
        }

        p->items[i]=crearItem(desc,cantItem,precio);    //inicializamos los item con la funcion
        i++;
    }

    return p;   //retorna un puntero a la memoria reservada para el pedido
}

double calcularTotal(const Pedido *p){
    double total=0; //el total iniicia en 0

    for(int i=0; i<p->cantidadItems; i++){  //recorre para cada item
        total+=(p->items[i].cantidad * p->items[i].precioUnitario); //precio y cantidad del item i
    }
    
    return total;   //retorna el total de los items
}

Item *itemMasCaro(const Pedido *p){
    double precioMasAlto=-1;    //precio por debajo de 0
    int indicePrecioMasAlto;    //indice para el item con mayor precio unitario

    for(int i=0; i<p->cantidadItems; i++){
        if(p->items[i].precioUnitario>precioMasAlto){
            precioMasAlto=p->items[i].precioUnitario;
            indicePrecioMasAlto=i;
        }
    }

    return (p->items)+indicePrecioMasAlto;  //puntero al item con precio unitario mas alto
}

void mostraPedidoYmas(const Pedido *p){
    cout<<"\nPedido N°: "<<p->numeroPedido;
    cout<<"\nCliente: "<<p->nombreCliente;

    cout<<"\n\nItems:\n";
    for(int i=0; i<p->cantidadItems; i++){  //tabla de items
        cout<<"- "<<p->items[i].descripcion<<" | Cant: "<<p->items[i].cantidad;
        cout<<" | Precio: "<<p->items[i].precioUnitario<<endl;
    }

    cout<<"\nTotal: "<<calcularTotal(p);

    Item *IMC=itemMasCaro(p);   //Item Mas Caro
    cout<<"\n\nItem mas caro: "<<IMC->descripcion<<" | "<<IMC->precioUnitario;
    cout<<endl;
}
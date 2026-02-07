#include<iostream>
#include<cstring>
using namespace std;

int numeroCorredores();
void sistema(char **&nombres, int *&tiempo, int n);
void registrarCorredores(char **nombres, int *tiempo, int n);
void datosCorredor(char **nombre, int *tiempo);
void ordenarRanking(char **nombres, int *tiempo, int n);
void rankingFinal(char **nombres, int *tiempo, int n);
void intercambiar(char **nombres1, int *tiempo1, char **nombres2, int *tiempo2);
void buscarCorredorPorNombre(char **nombres, int *tiempo, int n);   //funciona para mayusculas y minusculas por igual
void buscarCorredoresPorRango(char **nombres, int *tiempo, int n);
int opciones();
int compararNombres(char *nombres, char *temp);



int main(){
    int n=numeroCorredores();
    if(n==0) return 0;

    char **nombres=new char*[n];
    int *tiempo=new int[n];
    
    sistema(nombres,tiempo,n);

    return 0;
}

void sistema(char **&nombres, int *&tiempo, int n){
    registrarCorredores(nombres,tiempo,n);
    ordenarRanking(nombres,tiempo,n);
    rankingFinal(nombres,tiempo,n);

    int opc;
    do{
        opc=opciones();

        if(cin.fail()){ //detecta si hay error en el cin, ejm: cin>>opc="hola" -> no valido
            cin.clear();
            cin.ignore(50,'\n');
            opc=-1; //opcion de error
        }

        switch(opc){
            case 1: buscarCorredorPorNombre(nombres,tiempo,n);
            break;
            case 2: buscarCorredoresPorRango(nombres,tiempo,n);
            break;
            case 3:
            cout<<"\nSaliendo...\n";
            break;
            default:
            cout<<"\nNo es una opcion valida.\n";
            break;
        }
    }while(opc!=3);

    for(int i=0; i<n; i++){
        delete[] *(nombres+i);
        *(nombres+i)=nullptr;
    }
    delete[] nombres;   //liberamos memoria
    delete[] tiempo;
    nombres=nullptr;    //evitamos punteros colgantes
    tiempo=nullptr;

    cout<<"\nHa salido del programa.\n";
}

int numeroCorredores(){
    int n;
    cout<<"\nCuanto corredores desea registrar? (1-30): ";
    cin>>n;
    if(n<1 || n>30){
        cout<<"\nEl numero esta fuera del rango permitido.\n";
        return 0;
    }
    return n;   //devuelve el numero de corredores valido
}

void registrarCorredores(char **nombres, int *tiempo, int n){
    for(int i=0; i<n; i++){
        cin.ignore(50,'\n');   //limpiar buffer del anterior cin de n o tiempo

        while(true){
            char temp[20];
            cout<<"Nombre del corredor "<<i+1<<": ";
            cin.getline(temp,20);   //obtenemos el nombre

            //puesto dado que no registra bien con mas de 20 caracteres
            if(cin.fail()){     //si se excede los 20 caracteres incluyendo caracter nulo
                cin.clear();    //limpiamos el estado de fail
                cin.ignore(50,'\n');    //ignoramos lo sobrante del buffer
            }

            int tam=strlen(temp);   //obtenemos el tamaño del nombre
            if(tam==0){
                cout<<"No se registro un nombre, intentelo de nuevo\n\n";
                continue;    //si no hay texto, nos vuelve a pedir ingresar de nuevo
            }

            *(nombres+i)=new char[tam+1];   //creamos espacio de memoria

            //copiamos el nombre del corredor en nombres
            strcpy(*(nombres+i),temp);
            break;
        }

        while(true){
            int t;
            cout<<"Tiempo (en segundos): ";
            cin>>t; //obtenemos el tiempo del corredor

            if(cin.fail()){
                cin.clear();
                cin.ignore(50,'\n');
                cout<<"Entrada de tiempo invalido, intentelo de nuevo\n\n";
                continue;
            }

            if(t<0){
                cout<<"No puedes registrar un tiempo negativo, intentelo de nuevo\n\n";
                continue;
            }
            *(tiempo+i)=t;
            break;
        }
        cout<<endl;
    }
}

void ordenarRanking(char **nombres, int *tiempo, int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(*(tiempo+j)>*(tiempo+(j+1))){
                intercambiar(nombres+j,tiempo+j,nombres+j+1,tiempo+j+1);
            }
        }
    }
}

void intercambiar(char **nombres1, int *tiempo1, char **nombres2, int *tiempo2){
    char *tempN=*nombres1;
    int tempT=*tiempo1;
    *nombres1=*nombres2; *tiempo1=*tiempo2;
    *nombres2=tempN; *tiempo2=tempT;
}

void datosCorredor(char **nombre, int *tiempo){
    cout<<*nombre<<" - "<<*tiempo<<" segundos"<<endl;
}

void rankingFinal(char **nombres, int *tiempo, int n){
    cout<<"\nRANKING FINAL\n";
    for(int i=0; i<n; i++){
        cout<<i+1<<". ";
        datosCorredor(nombres+i,tiempo+i);
    }
}

int opciones(){
    int opc;
    cout<<"\n === Que desea realizar? ===";
    cout<<"\n1. Buscar corredor por nombre";
    cout<<"\n2. Buscar corredores por rango de tiempo";
    cout<<"\n3. Salir";
    cout<<"\nOpcion --> ";
    cin>>opc;
    return opc;
}

void buscarCorredorPorNombre(char **nombres, int *tiempo, int n){
    cin.ignore(50,'\n');
    char temp[20];
    cout<<"\nIngrese el nombre a buscar: ";
    cin.getline(temp,20);

    if(cin.fail()){ //si supera los 20 caracteres
        cin.clear();
        cin.ignore(50,'\n');
    }

    for(int i=0; i<n; i++){
        if(compararNombres(*(nombres+i),temp)==0){
            cout<<"Corredor encontrado";
            cout<<"\nPosicion: "<<i+1;
            cout<<"\nTiempo: "<<*(tiempo+i);
            cout<<endl;
            return;
        }
    }

    cout<<"Corredor no encontrado";
    cout<<"\nVerifique si escribio correctamente el nombre\n";
}

void buscarCorredoresPorRango(char **nombres, int *tiempo, int n){
    cin.ignore(50,'\n');
    int Tmax, Tmin;
    cout<<"\nIngrese el tiempo minimo y maximo: ";
    cout<<"\nTiempo minimo: "; cin>>Tmin;
    cout<<"Tiempo maximo: "; cin>>Tmax;

    if(Tmin<0 || Tmax<0 || Tmin>Tmax){
        cout<<"\nNo es un intervalo de tiempo adecuado\n";
        return;
    }

    cout<<"Corredores en el rango ["<<Tmin<<", "<<Tmax<<"]:\n";
    for(int i=0; i<n; i++){
        if(*(tiempo+i)>=Tmin && *(tiempo+i)<=Tmax){
            cout<<*(nombres+i)<<" - "<<*(tiempo+i)<<" segundos\n";
        }
    }
}

int compararNombres(char *nombres, char *temp){
    char a=*nombres, b=*temp;
    for(; *nombres!='\0' && *temp!='\0'; nombres++, temp++){
        a=*nombres; b=*temp;
        if(a>='A' && a<='Z') a+=32; //convierte a minusculas
        if(b>='A' && b<='Z') b+=32;
        if(a!=b) return a-b;    //retorna la diferencia si no son iguales
    }
    a=*nombres; b=*temp;
    if(a>='A' && a<='Z') a+=32; //convierte a minusculas
    if(b>='A' && b<='Z') b+=32;
    if(a!=b) return a-b;    //retorna la diferencia si no son iguales

    return 0;   //retorna 0 si las dos cadenas son iguales
}
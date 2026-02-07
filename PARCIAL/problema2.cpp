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
void buscarCorredorPorNombre(char **nombres, int *tiempo, int n);
void opciones(int &opc);



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
        opciones(opc);
        switch(opc){
            case 1: buscarCorredorPorNombre(nombres,tiempo,n);
            break;
            case 2:
            break;
            case 3:
            cout<<"\nSaliendo...\n";
            break;
            default:
            cout<<"\nNo es una opcion valida.\n";
            break;
        }
    }while(opc!=3);
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
        cout<<"Nombre del corredor "<<i+1<<": ";
        char temp[20];
        cin.ignore();   //limpiar buffer del anterior cin   
        cin.getline(temp,20);   //obtenemos el nombre

        int tam=strlen(temp);   //obtenemos el tamaño del nombre
        *(nombres+i)=new char[tam+1];   //creamos espacio de memoria

        //copiamos el nombre del corredor en nombres
        for(char *p=temp; p<=temp+tam; p++){
            *(*(nombres+i)+(p-temp))=*p;    //copiado con todo caracter nulo
        }

        //puesto dado que no registra bien con mas de 20 caracteres
        if(cin.fail()){     //si se excede los 20 caracteres incluyendo caracter nulo
            cin.clear();    //limpiamos el estado de fail
            cin.ignore(50,'\n');    //ignoramos lo sobrante del buffer
        }

        int t;
        cout<<"Tiempo (en segundos): ";
        cin>>t; //obtenemos el tiempo del corredor
        *(tiempo+i)=t;

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

void opciones(int &opc){
    cout<<"\n === ¿Que desea realizar? ===";
    cout<<"\n1. Buscar corredor por nombre";
    cout<<"\n2. Buscar corredores por rango de tiempo";
    cout<<"\n3. Salir";
    cout<<"\nOpcion --> ";
    cin>>opc;
}

void buscarCorredorPorNombre(char **nombres, int *tiempo, int n){
    char temp[20];
    cout<<"\nIngrese el nombre a buscar: ";
    cin.getline(temp,20);

    for(int i=0; i<n; i++){
        if(strcmp(*(nombres+i),temp)==0){
            cout<<"Corredor encontrado";
            cout<<"\nPosicion: "<<i+1;
            cout<<"\nTiempo: "<<*(tiempo+i);
            cout<<endl;
            return; //cuando lo encuentra sale del bucle y la funcion
        }
    }
    //si no lo encuentra, continual hacia al mensaje de no encontrado
    cout<<"Corredor no encontrado";
    cout<<"\nVerifique si escribio correctamente el nombre\n";
}

void buscarCorredoresPorRango(char **nombres, int *tiempo, int n){
    int Tmax, Tmin;
    cout<<"\nIngrese el tiempo minimo y maximo: ";
    cout<<"\nTiempo minimo: "; cin>>Tmin;
    cout<<"Tiempo maximo: "; cin>>Tmax;
    cout<<"Corredores en el rango ["<<Tmin<<", "<<Tmax<<"]:";
}
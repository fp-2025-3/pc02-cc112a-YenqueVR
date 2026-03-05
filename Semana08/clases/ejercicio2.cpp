#include <iostream>
#include <fstream>
using namespace std;

struct CuentaBancaria {
    int numeroCuenta;
    char titular[40];
    double saldo;
    bool activa=false;
};

int opciones(int &opc);
int ingresarNumCuentas(int &N);
bool crearArchivo(int N);
CuentaBancaria buscarCuenta(fstream &archivo, int numeroCuenta);
bool agregarCuentaArchivo(fstream &archivo, CuentaBancaria &cuenta);
void depositar(fstream &archivo, CuentaBancaria cuenta);
void retirar(fstream &archivo, CuentaBancaria cuenta);
void operacionCuenta(void (*operacion)(fstream&,CuentaBancaria));
void desactivarCuenta(fstream &archivo, int numeroCuenta);
void mostrarCuentasActivas(fstream &archivo);
void mostrarCuenta(CuentaBancaria cuenta);

int main(){
    int N;
    if(ingresarNumCuentas(N)==-1) return 1;

    if(!crearArchivo(N)) return 1;

    int opc;
    do{
        switch(opciones(opc)){
            case 1: operacionCuenta(depositar);
            break;

            case 2: operacionCuenta(retirar);
            break;

            case 3:
            {fstream archivo("output/cuentas.dat", ios::binary|ios::out | ios::in);
            int numeroCuenta=0;
            cout<<"\nIngresa el numero de cuenta: "; cin>>numeroCuenta;
            if(numeroCuenta<=0){
                cerr<<"\nEl numero de cuenta debe ser positivo mayor a 0.\n";
                break;
            }
            desactivarCuenta(archivo,numeroCuenta);
            }
            break;

            case 4:
            {fstream archivo("output/cuentas.dat", ios::binary|ios::out | ios::in);
            int numeroCuenta=0;
            cout<<"\nIngresa el numero de cuenta: "; cin>>numeroCuenta;
            if(numeroCuenta<=0){
                cerr<<"\nEl numero de cuenta debe ser positivo mayor a 0.\n";
                break;
            }
            CuentaBancaria cuenta=buscarCuenta(archivo,numeroCuenta);
            if(cuenta.numeroCuenta==-1) break;
            mostrarCuenta(cuenta);

            archivo.close();
            }
            break;

            case 5:
            {fstream archivo("output/cuentas.dat", ios::binary|ios::out | ios::in);
            mostrarCuentasActivas(archivo);
            }
            break;

            case 6: cout<<"\nSaliendo...\n";
            break;

            default: cout<<"\nOpcion no valida.\n";
            break;
        }

    }while(opc!=6);

    cout<<"\nHa salido del programa.\n";

    return 0;
}

int opciones(int &opc){
    cout<<"\n==============================\n";
    cout<<"\n--- Menu ---";
    cout<<"\n1. Depositar.";
    cout<<"\n2. Retirar.";
    cout<<"\n3. Desactivar cuenta.";
    cout<<"\n4. Buscar cuentas.";
    cout<<"\n5. Mostrar cuentas activas.";
    cout<<"\n6. Salir.";
    cout<<"\nOpcion --> "; cin>>opc;

    if(cin.fail()){
        cin.clear();
        cin.ignore(50,'\n');
        opc=-1;
    }

    cout<<"\n==============================\n";
    return opc;
}

int ingresarNumCuentas(int &N){
    cout<<"\nIngrese el numero de cuentas a crear: "; cin>>N;
    if(N<=0){
        cout<<"\nNo es un valor admisible. Operacion terminada.\n";
        return -1;
    }
    return N;
}

bool crearArchivo(int N){
    fstream archivo("output/cuentas.dat", ios::binary|ios::out | ios::in);

    if (!archivo){  //Si no existe lo creamos abriendo en solo escritura
        archivo.open("output/cuentas.dat", ios::out | ios::binary);
        if(!archivo){
            cerr<<"\nNo existe la carpeta ouput.\n";
            return false;
        }
        archivo.close();    //Cerramos para despues abrirlo en escritura y lectura
        archivo.open("output/cuentas.dat", ios::binary | ios::out | ios::in);
    }

    CuentaBancaria cuenta;

    for(int i = 0; i < N; ++i){
        cout<<"\nNumero de cuenta "<<i+1<<": ";
        cin>>cuenta.numeroCuenta;

        if(cin.fail()){
            cin.clear();
            cin.ignore(50,'\n');
            i--;
            continue;
        }

        if(!agregarCuentaArchivo(archivo,cuenta)) i--;
    }

    archivo.close();
    return true;
}

CuentaBancaria buscarCuenta(fstream &archivo, int numeroCuenta){
    CuentaBancaria cuenta;    //Creamos para verificar la cuenta en esa posision
    int posicion=sizeof(CuentaBancaria)*(numeroCuenta-1);

    archivo.seekg(posicion, ios::beg);    //Movemos el puntero de lectura a posicion
    archivo.read((char*)&cuenta, sizeof(CuentaBancaria)); //leemos la cuenta de esa posicion

    if(!archivo){
        cerr<<"\nNo existe esta cuenta.\n";
        archivo.clear();    //Si fallo la lectura, debemos reestablecer los valores de archivo
        archivo.close();
        cuenta.numeroCuenta=-1;
    }else{  //como el archivo se pasa por referencia, el puntero de escritura permanece despúes de la funcion
        archivo.seekp(posicion, ios::beg);
        cout<<"\nCuenta encontrada.\n";
    }
    
    return cuenta;
}

bool agregarCuentaArchivo(fstream &archivo, CuentaBancaria &cuenta){
    if(cuenta.numeroCuenta<=0){
        cerr<<"\nEl numero de cuenta debe ser positivo mayor a 0.\n";
        return false;
    }

    int posicion=sizeof(CuentaBancaria) * (cuenta.numeroCuenta-1);
    
    CuentaBancaria temp;
    archivo.seekg(posicion, ios::beg);
    archivo.read((char*)&temp, sizeof(CuentaBancaria));

    if(archivo && temp.numeroCuenta==cuenta.numeroCuenta){
        cerr<<"\nYa existe una cuenta con este numero\n";
        return false;
    }

    archivo.clear();    //Si fallo la lectura, debemos reestablecer los valores de archivo

    cin.width(40);
    cout<<"Titular: "; cin>>cuenta.titular;
    cin.ignore(50,'\n');
    cout<<"Saldo: "; cin>>cuenta.saldo;
    
    if(cuenta.saldo<0){
        cerr<<"\nEl saldo debe ser mayor o igual a 0.\n";
        return false;
    }
    cuenta.activa=true;

    archivo.seekp(posicion);    //Mover el puntero de escritura
    archivo.write((char*)&cuenta, sizeof(CuentaBancaria));
    // No se pueden repetir numero de cuentas

    return true;
}

void depositar(fstream &archivo, CuentaBancaria cuenta){
    double deposito;
    cout<<"\nCuanto deseea depositar?: "; cin>>deposito;
    if(deposito<=0){
        cerr<<"\nEl deposito debe ser mayor a 0. Deposito cancelado.\n";
        return;
    }

    cuenta.saldo+=deposito; //actualizamos el saldo
    archivo.write((char*)&cuenta, sizeof(CuentaBancaria));  //modificamos en el archivo

    cout<<"\nDeposito realizado con exito.\n";
}

void retirar(fstream &archivo, CuentaBancaria cuenta){
    double retiro;
    cout<<"\nCuanto desea retirar?: "; cin>>retiro;
    if(retiro<=0){
        cerr<<"\nEl retiro debe ser mayor a 0. Retiro cancelado.\n";
        return;
    }
    if(retiro>cuenta.saldo){    //evita saldo negativo
        cerr<<"\nEl retiro excede su saldo disponible. Retiro cancelado.\n";
        return;
    }

    cuenta.saldo-=retiro;   //actualizamos el saldo
    archivo.write((char*)&cuenta, sizeof(CuentaBancaria));  //modificamos en el archivo

    cout<<"\nRetiro realizado con exito.\n";
}

void operacionCuenta(void (*operacion)(fstream&,CuentaBancaria)){
    double numeroCuenta;
    cout<<"\nIngrese el numero de cuenta: "; cin>>numeroCuenta;
    if(numeroCuenta<=0){
        cerr<<"\nEl numero de cuenta debe ser positivo mayor a 0.\n";
        return;
    }

    fstream archivo("output/cuentas.dat", ios::binary|ios::out | ios::in);

    CuentaBancaria cuenta=buscarCuenta(archivo,numeroCuenta);   //se copia uan estructura de cuenta
    if(cuenta.numeroCuenta==-1){
        archivo.close();
        return;
    }
    if(!cuenta.activa){ //si esta desactivada, no hace la operacion
        cerr<<"\nCuenta inactiva. Operacion denegada.\n";
        return;
    }

    //el puntero de escritura queda listo en la posicion al encontrar la cuenta
    operacion(archivo,cuenta);
}

void desactivarCuenta(fstream &archivo, int numeroCuenta){
    CuentaBancaria cuenta=buscarCuenta(archivo,numeroCuenta);
    if(cuenta.numeroCuenta==-1) return;

    if(!cuenta.activa){
        cerr<<"\nLa cuenta no estaba activada. Desactivacion cancelada.\n";
        archivo.close();
        return;
    }

    cuenta.activa=false;
    archivo.write((char*)&cuenta, sizeof(CuentaBancaria));
    archivo.close();

    cout<<"\nCuenta desactivada exitosamente.\n";
}

void mostrarCuentasActivas(fstream &archivo){
    archivo.seekg(0, ios::end);
    int tamArchivoCuentas=archivo.tellg()/sizeof(CuentaBancaria);
    archivo.clear();

    CuentaBancaria cuenta;

    cout<<"\nCuentas activas:\n";
    for(int posicion=0; posicion<tamArchivoCuentas; posicion++){
        archivo.seekg(sizeof(CuentaBancaria) * posicion, ios::beg);

        if(!archivo.read((char*)&cuenta, sizeof(CuentaBancaria))){
            archivo.clear();
            continue;
        }

        if(!cuenta.activa) continue;

        mostrarCuenta(cuenta);
    }

    archivo.close();
}

void mostrarCuenta(CuentaBancaria cuenta){
    cout<<"Numero Cuenta: "<<cuenta.numeroCuenta<<" | Titular: "<<cuenta.titular;
    cout<<" | Saldo: "<<cuenta.saldo<<" | Estado: ";
    if(cuenta.activa) cout<<"Activo";
    else cout<<"Desactivado";
    cout<<endl;
}
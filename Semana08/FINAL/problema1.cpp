#include<iostream>
using namespace std;

int** crearMatriz(int n, int m);
void llenarMatriz(int** M, int n, int m);
int *sumarFilas(int** M, int n, int m);
void mostrarMatriz(int** M, int n, int m);
void mostrarVector(int* V, int n);
void liberarMatriz(int** &M, int n);
void liberarVector(int* &V);

int main(){
    int n,m;
    cout<<"\nIngrese el tamaño de las filas: "; cin>>n;
    cout<<"Ingrese el tamaño de las columnas: "; cin>>m;

    if(n<=0 || m<=0){
        cerr<<"\nLos datos deben ser mayor a 0.\n";
        return 1;
    }

    int **M=crearMatriz(n,m);   //creamos a la matriz de doble puntero
    llenarMatriz(M, n, m);  //lenamos la matriz con el patron

    int *vectorResultante=sumarFilas(M,n,m);

    mostrarMatriz(M,n,m);
    mostrarVector(vectorResultante,n);

    liberarMatriz(M,n);
    liberarVector(vectorResultante);

    return 0;
}

int** crearMatriz(int n, int m){
    int **M = new int*[n];  //reservar memoria para arreglo punteros a enteros de tamaño n
    for(int i=0; i<n; i++){ //reservar memoria para arreglo de enteros de tamaño m
        M[i]=new int[m];
    }
    
    return M;
}

void llenarMatriz(int** M, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            M[i][j]=(i+1)*(j+1);    //llenando la matriz con el patron
        }
    }
}

int *sumarFilas(int** M, int n, int m){
    //inicializado en 0
    int *vector = new int[n]{0};   //reservar memoria para un arreglo de enteros de tamaño n

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            vector[i]+=M[i][j];
        }
    }

    return vector;
}

void mostrarMatriz(int** M, int n, int m){
    cout<<"\nMatriz M:\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<M[i][j];

            if(M[i][j]<10) cout<<"   "; //para controlar el orden en la matriz entre distintos digitos
            else if(M[i][j]<100) cout<<"  ";
            
            cout<<" ";
        }
        cout<<endl;
    }
}

void mostrarVector(int* V, int n){
    cout<<"\nVector resultante: { ";
    for(int i=0; i<n; i++){
        cout<<V[i]<<" ";
    }
    cout<<"};\n\n";
}

void liberarMatriz(int** &M, int n){    //por referencia para modificar a nullptr a M
    for(int i=0; i<n; i++){ //primero liberamos memoria de cada fila
        delete[] M[i];  
        M[i]=nullptr;
    }

    delete[] M; //despues liberamos a M
    M=nullptr;
}

void liberarVector(int* &V){
    delete[] V;
    V=nullptr;
}
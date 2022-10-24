#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include "ArbolBinario.h"
using namespace std;

template <class T>
void lectura(ArbolBinario<T> arbol){
    ifstream archivo;
    string texto, palabra;
    int linea=0, palabras=0, letras=0;
    string delimitador = " ";
    size_t pos = 0;
    string token;

    archivo.open("d:\\pruebaaa\\palabras.txt", ios::in);

    if(archivo.fail()){
        cout << "no se pudo abrir el archivo" << endl;
        exit(1);
    }


    while(!archivo.eof()){ //mientras no sea el final del archivo
        getline(archivo, texto);
        int tamanio = texto.size();
        stringstream input_stringstream(texto);
        for (int i=0; i<tamanio; i++){
            if(isalpha(texto[i])){
                letras++;
            }
        }
        while (getline(input_stringstream, texto, '\n')) {
            linea++;
        }
        while ((pos = texto.find(delimitador)) != std::string::npos) {
            token = texto.substr(0, pos);
            arbol.put(token);
            palabras++;
            texto.erase(0, pos + delimitador.length());
        }
    }

    cout << "cant lineas: " << linea << endl;
    cout << "cant palabras: " << palabras << endl;
    cout << "cant letras: " << letras << endl;
}


int main(){
    ArbolBinario<string> arbol;
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    lectura(arbol);
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;
}
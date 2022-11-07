#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include "ArbolBinario.h"
#include "Lista.h"
using namespace std;

/*
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
            int aux=stoi(token);
            try
            {
                arbol.put(aux);
            }
            catch (int error)
            {
            } // Valor repetido en el arbol, omitiendolo..."
            palabras++;
            texto.erase(0, pos + delimitador.length());
        }
    }

    cout << "cant lineas: " << linea << endl;
    cout << "cant palabras: " << palabras << endl;
    cout << "cant letras: " << letras << endl;
}*/


int main(){
    ArbolBinario<string> arbol;
    Lista<string>lista;

    ifstream archivo1,archivo2;
    string excepciones, texto, palabra;
    int linea=0, palabras=0, letras=0;
    string delimitador = " ";
    size_t pos = 0;
    string token, excp;
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    //lectura(arbol);

    archivo1.open("D:\\excepciones.txt",ios::in);
    if(archivo1.fail()){
        cout << "no se pudo abrir el archivo con las excepciones" << endl;
        exit(1);
    }
    while(!archivo1.eof()){ //mientras no sea el final del archivo

        getline(archivo1, excepciones);
        stringstream input_stringstream(excepciones);
        while (getline(input_stringstream, excepciones, '\n')) {
            cout << "excepcion:" << excepciones << endl;
                try {
                    lista.insertarPrimero(excepciones);
                }
                catch (int error) {
                    throw 404;
                }
            }
        }
        excepciones.erase(0, pos + delimitador.length());



    archivo2.open("D:\\palabras.txt", ios::in);
    if(archivo2.fail()){
        cout << "no se pudo abrir el archivo con el texto a analizar" << endl;
        exit(1);
    }

    while(!archivo2.eof()){ //mientras no sea el final del archivo

        getline(archivo2, texto);
        int tamanio = texto.size();
        stringstream input_stringstream(texto);
        for (int i=0; i<tamanio; i++){
            if(isalpha(texto[i])){
                letras++;
            }
        }
        while (getline(input_stringstream, texto, '\n')) {
            linea++;
            //cout<<texto<<endl;
            while ((pos = texto.find(delimitador)) != std::string::npos) {
                token = texto.substr(0, pos);
                //cout<<token<<endl;
                try
                {
                    arbol.put(token);
                    for(int i=0; i<lista.getTamanio(); i++){
                        string dato = lista.getDato(i);
                        if(arbol.search(dato) == dato){
                            arbol.remove(dato);
                        }
                    }
                }
                catch (int error)
                {
                } // Valor repetido en el arbol, omitiendolo..."
                palabras++;
                texto.erase(0, pos + delimitador.length());

            }
        }

    }
    //primero excepciones(lista) palabra clave que sepamos que ya existe ejemplo doble espacio y despues crear arbol

    cout << "cant lineas: " << linea << endl;
    cout << "cant palabras: " << palabras << endl;
    cout << "cant letras: " << letras << endl;
    cout << "arbol: " ; arbol.print();
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;

}
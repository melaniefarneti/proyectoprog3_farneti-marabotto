#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include "ArbolBinario.h"
#include "Lista.h"
using namespace std;

int main(){
    ArbolBinario<string> arbol;
    Lista<string> lista;

    ifstream archivo1, archivo2; //archivo1 para excepciones y archivo2 para input del texto a analizar
    string excepciones, texto;
    int linea=0, palabras=0, letras=0, op, paldiferentes; //contadores
    string delimitador = " "; //para separar palabras
    size_t pos = 0;
    string token, excp; //variables auxiliares

    cout << "Segundo Parcial de Programacion 3: Farneti - Marabotto" << endl;
    cout << "Ingrese la operacion a realizar: " << endl;
    cout << "-> 1) Funciones Basicas: contar lineas, palabras, letras y palabras diferentes" << endl;
    cout << "-> 2) Mostrar palabras diferentes en en orden alfabetico." << endl;
    cout << "-> 3) Mostrar palabras diferentes en orden de mas ocurrencias (con excepciones)." << endl;
    cout << "-> 4) Mostrar cantidad de veces que aparece una palabra o grupo de palabras en el texto." << endl;
    cin >> op;


    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    archivo1.open("D:\\proyectoprueba\\excepciones.txt",ios::in);
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



    archivo2.open("D:\\proyectoprueba\\palabras.txt", ios::in);
    if(archivo2.fail()){
        cout << "no se pudo abrir el archivo con el texto a analizar" << endl;
        exit(1);
    }

    while(!archivo2.eof()){

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
            while ((pos = texto.find(delimitador)) != std::string::npos) {
                token = texto.substr(0, pos);
                try
                {
                    arbol.put(token);
                    paldiferentes = arbol.contarnodos();
                    for(int i=0; i<lista.getTamanio(); i++){
                        string dato = lista.getDato(i);
                        if(arbol.search(dato) == dato){
                            arbol.remove(dato);
                        }
                    }
                }
                catch (int error)
                {
                }
                palabras++;
                texto.erase(0, pos + delimitador.length());

            }
        }

    }

    switch(op){
        case 1:
        {
            cout << "lineas: " << linea << endl;
            cout << "palabras: " << palabras << endl;
            cout << "letras: " << letras << endl;
            cout << "palabras diferentes: " << paldiferentes  << endl;
            arbol.print();
            break;
        }
        case 2:
        {
            arbol.inorder();
            break;
        }
        default:
            break;
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    return 0;

}

//
// Created by farne on 19/10/2022.
//

#include "proyecto.h"
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    /*
     * * Insertar código a medir tiempo aquí
     */
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;

    cout << "hola como estas" << endl;
    return 0;
}


//
// Created by farne on 19/10/2022.
//

#ifndef PROYECTOPROG3_FARNETI_MARABOTTO_PROYECTO_H
#define PROYECTOPROG3_FARNETI_MARABOTTO_PROYECTO_H
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>


class Palabra {
public:
    Palabra( std::string = "", int = 0 );
    void establecerTotal();
    void establecerPalabra( std::string );
    int obtenerTotal() { return total; }

    bool bucarPalabra();
    void insertarPalabra( Palabra );
    void imprimir();

    std::string obtenerPalabra() { return palabra; }
    static int obtenerGranTotal() { return granTotal; }
private:
    int total;
    std::string palabra;
    static int granTotal;
};
int Palabra::granTotal = 0;

Palabra::Palabra( std::string p, int n ){
    palabra = p;
    total = n;
}
void Palabra::establecerTotal() { total++; }
void Palabra::establecerPalabra( std::string p ) { palabra = p; }

std::vector<Palabra> V;

bool Palabra::bucarPalabra(){

    std::string s;
    std::vector<Palabra>::size_type sz = V.size();

    for( unsigned i = 0; i < sz; i++ ){
        s = V[i].obtenerPalabra();
        if( s == palabra ){
            V[i].establecerTotal();
            granTotal++;
            return true;
        }
    }
    granTotal++;
    return false;
}

void Palabra::insertarPalabra( Palabra p ){
    p.establecerTotal();
    V.push_back( p );
}

void Palabra::imprimir(){

    std::vector<Palabra>::size_type sz = V.size();

    std::cout << "Total palabras leidas: "
         << Palabra::granTotal << std::endl;

    for( unsigned i = 0; i < sz; i++ ){

        std::cout << "La palabra " << V[i].obtenerPalabra()
             << " aparece " << V[i].obtenerTotal()
             << " veces.\n";
    }
    std::cout << std::endl;
}
#endif //PROYECTOPROG3_FARNETI_MARABOTTO_PROYECTO_H

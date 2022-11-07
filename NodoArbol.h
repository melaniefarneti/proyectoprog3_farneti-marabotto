#ifndef U05_ARBOL_ARBOL_NODOARBOL_H_
#define U05_ARBOL_ARBOL_NODOARBOL_H_

#include <string.h>

template <class T> class NodoArbol {
private:
    T data;
    int cont;
    NodoArbol *left, *right;
    int height;

public:
    NodoArbol() {
        left = nullptr;
        right = nullptr;
        cont = 1;
        height=1;
    }

    NodoArbol(T d) {
        data = d;
        cont = 1;
        height = 1;
        left = nullptr;
        right = nullptr;
    }

    T getData() const {
        return data;
    }

    void setData(T d) {
        data = d;
    }

    NodoArbol *getRight() const {
        return right;
    }

    void setRight(NodoArbol *r) {
        right = r;
    }

    NodoArbol *getLeft() const {
        return left;
    }

    void setLeft(NodoArbol *l) {
        left = l;
    }
    int getCont(){
        return cont;
    }
    void setCont(int c){
        cont= c;
    }
    int getHeight(){
        return height;
    }
    void setHeight(int h){
        height=h;
    }

    int contar(){
       return cont++;
    }

    void print(bool esDerecho, std::string identacion) {
        if (right != NULL) {
            right->print(true, identacion + (esDerecho ? "     " : "|    "));
        }
        std::cout << identacion;
        if (esDerecho) {
            std::cout << " /";
        } else {
            std::cout << " \\";
        }
        std::cout << "-- ";
        std::cout << data << std::endl;
        if (left != NULL) {
            left->print(false, identacion + (esDerecho ? "|    " : "     "));
        }
    }

};

#endif // U05_ARBOL_ARBOL_NODOARBOL_H_

#ifndef U05_ARBOL_ARBOL_NODOARBOL_H_
#define U05_ARBOL_ARBOL_NODOARBOL_H_

#include <string.h>
using namespace std;

template <class T>
class NodoArbol{
private:
    T data;
    int cont;
    NodoArbol *left, *right;
    int height;

public:
    NodoArbol(){
        left = nullptr;
        right = nullptr;
        cont = 1;
        height=1;
    }

    NodoArbol(T d){
        data = d;
        cont = 1;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    T getData() const{
        return data;
    }

    void setData(T d){
        this->data = d;
    }

    NodoArbol *getRight() const{
        return right;
    }

    void setRight(NodoArbol *r){
        this->right = r;
    }

    NodoArbol *getLeft() const{
        return left;
    }

    void setLeft(NodoArbol *l){
        this->left = l;
    }

    int getCont(){
        return cont;
    }

    void setCont(int c){
        cont = c;
    }

    int getHeight(){
        return height;
    }

    void setHeight(int h){
        height = h;
    }

    int contar(){
        return cont++;
    }

    void print(bool esDerecho, string identacion){
        if (right != NULL){
            right->print(true, identacion + (esDerecho ? "     " : "|    "));
        }
        cout << identacion;
        if (esDerecho){
            cout << " /";
        } else {
            cout << " \\";
        }
        cout << "-- ";
        cout << data << endl;
        if (left != NULL){
            left->print(false, identacion + (esDerecho ? "|    " : "     "));
        }
    }

};

#endif // U05_ARBOL_ARBOL_NODOARBOL_H_
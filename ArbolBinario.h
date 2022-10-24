#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#include <iostream>
#include "NodoArbol.h"
using namespace std;

template <class T> class ArbolBinario {
private:
    NodoArbol<T> *root;
    T search(T data, NodoArbol<T> *r);
    NodoArbol<T> * put(T data, NodoArbol<T> *r);
    NodoArbol<T> * remove(T data, NodoArbol<T> *r);
    NodoArbol<T> * findMaxAndRemove(NodoArbol<T> *r, bool *found);
    void preorder(NodoArbol<T> *r);
    void inorder(NodoArbol<T> *r);
    void postorder(NodoArbol<T> *r);

public:
    ArbolBinario(){
        root == nullptr;
    };

    void put(T dato);

    T search(T dato);

    void remove(T dato);

    void preorder();

    void inorder();

    void postorder();

    ~ArbolBinario();

    bool esVacio();

    void print();

    NodoArbol<T> getraiz(){
        return root;
    };

    int contarPorNivel(NodoArbol<T> *aux, int);

    void espejo(NodoArbol<T> *r){
        // Función para convertir un árbol binario dado en su espejo
        // caso base: si el árbol está vacío
        if (root == nullptr) {
            return;
        }
        // convertir el subárbol izquierdo
        espejo(root->getLeft());

        // convertir el subárbol derecho
        espejo(root->getRight());

        // intercambiar el subárbol izquierdo con el subárbol derecho
        swap(root->getLeft(), root->getRight());
    };
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
//template <class T> ArbolBinario<T>::ArbolBinario() {}

/**
 * Destructor del Arbol
 */
template <class T> ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T> T ArbolBinario<T>::search(T dato) {
    return search(dato, root);
}

template <class T> T ArbolBinario<T>::search(T dato, NodoArbol<T> *r) {
    if(r == nullptr){
        throw 404;
    }

    if(r->getData() == dato){
        return r->getData();
    }

    if(r->getData() > dato){
        return search(dato, r->getLeft());
    }
    else{
        return search(dato, r->getRight());
    }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template <class T> void ArbolBinario<T>::put(T dato) {
    root = put(dato, root);
}

template <class T> NodoArbol<T> * ArbolBinario<T>::put(T dato, NodoArbol<T> *r) {
    if(r == nullptr){
        return new NodoArbol<T>(dato);
    }

    if(r->getData() == dato){
        throw 200;
    }

    if(r->getData() >dato){
        r->setLeft(put(dato, r->getLeft()));
    }
    else{
        r->setRight(put(dato, r->getRight()));
    }

    return r;

    /*
     *         10
     *        /  \
     *       5   15
     *      / \  / \
     *     3  6 12  17
     *         NULL
     *
     * Arbol1.put(2) -> root = Arbol.put(2, root)  --> root atributo privado del arbol !!!!
     *
     *
    if(r->getData() >dato){
        r->setLeft(put(dato, r->getLeft()));  (10)
    }
        if(r->getData() >dato){
            r->setLeft(put(dato, r->getLeft()));  (5)
        }
            if(r->getData() >dato){
                r->setLeft(put(dato, r->getLeft()));  (3)
            }
                if(r == nullptr){
                    return new NodoArbol<T>(2);  (llego al nullptr asi que crea un nodo nuevo y setea el 2)
                }

     (!!!) se traduce a getsiguiente->getsiguiente->getsiguiente->/// (llega a nullptr)
    */
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T> void ArbolBinario<T>::remove(T dato) {
    root = remove(dato, root);
}

template <class T> NodoArbol<T> *  ArbolBinario<T>::remove(T data, NodoArbol<T> *r){
    NodoArbol<T> *aux;

    if (r == nullptr){
        throw 404;
    }

    if (r->getData() == data){

        if (r->getLeft() == nullptr && r->getRight() == nullptr){ //si es el ultimo
            delete r;
            return nullptr;
        }
        else if (r->getLeft() != nullptr && r->getRight() == nullptr){ //si hay algo a la izquierda
            aux = r->getLeft();
            delete r;
            return aux;
        }
        else if (r->getLeft() == nullptr && r->getRight() != nullptr){ //si hay algo a la derecha
            aux = r->getRight();
            delete r;
            return aux;
        }
        else if (r->getLeft() != nullptr && r->getRight() != nullptr){

            if (r->getLeft()->getRight() != nullptr){
                // Aca tenemos que buscar el valor maximo
                bool found;
                aux = findMaxAndRemove(r->getLeft(), &found);
                aux->setRight(r->getRight());
                aux->setLeft(r->getLeft());
            }
            else{
                aux = r->getLeft();
                aux->setRight(r->getRight());
            }
            delete r;
            return aux;
        }
    }
    else if (r->getData() > data){
        r->setLeft(remove(data, r->getLeft()));
    }
    else{
        r->setRight(remove(data, r->getRight()));
    }

    return r;
}

template <class T> NodoArbol<T> * ArbolBinario<T>::findMaxAndRemove(NodoArbol<T> *r, bool *found){
    NodoArbol<T> *max;
    *found = false;

    if(r->getRight() == nullptr){
        *found = true;
        return r;
    }

    max = findMaxAndRemove(r->getRight(), &found);

    if(*found){
        r->setRight(max->getLeft());
        *found = false;
    }
    return max;
}
/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T> bool ArbolBinario<T>::esVacio() {
    return root == nullptr;
}

/**
 * Recorre un árbol en preorden
 */
template <class T> void ArbolBinario<T>::preorder() {
    preorder(root);
}

template <class T> void ArbolBinario<T>::preorder(NodoArbol<T> *r) {
    if (r == nullptr){
        return;
    }

    cout << r->getData() << " ";
    preorder(r->getLeft());
    preorder(r->getRight());
}

/**
 * Recorre un árbol en orden
 */
template <class T> void ArbolBinario<T>::inorder() {
    inorder(root);
}

template <class T> void ArbolBinario<T>::inorder(NodoArbol<T> *r) {
    if (r == nullptr){
        return;
    }

    inorder(r->getLeft());
    cout << r->getData() << " ";
    inorder(r->getRight());
}

/**
 * Recorre un árbol en postorden
 */
template <class T> void ArbolBinario<T>::postorder() {
    postorder(root);
}

template <class T> void ArbolBinario<T>::postorder(NodoArbol<T> *r) {
    if (r == nullptr){
        return;
    }

    postorder(r->getLeft());
    postorder(r->getRight());
    cout << r->getData() << " ";
}
/**
 * Muestra un árbol por consola
 */
template <class T> void ArbolBinario<T>::print() {
    if (root != nullptr)
        root->print(false, "");
}

template <class T> int ArbolBinario<T>::contarPorNivel(NodoArbol<T> *aux, int n){
    if(aux != NULL){
        if(n == 0){
            return contarPorNivel(aux->getLeft(), n-1) + contarPorNivel(aux->getRight(), n-1) + 1;
        }
        else {
            return contarPorNivel(aux->getLeft(), n-1) + contarPorNivel(aux->getRight(), n-1);
        }
    }
    return 0;

}

#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_

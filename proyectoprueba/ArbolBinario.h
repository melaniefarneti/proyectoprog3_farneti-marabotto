#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#include <iostream>
#include "NodoArbol.h"
using namespace std;

template <class T> class ArbolBinario{
public:
    ArbolBinario();
    void put(T data);
    T search(T data);
    void remove(T data);
    void preorder();
    void inorder();
    void postorder();
    ~ArbolBinario();
    bool esVacio();
    void print();
    int getBalance(){
        return getBalance(root);
    }
    NodoArbol<T> getraiz(){
        return root;
    };
    void quickSort();
    void mostrarRep();
    int contarnodos();

private:
    NodoArbol<T> *root;
    T search(T data, NodoArbol<T> *r);
    void preorder(NodoArbol<T> *r);
    void inorder(NodoArbol<T> *r);
    void postorder(NodoArbol<T> *r);

    int max(int a, int b);
    int calculateHeight(NodoArbol<T> *r);
    int getBalance(NodoArbol<T> *r);
    NodoArbol<T> *rotacionDerecha(NodoArbol<T> *y);
    NodoArbol<T> *rotacionIzquierda(NodoArbol<T> *x);
    NodoArbol<T> *put(T data, NodoArbol<T> *r);
    NodoArbol<T> *remove(T data, NodoArbol<T> *r);

    int calcularcont(NodoArbol<T> *r);
    void mostrarRep(NodoArbol<T> *r);
    int contarnodos(NodoArbol<T> *r);

    NodoArbol<T> *findMin(NodoArbol<T> *r);
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template <class T>
ArbolBinario<T>::ArbolBinario() { root = nullptr; }

/**
 * Destructor del Arbol
 */
template <class T>
ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template <class T>
T ArbolBinario<T>::search(T data){
    return search(data, root);
}

template <class T>
T ArbolBinario<T>::search(T data, NodoArbol<T> *r){
    if (r == nullptr){
        throw 404;
    }

    if (r->getData() == data){
        return r->getData();
    }

    if (r->getData() > data){
        return search(data, r->getLeft());
    }
    else{
        return search(data, r->getRight());
    }
}

/**
 * Cuenta la cantidad de repeticiones de una palabra
 */
template <class T>
int ArbolBinario<T>::calcularcont(NodoArbol<T> *r){
    int cont;
    if (r == nullptr){
        return 0;
    }
    else
        return r->contar();
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */

template <class T>
void ArbolBinario<T>::put(T data) { root = put(data, root); }

template <class T>
NodoArbol<T> *ArbolBinario<T>::put(T data, NodoArbol<T> *r)
{
    //1. Realizar Insercion normal
    if (r == nullptr){
        return new NodoArbol<T>(data);
    }

    if (r->getData() == data){
        calcularcont(r);
        throw 200;
    }

    if (r->getData() > data){
        r->setLeft(put(data, r->getLeft()));
    }
    else{
        r->setRight(put(data, r->getRight()));
    }

    //2. Actualizar altura de este nodo padre
    r->setHeight(max(calculateHeight(r->getLeft()), calculateHeight(r->getRight())) + 1);

    //3. Obtener el factor de balance de este nodo padre
    // y chequear si este nodo se desbalanceo
    int balance = getBalance(r);

    //Quedo desbalanceado II: corresponde una rot Der
    if (balance > 1 && data < r->getLeft()->getData())
    {
        return rotacionDerecha(r);
    }

    //Quedo desbalanceado ID: corresponde una rot Izq Der
    if (balance > 1 && data > r->getLeft()->getData())
    {
        r->setLeft(rotacionIzquierda(r->getLeft()));
        return rotacionDerecha(r);
    }

    //Quedo desbalanceado DD: corresponde una rot Izq
    if (balance < -1 && data > r->getRight()->getData())
    {
        return rotacionIzquierda(r);
    }

    //Quedo desbalanceado DI: corresponde una rot Der Izq
    if (balance < -1 && data < r->getRight()->getData())
    {
        r->setRight(rotacionDerecha(r->getRight()));
        return rotacionIzquierda(r);
    }

    return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template <class T>
void ArbolBinario<T>::remove(T data){ root = remove(data, root); }

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r){
    if (r == nullptr)
        return r;

    // Si el valor data es menor al valor almacenado
    // en r, entonces debe estar en el subarbol
    // izquierdo
    if (data < r->getData())
        r->setLeft(remove(data, r->getLeft()));

        // Si el valor data es mayor al valor almacenado
        // en r, entonces debe estar en el subarbol
        // derecho
    else if (data > r->getData())
        r->setRight(remove(data, r->getRight()));

        // Si data es el mismo valor que esta almacenado
        // en r, entonces es el nodo que hay que eliminar
    else{
        // Si r no tiene sub nodos, o si tiene uno solo
        if ((r->getLeft() == nullptr) || (r->getRight() == nullptr)){
            NodoArbol<T> *temp = r->getLeft() ? r->getLeft() : r->getRight();

            // En caso de que no tenga
            if (temp == nullptr){
                temp = r;
                r = nullptr;
            }
            else            // Caso con un solo sub nodo
                *r = *temp; // Se copian los valores del
                            // sub nodo no vacio
            delete temp;
        }
        else{
            // Nodo r con dos sub nodos: Se debe obtener el
            // sucesor inorder (el mas chico en el subarbol derecho)
            NodoArbol<T> *temp = findMin(r->getRight());

            // Copiar la data del sucesor inorder en r
            r->setData(temp->getData());

            // Eliminar el sucesor inorder
            r->setRight(remove(temp->getData(), r->getRight()));
        }
    }

    // Si el arbol tuviera un solo nodo, return
    if (r == nullptr)
        return r;

    // 2. Actualizar la altura del nodo r
    r->setHeight(1 + max(calculateHeight(r->getLeft()),
                         calculateHeight(r->getRight())));

    // 3. Obtener el factor de balance del nodo r
    // para determinar si r se desbalanceo o no
    // luego de la eliminacion
    int balance = getBalance(r);

    //Quedo desbalanceado II: corresponde una rot Der
    if (balance > 1 && getBalance(r->getLeft()) >= 0)
        return rotacionDerecha(r);

    //Quedo desbalanceado ID: corresponde una rot Der Izq
    if (balance > 1 && getBalance(r->getLeft()) < 0)
    {
        r->setLeft(rotacionIzquierda(r->getLeft()));
        return rotacionDerecha(r);
    }

    //Quedo desbalanceado DD: corresponde una rot Izq
    if (balance < -1 && getBalance(r->getRight()) <= 0)
        return rotacionIzquierda(r);

    //Quedo desbalanceado DI: corresponde una rot Izq Der
    if (balance < -1 && getBalance(r->getRight()) > 0)
    {
        r->setRight(rotacionDerecha(r->getRight()));
        return rotacionIzquierda(r);
    }

    return r;
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::findMin(NodoArbol<T> *r){
        NodoArbol<T> *ret = r;
        while (ret->getLeft() != nullptr)
            ret = ret->getLeft();

        return ret;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template <class T>
bool ArbolBinario<T>::esVacio() { return root == nullptr; }

/**
 * Recorre un árbol en preorden
 */
template <class T>
void ArbolBinario<T>::preorder(){
    preorder(root);
    cout << endl;
}

template <class T>
void ArbolBinario<T>::preorder(NodoArbol<T> *r){
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
template <class T>
void ArbolBinario<T>::inorder(){
    inorder(root);
    cout << endl;
}

template <class T>
void ArbolBinario<T>::inorder(NodoArbol<T> *r){
    if (r == nullptr){
        return;
    }

    inorder(r->getLeft());
    cout << r->getCont() << " " << r->getData() << " " << endl;
    inorder(r->getRight());
}



/**
 * Recorre un árbol en postorden
 */
template <class T>
void ArbolBinario<T>::postorder(){
    postorder(root);
    cout << endl;
}

template <class T>
void ArbolBinario<T>::postorder(NodoArbol<T> *r){
    if (r == nullptr){
        return;
    }

    postorder(r->getLeft());
    postorder(r->getRight());
    cout << r->getData() << " ";
}

template <class T> void ArbolBinario<T>::print() {
    if (root != nullptr)
        root->print(false, "");
}


/**
 * cuenta la cantidad de nodos
 */
template <class T>
int ArbolBinario<T>::contarnodos() {
    return contarnodos(root);
}

template <class T>
int ArbolBinario<T>::contarnodos(NodoArbol<T> *r){
    if(r != NULL){
        int izq = contarnodos(r->getLeft());
        int der = contarnodos(r->getRight());
        return izq + der + 1;
    }
    return 0;
}

/**
 * mostrar repeticiones (acceder a contador)
 */
template <class T>
void ArbolBinario<T>::mostrarRep() {
    mostrarRep(root);
}

template <class T>
void ArbolBinario<T>::mostrarRep(NodoArbol<T> *r) {
    if (r == nullptr){
        return;
    }
    mostrarRep(r->getLeft());
    cout << r->getData() << " :" << r->getCont();
    mostrarRep(r->getRight());
}

/**
 * metodo de ordenamiento de datos
 * para ordenar en funcion de la
 * cantidad de repeticiones
 */

void quickSort(int *cont, int inicio, int fin)
{
    int i, j, medio;
    int pivot, aux;

    medio = (inicio + fin) / 2;
    pivot = cont[medio];
    i = inicio;
    j = fin;

    do
    {
        while (cont[i] < pivot)
            i++;
        while (cont[j] > pivot)
            j--;

        if (i <= j)
        {
            aux = cont[i];
            cont[i] = cont[j];
            cont[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > inicio)
        quickSort(cont, inicio, j);
    if (i < fin)
        quickSort(cont, i, fin);
}

template <class T>
int ArbolBinario<T>::max(int a, int b){
    return (a > b) ? a : b;
}

template <class T>
int ArbolBinario<T>::calculateHeight(NodoArbol<T> *r){
    if (r == nullptr){
        return 0;
    }
    else
        return r->getHeight();
}

template <class T>
int ArbolBinario<T>::getBalance(NodoArbol<T> *r){
    if (r == nullptr){
        return 0;
    }
    return calculateHeight(r->getLeft()) - calculateHeight(r->getRight());
}
template <class T>
NodoArbol<T> *ArbolBinario<T>::rotacionDerecha(NodoArbol<T> *y){
    NodoArbol<T> *x = y->getLeft();
    NodoArbol<T> *T2 = x->getRight();

    //Rotacion
    x->setRight(y);
    y->setLeft(T2);

    //Actualizar alturas
    y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);
    x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);

    //Devolver la nueva raiz;
    return x;
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::rotacionIzquierda(NodoArbol<T> *x){
    NodoArbol<T> *y = x->getRight();
    NodoArbol<T> *T2 = y->getLeft();

    //Rotacion
    y->setLeft(x);
    x->setRight(T2);

    //Atualizar alturas
    x->setHeight(max(calculateHeight(x->getLeft()), calculateHeight(x->getRight())) + 1);
    y->setHeight(max(calculateHeight(y->getLeft()), calculateHeight(y->getRight())) + 1);

    //Devolver la nueva raiz
    return y;
}

#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_
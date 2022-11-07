#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#include <iostream>
#include "NodoArbol.h"
#include "Lista.h"

using namespace std;

template <class T> class ArbolBinario {
public:
    ArbolBinario(){
        root = nullptr;
    };

    void put(T data);

    T search(T data);

    void remove(T data);

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

    void quickSort();
    void mostrarRep();

private:
    NodoArbol<T> *root;
    T search(T data, NodoArbol<T> *r);
    NodoArbol<T> * put(T data, NodoArbol<T> *r);
    NodoArbol<T> * remove(T data, NodoArbol<T> *r);
    NodoArbol<T> * findMaxAndRemove(NodoArbol<T> *r, bool *found);
    void preorder(NodoArbol<T> *r);
    void inorder(NodoArbol<T> *r);
    void postorder(NodoArbol<T> *r);
    int calcularcont(NodoArbol<T> *r);
    void mostrarRep(NodoArbol<T> *r);

    NodoArbol<T> *findMin(NodoArbol<T> *r);
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
template <class T> T ArbolBinario<T>::search(T data) {
    return search(data, root);
}

template <class T> T ArbolBinario<T>::search(T data, NodoArbol<T> *r) {
    if(r == nullptr){
        throw 404;
    }

    if(r->getData() == data){
        return r->getData();
    }

    if(r->getData() > data){
        return search(data, r->getLeft());
    }
    else{
        return search(data, r->getRight());
    }
}

template <class T>
int ArbolBinario<T>::calcularcont(NodoArbol<T> *r)
{
    int cont;
    if (r == nullptr)
    {
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
template <class T> void ArbolBinario<T>::put(T data) {
    root = put(data, root);
}

template <class T> NodoArbol<T> * ArbolBinario<T>::put(T data, NodoArbol<T> *r) {
    if(r == nullptr){
        return new NodoArbol<T>(data);
    }
    //ingresar lista excepcion

    if(r->getData() == data){
        calcularcont(r);
        throw 200;
    }

    if(r->getData() >data){
        r->setLeft(put(data, r->getLeft()));
    }
    else{
        r->setRight(put(data, r->getRight()));
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
template <class T> void ArbolBinario<T>::remove(T data) {
    root = remove(data, root);
}

template <class T>
NodoArbol<T> *ArbolBinario<T>::remove(T data, NodoArbol<T> *r)
{
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
    else
    {
        // Si r no tiene sub nodos, o si tiene uno solo
        if ((r->getLeft() == nullptr) || (r->getRight() == nullptr))
        {
            NodoArbol<T> *temp = r->getLeft() ? r->getLeft() : r->getRight();

            // En caso de que no tenga
            if (temp == nullptr)
            {
                temp = r;
                r = nullptr;
            }
            else          // Caso con un solo sub nodo
                *r = *temp; // Se copian los valores del
            // sub nodo no vacio
            delete temp;
        }
        else
        {

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
NodoArbol<T> *ArbolBinario<T>::findMin(NodoArbol<T> *r)
{
    {
        NodoArbol<T> *ret = r;
        while (ret->getLeft() != nullptr)
            ret = ret->getLeft();

        return ret;
    }
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


template <class T> void ArbolBinario<T>::mostrarRep() {
    mostrarRep(root);
}

template <class T> void ArbolBinario<T>::mostrarRep(NodoArbol<T> *r) {
        if (r == nullptr){
            return;
        }

        mostrarRep(r->getLeft());
        cout << r->getData() << " :" << r->getCont();
        mostrarRep(r->getRight());
    }


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

#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_

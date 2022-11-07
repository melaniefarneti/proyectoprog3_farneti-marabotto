#ifndef U02_LISTAS_LISTA_LISTA_H_
#define U02_LISTAS_LISTA_LISTA_H_

#include "Nodo.h"

/**
 * Clase que implementa una Lista Enlasada generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */

using namespace std;

template <class T> class Lista {
private:
    Nodo<T> *inicio_lista;
public:
    Lista();

    Lista(const Lista<T> &li);

    ~Lista();

    bool esVacia();

    Nodo<T>* get_inicio_lista();
    void set_inicio_lista(Nodo<T>* nuevo_inicio);
    int getTamanio();

    void insertar(int pos, T dato);

    void insertarPrimero(T dato);

    void insertarUltimo(T dato);

    void remover(int pos);

    T getDato(int pos);

    void reemplazar(int pos, T dato);

    void vaciar();

    void imprimir_lista();
};

/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T> Lista<T>::Lista() {
    inicio_lista = nullptr;
}

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T> Lista<T>::Lista(const Lista<T> &li) {

}

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Lista<T>::~Lista() {

}

/**
 * Metodo para saber si la lista esta vacia
 * @tparam T
 * @return true si la lista esta vacia, sino false
 */
template <class T> bool Lista<T>::esVacia() {
    return (inicio_lista== nullptr);
}

/**
 * Metodo para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
template <class T> int Lista<T>::getTamanio() {
    int tamano = 0;
    Nodo <T> *auxiliar_nodo = inicio_lista;
    while (auxiliar_nodo != nullptr) {
        tamano++;
        auxiliar_nodo = auxiliar_nodo->get_siguiente_nodo();
    }
    return tamano;
}

/**
 * Inserta un nodo con el dato en la posicion pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato  dato a insertar
 */
template <class T> void Lista<T>::insertar(int pos, T dato) {
    int posicion_actual=0;

    Nodo<T> * auxiliar_nodo = inicio_lista, *nuevo_nodo;

    nuevo_nodo = new Nodo<T>;
    nuevo_nodo->set_dato(dato);

    if(pos==0){
        nuevo_nodo->set_puntero_a_siguiente_nodo(inicio_lista);
        inicio_lista = nuevo_nodo;
        return;
    }
    while (auxiliar_nodo!= nullptr && posicion_actual<pos-1){
        auxiliar_nodo=auxiliar_nodo->get_siguiente_nodo();
        posicion_actual++;

    }

    if(auxiliar_nodo== nullptr){
        throw 404;
    }
    nuevo_nodo->set_puntero_a_siguiente_nodo(auxiliar_nodo->get_siguiente_nodo());
    auxiliar_nodo->set_puntero_a_siguiente_nodo(nuevo_nodo);
}


/**
 * Inserta un nodo con el dato en la primera posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarPrimero(T dato) {

    Nodo<T> * nuevo_nodo = new Nodo <T>;
    nuevo_nodo->set_dato(dato);
    nuevo_nodo->set_puntero_a_siguiente_nodo(inicio_lista);
    inicio_lista=nuevo_nodo;
}

/**
 * Inserta un nodo con el dato en la ultima posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarUltimo(T dato) {
    Nodo <T> *auxiliar_nodo = inicio_lista;
    Nodo<T> *nuevo_ultimo_nodo= new Nodo<T>;
    nuevo_ultimo_nodo->set_dato(dato);

    while (auxiliar_nodo->get_siguiente_nodo() != nullptr){
        auxiliar_nodo=auxiliar_nodo->get_siguiente_nodo();
    }

    auxiliar_nodo->set_puntero_a_siguiente_nodo(nuevo_ultimo_nodo);
    nuevo_ultimo_nodo->set_puntero_a_siguiente_nodo(nullptr);
}


/**
 * Elimina el nodo en la posicion 'pos' de la lista enlasada
 * @tparam T
 * @param pos posicion del nodo a eliminar
 */
template <class T> void Lista<T>::remover(int pos) {
    //podria haber usado el metodo insertar tranquilamente
    unsigned int posicion_actual=0;

    Nodo<T> * auxiliar_nodo = inicio_lista;
    Nodo<T> * auxiliar_eliminacion;

    if(esVacia()){
        throw 404;
    }
    if(pos==0){
        inicio_lista = inicio_lista->get_siguiente_nodo();
        delete auxiliar_nodo;
        return;
    }

    while (posicion_actual<pos-1){
        auxiliar_nodo=auxiliar_nodo->get_siguiente_nodo();
        posicion_actual++;
        if(auxiliar_nodo == nullptr){
            throw 401;
        }
    }
    auxiliar_eliminacion=auxiliar_nodo->get_siguiente_nodo();
    auxiliar_nodo->set_puntero_a_siguiente_nodo(auxiliar_nodo->get_siguiente_nodo()->get_siguiente_nodo());
    delete auxiliar_eliminacion;
}

/**
 * Obtener el dato del nodo en la posicion pos
 * @tparam T
 * @param pos posicion del dato
 * @return dato almacenado en el nodo
 */
template <class T> T Lista<T>::getDato(int pos) {
    unsigned int posicion_actual=0;

    Nodo<T> * auxiliar_nodo = inicio_lista;

    if(esVacia()){
        throw 404;  }

    while (posicion_actual < pos){
        auxiliar_nodo = auxiliar_nodo->get_siguiente_nodo();
        posicion_actual++;
        if(auxiliar_nodo == nullptr){
            throw 399;
        }
    }
    return auxiliar_nodo->get_dato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posicion donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T> void Lista<T>::reemplazar(int pos, T dato) {
    unsigned int posicion_actual=0;

    Nodo<T> * auxiliar_nodo = inicio_lista;

    if(esVacia()){
        throw 404;
    }

    while (posicion_actual < pos){
        auxiliar_nodo = auxiliar_nodo->get_siguiente_nodo();
        posicion_actual++;
        if(auxiliar_nodo == nullptr){
            throw 399;
        }
    }
    auxiliar_nodo->set_dato(dato);
}

/**
 * Función que vacia la lista enlazada
 * @tparam T
 */
template <class T> void Lista<T>::vaciar() {
    unsigned int posicion_actual = 0;
    Nodo<T> * auxiliar_eliminacion, auxiliar_nodo=inicio_lista;

    if(auxiliar_nodo == nullptr) {
        throw 401;
    }

    while (posicion_actual<getTamanio()) {
        auxiliar_eliminacion = auxiliar_nodo;
        auxiliar_nodo = auxiliar_nodo->get_siguiente_nodo();
        delete auxiliar_eliminacion;
        posicion_actual++;
    }
    delete auxiliar_nodo;
}


template<class T>void Lista<T>::imprimir_lista() {
    Nodo<T>*auxiliar_nodo = inicio_lista;

    while(auxiliar_nodo!= nullptr){
        cout<<" | "<< auxiliar_nodo->get_dato()<<" | ";
        auxiliar_nodo=auxiliar_nodo->get_siguiente_nodo();
    }
    cout<< endl;
}



#endif // U02_LISTAS_LISTA_LISTA_H_

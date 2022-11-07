//
// Created by Tizx on 13/9/2022.
//

#ifndef INC_2021A2_U02_LISTAS_TIZX_NODO_H
#define INC_2021A2_U02_LISTAS_TIZX_NODO_H


template<class T>
class Nodo {
public:
    T get_dato();
    void set_dato(T data);

    void set_puntero_a_siguiente_nodo(Nodo<T> *nodo);//paso un puntero ya que estoy modificando el puntero siguiente nodo.
    Nodo<T> *get_siguiente_nodo();//esta pididiendo el puntero siguiente nodo, entocnes debe devolver un puntero a nodo.

private:
    T dato;
    Nodo<T>* siguiente_nodo;
};

template<class T>
T Nodo<T>::get_dato() {
    return dato;
}

template<class T>
void Nodo<T>::set_dato(T data) {
    dato = data;
}

template<class T>
void Nodo<T>::set_puntero_a_siguiente_nodo(Nodo<T> *nodo) {
    siguiente_nodo = nodo;
}

template<class T>
Nodo<T> *Nodo<T>::get_siguiente_nodo() {
    return siguiente_nodo;
}


#endif //LISTA_NODO_H
#ifndef U05_ARBOL_ARBOL_NODOARBOL_H_
#define U05_ARBOL_ARBOL_NODOARBOL_H_

template <class T> class NodoArbol {
private:
    T data;
    NodoArbol *left, *right;

public:
    NodoArbol() {
        left = nullptr;
        right = nullptr;
    }

    NodoArbol(T d) {
        data = d;
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
};

#endif // U05_ARBOL_ARBOL_NODOARBOL_H_

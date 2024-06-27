#ifndef MIVECTOR_H
#define MIVECTOR_H
#include "MyArrasy.h"

template<typename T>
class MiVector {
public:
    MiVector() : capacidad(0), size(0), data(0) {}
    ~MiVector() {
        // No need to call the destructor of MyArray here.
        // It will be called automatically when the MiVector object is destroyed.
    }

    void push_back(const T& value) {
        if (size == capacidad) {
            if (capacidad == 0) {
                capacidad = 1;
            } else {
                capacidad *= 2;
            }
            data.resize(capacidad);
        }
        data[size] = value;
        size++;
    }

    T& operator[](size_t index) {  // Operador [] añadido
        return data[index];
    }

    size_t get_size() const {
        return size;
    }


private:
    size_t capacidad;
    size_t size;
    MyArray<T> data;
};

#endif //MIVECTOR_H
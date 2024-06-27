template<typename T>
class MyArray {
public:
    MyArray(size_t initialSize) : size(initialSize), data(new T[size]) {}

    // Copy constructor
    MyArray(const MyArray& other) : size(other.size), data(new T[size]) {
        std::copy(other.data, other.data + size, data);
    }

    // Copy assignment operator
    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    ~MyArray() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    void resize(size_t newSize) {
        T* newData = new T[newSize];
        size_t copySize = (newSize > size) ? size : newSize;
        std::copy(data, data + copySize, newData);
        delete[] data;
        data = newData;
        size = newSize;
    }

    size_t get_size() const {
        return size;
    }

private:
    size_t size;
    T* data;
};
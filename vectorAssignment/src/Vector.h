#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::range_error
#include <vector>

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow(){
        if (_capacity == 0) {
        _capacity = 1;
        } else {
            _capacity *= 2;
        }
        T* new_data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(array[i]);
        }
        delete[] array;
        array = new_data;
    }

public:

    // default constructor
    Vector() noexcept:  _size{0}, _capacity{0}, array{nullptr} {}

    // parameterized constructor || size of array set to a value
    Vector(size_t count, const T& value) {
        _size = count;
        _capacity = count;
        array = new T[_capacity]();
        for (size_t i = 0; i < count; i++){
            array[i] = value;
        }
    }
    
    // default inserted constructor || int * arr = new int[20]();
    explicit Vector(size_t count) {
        _size = count;
        _capacity = count;
        array = new T[count]();
    }

    // copy constructor
    Vector(const Vector& other): _size(other._size), _capacity(other._capacity), array(nullptr) {
        array = new T[other._capacity];
        for (size_t i = 0; i < other._size; i++){
            array[i] = other[i];
        }
    }

    // move constructor 
    // when constructor exits scope others destructor 
    Vector(Vector&& other) noexcept{
        this->_size = other._size;
        this->_capacity = other._capacity;
        this->array = other.array;
        other.array = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // destructor
    ~Vector(){
        delete[] array;
        _size = 0;
        _capacity = 0;
    }

    // copy assignment
    Vector& operator=(const Vector& other){
        if (this != &other){
            delete[] array;
            array = nullptr;
            _size = other._size;
            _capacity = other._capacity;
            array = new T[_capacity];
            for (size_t i = 0; i < _size; i++){
                array[i] = other[i];
            }
        }
        return *this;
    } 

    // move assignment || check github
    Vector& operator=(Vector&& other) noexcept{
        if (this == &other) { return *this; }

        if (array) delete[] array;

        this->_size = other._size;
        this->_capacity = other._capacity;

        this->array = other.array;
        other.array = nullptr;
        other._size = 0;
        other._capacity = 0;
        return *this;
    }
// -------------------------------------------------------------------------------------------------------------------------
    //
    iterator begin() noexcept{
        if (_size == 0) {
            return iterator(nullptr);
        } else {
            return iterator(array);
        }
    }
    iterator end() noexcept{
        return iterator(array + _size);
    }

    [[nodiscard]] bool empty() const noexcept{
        if (_size == 0){
            return true;
        }
        return false;
    }
    size_t size() const noexcept{
        return _size;
    }
    size_t capacity() const noexcept{
        return _capacity;
    }

    T& at(size_t pos){
        if (pos < 0 || pos >= _size){
            throw std::out_of_range("out of range of vector");
        }
        return array[pos];
    }

    const T& at(size_t pos) const{
        if (pos < 0 || pos >= _size){
            throw std::out_of_range("out of range of vector");
        } else {
            return array[pos];
        }
    }

    T& operator[](size_t pos){
        return array[pos];
        
    }
    const T& operator[](size_t pos) const{
        return array[pos];
    }


    T& front(){
        return array[0];
    }
    const T& front() const{
        return array[0];
    }
    T& back(){
        return array[_size-1];
    }
    const T& back() const{
        return array[_size-1];
    }

    void push_back(const T& value){ // [1] [2] [3] [4] [ ] 
        while (_size >= _capacity) {
            grow();
        }
        array[_size] = value;
        _size++;
    }
    void push_back(T&& value){
        while (_size >= _capacity) {
            grow();
        }
        array[_size] = std::move(value);
        _size++;
    }
    void pop_back(){
        _size--;
    }

    iterator insert(iterator pos, const T& value){
        ptrdiff_t ind = pos - begin();

        if (_size == _capacity){
            grow();
        }

        pos = begin() + ind;

        for (ptrdiff_t i = end() - begin(); i > ind; i--){
            array[i] = std::move(array[i-1]);
        }
        _size++;
        array[ind] = value;
        return pos;

    }
    iterator insert(iterator pos, T&& value){
        ptrdiff_t ind = pos - begin();

        if (_size == _capacity){
            grow();
        }

        pos = begin() + ind;

        for (ptrdiff_t i = end() - begin(); i > ind; i--){
            array[i] = std::move(array[i-1]);
        }
        _size++;
        array[ind] = std::move(value);
        return pos;
    }
    iterator insert(iterator pos, size_t count, const T& value){
        ptrdiff_t ind = pos - begin();
        while (_size + count > _capacity){
            grow();
        }
        
        pos = begin() + ind;

        for (ptrdiff_t i = end() - begin() + count-1; i > ind + count - 1; i--){
            array[i] = std::move(array[i-count]);
        }
        for (ptrdiff_t i = ind; i < count+ind; i++){
            array[i] = value;
        }
        _size = _size + count;

        return pos;


    }


    iterator erase(iterator pos){
        if (pos == end()) {
            return end();
        }

        for (size_t i = pos - begin(); i < end() - begin() -1;  i++){
            array[i] = std::move(array[i+1]);
        }


        pop_back();
        return pos;
    


    }
    iterator erase(iterator first, iterator last){
        if (last >= end()) {
            return end();
        }

        // [1] [2] [3] [4] [5] [6] [7] [8] [9]
        // remove  [3] [4] [5]
        // [1] [2] [6] [7] [8] [9]

        size_t diff = last - first;

        for (size_t i = first - begin(); i < (end() - begin() - diff);  i++){
            array[i] = std::move(array[i+diff]);
        }

        for (size_t i = 0; i < diff; i++){
            pop_back();
        }

        return first;
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
        pointer ptr;
    public:
        iterator () = default;
        iterator(pointer ref): ptr(ref) {}
        // Add any constructors that you may need

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        // return the reference
        [[nodiscard]] reference operator*() const noexcept{
            return *ptr;
        }
        // return the pointer || 
        [[nodiscard]] pointer operator->() const noexcept{
            return ptr;
        }

        // Prefix Increment: ++a
        iterator& operator++() noexcept{
            ptr++;
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept{
            iterator temp = ptr;
            //++(*this);
            ptr++;
            return temp;
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept{
            ptr--;
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept{
            iterator temp = ptr;
            //--(*this);
            ptr--;
            return temp;
        }

        iterator& operator+=(difference_type offset) noexcept{
            ptr += offset;
            return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept{
            iterator temp = *this;
            return temp += offset;
        }
        
        iterator& operator-=(difference_type offset) noexcept{
            return (*this += (-offset));
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept{
            iterator temp = *this;
            return (temp -= offset);
        }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept{
            return ( ptr - rhs.ptr);
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept{
            return *(ptr + offset);
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept{
            return ptr == rhs.ptr;
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept{
            return (!(ptr == rhs.ptr));
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept{
            return ptr < rhs.ptr;
        }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept{
            return ptr > rhs.ptr;
        }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept{
            return ptr <= rhs.ptr;
        }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept{
            return ptr >= rhs.ptr;
        }
    };


    void clear() noexcept{
        _size = 0;
    }
};




template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept{}

#endif

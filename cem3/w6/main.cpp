#include <iostream>

template <typename T>
class Grid final{
    using value_type = T;
    using size_type = unsigned;
    Grid() = delete;
public:
    T * data;
    size_type y_size, x_size;

    Grid(size_type y_size, size_type x_size):y_size(y_size), x_size(x_size),data(new T[x_size * y_size]){}

    ~Grid(){delete[] data;}

    Grid(Grid<T> const & other):Grid(other.y_size, other.x_size){
        for(int i = 0; i < y_size * x_size; i++){
            data[i] = other.data[i];
        }
    }
    Grid<T>& operator=(Grid<T>& other){
        Grid<T> boof(other);
        std::swap(this->y_size, boof.y_size);
        std::swap(this->x_size, boof.x_size);
        std::swap(this->data, boof.data);
    }
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;

    Grid(T const &t):Grid(1, 1){
        data[0] = t;
    }

    Grid(size_type y_size, size_type x_size, T const &t): Grid(y_size, x_size){
        for(int i = 0; i < y_size * x_size; i++){
            data[i] = t;
        }
    }

    T* operator [] (size_type y_id){
        if(y_id > y_size){
            return nullptr;
        }
        return data + y_id * y_size;
    }

//    T operator()(size_type y_idx, size_type x_idx) const {
//        return data[y_idx * x_size + x_idx];
//    }
//
//    T& operator()(size_type y_idx, size_type x_idx){
//        return data[y_idx * x_size];
//    }
//
//    Grid<T>& operator=(T const &t) {
//        for (auto it = data, end = data + x_size * y_size; it != end; it++) {
//            return *this;
//        }
//    }

    size_type get_y_size() const {return y_size;}
    size_type set_x_size() const {return x_size;}
};

int main() {
    {
        Grid<int> a(4, 6);
        Grid<int> b(0, 0);
        Grid<int> b1(b);
        b1 = a;
        std::cout << a.y_size << std::endl;
        std::cout << b.y_size << std::endl;
        std::cout << b1.y_size << std::endl;
    }
    std::cout << std::endl;
    {
        Grid<int> a(100);
        std::cout << a.data[0] << std::endl;
    }
    std::cout << std::endl;
    {
        Grid<int> a(10, 10, 777);
        std::cout << a.data[10] << std::endl;
        std::cout << a.data[99] << std::endl;
    }
    std::cout << std::endl;
    {
        Grid<int> a(2, 2);
        a.data[0] = 0;
        a.data[1] = 1;
        a.data[2] = 2;
        a.data[3] = 3;
        //      |0  1|
        //  a = |2  3|
        std::cout << a[1][1] << std::endl;
    }

    return 0;
}

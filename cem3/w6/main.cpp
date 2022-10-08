#include <iostream>

template <typename T>
class Grid final{
private:
    using value_type = T;
    using size_type = unsigned;
public:
    Grid() = delete;
    T * const data;
    size_type const y_size, x_size;

    Grid(size_type y_size, size_type x_size):y_size(y_size), x_size(x_size),data(new T[x_size * y_size]){}

    ~Grid(){delete data;}

    Grid(Grid<T> const &) = delete;
    Grid(Grid<T>&&) = delete;
    Grid<T>& operator=(Grid<T>&) = delete;
    Grid<T>& operator=(Grid<T>&&) = delete;

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
    Grid<int> a(4, 6);
    return 0;
}

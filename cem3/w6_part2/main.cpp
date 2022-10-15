#include <iostream>

template <typename T, unsigned N>
class Grid final{
    using size_type = unsigned;
    Grid() = delete;
    unsigned ptr = 0;
public:
    T * data;
    size_type size[N];

    void foo(size_type* array, int i){
        return;
    }

    template<typename First, typename ...Args>
    void foo(size_type* array, int i, First first, Args ...args){
        array[i] = first;
        ptr++;
        foo(array, ++i, args...);
    }

    template<typename ...Args>
    Grid(Args ...args){
        foo(size, 0, args ...);
        unsigned line_size = 1;
        for(int i = 0; i < N; i ++){
            line_size = line_size * size[i];
        }
        data = new T[line_size];
    }

    template<typename ...Args>
    Grid(T t, Args ...args){
        foo(size, 0, args ...);
        unsigned line_size = 1;
        for(int i = 0; i < N; i ++){
            line_size = line_size * size[i];
        }
        data = new T[line_size];
        for(int i = 0; i < line_size; i++){
            data[i] = t;
        }
    }

    Grid(Grid<T, N> const & other){
        unsigned line_size = 1;
        for(int i = 0; i < N; i ++){
            size[i] = other.size[i];
            line_size = line_size * size[i];
        }
        data = new T[line_size];
        for(int i = 0; i < line_size; i++){
            data[i] = other.data[i];
        }
    }

    ~Grid(){delete[] data;}

    Grid<T, N>& operator=(Grid<T, N>& other){
        Grid<T, N> boof(other);
        std::swap(this->size, boof.size);
        std::swap(this->data, boof.data);
    }
    Grid(Grid<T, N>&&) = delete;
    Grid<T, N>& operator=(Grid<T, N>&&) = delete;

    template<typename ...Args>
    T* operator ()(Args ...args) {
        size_type id[N];
        foo(id, 0, args...);
        size_type line_id = 0;
        for(int i = 0; i < N; i ++){
            size_type current_size = 1;
            for(int j = i + 1; j < N; j ++){
                current_size = current_size * size[j];
            }
            line_id += id[i] * current_size;
        }
        return data + line_id;
    }
};

int main() {
    Grid<float, 3> const g3(2, 3, 4);
    Grid<float, 4> g4(4, 4, 4, 4);
    Grid<float, 3> new_g(g3);
    Grid<float, 4> new_g4(1, 1, 1, 1);
    std::cout << new_g.size[0] << ' ' << new_g.size[1] << ' ' << new_g.size[2] << std::endl;
    new_g4 = g4;
    std::cout << new_g4.size[0] << ' ' << new_g4.size[1] << ' ' << new_g4.size[2] << ' ' << new_g4.size[3] << std::endl;
    g4.data[85] = 1234.f;
    std::cout << *g4(1, 1, 1, 1) << std::endl;
    Grid<float, 2> g2(1.f, 2, 2);
    std::cout << *g2(1, 0) << std::endl;
    return 0;
}

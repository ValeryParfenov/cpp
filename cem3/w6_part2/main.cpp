#include <iostream>

template <typename T, unsigned N>
class Grid final{
    using size_type = unsigned;
    Grid() = delete;
public:
    T * data;
    size_type* size;

    Grid(size_type* size):size(size), data(){
        unsigned line_size = 1;
        for(int i = 0; i < N; i ++){
            line_size = line_size * size[i];
        }
        data = new T[line_size];
    }

    ~Grid(){delete data;}

    Grid(Grid<T, N> const & other):Grid(other.size){
        unsigned line_size = 1;
        for(int i = 0; i < N; i ++){
            line_size = line_size * size[i];
        }
        for(int i = 0; i < line_size; i++){
            data[i] = other.data[i];
        }
    }
    Grid<T, N>& operator=(Grid<T, N>& other){
        Grid<T, N> boof(other);
        std::swap(this->size, boof.size);
        std::swap(this->data, boof.data);
    }
    Grid(Grid<T, N>&&) = delete;
    Grid<T, N>& operator=(Grid<T, N>&&) = delete;

    T* operator ()(size_type * id){
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
    {
        unsigned N[4] = {1, 2, 3, 4};
        Grid<int, 4> a(N);
        Grid<int, 4> b(a);
        Grid<int, 4> c(N);
        c = a;
    }
    {
        unsigned N[3] = {2, 2, 2};
        Grid<int, 3> a(N);
        for(int i = 1; i <= 8; i++){
            a.data[i-1] = i;
        }
        unsigned id[3] = {1,1,0};
        std::cout << *a(id);
    }
    return 0;
}

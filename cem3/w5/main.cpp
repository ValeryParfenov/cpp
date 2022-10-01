#include <iostream>

template <typename T>
struct Comparator {
    virtual int operator()(T const &lha, T const&rha) const = 0 ;
};

struct IntComparator final : Comparator<int> {
    int operator () (int const &lha , int const &rha ) const override {
        return rha - lha ;
        }
};

void swap(void* a, void* b, size_t size){
    char buff[size];
    memcpy(buff, a, size);
    memcpy(a, b, size);
    memcpy(b, buff, size);
}

template <typename T>
void qsort ( T* first, size_t number, Comparator<T> &comparator){
    if(number <= 1){
        return;
    }
    T* point = first + (number - 1);
    bool flag = true;
    for(int i = 0; i < number - 1; i ++){
        T* actual = first +  i;
        if(flag == true && comparator(*point, *actual) > 0){
            swap(point, actual, sizeof(T));
            point = actual;
            flag = false;
        }
        else if(flag == false && comparator(*point, *actual) < 0){
            while(point != actual){
                swap(actual - 1, actual, sizeof(T));
                actual = actual - 1;
            }
            point = point + 1;
        }
    }
    size_t new_number1 = (point - first);
    size_t new_number2 = number - new_number1 - 1;
    qsort (first, new_number1, comparator);
    qsort (point + 1, new_number2, comparator);
}

int main() {
    int a [10] = {1, 9, 5, 6, 3, 4, 10, 12, 0, 7};
    IntComparator comparator;
    qsort(a, 10, comparator);
    for(int i = 0; i < 10; i ++){
        std::cout << a[i] << " " << std::endl;
    }
    return 0;
}
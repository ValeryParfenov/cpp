#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void swap(void* a, void* b, size_t size){
    char buff[size];
    memcpy(buff, a, size);
    memcpy(a, b, size);
    memcpy(b, buff, size);
}

int comparator(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

void qsort ( void * first, size_t number, size_t size, 
int ( * comparator ) ( const void *, const void * ) ){
    if(number <= 1){
        return;
    }
    void* point = (char*)first + size * (number - 1);
    bool flag = true;
    for(int i = 0; i < number - 1; i ++){
        void* actual = (char*)first + size * i;
        if(flag == true && comparator(point, actual) > 0){
            swap(point, actual, size);
            point = actual;
            flag = false;
        }
        else if(flag == false && comparator(point, actual) < 0){
            while(point != actual){
                swap((char*)actual - size, actual, size);
                actual = (char*)actual - size;
            }
            point = (char*)point + size;
        }
    }
    size_t new_number1 = ((char*)point - (char*)first)/size;
    size_t new_number2 = number - new_number1 - 1;
    qsort (first, new_number1, size, comparator);
    qsort ((char*)point + size, new_number2, size, comparator);
}

int main() {
    int a [10] = {1, 9, 5, 6, 3, 4, 10, 12, 0, 7};
    qsort (&a, 10, sizeof(int), comparator);
    for(int i = 0; i < 10; i ++){
    cout << a[i] << " " << endl;
    }
    return 0;
}
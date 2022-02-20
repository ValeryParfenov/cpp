#include <iostream>
using namespace std;

int main() {
    unsigned length;
    cin >> length;
    int array[length];
    for(int i = 0; i < length; i++){
        cin >> array[i];
    }

    bool sorted = false;
    int unsorted_length = length;
    while(sorted == false){
        sorted = true;
        for(int i = 1; i < unsorted_length; i++){
            if(array[i] < array[i -1]) {
                array[i] += array[i - 1];
                array[i - 1] = array[i] - array[i - 1];
                array[i] -= array[i - 1];
                sorted = false;
            }
        }
        unsorted_length -= 1;
    }
    for(int i = 0; i < length; i++){
        cout << array[i] << endl;
    }
    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int length;
    cin >> length;
    int array[length];
    for(int i = 0; i < length; i++){
        cin >> array[i];
    }

    int min = array[0];
    for(int a : array){
        if(min > a)
            min = a;
    }

    int max = array[0];
    for(int a : array){
        if(max < a)
            max = a;
    }

    int sum = 0;
    for(int a : array){
        sum += a;
    }
    double sr = sum / double(length);

    cout << "min = " << min << "; max = " << max << "; sr = " << sr << endl;

    return 0;
}

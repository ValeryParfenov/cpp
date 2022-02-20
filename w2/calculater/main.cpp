#include <iostream>
#include <math.h>
using namespace std;

int main() {
    char operation;
    while(operation != '!') {
        cin >> operation;
        double a;
        double b;
        if (operation != 'l') {
            cin >> a >> b;
            if (operation == '+')
                cout << a + b << endl;
            if (operation == '*')
                cout << a * b << endl;
            if (operation == '-')
                cout << a - b << endl;
            if (operation == '/')
                cout << a / b << endl;
        }
        else {
            if (operation == 'l')
                cin >> a;
                cout << log(a) << endl;
        }
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void read(std::string filename){
    std::ifstream f;
    f.open(filename);
    std::string string;
    int value;
    while(!f.eof())
    {
        getline(f, string);
        if(string.empty()){
            continue;
        }
        std::stringstream buffer(string);
        while(buffer >> value){
            std::cout << "0";
        }
        std::cout << string << std::endl;
    }
    f.close();
}

int main() {
    read("input.txt");
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

template <typename VarType>
class Matrix final{
public:
    std::vector<std::vector<VarType>> matrix;
    std::unique_ptr<int[]> is_var_free; // ели i эллемент массива 1, то переменная свободна, если 0 - не свободна
    unsigned Height = 0; // размеры матрицы
    unsigned Width = 0;
    Matrix(){};
public:
    // Конструктор, считывающий матрицу из файла
    Matrix(std::string filename){
        std::ifstream input;
        input.open(filename);
        std::string string;
        VarType value;
        while(!input.eof()){
            getline(input, string);
            if(string.empty()){
                continue;
            }
            matrix.push_back(std::vector<VarType>()); // пушим новую строчку в матрицу и начинаем заполнять
            std::stringstream buffer(string);
            if(Height == 0){
                while(buffer >> value){
                    Width += 1;
                    matrix[0].push_back(value);
                }
                if(Width == 0){
                    std::cerr << "invalid input (Mat[0x0])";
                    exit(1);
                }
            } // если заполняемая строка первая
            else{
                unsigned current_width = 0;
                while(buffer >> value){
                    matrix[Height].push_back(value);
                    current_width += 1;
                    if(current_width > Width){
                        std::cerr << "invalid input";
                        exit(1);
                    }
                }
                if(current_width < Width){
                    std::cerr << "invalid input";
                    exit(1);
                }
            }
            Height += 1;
        }
        is_var_free.reset(new int[Width] {0});
        input.close();
    }

    void print() const{
        for(int i = 0; i < Height; i ++){
            for(int j = 0; j < Width; j++){
                std::cout << matrix[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    Matrix<int> m("input.txt");
    //m.print();
    return 0;
}

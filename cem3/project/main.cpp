#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cassert>

template <typename VarType>
struct MatrixString final: std::vector<VarType> {
    void operator += (MatrixString<VarType> other){
        if(other.size() != this->size()){
            std::cerr << "unvalid matrix condition";
            exit(1);
        }
        for(int i = 0; i < this->size(); i++){
            this->at(i) += other.at(i);
        }
    }

    void operator -= (MatrixString<VarType> other){
        if(other.size() != this->size()){
            std::cerr << "unvalid matrix condition";
            exit(1);
        }
        for(int i = 0; i < this->size(); i++){
            this->at(i) -= other.at(i);
        }
    }

    MatrixString operator + (MatrixString<VarType> other){
        MatrixString<VarType> new_string(*this);
        new_string += other;
        return new_string;
    }

    MatrixString operator - (MatrixString<VarType> other){
        MatrixString<VarType> new_string(*this);
        new_string -= other;
        return new_string;
    }

    MatrixString operator * (VarType value){
        MatrixString<VarType> new_string(*this);
        for(int i = 0; i < new_string.size(); i++){
            new_string.at(i) = new_string.at(i) * value;
        }
        return new_string;
    }

    MatrixString operator / (VarType value){
        assert(value != 0);
        MatrixString<VarType> new_string(*this);
        for(int i = 0; i < new_string.size(); i++){
            new_string.at(i) = new_string.at(i) / value;
        }
        return new_string;
    }
};

// от VarType требуется, чтобы нулевой эллемент давал true при сравнении с 0
// а также поддержка арифметических операций (/ * + -)
template <typename VarType>
class Matrix final{
public:
    std::vector<MatrixString<VarType>> matrix;
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
            matrix.push_back(MatrixString<VarType>()); // пушим новую строчку в матрицу и начинаем заполнять
            matrix.at(Height).reserve(Width); //сразу выделяем нужное количество памяти
            std::stringstream buffer(string);
            if(Height == 0){
                while(buffer >> value){
                    Width += 1;
                    matrix.at(0).push_back(value);
                }
                if(Width == 0){
                    std::cerr << "invalid input (Mat[0x0])";
                    exit(1);
                }
            } // если заполняемая строка первая
            else{
                unsigned current_width = 0;
                while(buffer >> value){
                    matrix.at(Height).push_back(value);
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
        is_var_free.reset(new int[Width - 1] {1});
        matrix.shrink_to_fit(); // отдаём назад лишнюю память, если она была выделена под эллементы вектора
        input.close();
    }

    void find_support_elements(){ //нахождение опорных эллементов (нужны для корректной работы simplify)
        unsigned free_vars_amount = 0;
        for(int i = 0; (i < Width - 1) && (i < Height); i++){
            for(int j = i - free_vars_amount; j < Height; j++){
                if(matrix.at(i).at(j) != 0){
                    is_var_free[i] = 0;
                    std::swap(matrix.at(j), matrix.at(i)); // отппрявляем строку с опорным эллементом Xi на i строку
                    break;
                }
            }
            if(is_var_free[i] == 1){
                free_vars_amount += 1;
            }
        }
    }

    void simplify(){
        find_support_elements();
    }

    void print() const{
        for(auto string : matrix){
            for(auto value : string){
                std::cout << value << ' ';
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    Matrix<double> m("input.txt");
    m.find_support_elements();
    m.matrix[0] += m.matrix[2];
    m.matrix[0] = m.matrix[0] / 5;
    m.print();
    //std::cout << (m.matrix[0] + m.matrix[2])[2];
    return 0;
}
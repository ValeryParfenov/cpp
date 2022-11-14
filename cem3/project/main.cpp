#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cassert>

template <typename VarType>
struct MatrixLine final: std::vector<VarType> {
    void operator += (MatrixLine<VarType> other){
        if(other.size() != this->size()){
            std::cerr << "unvalid matrix condition";
            exit(1);
        }
        for(int i = 0; i < this->size(); i++){
            this->at(i) += other.at(i);
        }
    }

    void operator -= (MatrixLine<VarType> other){
        if(other.size() != this->size()){
            std::cerr << "unvalid matrix condition";
            exit(1);
        }
        for(int i = 0; i < this->size(); i++){
            this->at(i) -= other.at(i);
        }
    }

    MatrixLine operator + (MatrixLine<VarType> other){
        MatrixLine<VarType> new_string(*this);
        new_string += other;
        return new_string;
    }

    MatrixLine operator - (MatrixLine<VarType> other){
        MatrixLine<VarType> new_string(*this);
        new_string -= other;
        return new_string;
    }

    MatrixLine operator * (VarType value){
        MatrixLine<VarType> new_string(*this);
        for(int i = 0; i < new_string.size(); i++){
            new_string.at(i) = new_string.at(i) * value;
        }
        return new_string;
    }

    MatrixLine operator / (VarType value){
        assert(value != 0);
        MatrixLine<VarType> new_string(*this);
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
private:
    std::vector<MatrixLine<VarType>> matrix;
    std::vector<bool> is_var_free; // ели i эллемент массива 1, то переменная свободна, если 0 - не свободна
    std::vector<std::string> solution; // сдесь будет лежать решение системы
    unsigned Height = 0; // размеры матрицы
    unsigned Width = 0;
    unsigned free_vars_amount = 0;
    Matrix(){};

    // сделаем опорный эллемент равный 1, поделив строку на его значение. занулим все остальные эллементы
    // в столбце с данным опорным эллементом вычитанием строки, содержащей опорный эллемент
    void pick_out_support_var(unsigned line_id, unsigned column_id){
        VarType current_support_var = matrix.at(line_id).at(column_id);
        matrix.at(line_id) = matrix.at(line_id) / current_support_var;
        for(unsigned i = 0; i < Height; i++){
            if(i == line_id){
                continue;
            }
            matrix.at(i) -= matrix.at(line_id) * matrix.at(i).at(column_id);
        }
    }

    // Для матрицы в УПРОЩЁННОМ ВИДЕ возвращает true если система разрешима, false - иначе
    bool is_simple_matrix_solvable() const{
        unsigned non_free_vars_amount = Width - free_vars_amount - 1;
        for(unsigned i = non_free_vars_amount; i < Height; i++){
            if(matrix.at(i).at(Width - 1) != 0){
                return false;
            }
        }
        return true;
    }

    // Находит опорные эллементы и приводим матрицу к упрощённому виду
    void find_support_elements(){ //нахождение опорных эллементов (нужны для нахождений решеня)
        for(unsigned i = 0; i < Width - 1; i++){
            for(unsigned j = i - free_vars_amount; j < Height; j++){
                if(matrix.at(j).at(i) != 0){
                    is_var_free.at(i) = 0;
                    // отппрявляем строку с опорным эллементом Xi на строку под последней опорной строкой
                    std::swap(matrix.at(j), matrix.at(i-free_vars_amount));
                    pick_out_support_var(i-free_vars_amount, i);
                    break;
                }
            }
            free_vars_amount += is_var_free.at(i);
        }
    }

    void make_simple_matrix_solution(){
        assert(is_simple_matrix_solvable() == true);
        solution.insert(solution.begin(), Width - 1, "free variable"); // для несвободных переменных переопределим ниже
        unsigned non_free_vars_amount = Width - free_vars_amount - 1;
        unsigned current_non_free_var_id = 0;
        std::ostringstream buffer;
        for(unsigned i = 0; i < non_free_vars_amount; i ++){
            while(is_var_free.at(current_non_free_var_id) == 1){
                current_non_free_var_id += 1;
                assert(current_non_free_var_id < Width - 1);
            }
            buffer << matrix.at(i).at(Width - 1);
            for(unsigned j = 0; j < Width - 1; j++){
                if(j != i && is_var_free.at(j) == 1 && matrix.at(i).at(j) != 0){
                    buffer << " + " << matrix.at(i).at(j) << "*" << "x_"<< j+1;
                }
            }
            solution.at(current_non_free_var_id) = buffer.str();
            buffer.str("");
            current_non_free_var_id += 1;
        }
    }

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
            matrix.push_back(MatrixLine<VarType>()); // пушим новую строчку в матрицу и начинаем заполнять
            matrix.at(Height).reserve(Width); //сразу выделяем нужное количество памяти
            std::stringstream buffer(string);
            // если заполняемая строка первая
            if(Height == 0){
                while(buffer >> value){
                    Width += 1;
                    matrix.at(0).push_back(value);
                }
                if(Width == 0){
                    std::cerr << "invalid input (Mat[0x0])";
                    exit(1);
                }
            }
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
        solution.reserve(Width - 1);
        is_var_free.reserve(Width - 1);
        is_var_free.insert(is_var_free.begin(), Width - 1, 1);
        matrix.shrink_to_fit(); // отдаём назад лишнюю память, если она была выделена под эллементы вектора
        input.close();
    }

    void print_solution(){
        find_support_elements();
        if(is_simple_matrix_solvable() == false){
            std::cout << "no solutions" << std::endl;
            return;
        }
        make_simple_matrix_solution();
        for(unsigned var_id = 0; var_id < solution.size(); var_id++){
            std::cout << "x_" << var_id + 1 << " = " << solution.at(var_id) << std::endl;
        }
    }

    void print() const{
        for(auto line : matrix){
            for(auto value : line){
                std::cout << value << ' ';
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Matrix<double> m("input1.txt");
//    m.matrix[0] += m.matrix[2];
//    m.matrix[0] = m.matrix[0] / 5;
//    m.find_support_elements();
//    m.print();
    m.print_solution();

    //std::cout << m.solution[3];
    return 0;
}
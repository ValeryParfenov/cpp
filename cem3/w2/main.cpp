#include <iostream>
#include <string>
#include <cmath>

class Point {
public:
        unsigned long long x , y ;
public:
        Point (unsigned long long x , unsigned long long y): x(x) , y(y) {}

        Point minx(Point const &rha ) const{
            return Point ( rha.x < x ? rha.x : x , y ) ;
            }

        Point miny(Point const &rha ) const{
            return Point (x, rha.y < y ? rha.y : y);
            }

        Point maxx(Point const &rha) const{
            return Point (rha.x > x ? rha.x : x , y);
            }

        Point maxy(Point const &rha) const{
            return Point(x , rha.y > y ? rha.y : y);
            }

        void print() const{
            std::cout << "(" << x << "," << y << ")";
            }
        };

class Rectangle: public Point{
public:
    Rectangle(): Point(0,0){}

    Rectangle(Point const& other): Point(other.x, other.y){}

    Rectangle(unsigned long long x, unsigned long long y): Point(x, y){}

    Rectangle operator+(Rectangle const & oter_Rectangle)
    {
        return Rectangle(this->maxx(oter_Rectangle).x, this->maxy(oter_Rectangle).y);
    }

    Rectangle operator*(Rectangle const & oter_Rectangle)
    {
        return Rectangle(this->minx(oter_Rectangle).x, this->miny(oter_Rectangle).y);
    }
};

struct Expression{
    std::string expression;
    void erase_spaces(){
        while(expression[0] == ' ' || expression[0] == '(' || expression[0] == ')' || expression[0] == ','){
            expression = expression.substr(1);}
    }

    unsigned long long  get_number(){
        std::string number_string;
        erase_spaces();
        while(expression[0] != ' ' && expression[0] != ')' && expression[0] != ',' && expression.empty() == false){
            number_string.push_back(expression[0]);
            expression = expression.substr(1);
        }
        erase_spaces();
        unsigned long long number = 0;
        for(int i = number_string.size() - 1; i >= 0; i -= 1){
            number += (static_cast<int>(number_string[i]) - 48) * pow(10, number_string.size() - 1 - i);
        }
        return number;
    }

    Rectangle get_rectangle(){
        erase_spaces();
        unsigned long long x = get_number();
        erase_spaces();
        unsigned long long y = get_number();
        erase_spaces();
        return Rectangle(x, y);
    }

    char get_operator(){
        erase_spaces();
        char operatorr = expression[0];
        expression = expression.substr(1);
        erase_spaces();
        return operatorr;
    }
};


int main() {
    Expression expression;
    std::getline(std::cin, expression.expression);
    std::string number;
    Rectangle actual;
    Rectangle result = expression.get_rectangle();
    char operatorr;
    while(expression.expression.empty() == false){
        operatorr = expression.get_operator();
        actual = expression.get_rectangle();
        if(operatorr == '+'){
            result = result + actual;
        }
        if(operatorr == '*'){
            result = result * actual;
        }
    }
    result.print();
    //std::cout << expression.get_number() + 1;
    //expression.get_rectangle().print();


//    while(expression.empty() == false){
//
//    }
//    Point a(10, 20);
//    Point b(5, 10);
//    Rectangle r1(a);
//    Rectangle r2(b);
//    (r1 * r2).print();
    return 0;
}

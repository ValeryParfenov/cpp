#include <iostream>
#include <vector>

template <typename T>
struct Comparator {
    virtual int operator()(T const &lha, T const&rha) const{
        return rha > lha ;
    }
};

struct IntComparator final : Comparator<int> {
    int operator () (int const &lha , int const &rha ) const override {
        return rha > lha ;
    }
};



template <typename T>
class Q{
    Q (){}
    Comparator<T> comparator;
    std::vector<T> A;

    void heapify(int root){
        root += 1;
        int biggest_child = -1;
        if(root * 2 > A.size()){
            return;
        }
        if(root * 2 == A.size()){
            biggest_child = root * 2 - 1;
        }
        else if(comparator(A.at(root * 2 - 1), A.at(root * 2)) == 1){
            biggest_child = root * 2 - 1;
        }
        else{biggest_child = root * 2;}
        if(comparator(A.at(root-1), A.at(biggest_child)) == 1){
            return;
        }
        T boof = A.at(root-1);
        A.at(root-1) = A.at(biggest_child);
        A.at(biggest_child) = boof;
        heapify(biggest_child);
    }
public:
    Q(Comparator<T> &comparator): comparator(comparator){}

    void push(T key){
        A.push_back(key);
        if(A.size() <= 3){
            return;
        }
        int unsestor = A.size()/2;
        int leaf = A.size();
        do{
            if(comparator(A.at(unsestor - 1), A.at(leaf - 1)) == 1){
                break;
            }
            T boof = A.at(leaf - 1);
            A.at(leaf - 1) = A.at(unsestor - 1);
            A.at(unsestor - 1) = boof;
            leaf = unsestor;
            unsestor = unsestor/2;
       } while (unsestor != leaf);
    }

    void print(){
        for(int i = 0; i < A.size(); i++) {
            std::cout << A.at(i)<< " " << std::endl;
        }
        std::cout << std::endl;
    }

    T peak(){
        if(A.size() == -1){
            std::cout << "Try to peak empty que" << std::endl;
            return 0;
        }
        return A.at(0);
    }

    T pull(){
        T boof = A.at(0);
        A.at(0) = A.at(A.size()-1);
        A.pop_back();
        heapify(0);
        return boof;
    }

    bool is_empty(){
        return A.size() == 0;
    }

    void clear(){
        A.clear();
    }
};

int main() {
    IntComparator comparator;
    Q<int> q(comparator);

    std::cout << "Is que emty?   " << q.is_empty() << std::endl;

    q.push(0);
    q.push(1);
    q.push(11);
    q.push(5);
    q.push(9);
    q.push(8);
    q.push(4);
    q.push(10);


    q.print();
    std::cout << "Is que emty?  " << q.is_empty() << std::endl;
    std::cout << "We peaked: " << q.peak() << std::endl;
    std::cout << "We pulled: " << q.pull() << std::endl;
    q.print();
    std::cout << "We pulled: " << q.pull() << std::endl;
    q.print();
    q.clear();
    std::cout << "We cleared que " << std::endl;
    std::cout << "Is que emty?  " << q.is_empty() << std::endl;
    return 0;
}

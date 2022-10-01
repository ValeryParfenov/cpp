#include <iostream>

template <typename T>
struct Comparator {
    virtual int operator()(T const &lha, T const&rha) const = 0 ;
};

struct IntComparator final : Comparator<int> {
    int operator () (int const &lha , int const &rha ) const override {
        return rha > lha ;
    }
};

void swap(void* a, void* b, size_t size){
    char buff[size];
    memcpy(buff, a, size);
    memcpy(a, b, size);
    memcpy(b, buff, size);
}


template <typename T>
struct Leafs{
    T key;
    Leafs* right;
    Leafs* left;
    Leafs* unsestor;
};

template <typename T>
class Q{
    Leafs<T>* head;
    Comparator<T> comparator;
    int lenth = 1;

    Leafs<T>* biggest_baby(Leafs<T>* head){
        if(head->right == NULL && head->left == NULL){
            return NULL;
        }
        if(head->right == NULL){
            return head->left;
        }
        if(head->left == NULL){
            return head->right;
        }
        if(comparator(head->left->key, head->right->key) == 1){
            return head->left;
        }
        else{return head->right;}
    }

    void heapify_subtree(Leafs<T>* head){
        Leafs<T>* big_boy = biggest_baby(head);
        if(big_boy == NULL){
            return;
        }
        if(comparator(big_boy->key, head->key) == 1){
            swap(head, big_boy, sizeof(Leafs<T>));
            heapify(head);
        }
    }

    void hiapify_supertree(Leafs<T>* head, T s){
        if(comparator(head->key, s) == 1){
            std::cout << "error in increase key" << std::endl;
            return;
        }
        head->key = s;
        while(head->unsestor != NULL){
            if(comparator(head->key, head->unsestor->key) == 0){
                break;
            }
            swap(head, head->unsestor, sizeof(head));
            head = head->unsestor;
        }
    }

public:
    Q(Comparator<T> &comparator): comparator(comparator), head(new T){
        head->left = NULL;
        head->right = NULL;
        head->unsestor = NULL;
    }

    void push(T s){

        Leafs<T>* tail = new Leafs<T>;
        tail->key = s;
        tail->left = NULL;
        tail->right = NULL;
        int l = this->lenth;
        for(int i = 0; l > 0; i ++){

        }
        this->lenth += 1;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

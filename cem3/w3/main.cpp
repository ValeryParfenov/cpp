#include <iostream>
#include <set>
#include <random>
#include <chrono>

class State {
public:
    virtual bool contains(int s) const = 0;
};

class DiscreteState : public State {
private:
    int state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const override {
        return s == state;
    }
};

class SegmentState : public State{
public:
    int beg, end;

public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const override {
        return s >= beg && s <= end;
    }
};

class SetState : public State {
public:
    std::set<int> states;
public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const override {
        return states.count(s) > 0;
    }
};

struct LineSegmint{
    int begin = 0;
    int end = 0;
    LineSegmint(int begin, int end): begin(begin), end(end){}
};

class SuperState : State{
public:
    std::set<int> in_states = {};
    std::set<int> out_states = {};
    LineSegmint &line_segment;
    SuperState(LineSegmint &line_segment, std::set<int> in_states, std::set<int> out_states):
    line_segment(line_segment), in_states(in_states), out_states(out_states){};
    bool contains(int s) const override {
        return (in_states.count(s) + (line_segment.begin < s && s < line_segment.end) - out_states.count(s));
    }
};

class ProbabilityTest {
public:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(State &s) {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

std::set<int> random_set(int n, int min, int max, int seed){
    std::set<int> set;
    int i = 0;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> dstr(min,max);
    while(i < n){

        int x = dstr(rng);
        if(set.count(x) == 0){
            set.emplace(x);
            i ++;
        }
    }
    return set;
}

int main(int argc, const char * argv[]) {
    LineSegmint l(3, 6);
    SuperState state(l, {6, 8, 9}, {5});
    std::cout << state.contains(7) << std::endl;
//    DiscreteState d(1);
//    SegmentState s(0,10);
//    SetState ss({2, 3, 5, 7, 23, 48, 57, 60, 90, 98});

//    ProbabilityTest pt(10,0,100,1);
//    for(int i = 0; i < 10000; i++){
//        pt.test_count = 10 * i;
//        std::cout << pt(s) << ", " << std::endl;
//        //std::cout << i * 10 << ", " << std::endl;
//    }

//    ProbabilityTest pt(10,0,100,1);
//    for(int i = 0; i < 10000; i++){
//        pt.test_count = 10 * i;
//        std::cout << pt(ss) << ", " << std::endl;
//        //std::cout << i * 10 << ", " << std::endl;
//    }

//    ProbabilityTest pt(10,0,100,1000);
//    SegmentState s1(0,10);
//    for(int i = 1; i < 100; i++){
//        s1.end = i;
//        //std::cout << pt(s1) << ", " << std::endl;
//        std::cout << i << ", " << std::endl;
//    }

//    ProbabilityTest pt(10,0,100,10000);
//    SetState sss;
//    for(int i = 1; i < 100; i++){
//        sss = random_set(i, 0, 100, 11);
//        std::cout << pt(sss) << ", " << std::endl;
//        //std::cout << i << ", " << std::endl;
//    }

//    std::cout << pt(s) << std::endl;
//    std::cout << pt(ss) << std::endl;
    return 0;
}
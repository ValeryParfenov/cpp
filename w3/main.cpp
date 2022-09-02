#include <iostream>
#include <thread>

#define SIZE  12
#define RADIUS 50
#define CONCENTRATION 2
//#define SEED 1

void DrawArray(int (&array)[2 * RADIUS + 1][2 * RADIUS + 1]){
    for(int j = 0; j < 2 * RADIUS + 1; j++){
        for(int i = 0; i < 2 * RADIUS + 1; i++){
            std::cout << array[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------" << std::endl;
}

int RandomRange(int range){
    return (static_cast<double>(std::rand()) / RAND_MAX) * range;
}

void ClearScreen(){
    std::cout << "\x1B[2J\x1B[H";
}

void MakeDislocations(int (&array)[2 * RADIUS + 1][2 * RADIUS + 1]){
    int i = 0;
    while (i <= (2 * RADIUS + 1)*(2 * RADIUS + 1)*(static_cast<float>(CONCENTRATION)/100)){
        int x = RandomRange(2 * RADIUS + 1);
        int y = RandomRange(2 * RADIUS + 1);
        if(array[x][y] != 1){
            array[x][y] = 1;
            i++;
        }
    }
}

void MoveOneDislocation(int (&new_array)[2 * RADIUS + 1][2 * RADIUS + 1], int i, int j, int moshion_direction){
    if(moshion_direction == 0 && new_array[i+1][j] == 0) new_array[i+1][j] = 1;
    else if(moshion_direction == 1 && new_array[i][j+1] == 0) new_array[i][j+1] = 1;
    else if(moshion_direction == 2 && new_array[i-1][j] == 0) new_array[i-1][j] = 1;
    else if(moshion_direction == 3 && new_array[i][j-1] == 0) new_array[i][j-1] = 1;
    else new_array[i][j] = 1; // если наткнулись на препятствие в новом массиве (в старом их не может быть), то стоим на месте
}

bool MoveDislocations(int (&array)[2 * RADIUS + 1][2 * RADIUS + 1]){
    bool changes = false;
    int moshion_direction;
    int new_array[2 * RADIUS + 1][2 * RADIUS + 1] = {0};
    for(int j = 0; j < 2 * RADIUS + 1; j++){
        for(int i = 0; i < 2 * RADIUS + 1; i++){
            if(array[i][j] == 1 && ((array[i+1][j] != 0 || array[i][j+1] != 0 ||
                    array[i-1][j] != 0 || array[i][j-1] != 0) || i == 0 || j == 0 ||
                    i == 2 * RADIUS || j == 2 * RADIUS)) array[i][j] = 2; // проверка не должна ли дислокация
                    // остановиться
            if(array[i][j] == 2) new_array[i][j] = 2;  // копируем неподвижную дислокацию в новый массив
            else if(array[i][j] == 1){ // двигаем подвижную дислокацию (только в новом массиве)
                moshion_direction = RandomRange(4);
                MoveOneDislocation(new_array, i, j, moshion_direction);
                changes = true;
            }
        }
    }
    for(int j = 0; j < 2 * RADIUS + 1; j++){
        for(int i = 0; i < 2 * RADIUS + 1; i++){
            array[i][j] = new_array[i][j]; // обновляем наш постоянный массив
        }
    }
    return changes;
}

int OneDislocationMoveTime(){
    int array[2 * RADIUS + 1][2 * RADIUS + 1] = {0};
    array[RADIUS][RADIUS] = 1;
    bool changes = true;
    int counter = 0;

    while(changes){
        //DrawArray(array);
        //std:: this_thread::sleep_for(std::chrono::milliseconds(0));
        //ClearScreen();
        changes = MoveDislocations(array);
        counter ++;
    }
    //DrawArray(array);
    return counter - 1; // возвращается значение, меньшее на 1, т к на последнем шаге дислокации уже не двигались
}

int DislocationsMoveTime(){
    int array[2 * RADIUS + 1][2 * RADIUS + 1] = {0};
    MakeDislocations(array);

    bool changes = true;
    int counter = 0;
    while(changes){
        //DrawArray(array);
        //std:: this_thread::sleep_for(std::chrono::milliseconds(10));
        //ClearScreen();
        changes = MoveDislocations(array);
        counter ++;
    }
    //DrawArray(array);
    return counter - 1; // возвращается значение, меньшее на 1, т к на последнем шаге дислокации уже не двигались
}

int main() {
    #ifdef SEED
        std::srand(SEED);
    #else
        std::srand(std::time(nullptr));
    #endif

    int sumary_time = 0;
    double time;
    for(int i = 0; i < 10000; i++){
        sumary_time += DislocationsMoveTime();
    }
    time = static_cast<double>(sumary_time) / 10000;
    std::cout << time << std::endl;

    /*int sumary_time = 0;
    double time;
    for(int i = 0; i < 10000; i++){
        sumary_time += OneDislocationMoveTime();
    }
    time = static_cast<double>(sumary_time) / 10000;
    std::cout << time << std::endl;*/

    return 0;
}

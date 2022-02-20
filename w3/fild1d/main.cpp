#include <iostream>
#include <thread>

#define MAX_LENGTH 1001
int RADIUS = 250;
int CONCENTRATION = 10;
#define DIAM (2 * RADIUS + 1)

void DrawArray(int (&array)[MAX_LENGTH]){
    for(int i = 0; i < DIAM; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void ClearScreen(){
    std::cout << "\x1B[2J\x1B[H";
}

int RandomRange(int range){
    return (static_cast<double>(std::rand()) / RAND_MAX) * range;
}

void MakeDislocations(int (&array)[MAX_LENGTH]){
    int i = 0;
    while (i <= DIAM*(static_cast<float>(CONCENTRATION)/100)){
        int x = RandomRange(DIAM);
        if(array[x] != 1){
            array[x] = 1;
            i++;
        }
    }
}

void MoveOneDislocation(int (&new_array)[MAX_LENGTH], int x, int moshion_direction){
    if(moshion_direction == 0 && new_array[x+1] == 0) new_array[x+1] = 1;
    else if(moshion_direction == 1 && new_array[x-1] == 0) new_array[x-1] = 1;
    else new_array[x] = 1; // если наткнулись на препятствие в новом массиве (в старом их не может быть), то стоим на месте
}

bool MoveDislocations(int (&array)[MAX_LENGTH]){
    bool changes = false;
    int moshion_direction;
    int new_array[MAX_LENGTH] = {0};
    for(int j = 0; j < 2 * RADIUS + 1; j++){
        if(array[j] == 1 && ((array[j+1] != 0 || array[j-1] != 0) || j == 0 |j == DIAM - 1))
            array[j] = 2; // проверка не должна ли дислокация остановиться
        if(array[j] == 2) new_array[j] = 2;  // копируем неподвижную дислокацию в новый массив
        else if(array[j] == 1){ // двигаем подвижную дислокацию (только в новом массиве)
            moshion_direction = RandomRange(2);
            MoveOneDislocation(new_array, j, moshion_direction);
            changes = true;
        }
    }
    for(int j = 0; j < DIAM; j++){
            array[j] = new_array[j]; // обновляем наш постоянный массив
    }
    return changes;
}

int OneDislocationMoveTime(){
    int array[MAX_LENGTH] = {0};
    array[RADIUS] = 1;
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
    int array[MAX_LENGTH] = {0};
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

    /*for(int i = 1; i < 100; i += 1){
        CONCENTRATION = i;
        int time = 0;
        for(int j = 0; j < 500; j++){
            time += DislocationsMoveTime();
        }
        float sr_time = static_cast<float>(time) / 500;
        std::cout << sr_time << ", ";
    }*/
    std::cout << std::endl;
    for(int i = 1; i < 100; i += 1){
        std::cout << i << ", ";
    }

    /*for(int i = 10; i < 500; i += 10){
        RADIUS = i;
        int time = 0;
        for(int j = 0; j < 500; j++){
            time += OneDislocationMoveTime();
        }
        float sr_time = static_cast<float>(time) / 500;
        std::cout << sr_time << ", ";
    }
    std::cout << std::endl;
    for(int i = 10; i < 500; i += 10){
        RADIUS = i;
        std::cout << DIAM << ", ";
    }*/
    return 0;
}

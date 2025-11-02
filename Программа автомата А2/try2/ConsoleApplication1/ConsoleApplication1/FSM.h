#pragma once
#include <iostream>
#include <vector>


template <class T> void Swap(T& a, T& b);

// Шаблон-функция для перемешивания с получением полноцикловой перестановки вектора-чисел
template <typename standardType> void shuffle_full_cycle(std::vector < standardType >& hexa);




/// класс-перестановка
class Permut {
private:
    std::vector<unsigned int> hexa;
    unsigned int size;
public:

    // деструктор
    ~Permut();

    // конструктор по умолчанию + конструктор выборочной генерации( (0 - тождественная (01234...n-1)     1 - случайная полноцикловая ) )
    Permut(unsigned int n = 0, unsigned int t=0);
    
    // конструктор копирования
    Permut(Permut& s);
    
    // конструктор по перемещению
    Permut(Permut&& s);
    
    // конструктор по вектору
    Permut(std::vector < unsigned int > s);
    
    // конструктор по массиву
    Permut(unsigned int n, unsigned int* s);

    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =  


    // перегрузка " = "
    Permut operator=(const Permut& s);

    // перегрузка " * "
    Permut operator*(Permut s);
    
    // перегрузка " [] "
    unsigned int& operator[](int i);
    
    // перегрузка " >> "
    Permut operator>>(unsigned int k);
    
    // перегрузка " << "
    Permut operator<<(unsigned int k);

    // перегрузка " == "
    bool operator==(const Permut& s);
    // Степень
    Permut pow(int power);


    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =  


    // shuffle_full_cycle() - функция "перемешивания". Выход: случайная полноцикловая перестановка
    void shuffle_full_cycle();

    // shuffle() - функция "перемешивания". Выход: случайная перестановка
    void shuffle();

    // Нахождение обратной перестановки
    Permut reverse();

    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =  
     
     
    // Геттер размера
    unsigned int Size();

    // Вывод
    void Output();

    // Ввод (по порядку) с размером (БЕЗ ПРОВЕРКИ НА КОРРЕКТНОСТЬ)
    void Input();
    // Convert to std::vector<unsigned int>
    std::vector<unsigned int> To_Vector();
};



class A1 {
private:
    int current_state;          // текущее состояние                                         *   *   *   *   *   *   *
    std::vector <unsigned int> g1;           // функция переходов(полноциковая перестановка) *   А В Т О М А Т   А1  *
    std::vector <unsigned int> f1;           // функция выходов(заполнение по битам)         *   *   *   *   *   *   *
    unsigned int N;             // g1.size() = 2^N  |   f1.size() = 2^N / 32 (+1 if N<=5)
    unsigned int f1_size;       // f1.size() = 2^N / 32 (+1 if N<=5)
public:
    
    // Деструктор
    ~A1();


    // конструктор по умолчанию
    A1(unsigned int NN, int cur_st, 
        std::vector<unsigned int> gg1 = std::vector<unsigned int>(), 
        std::vector<unsigned int> ff1 = std::vector<unsigned int>());


    // конструктор копирования
    A1(A1& s);


    // конструктор по перемещению
    A1(A1&& s); 


    // конструктор для генерации, t=0 - g1 - 234...(n-1)1 | f1 = 0000..001
    //                            t=1 - g1 - randmized | f1 - randomized
    A1(unsigned int NN=0, unsigned int cur_st=0, int t = 0);

    // перегрузка " = "
    A1 operator=(A1& s);


    // Получить выход из текущего состояния
    unsigned int get_output();


    // Получить выход из состояния state
    unsigned int get_output_from(unsigned int state);


    // Получить следующее состояние из текущего состояния
    int get_next_state();


    // Получить следующее состояние из состояния state
    int get_next_state_from();


    // Инициирование перерхода из текущего состояние в следующее
    void transit();
};




/* пока что 0 < M < 32, иначе g2 превращается в БЧ(большое число)
* 100...010     011...001     010...101
* f2(0,1)[0]    f2(0,1)[1]    f2(0,1)[2]    заполяняются слева направо в ячейке, слева направо по ячейкам(длинный булев вектор)
* f2[0] - первые 32 состояния, f2[1] - вторые 32 состояния и т.д.
* 
* g2(0,1) - классический массив состояний -  функция переходов
*/
class A2 {
private:
    std::vector <unsigned int> g20;     // функция переходов g2(0, •)
    std::vector <unsigned int> g21;     // функция переходов g2(1, •)
    unsigned int g2_size;               // размер массива для функции g2

    std::vector <unsigned int> f20;     // булев вектор для функции f2(0, •)
    std::vector <unsigned int> f21;     // булев вектор для функции f2(1, •)

    unsigned int M;                     // порядок автомата: 2^M состояний в автомате
    unsigned int f2_size;               // размер массива для булева вектора функции f2

    unsigned int current_state;         // текущее состояние автомата
public:

    // Деструктор
    ~A2();

    // Конструктор по умолчанию
    A2(std::vector <unsigned int> gg20 = std::vector<unsigned int>(),
       std::vector <unsigned int> gg21 = std::vector<unsigned int>(),
       std::vector <unsigned int> ff20 = std::vector<unsigned int>(),
       std::vector <unsigned int> ff21 = std::vector<unsigned int>(),
       unsigned int MM = 0, unsigned int cur_st = 0);

    // Конструктор копирования
    A2(A2& s);

    // Конструктор по перемещению
    A2(A2&& s);

    // Конструктор для построения пустого или случайно_сгенерированного автомата(w_f20 - вес f2)
    A2(unsigned int MM = 0, unsigned int cur_st = 0, int t = 0, unsigned int w_f2=1);

    // Перегрузка " = "
    A2 operator=(A2& s);



//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   
    
    // Получить СЛЕД. СОСТОЯНИЕ из текущего состояния по входу input
    unsigned int get_next_state(unsigned char input);

    // Получить ВЫХОД из текущего состояния по входу input
    unsigned int get_output(unsigned char input);

    // получить ТЕКУЩЕЕ состояние по входу input
    unsigned int get_current_state();

    // Получить СЛЕД. СОСТОЯНИЕ из состояния state по входу input
    unsigned int get_next_state_from(unsigned int state, unsigned char input);

    // Получить ВЫХОД из состояния state по входу input
    unsigned int get_output_from(unsigned int state, unsigned char input);

    // Инициировать переход из текущего состояния по входу input
    void transit(unsigned char input);

    // Получение размера (порядка)
    unsigned int get_M();

    // Получение размера (кол-ва состояний)
    unsigned int get_size();

    // Получение g(0, •)
    std::vector<unsigned int> get_g20();

    // Получение g(1, •)
    std::vector<unsigned int> get_g21();

    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   
    
    // Вывод g20
    void Output_g20();
    
    // Вывод g21
    void Output_g21();
    
    // Вывод f20
    void Output_f20();
    
    // Вывод f21
    void Output_f21();

    // Вывод g2
    void Output_g2();

    // Вывод f2
    void Output_f2();

    // Вывод Всего автомата А2
    void Output();

    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   

    // заменить функцию f20
    void change_f20(std::vector<unsigned int> ff20);

    // заменить функцию f21
    void change_f21(std::vector<unsigned int> ff21);

    // заменить g20
    void change_g20(std::vector<unsigned int> gg20);

    // заменить g21
    void change_g21(std::vector<unsigned int> gg21);


};


//  ==========================================================================
//  =============   С Т Р  У К Т У Р А  -   Д Е Р Е В О     ==================
//  ==========================================================================
// структура дерево-обращения
struct R_Tree {
    R_Tree* left;
    R_Tree* right;
    R_Tree* back;
    unsigned int s;     // поле-данные будет хранить состояние автомата А2
    bool chet;          // чётность последовательности-пути от корня до этого 
};

// Вывод дерева R_Tree, начиная с узла *root
// с оступом k
void PrintTree(R_Tree* p, int k);

// Удалить дерево с корнем *root
void DeleteTree(R_Tree* &root);

// Подсчитать число листьев у дерева R_Tree с корнем *root
unsigned int Number_of_Leafs(R_Tree* root, unsigned int* counter = new unsigned int{ 0 });

//  ==========================================================================
//  =============   С Т Р  У К Т У Р А  -   Д Е Р Е В О     ==================
//  ==========================================================================


//============================================================================================================
/*	// Функция обращения автомата А2 по z(t) для первых 2^N бит
    A2 А -  заданный автомат А2
    vector<uint> zt - выходная последовательность автомата А2, по ней выполняется обращение
    ut - управляющая последовательность u(t)(булев вектор)		( пока что длиной до 32 бит )
    ut_size - длина u(t)	[1, 32]
    i - шаг рекурсии
*/
void Reverse_from_zt_only_first_2pow_N_bits(A2& A, R_Tree* &root, std::vector<unsigned int> zt, int ut_size, int i);





// Генерация случайной u(t) с заданным весом W и длины N (0<N<=32)
unsigned int Generate_Random_ut(unsigned int W, unsigned int N);
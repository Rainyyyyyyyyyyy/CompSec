// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "FSM.h"
#include <math.h>
#include <time.h>
#include <chrono>




/*void set_complete_cycle_permutation(std::vector<int>& a, int size) {
    std::vector<unsigned int> cache;
    a.clear();
    for (int i = 0; i < size - 1; i++) {
        cache.push_back(i + 1); a.push_back(0);
    }
    a.push_back(0);

    int wall = size - 1;                        // Эта неработает
    int i = 0;
    int j = 0;
    for (wall; wall > 0; wall--) {
        j = rand() % wall;
        a[i] = cache[j];
        Swap(cache[j], cache[wall - 1]);
        i = cache[j];
    }
    //a[size - 1] = cache[0];
}
void set_complete_cycle_permutation(std::vector<unsigned int> &a, int size) {
    std::vector<unsigned int> cache;
    a.clear();
    for (int i = 0; i < size-1; i++) {
        cache.push_back(i+1); a.push_back(0);
    }
    a.push_back(0);

    int wall = size - 1;
    int i = 0;
    int j = 0;
    for (wall; wall > 0; wall--) {
        j = rand() % wall;
        a[i] = cache[j];
        i = cache[j];
        Swap(cache[j], cache[wall - 1]);
        
    }

    //a[size - 1] = cache[0];
}
*/

void set_complete_cycle_permutation(std::vector<unsigned int>& a, int size) {
    std::vector<unsigned int> cache;
    a.clear();
    for (int i = 0; i < size - 1; i++) {
        cache.push_back(i + 1); a.push_back(0);
    }
    a.push_back(0);

    int wall = size - 1;
    int i = 0;
    int j = 0;
    for (wall; wall > 0; wall--) {
        j = rand() % wall;
        a[i] = cache[j];
        i = cache[j];
        Swap(cache[j], cache[wall - 1]);
    }
}

int main()
{                     
    srand(time(NULL));

    std::cout << "Need to debug: E:\\VSYAKOE_DLYA_UCHOBY\\4kurs1Cem\\.Dlya_Kursovoi\\Programma_avtomata_A2\\try2\\To_Debug.txt\n\n\n";

    

    /*for (int i = 0; i < 7; i++)std::cout << i << ' ';
    std::cout << '\n';
    std::vector<unsigned int> a;
    int size = 7;
    for (int j = 0; j < 10; j++) {
        set_complete_cycle_permutation(a, size);
        for (int i = 0; i < 7; i++)std::cout << a[i] << ' ';
        std::cout << '\n';
    }
    return 0;
    */



    /*
    unsigned int M = 5;
    unsigned int g2_Size = 1 << M;
    unsigned int f2_size = f2_size = (M < 5) ? 1 : 1 << (M - 5);

    std::vector<unsigned int> g20;// = new unsigned int[g2_Size];
    unsigned int* g21 = new unsigned int[g2_Size];

    unsigned int* f20 = new unsigned int[f2_size];
    unsigned int* f21 = new unsigned int[f2_size];

    */

    //set_complete_cycle_permutation(g20, g2_Size);
    //g20[0] = 3;
    //g20[1] = 2;
    //g20[2] = 0;
    //g20[3] = 1;
    /*for (int i = 0; i < g2_Size; i++)std::cout << i << '\t';
    std::cout << '\n';
    for (int i = 0; i < g2_Size; i++) {
        std::cout << g20[i] << '\t';
    }*/
    std::vector<unsigned int> zt;
    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =   
    //  =   =   =        Общие параметры автомата А2        =   
    //  =   =   =   =   =   =   =   =   =   =   =   =   =   =
    unsigned int M = 2;             // поряжок автомата А2
    unsigned int w_f2 = 3;          // вес функции выходов автомата А2
    A2 a2(M, 0u, 1, w_f2);
    a2.change_g21((Permut(a2.get_g20()).pow(0)).To_Vector());


    a2.Output();
    std::cout << '\n';
    std::cout << "w(f2): " << w_f2 << '\n';
    //unsinged int U = 0b1011<<28;         // управляющая последовательность u(t)      булев вектор
    int U_S = 2;                // порядок управляющей последовательности u(t) (до 5-го порядка)
    int U_size = 1<<(U_S);             // кол-во бит в управляющей последовательности (2^U_S) (до 32 бит)
    unsigned int U = Generate_Random_ut(3, U_size);
    int zt_size = 1 << (M + U_S);
    int zt_mas_size = (zt_size >> 5)?zt_size>>5 : 1;
    for (int i = 0; i < zt_mas_size; i++)zt.push_back(0);

    std::cout << "u(t): ";
    for (int i = 0; i < U_size; i++) {
        std::cout << ((U >> (31 - i)) & 1) << ' ';
    }
    
    std::cout << '\n';
    std::cout << '\n';
    unsigned int M_sh = 1 << M;
    for (int i = 0; i < M_sh; i++) {
        for (int j = 0; j < U_size; j++) {
            std::cout << a2.get_output((U >> (31 - j))&1);
            zt[(i * U_size + j) >> 5] = zt[(i * U_size + j) >> 5] | (a2.get_output((U >> (31 - j)) & 1) << (31 - ((i * U_size + j) & 31))); //(zt[(i * U_size + j - 1) >> 5] << 1) | a2.get_output((U >> (U_size - j)) & 1);
            a2.transit((U >> (31 - j)) & 1);
        }
        std::cout << '\n';
    }
    M_sh = 1 << M;
    std::cout << '\n';
    for (int i = 0; i < M_sh; i++) {
        for (int j = 0; j < U_size; j++) {
            //zt[(i * U_size + j - 1) >> 5] = zt[(i * U_size + j - 1) >> 5] | (a2.get_output((U >> (U_size - j)) & 1) << (31 - ((i * U_size + j - 1) & 31))); //(zt[(i * U_size + j - 1) >> 5] << 1) | a2.get_output((U >> (U_size - j)) & 1);
            a2.transit((U >> (31 - j)) & 1);
            std::cout << a2.get_current_state()<<'\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';


    /*unsigned int ff20u = (unsigned int)(0b00000001 << 28);
    unsigned int ff21u = (unsigned int)(0b10010001 << 28);
    unsigned int f_xoru = ff20u ^ ff21u;

    std::vector<unsigned int> ff20 = { ff20u };
    std::vector<unsigned int> ff21 = { ff21u };
    std::vector<unsigned int> f_xor = { f_xoru };
    
    a2.change_f20(ff20);
    a2.change_f21(ff21);

    a2.Output();
    for (int i = 0; i < zt_mas_size; i++)zt[i] = 0;
    std::cout << '\n';
    M_sh = 1 << M;
    for (int i = 0; i < M_sh; i++) {
        for (int j = 1; j <= U_size; j++) {
            std::cout << a2.get_output((U >> (U_size - j)) & 1);
            zt[(i * U_size + j - 1) >> 5] = (zt[(i * U_size + j - 1) >> 5] << 1) | a2.get_output((U >> (U_size - j)) & 1);
            a2.transit((U >> (U_size - j)) & 1);
        }
        std::cout << '\n';
    }
    */
    for (int i = 0; i < zt_mas_size; i++) {
        for (int j = 0; j < 32; j++) {
            std::cout << ((zt[i] >> (31 - j)) & 1);
            if (((j+1) & (U_size-1)) == 0)std::cout << '\n';
        }
    }




    //  =   =   =   =   =   =   =   =   =   =   =   =   =   
    //  =   =   =   =    попытка обрaщения 1  =   =   =   
    //  =   =   =   =   =   =   =   =   =   =   =   =   =
    R_Tree* ROOT = new R_Tree;
    ROOT->left = ROOT->right = ROOT->back = nullptr;
    ROOT->s = a2.get_current_state();



    Reverse_from_zt_only_first_2pow_N_bits(a2, ROOT, zt, U_size, 0);
    std::cout << '\n';

    PrintTree(ROOT, 5);

    std::cout << '\n';
    std::cout << Number_of_Leafs(ROOT);

    std::cout << '\n';
    //std::cout << Generate_Random_ut(7, 16);

    return 0;


    /*Permut A(12, 1); A.Output(); std::cout << '\n';
    Permut B(4, 1);
        
    for (int i = 0; i < 16; i++) {
        (A << i).Output();
        std::cout << '\n';
    }
    return 0;
    Permut C = A * B;

    A.Output();
    std::cout << '\n';

    B.Output();
    std::cout << '\n';

    C.Output();
    std::cout << '\n';
    */
    //delete[] g20;
    //delete[] g21;
    //delete[] f20;
    //delete[] f21;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

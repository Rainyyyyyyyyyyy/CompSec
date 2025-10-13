// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "BigNumber.h"
#include <time.h>
#include <chrono>
#include <math.h>
#include <vector>

// Свап
template <class T> void Swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}

// НОД int'ов методов Еклида
int NOD(int a, int b) {
    while (b != 0) {
        a = a % b;
        //std::cout << a << '\n';
        swap(a, b);
    }
    return a;
}

// проверка на В-гладкость числа N
bool check_B_glad(int N, int B) {
    bool* isPrime = new bool[B];
    for (int i = 2; i < B; i++)isPrime[i] = true;
    for (int i = 2; i < B; i++) {
        if (isPrime[i]) {
            for (int j = i * 2; j < B; j += i)isPrime[j] = false;
        }
    }
    int wall = 0;
    for (int i = 2; i < B; i++)if (isPrime[i])wall++;
    int* primes = new int[wall];
    int j = 0;
    for (int i = 2; i < B; i++)if (isPrime[i])primes[j++] = i;

    //for (int i = 0; i < wall; i++)std::cout << primes[i] << ' ';
    //std::cout << '\n';


    j = 0;
    while (j!=wall) {
        while (N && N % primes[j] == 0) {
            N = N / primes[j];
        }
        j++;
    }
    if (N>1 || N==0)return false; else return true;



    return false;

}

// вывод матрицы векторов
void Output_Matrix_vector(std::vector < std::vector < int > > M) {
    for (std::vector<int>& i : M) {
        for (int& j : i)std::cout << j << ' ';
        std::cout << '\n';
    }
}

// Функция для рекурсивного вычисления определителя
int determinant(int matrix[5][5], int n) {
    int det = 0;
    int submatrix[5][5];

    // Базовый случай для матрицы 1x1
    if (n == 1) {
        return matrix[0][0];
    }

    // Базовый случай для матрицы 2x2
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    // Рекурсивный случай для больших матриц
    int sign = 1;
    for (int k = 0; k < n; k++) {
        // Создание подматрицы
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == k) continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }

        // Рекурсивное вычисление
        det += sign * matrix[0][k] * determinant(submatrix, n - 1);
        sign = -sign;
    }

    return det;
}


// факторизация по фактор-базе
std::vector<int> Factor_by_FactorBase(std::vector<int> FactorBase, int N) {
    std::vector<int>result;
    for (int i = 0; i < FactorBase.size(); i++) {
        result.push_back(0);
        while (N && N % FactorBase[i] == 0) {
            N = N / FactorBase[i];
            result[i]++;
        }
    }
    return result;
}


// разность строк уже в булевом виде (a-b) (для получения нулей под главной диагональю)
 std::vector<int> Sub(std::vector<int> a, std::vector<int> b) {
    std::vector<int> local = a;
    for (int i = 0; i < a.size(); i++) {
        local[i] = local[i] ^ b[i];
    }
    return local;
}


 // приведение к треугольному виду (нули под главной диагональю)
 void triangularize_matrix(std::vector < std::vector <int> >& MT) {
     int MT_size_y = MT.size();
     int MT_size_x = MT[0].size();
     //================================================
        /* Получение нулей под главной диагональю */
     int index_need_to_zero_y = 1; // индекс (строки), в которой на текущей позиции получаем 0
     int index_need_to_zero_x = 0; // индекс (столбца), в котором на текущей строке (index_need_to_zero_y) получаем 0
     int index_deal_to_zero = 1; // индекс (строки), с помощью которой получаем ноль для index_need_to_zero-й строки
     for (; index_need_to_zero_x < MT_size_y;) {
         // ищем, нужно ли убрать единицу в столбце [index_need_to_zero_x]
         for (index_need_to_zero_y; index_need_to_zero_y < MT_size_y; index_need_to_zero_y++) {
             if (MT[index_need_to_zero_y][index_need_to_zero_x] == 1)break;
         }
         // если прошлись по всему стобцу, то отлично, переход на след. столбец
         if (index_need_to_zero_y == MT_size_y) {
             index_need_to_zero_y = index_need_to_zero_x + 2; index_need_to_zero_x++; continue;
         }

         for (index_deal_to_zero = index_need_to_zero_y + 1; index_deal_to_zero < MT_size_y; index_deal_to_zero++) {
             if (MT[index_deal_to_zero][index_need_to_zero_x] == 1)break;
         }
         // не нашли вторую единицу для вычитания, значит обращаемся к главной диагонали
         if (index_deal_to_zero == MT_size_y) {
             // если гл.диагональ имеет единицу - вычитаем её из текущей строки
             if (MT[index_need_to_zero_x][index_need_to_zero_x] == 1) {
                 //for (int ii = 0; ii < MT_size_y; ii++) {
                 //    for (int jj = 0; jj < MT_size_x; jj++) {
                 //        if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                 //            if (ii == index_need_to_zero_x && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                 //                std::cout << MT[ii][jj] << ' ';
                 //    }
                 //    std::cout << '\n';
                 //}
                 //std::cout << '\n';
                 MT[index_need_to_zero_y] = Sub(MT[index_need_to_zero_y], MT[index_need_to_zero_x]);
             }
             // иначе меняем местами эту строку и строку с главной диагонали
             else {
                 //for (int ii = 0; ii < MT_size_y; ii++) {
                 //    for (int jj = 0; jj < MT_size_x; jj++) {
                 //        if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                 //            if (ii == index_need_to_zero_x && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']';
                 //            else std::cout << MT[ii][jj] << ' ';
                 //    }
                 //    std::cout << '\n';
                 //}
                 //std::cout << '\n';
                 Swap(MT[index_need_to_zero_y], MT[index_need_to_zero_x]);
             }
         }
         else {
             //for (int ii = 0; ii < MT_size_y; ii++) {
             //    for (int jj = 0; jj < MT_size_x; jj++) {
             //        if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
             //            if (ii == index_deal_to_zero && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']';
             //            else std::cout << MT[ii][jj] << ' ';
             //    }
             //    std::cout << '\n';
             //}
             //std::cout << '\n';
             MT[index_need_to_zero_y] = Sub(MT[index_need_to_zero_y], MT[index_deal_to_zero]);
         }
         index_need_to_zero_y = index_deal_to_zero;
         index_deal_to_zero = index_need_to_zero_y + 1;
     }
     std::cout << "NOLI pod diagonal'yu: \n";
     for (int i = 0; i < MT_size_y; i++) {
         for (int j = 0; j < MT_size_x; j++) {
             if (i == j)std::cout << '[';
             std::cout << MT[i][j];
             if (i == j)std::cout << ']';
         }
         std::cout << '\n';
     }
 }


int main()
{
    

    srand(time(NULL));
    
    
    //*   *   *   * генерация начальной последовательности (ai, bi)
    //*   *   *   * для метода случаных квадратов: метод диксона
    int N;
    std::cin >> N;
    std::vector<int> Factorbase = { 2, 3, 5, 7};
    int F_size = Factorbase.size() + 1;
    int M_size = F_size;

    std::vector<std::vector<int> > M;

    int B = Factorbase[Factorbase.size() - 1];
    for (int j = 0; j < Factorbase.size(); j++)std::cout << Factorbase[j] << ' ';
    std::cout << '\n';//std::cout << Factorbase << '\n';
    int counter = 0;
    for (int i = sqrt(N); counter<Factorbase.size()+1; i++) {
        if (check_B_glad((i * i) % N, B + 1)) {
            std::cout << "a" << counter << " = " << i << "\t" << "b" << counter++ << " = " << (i * i) % N << "\t\t(";
            std::vector<int> facta = Factor_by_FactorBase(Factorbase, (i * i) % N);
            M.push_back(facta);
            for (int j : facta)std::cout << j << ' ';
            std::cout << ")\n";
        }
    }

    /* вывод матрицы и приведение её в булев вид*/
    for (std::vector<int> &i : M)
        for (int &j : i)j = j & 1;

    for (std::vector<int> &i : M) {
        for (int &j : i)std::cout << j << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
    //===========================================
    /* фильтрование одинаковых строк */
    //for (int i = 0; i < M_size; i++) {
    //    for (int j = i + 1; j < M_size; j++) {
    //        if (M[i] == M[j]) {
    //            Swap(M[j], M[M_size - 1]);
    //            M.pop_back();
    //            M_size--;
    //            j--;
    //            break;
    //        }
    //    }
    //}

    //for (std::vector<int>& i : M) {
    //    for (int& j : i)std::cout << j << ' ';
    //    std::cout << '\n';
    //}
    //std::cout << '\n';
    //===========================================
    /* Транспонирование */
    std::vector<int> NOL; for (int i = 0; i < M_size; i++)NOL.push_back(0);
    std::vector<std::vector<int>> MT;
    for (int i = 0; i < F_size-1; i++) {      
        MT.push_back(NOL);
        for (int j = 0; j < M_size; j++) {
            MT[i][j] = M[j][i];
        }

    }
    int MT_size_y = MT.size();
    int MT_size_x = MT[0].size();
    for (std::vector<int>& i : MT) {
        for (int& j : i)std::cout << j << ' ';
        std::cout << '\n';
    }
    std::cout<< '\n';
    //==========================================
    /* Фильтрование одинаковых и нулевых строк в MT */
    for (int i = 0; i < MT_size_y; i++) {
        for (int j = i + 1; j < MT_size_y; j++) {
            if (MT[i] == NOL) {
                Swap(MT[i], MT[MT_size_y - 1]);
                MT.pop_back();
                MT_size_y--;
                i--;
                break;
            }
            if (MT[i] == MT[j] || MT[j] == NOL) {
                Swap(MT[j], MT[MT_size_y - 1]);
                MT.pop_back();
                MT_size_y--;
                j--;
            }
        }
    }
    if (MT_size_y == 0) { std::cout << "Matrix is empty..........."; }
    std::cout << "MT filtered: \n";
    for (int i = 0; i < MT_size_y; i++) {
        for (int j = 0; j < MT_size_x; j++) {
            if (i == j)std::cout << '[';
            std::cout << MT[i][j];
            if (i == j)std::cout << ']';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << "Processing: \n";
    //================================================
    /* Получение нулей под главной диагональю */
    int index_need_to_zero_y = 1; // индекс (строки), в которой на текущей позиции получаем 0
    int index_need_to_zero_x = 0; // индекс (столбца), в котором на текущей строке (index_need_to_zero_y) получаем 0
    int index_deal_to_zero = 1; // индекс (строки), с помощью которой получаем ноль для index_need_to_zero-й строки
    for(; index_need_to_zero_x<MT_size_y;) {
        // ищем, нужно ли убрать единицу в столбце [index_need_to_zero_x]
        for (index_need_to_zero_y; index_need_to_zero_y < MT_size_y; index_need_to_zero_y++){
            if (MT[index_need_to_zero_y][index_need_to_zero_x] == 1)break;
        }
        // если прошлись по всему стобцу, то отлично, переход на след. столбец
        if (index_need_to_zero_y == MT_size_y) {
            index_need_to_zero_y = index_need_to_zero_x+2; index_need_to_zero_x++; continue;
        }
        
        for (index_deal_to_zero = index_need_to_zero_y + 1; index_deal_to_zero < MT_size_y; index_deal_to_zero++) {
            if (MT[index_deal_to_zero][index_need_to_zero_x] == 1)break;
        }
        // не нашли вторую единицу для вычитания, значит обращаемся к главной диагонали
        if(index_deal_to_zero == MT_size_y){
            // если гл.диагональ имеет единицу - вычитаем её из текущей строки
            if (MT[index_need_to_zero_x][index_need_to_zero_x] == 1) {
                for (int ii = 0; ii < MT_size_y; ii++) {
                    for (int jj = 0; jj < MT_size_x; jj++) {
                        if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                        if (ii == index_need_to_zero_x && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                        std::cout << MT[ii][jj]<<' ';
                    }
                    std::cout << '\n';
                }
                std::cout << '\n';
                MT[index_need_to_zero_y] = Sub(MT[index_need_to_zero_y], MT[index_need_to_zero_x]);
            }
            // иначе меняем местами эту строку и строку с главной диагонали
            else {
                for (int ii = 0; ii < MT_size_y; ii++) {
                    for (int jj = 0; jj < MT_size_x; jj++) {
                        if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                        if (ii == index_need_to_zero_x && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']';
                        else std::cout << MT[ii][jj]<<' ';
                    }
                    std::cout << '\n';
                }
                std::cout << '\n';
                Swap(MT[index_need_to_zero_y], MT[index_need_to_zero_x]);
            }
        }
        else {
            for (int ii = 0; ii < MT_size_y; ii++) {
                for (int jj = 0; jj < MT_size_x; jj++) {
                    if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']';else 
                    if (ii == index_deal_to_zero && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']';
                    else std::cout << MT[ii][jj] << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
            MT[index_need_to_zero_y] = Sub(MT[index_need_to_zero_y], MT[index_deal_to_zero]);
        }
        index_need_to_zero_y = index_deal_to_zero;
        index_deal_to_zero = index_need_to_zero_y+1;
    }
    std::cout << "NOLI pod diagonal'yu: \n";
    for (int i = 0; i < MT_size_y; i++) {
        for (int j = 0; j < MT_size_x; j++) {
            if (i == j)std::cout << '['; 
            std::cout << MT[i][j];
            if (i == j)std::cout << ']';
        }
        std::cout << '\n';
    }
    //===================================================
       /* Фильтрование одинаковых и нулевых строк в MT после получения нулей под диагональю */
    for (int i = 0; i < MT_size_y; i++) {
        for (int j = i + 1; j < MT_size_y; j++) {
            if (MT[i] == NOL) {
                Swap(MT[i], MT[MT_size_y - 1]);
                MT.pop_back();
                MT_size_y--;
                i--;
                break;
            }
            if (MT[i] == MT[j] || MT[j] == NOL) {
                Swap(MT[j], MT[MT_size_y - 1]);
                MT.pop_back();
                MT_size_y--;
                j--;
            }
        }
    }
    if (MT_size_y == 0) { std::cout << "Matrix is empty..........."; }
    std::cout << "MT filtered (NOLI pod diagonal'yu): \n";
    for (int i = 0; i < MT_size_x; i++)std::cout << i << ' '; std::cout << '\n';
    for (int i = 0; i < MT_size_x * 2; i++)std::cout << '-'; std::cout << '\n';
    Output_Matrix_vector(MT);
    //===============================================================
    
    // Выбор базисного минора (переменные в нём будут "связанные", остальные "свободными")
    // у базисного минора определитель не равен 0       < ! >
    bool Basis_captured = false;
    std::vector < std::vector < int> > Basis_minor;
    int R = MT_size_y;  // ранг базисного минора 
    std::vector<int>choses; // выбранные столбцы для базисного минора (их всего R)
    for (int i = 0; i < R; i++)choses.push_back(MT_size_x);
    int i = 0;
    int j = 0;
    while (!Basis_captured) {
        //i = 0;
        for (i; i < R; i++) {
            //int j = 0;
            for (j; j < MT_size_x; j++) {
                bool repeat_flag = false;
                for (int k = 0; k < choses.size(); k++) {
                    if (j == choses[k]) { repeat_flag = true; break; }
                }
                if (repeat_flag == false && MT[i][j] == 1) { choses[i] = j;  j = i; break; }
            }
            if (j == MT_size_x) {
                if (i == 0) {
                    std::cout << "\n\n";
                    Output_Matrix_vector(MT);

                    std::cout << "\nNon solvable... :(\n";
                    return 0;
                }
                choses[i] = MT_size_x;
                j = choses[i - 1];
                i -= 2;
                //choses[i-1] = 0;
            }
            std::cout << "Chosen for B: "; for (int i : choses)std::cout << i << ' '; std::cout << "\ti,j: " << i << ' ' << j;
            std::cout << '\n';
        }
        std::cout << "Chosen for B: "; for (int i : choses)std::cout << i << ' ';
        std::cout << '\n';
        // генерация этого выбранного минора и проверка его определителя
        for (int i = 0; i < R; i++) {
            std::vector <int> stroka;
            for (int j = 0; j < R; j++) {
                stroka.push_back(MT[i][choses[j]]);
            }
            Basis_minor.push_back(stroka);
        }
        std::cout << "Basis minor: \n";
        Output_Matrix_vector(Basis_minor);
        std::cout << '\n';
        triangularize_matrix(Basis_minor);
        std::cout << "Basis minor(triangulazed): \n";
        Output_Matrix_vector(Basis_minor);
        bool flag_diagonal_contains_zero = false;
        for (int i = 0; i < R; i++) {
            if (Basis_minor[i][i] == 0) { flag_diagonal_contains_zero = true; break; }
        }
        // Если в гл.диагонали есть ноль, то определитель 0, следовательно нужно искать другой базисный минор
        if (flag_diagonal_contains_zero) {
            Basis_minor.clear();
            j = choses[R-1]+1;
            choses[R-1] = MT_size_x;
            i = MT_size_y - 1;
            continue;
        }
        else break;
        //std::cout << '\n';
        //return 0;
    }
    std::cout << "Final Basis minor: \n";
    Output_Matrix_vector(Basis_minor);
    //==============================================================
    // Базисный минор нашли, отлично
    // Вывод зависимых и свободных переменных 
    std::vector<int> frees;     // свободные переменные
    for (int i = 0; i < MT_size_x; i++)frees.push_back(i);
    std::cout << "\n3aBucuMble xi: ";
    for (i = 0; i < R; i++) {
        std::cout << 'x' << choses[i]<<' ';
        for (j = 0; j < frees.size(); j++) {
            if (choses[i] == frees[j])break;
        }
        Swap(frees[j], frees[frees.size()-1]);
        frees.pop_back();
    } 
    std::cout << "\nCBo6ogHble xi: ";
    int frees_size = frees.size();
    for (int i = 0; i < frees_size; i++)std::cout << 'x' << frees[i] << ' ';
    std::cout << '\n';
    for (int i = 0; i < MT_size_x; i++)std::cout << i << ' '; std::cout << '\n';
    for (int i = 0; i < MT_size_x * 2; i++)std::cout << '-'; std::cout << '\n';
    Output_Matrix_vector(MT);
    //===============================================================
    // Вывод уравений относительно зависимых (fi(зав-е) = gi(своб-е))
    for(int i = 0; i < MT_size_y; i++) {
        for (int j = 0; j < R; j++) {
            if (MT[i][choses[j]] == 1)std::cout << " + x" << choses[j];
            std::cout << '\t';
        }
        std::cout << " = ";
        for (int j = 0; j < frees_size; j++) {
            if (MT[i][frees[j]] == 1)std::cout << " + x" << frees[j];
        }
        std::cout << '\n';
    }
    //===============================================================
    // Решение полученной системы линейных уравнений с помощью ФСР 
    /*std::vector < std::vector < int > > basis_C;
    for (int i = 0; i < frees_size; i++) {
        for (int k = R-1; k >=0; k--) {
            std::vector<int> local;
            for (int j = 0; j < R; j++)local.push_back(0);
            int answer = 0;
            for (int f = 0; f < frees_size; f++)answer = answer ^ frees[f];
            local[choses[k]] = answer;
        }
    }*/
    return 0;

}


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
    if (N < 0)N = N * (-1);
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
        while (N!=1 && N % primes[j] == 0) {
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
    int i = 0;
    //if (N < 0) { N = N * (-1); result.push_back(1); }
    if (FactorBase[0] < 0) {
        i++; result.push_back(N < 0); N = (N < 0) ? N * -1 : N;
    }
    for (i; i < FactorBase.size(); i++) {
        result.push_back(0);
        while (N && N % FactorBase[i] == 0) {
            N = N / FactorBase[i];
            result[i]++;
        }
    }
    return result;
}


// Проверка на разложение только в факторной базе
bool is_Factor_by_FactorBase(std::vector<int> FactorBase, int N) {
    bool result = false;
    int i = 0;
    //if (N < 0) { N = N * (-1); result.push_back(1); }
    if (FactorBase[0] < 0) {
        i++; N = (N < 0) ? N * -1 : N;//result.push_back(N < 0); N = (N < 0) ? N * -1 : N;
    }
    for (i; i < FactorBase.size(); i++) {
        //result.push_back(0);
        while (N && N % FactorBase[i] == 0) {
            N = N / FactorBase[i];
            //result[i]++;
        }
    }
    return N <= 1;
    //return result;
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
    int Functionality = 0;
    std::cout <<"Enter 0 for Dikson's algorythm\nEnter 1 for generating cyclic group: ";
    std::cin >> Functionality;
    //*   *   *   * генерация начальной последовательности (ai, bi)
    //*   *   *   * для метода случаных квадратов: метод диксона
    if (Functionality == 0) {
        int N;
        std::cout << "Enter N: ";
        std::cin >> N;
        int T = 0;
        std::cout << "Enter T(Skolko dop. par): ";
        std::cin >> T;
        T++;
        std::vector<int> Factorbase = { 2, 3, 5, 7 };
        int F_size = Factorbase.size() + 1;
        int M_size = F_size;

        std::vector<std::vector<int> > M;
        //  1 - метод Диксона подбора пар   
        //  2 - Метод квадратичного решета  (от руки искать факторную базу)
        //  3 - Метод цепных дробей         (от руки искать факторную базу)
        std::cout << "Enter type: 1 - Deekson's, 2 - square_sheet, 3 - chain_divs: ";
        int type = 0; std::cin >> type;
        if (type == 1) {
            int B = Factorbase[Factorbase.size() - 1];
            for (int j = 0; j < Factorbase.size(); j++)std::cout << Factorbase[j] << ' ';
            std::cout << '\n';//std::cout << Factorbase << '\n';
            int counter = 0;
            for (int i = sqrt(N); counter < Factorbase.size() + T; i++) {
                if (check_B_glad((i * i) % N, B + 1)) {
                    std::cout << "a" << counter << " = " << i << "\t" << "b" << counter++ << " = " << (i * i) % N << "\t\t(";
                    std::vector<int> facta = Factor_by_FactorBase(Factorbase, (i * i) % N);
                    M.push_back(facta);
                    for (int j : facta)std::cout << j << ' ';
                    std::cout << ")\n";
                }
            }
        }
        else if (type == 2) {
            Factorbase.clear();
            Factorbase.emplace_back(2);
            bool* isPrime = new bool[1000];
            std::vector<int> q_primals;
            for (int i = 2; i * i < 1000; i++) {
                if (isPrime[i]) {
                    for (int j = i * i; j < 1000; j += i) {
                        isPrime[j] = false;
                    }
                }
            }
            for (int i = 2; i < 1000; i++)if (isPrime[i])q_primals.push_back(i);
            
            //for (int i = 0; i < q_primals.size(); i++)std::cout << q_primals[i] << '\n';
              
            int jjj = 1;
            BM NBM = N;
            for (int i = 0; i < 2; i++) {
                for (jjj; jjj < q_primals.size(); jjj++) {
                    if (NBM.Jacobi_symbol(q_primals[jjj]) == 1) {
                        Factorbase.emplace_back(q_primals[jjj]);
                        jjj++;
                        break;
                    }
                }
                // сделать список простых чисел методов кв. решета(например) и искать файт. базу 
                // проверяя чиселки символов Якоби (для простого основаня он поглощает полностью Лежандра)
            }
            Factorbase.emplace(Factorbase.begin(), -1);
            for (int i = 0; i < Factorbase.size(); i++) {
                std::cout << Factorbase[i] << ' ';
            }std::cout << '\n';

            int m = sqrt(N);
            int l_i = 0;
            if (m * m - N == -81) {
                m = m;
            }
            if (is_Factor_by_FactorBase(Factorbase, m*m-N)){//_check_B_glad(m*m-N, Factorbase[Factorbase.size() - 1] + 1)) {
                std::vector<int> facta = Factor_by_FactorBase(Factorbase, m*m-N);
                std::cout << "a" << 0 << " = " << m << "\t" << "b" << 0 << " = " << m*m-N << "\t\t(";
                for (int j : facta)std::cout << j << ' ';
                std::cout << ")\n";
                M.push_back(facta);
                l_i++;
            }


            for (int i = l_i, i1 = i, i2 = -i; i < Factorbase.size() + T; i1++, i2--) {
                int a1 = i1 + m;
                int a2 = i2 + m;

                int b1 = a1 * a1 - N;
                int b2 = a2 * a2 - N;

                if (is_Factor_by_FactorBase(Factorbase, b1)){//(b1, Factorbase[Factorbase.size() - 1] + 1)) {
                    std::vector<int> facta = Factor_by_FactorBase(Factorbase, b1);
                    std::cout << "a" << i << " = " <<a1 << "\t" << "b" << i << " = " << b1 << "\t\t(";
                    for (int j : facta)std::cout << j << ' ';
                    std::cout << ")\n";
                    M.push_back(facta);
                    i++;
                }
                if (is_Factor_by_FactorBase(Factorbase, b2)) {//check_B_glad(b2, Factorbase[Factorbase.size() - 1] + 1)) {
                    std::vector<int> facta = Factor_by_FactorBase(Factorbase, b2);
                    std::cout << "a" << i << " = " << a2 << "\t" << "b" << i << " = " << b2 << "\t\t(";
                    for (int j : facta)std::cout << j << ' ';
                    std::cout << ")\n";
                    M.push_back(facta);
                    i++;
                }
            }
        }
        else if (type == 3) {
            Factorbase.clear();
            Factorbase.emplace_back(2);
            bool* isPrime = new bool[1000];
            std::vector<int> q_primals;
            for (int i = 2; i * i < 1000; i++) {
                if (isPrime[i]) {
                    for (int j = i * i; j < 1000; j += i) {
                        isPrime[j] = false;
                    }
                }
            }
            for (int i = 2; i < 1000; i++)if (isPrime[i])q_primals.push_back(i);

            //for (int i = 0; i < q_primals.size(); i++)std::cout << q_primals[i] << '\n';

            int jjj = 1;
            BM NBM = N;
            for (int i = 0; i < 2; i++) {
                for (jjj; jjj < q_primals.size(); jjj++) {
                    if (NBM.Jacobi_symbol(q_primals[jjj]) == 1) {
                        Factorbase.emplace_back(q_primals[jjj]);
                        jjj++;
                        break;
                    }
                }
                // сделать список простых чисел методов кв. решета(например) и искать файт. базу 
                // проверяя чиселки символов Якоби (для простого основаня он поглощает полностью Лежандра)
            }
            Factorbase.emplace(Factorbase.begin(), -1);
            for (int i = 0; i < Factorbase.size(); i++) {
                std::cout << Factorbase[i] << ' ';
            }std::cout << '\n';
            
            std::vector <int> qqi;
            std::vector <int> ci;
            std::vector <int> alphai;

            qqi.push_back(sqrt(N));
            ci.push_back(1);
            alphai.push_back(qqi[0]);
            int i = 1;
            std::cout << "qi ci, alphai: \n";
            do {        // раскладываем корень в цепную дробь
                ci.push_back((N - alphai[i - 1] * alphai[i - 1]) / ci[i - 1]);  // ci = (n-a[i-1]^2) / c[i-1]
                qqi.push_back((sqrt(N) + alphai[i - 1]) / ci[i]);               // qi = ([√n] + a[i-1]) / ci
                alphai.push_back(-(alphai[i - 1] - (qqi[i] * ci[i])));             // ai = a[i-1] - qi*ci
                std::cout << qqi[i]<<' '<<ci[i]<<' '<<alphai[i] << '\n';
                //qqi.push_back(ci[i - 1] * (sqrt(N) + alphai[i - 1]) / (N - alphai[i - 1] * alphai[i - 1]));
                //ci.push_back((N - alphai[i - 1] * alphai[i - 1]) / ci[i - 1]);
                //alphai.push_back(alphai[i - 1] - qqi[i] * (N - alphai[i - 1] * alphai[i - 1]) / ci[i - 1]);
                i++;
            } while (ci[i-1] != ci[0] || alphai[i-1] != alphai[0]);
            // считаем подходящие дроби и проверяем их на условия ai = Pi mod n && bi = Pi^2 - n * Qi^2
            int cc = 0;
            int Pj = 0; int Qj = 0;         // Pn = qn*P[n-1] + P[n-2]
            int Pj1 = 1; int Qj1 = 0;       // Qn = qn*Q[n-1] + Q[n-2]
            int Pj0 = qqi[0]; int Qj0 = 1;
            for (i = 0; i < Factorbase.size() + T; i++) {
                int Ai = 0, Bi = 0;
                bool aibi_captured = false;
                
                do {
                    Pj = qqi[cc % (qqi.size() - 1) + 1] * Pj0 + Pj1;
                    Qj = qqi[cc % (qqi.size() - 1) + 1] * Qj0 + Qj1;
                    Pj1 = Pj0; Pj0 = Pj;
                    Qj1 = Qj0; Qj0 = Qj;
                    std::cout << "Pi = " << Pj << '\t' << "Qi = " << Qj << "\t\t";

                    Ai = Pj1 % N;
                    Bi = Pj1 * Pj1 - N * Qj1 * Qj1;
                    aibi_captured = is_Factor_by_FactorBase(Factorbase, Bi);// (Bi, Factorbase[Factorbase.size() - 1] + 1);
                    std::cout << 'a' << i << ": " << Ai << '\t' << 'b' << i << ": " << Bi<<'\t'<<aibi_captured<<'\n';
                    cc++;
                } while (aibi_captured == false);
                std::vector <int> facta = Factor_by_FactorBase(Factorbase, Bi);
                std::cout << "============     "<<'a' << i << ": " << Ai << '\t' << 'b' << i << ": " << Bi;
                std::cout << "( ";
                for (int i : facta)std::cout << i<<' ';
                std::cout << ')' << '\n';
                M.push_back(facta);
                //int ai = 0; int bi = 0;
                //bool captured_ai_bi = false;
                //while (!captured_ai_bi) {
                //    Pj = 0;
                //}
            }
        }
    
       
        /* вывод матрицы и приведение её в булев вид*/
        for (std::vector<int>& i : M)
            for (int& j : i)j = j & 1;

        for (std::vector<int>& i : M) {
            for (int& j : i)std::cout << j << ' ';
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
        F_size = Factorbase.size() + T;
        M_size = F_size;
        std::vector<int> NOL; for (int i = 0; i < M_size; i++)NOL.push_back(0);
        std::vector<std::vector<int>> MT;
        for (int i = 0; i < F_size - T; i++) {
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
        std::cout << '\n';
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
                    for (int ii = 0; ii < MT_size_y; ii++) {
                        for (int jj = 0; jj < MT_size_x; jj++) {
                            if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                                if (ii == index_need_to_zero_x && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                                    std::cout << MT[ii][jj] << ' ';
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
                                else std::cout << MT[ii][jj] << ' ';
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
                        if (ii == index_need_to_zero_y && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']'; else
                            if (ii == index_deal_to_zero && jj == index_need_to_zero_x)std::cout << MT[ii][jj] << ']';
                            else std::cout << MT[ii][jj] << ' ';
                    }
                    std::cout << '\n';
                }
                std::cout << '\n';
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
                j = choses[R - 1] + 1;
                choses[R - 1] = MT_size_x;
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
            std::cout << 'x' << choses[i] << ' ';
            for (j = 0; j < frees.size(); j++) {
                if (choses[i] == frees[j])break;
            }
            Swap(frees[j], frees[frees.size() - 1]);
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
        for (int i = 0; i < MT_size_y; i++) {
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
    BM a(1, 0); // от чего считать логарифм
    BM one("1");
    G g1;       // циклическая группа G
    std::cout << "Input module: ";
    g1.mod.InputDEC();
    std::cout << "Input < g >: ";
    g1.p.InputDEC();
    if (g1.mod.NOD(g1.p) != one) {
        std::cout << "NOD: "; (g1.mod.NOD(g1.p)).OutputDEC();
        std::cout << "g = "; g1.p.OutputDEC();
        std::cout << "cannot produce <g>\n";
        return 0;
    }
    g1.hexa.emplace_back(BM("1"));
    g1.size = one;
    BM step = g1.p;
    //BM one("1");
    while (step != one) {
        g1.hexa.emplace_back(step);
        //step.OutputDEC(); 
        step = step * g1.p % g1.mod;
        g1.size = g1.size + one;
    }
    //g1.size = g1.hexa.size();

    /*for (int i = 0; i < g1.hexa.size(); i++) {
        std::cout << '['<<i<<']'; g1.hexa[i].OutputDEC();
        std::cout << '\n';
    }*/
    std::cout << "\nsize: "; g1.size.OutputDEC();

    std::cout << "Enter a: "; a.InputDEC();
    bool flag = false;
    
    BM result = discrete_log_P0_Pollard_method(g1, a, flag);
    std::cout << "\nresult: ";
    result.OutputDEC();


    return 0;


    
    //*   *   *   *
    //*   *   *   *
    //*/

    //BM a(1.0);
    //a.InputDEC();
    //BM b(1,0);
    //auto start = std::chrono::high_resolution_clock::now(); // начало замера  
    //auto end = std::chrono::high_resolution_clock::now(); // конец замера  
    //std::chrono::duration<double> duration = end - start; // вычисление длительности
    //std::cout << "time: " << duration.count() << '\n';; 
    srand(time(NULL));
    /*int N = 100;
    bool* isPrime = new bool[N];
    for (int i = 2; i < N; i++)isPrime[i] = true;
    //Arrays.fill(isPrime, true);

    isPrime[1] = false;
    auto start = std::chrono::high_resolution_clock::now(); // начало замера  
    for (int i = 2; i * i < N; i++) {

        if (isPrime[i]) {
            for (int j = i * i; j < N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now(); // конец замера  
    std::chrono::duration<double> duration = end - start; // вычисление длительности  
    for (int i = 1; i < N; i++)std::cout << i << ' ' << isPrime[i] << '\n';
    int u = 0;
    for (int i = N - 1; i > 0; i--) {
        if (isPrime[i]) {
            u = i;
            break;
        }
    }
    std::cout << u << '\n';
    std::cout << '\n' << duration.count() << '\n';
    return 0;
    */
    //BM n(1, 0);
    //n.InputDEC();
    //bool flag = false;
    /*bool flag = false;
    auto start = std::chrono::high_resolution_clock::now(); // начало замера  
    BM kkk = n.P1_Pollard_method_factor(flag);
    auto end = std::chrono::high_resolution_clock::now(); // конец замера  
    std::chrono::duration<double> duration = end - start; // вычисление длительности  
    kkk.OutputDEC(); std::cout << '\n';
    std::cout << "time: " << duration.count() << '\n';;
    return 0;
    */
    /*std::vector<BM> PP = n.Ferma_method_factor(flag);
    PP[0].OutputDEC(); std::cout << '\n';
    PP[1].OutputDEC(); 
    return 0;
    BM p = n.P0_Pollard_method_factor(flag);
    p.OutputDEC();
    return 0;
    */
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

// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;



class Automata {
private:
    int n;
    vector <int> states;
    vector <int> transits;
    vector <int> outputs;
public:

    Automata() {
        n = 0;
        states.clear();
        transits.clear();
        outputs.clear();
    }

    ~Automata() {
        states.clear();
        transits.clear();
        outputs.clear();
        //states = NULL;
        //outputs = NULL;
        n = 0;
    }

    Automata(int N, int* s, int* o) {
        n = N;
        for (int i = 0; i < n; i++)states.push_back(i);
        //states = new int[n];
        //outputs = new int[n];
        for (int i = 0; i < n; i++) {
            transits.push_back(s[i]);
            outputs.push_back(o[i]);
        }
    }


    int get_state(int i) { return states[i]; }
    int get_transit(int i) { return transits[i]; }
    int get_output(int i) { return outputs[i]; }

    void Automata_Output() {
        for (int i = 0; i < n; i++)cout << states[i] << '\t';
        cout << endl;
        for (int i = 0; i < n; i++)cout << transits[i] << '\t';
        cout << endl;
        for (int i = 0; i < n; i++)cout << outputs[i] << '\t';
        cout << endl;
    }
};

class Automata_with_trans {      // расширенный класс, который описывает автомат А1 и имеет доп. поле для текущего состояния
    // int transit() переводит current_State в новое и возвращает выход(реакцию) автомата
// p.s. т.к. автомат А1 автономный, то вход не нужен
private:
    Automata au;
    int current_state;

public:

    Automata_with_trans() { Automata(); }
    ~Automata_with_trans() { au.~Automata(); }

    Automata_with_trans(int n, int* s, int* o, int st_s) {    // st_s - стартовое состояние А1
        au = Automata(n, s, o);
        current_state = st_s;
    }

    int transit() {             // функция перехода, возвращает выход 
        int i = current_state;
        current_state = au.get_transit(current_state);
        return au.get_output(i);

    }

    void Automata_Output() { au.Automata_Output(); }
};
class FSM {         // FSM - Finite State Machine       конечный автомат
private:
    int n;                  // кол-во состояний
    int m;                  // кол-во входов
    vector <int> states;    // переходы
    vector < vector <int> > transits;
    vector < vector <int> > outputs;   // выходы
public:

    FSM() {
        n = m = 0;
        states.clear();
        transits.clear();
        outputs.clear();
    }
    ~FSM() {
        states.clear();
        transits.clear();
        outputs.clear();
    }

    FSM(int N, int M, int **s, int **o) {   // s = n X 2, 
        n = N;                              //  1 2 3 4
        m = M;                              //  2 3 4 1
                                            //-------------
                                            // o = n X m
                                            // 1 2 3 4      : n
                                            // 1 0 1 1      : 0
                                            // 0 0 1 1      : 1
        states.clear();
        outputs.clear();
        transits.clear();
        
        vector <int> temp;
        temp.clear();
        for (int i = 0; i < n; i++)states.push_back(i);
        //for (int i = 0; i < n; i++)transits.push_back(s[i]);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                temp.push_back(s[i][j]);
            }
            transits.push_back(temp);
            temp.clear();
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                temp.push_back(o[i][j]);
            }
            outputs.push_back(temp);
            temp.clear();
        }
    }

    vector < vector <int> > get_transits() { return transits; }
    vector < vector <int> > get_outputs() { return outputs; }
    vector<int> get_states() { return states; }


    void FSM_output() {
        for (int i = 0; i < n; i++)cout << states[i] << '\t';
        cout << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << transits[i][j] << '/' << outputs[i][j] << '\t';
            }
            cout << endl;
        }
    }

};

class FSM_with_trans {
private:
    FSM fsm;
    int current_state;
public:

    FSM_with_trans() { FSM(); }
    ~FSM_with_trans() { fsm.~FSM(); }

    FSM_with_trans(int N, int M, int** s, int** o, int st_s) {
        current_state = st_s;
        fsm = FSM(N, M, s, o);
    }

    int transit(int input) {
        int i = current_state;
        current_state = fsm.get_transits()[input][current_state];
        return fsm.get_outputs()[input][i];
    }
};
/*
class Automata {            // автомат А1, автономный автомат
private:
    int sn;                 // количество состояний
    int on;                 // количество выходов
    int **states;
    int **outputs;

public:
    Automata() {
        sn = on = 0;
        states = NULL;
        outputs = NULL;
    }

    ~Automata() {
        if (states != NULL) {
            for (int i = 0; i < sn; i++)delete[] states[i];
            for (int i = 0; i < sn; i++)delete[] outputs[i];
            delete[] states;
            delete[] outputs;
        }
        on = sn = 0;
        states = NULL;
        outputs = NULL;
    }

    Automata(int sN, int oN, int** s, int **o) {
        sn = sN;
        on = oN;
        states = new int* [sn];
        outputs = new int* [sn];
        for (int i = 0; i < sn; i++) {
            states[i] = new int[n];
            for (int j = 0; j < n; j++) {
                states[i][j] = s[i][j];
                
            }
        }

        for(int i=0; i<)
    }

    void Output_Automata() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << states[i][j] << '/'<<outputs[i][j]<<' ';
            }
            cout << endl;
        }
    }

};

*/
/*
class FSM {     // Finite State Machine
private:
    int s;

};
*/
int main()
{
    /*int** at = new int* [2];
    for (int i = 0; i < 2; i++) {
        at[i] = new int[4];
        for (int j = 0; j < 4; j++) {
            at[i][j] = 0;
            cout << at[i][j] << ' ';
        }
        cout << endl;
    }*/


    int* x1 = new int[4];
    int* x2 = new int[4];
    for (int i = 0; i < 4; i++)x1[i] = (i+1)%4;
    x2[0] = 1;
    x2[1] = 0;
    x2[2] = 1;
    x2[3] = 1;
    Automata au(4, x1,x2);
    au.Automata_Output();
    Automata_with_trans AU(4, x1, x2, 0);
    AU.Automata_Output();
    //for (int i = 0; i < 100; i++)cout << AU.transit() << ' ';

    int** m = new int* [2];
    for (int i = 0; i < 2; i++) {
        m[i] = new int[4];
        for (int j = 0; j < 4; j++) {
            m[i][j] = (i+j) % 2;
        }
    }
    cout << "=============" << endl;
    FSM F(4, 2, m, m);
    F.FSM_output();
    //==========================================================
    int N = 4;
    int M = 4;
    int INPUTS = 2;
    int OUTPUTS = 2;
    int* g1 = new int[N];
    int* f1 = new int[N];
    f1[0] = 1; f1[1] = 0; f1[2] = 1; f1[3] = 1;
    for (int i = 0; i < N; i++)g1[i] = (i + 1) % N;

    int** g2 = new int*[INPUTS];
    int** f2 = new int*[INPUTS];
    for (int i = 0; i < 2; i++) {
        g2[i] = new int[N];
        f2[i] = new int[M];
    }
    g2[0][0] = 1;   g2[1][0] = 0;
    g2[0][1] = 2;   g2[1][1] = 1;
    g2[0][2] = 0;   g2[1][2] = 3;
    g2[0][3] = 3;   g2[1][3] = 2;

    f2[0][0] = 0;   f2[1][0] = 1;
    f2[0][1] = 0;   f2[1][1] = 1;
    f2[0][2] = 0;   f2[1][2] = 1;
    f2[0][3] = 0;   f2[1][3] = 0;




    Automata_with_trans A1(N, g1, f1, 0);
    FSM_with_trans A2(N, INPUTS, g2, f2, 0);
    for (int i = 0; i < 32; i++) {
        cout << A2.transit(A1.transit())<<' ';// system("pause");
    }
    
    /*
    cout << endl;
    for (int i = 0; i < 16; i++)cout << FFF.transit(i % 2)<<' ';
    */
    system("pause");
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

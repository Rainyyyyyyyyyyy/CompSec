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

    Automata_with_trans transit() {             // функция перехода, возвращает выход 
        int i = current_state;
        current_state = au.get_transit(current_state);
        return *this; // au.get_output(i);

    }
    int get_output(int curr_cond) {
        return au.get_output(curr_cond);
    }
    void set_current_state(int i) { current_state = i; }

    int get_current_state() { return current_state; }

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
    FSM(FSM& s) {
        n = s.n;
        m = s.m;
        states = s.states;
        transits = s.transits;
        outputs = s.outputs;
    }
    /*FSM operator=(FSM s) {
        n = s.n;
        m = s.m;
        states = s.states;
        transits = s.transits;
        outputs = s.outputs;
    }*/
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

    FSM_with_trans(FSM_with_trans& s) {
        fsm = s.fsm;
        current_state = s.current_state;
    }
    FSM_with_trans operator =(FSM_with_trans& s) {
        if (this == &s)return *this;
        fsm = s.fsm;
        current_state = s.current_state;
    }

    FSM_with_trans transit(int input) {
        int i = current_state;
        current_state = fsm.get_transits()[input][current_state];
        return *this;;//.get_outputs()[input][i];
    }
    int get_output(int i) {
        return fsm.get_outputs()[i][current_state];
    }
    int get_next_cond(int i) {
        return fsm.get_transits()[i][current_state];
    }

    void set_current_state(int i) { current_state = i;  }
    int get_current_state() { return current_state; }
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


class Perm {
    vector <int> p;
    int n;
public:
    Perm(int sn) {
        for(int i=0; i<sn; i++)p.push_back(i);
        n = sn;
    }

    Perm(vector <int> s, int sn) {
        for (int i = 0; i < sn; i++)p.push_back(s[i]);
        n = sn;
    }

    Perm operator*(Perm s) {
        if (n != s.n)return Perm(1);
        Perm t(n);
        for (int i = 0; i < n; i++)t.p[i] = s.p[p[i]];
        return t;
    }
    void output() {
        for (int i = 0; i < n; i++)cout << p[i] << ' ';
    }
};

struct Node {
    Node* left;
    Node* right;
    Node* back;
    int s;
    bool chet = false; // чётность ветви (будет проверятся в листьях) 1 - нечётн.
    bool need_to_delete = false;
};

Node* rev(Node* root, int i, int* z, FSM_with_trans A2, int wall, Node *&ROOT, bool &dead_end) {
    if (i < wall) {
        //root = new Node;
        //root->s = A2.get_current_state();
        Node* p = root;
        //p->chet = false;
        if (A2.get_output(0) == z[i]) {
            Node* t = new Node; t->left = t->right = NULL; t->need_to_delete = false;
            t->s = A2.get_next_cond(0);
            p->left = t;
            t->back = p;
            //FSM_with_trans t_A = A2;
            //t_A.transit(0);
            //rev(t, i + 1, z, t_A, wall);
        }
        if (A2.get_output(1) == z[i]) {
            Node* t = new Node; t->left = t->right = NULL; t->need_to_delete = false;
            t->s = A2.get_next_cond(1);
            t->chet = !(p->chet);
            p->right = t;
            t->back = p;
            //FSM_with_trans t_A = A2;
            //t_A.transit(1);
            //rev(t, i + 1, z, t_A, wall);
        }
        //if (p->left != NULL && p->right != NULL)succ = p;
        if (p->left != NULL) {
            FSM_with_trans t_A = A2;
            t_A.transit(0);
            rev(p->left, i + 1, z, t_A, wall, ROOT, dead_end);
            if (p->need_to_delete)return NULL;
            /*if (p->need_to_delete == true) {
                if (p == ROOT) { 
                    delete ROOT; ROOT = NULL; return ROOT;
                }
                else {
                    p->back->left = NULL;
                    delete p; p = NULL;
                }
            }*/
            //if (p == NULL)p = succ;
            //if (dead_end)return NULL;
        }
        if(p!=NULL)
        if (p->right != NULL) {
            FSM_with_trans t_A = A2;
            t_A.transit(1);
            rev(p->right, i + 1, z, t_A, wall, ROOT, dead_end);
            if (p->need_to_delete)return NULL;
            /*if (p->need_to_delete == true) {
                if (p == ROOT) {
                    ROOT = NULL; delete ROOT; return ROOT;
                }
                else {
                    p->back->right = NULL;
                    delete p; p = NULL;
                }
            }
            */
            //if (p == NULL)p = succ;
            //if (dead_end)return NULL;
        }
        if (A2.get_output(0) != z[i] && A2.get_output(1) != z[i]) {
            Node* del = p;
            p->need_to_delete = true;
            /*if (del == ROOT) {
                delete ROOT; ROOT = NULL; return ROOT;
            }
            */
            if (p->back != NULL)del = p->back;
            else return ROOT;
            while (del->back != NULL) {
                if ((del->left == NULL) != (del->right == NULL)) {
                    del->need_to_delete = true;
                    if (del->left != NULL) {
                        del->left->need_to_delete = true;
                        //p = del->left;
                        //p->left = p->right = NULL;
                        //delete p; p = NULL;
                        //del->left = NULL;
                        del = del->back;
                    }
                    else {
                        del->right->need_to_delete = true;
                        //p = del->right;
                        //p->left = p->right = NULL;
                        //delete p; p = NULL;
                        //del->right = NULL;
                        del = del->back;
                    }
                }
                else {
                    if (del->left->need_to_delete && del->right->need_to_delete) {
                        del->need_to_delete = true;
                        //del->left->need_to_delete = del->right->need_to_delete = true;
                        del = del->back;
                    }
                    else break;
                }
            }
            //if (del->left != NULL && del->right != NULL); else
            //if (del == ROOT) { delete ROOT; ROOT = NULL; return NULL; }
        }

        /*    if (p == ROOT) {
                delete ROOT; ROOT = NULL; dead_end = true; return NULL;
            }
            Node* del = p->back;
            while ((del->left != NULL && del->right == NULL)
                ||   (del->left == NULL && del->right != NULL)
                ) {
                if (del == ROOT) { delete ROOT; ROOT = NULL; dead_end = true; return NULL; }
                if (del->left != NULL) {
                    p = del->left;
                    p->left = p->right = NULL;
                    delete p;
                    del->left = NULL;
                    del = del->back; // прописать удаление ветви вверх до узла, у которого два потомка
                }
                else {
                    p = del->right;
                    p->left = p->right = NULL;
                    delete p;
                    del->right = NULL;
                    del = del->back;
                }
                //delete p;
            }
        }*/
    }
    return ROOT;
}

void Output_TreeLKP(Node* root, int deep, int i = 0) {
    if (root->left != NULL) {
        cout << 0;
        //cout << root->s;
        Output_TreeLKP(root->left, deep, i + 1);
    }
    if (root->right != NULL) {
        cout << 1;
        //cout << root->s;
        Output_TreeLKP(root->right, deep, i + 1);
    }
    if (root->left == NULL && root->right == NULL) {
        //cout << " END "<<i<<'.';
        cout << ' ' << root->s << endl;
        //for (int j = 0; j < i - 1; j++)cout << ' ';
        return;
    }
}
void delete_tree(Node* root) {
    if (root == NULL)return;
    if (root->left != NULL) {
        delete_tree(root->left);
        root->left = NULL;
    }
    if (root->right != NULL) {
        delete_tree(root->right);
        root->right = NULL;
    }
    if (root->left == NULL && root->right == NULL) {
        if (root != NULL)delete root; root = NULL;
    }
        
}

void delete_tree_where_is_need(Node* root) {
    Node* t = root;
    if (t->need_to_delete) {
        delete_tree(t); return;
    }
    if (t->left != NULL) {
        if (t->left->need_to_delete) {
            delete_tree_where_is_need(t->left);
            t->left = NULL;
        }
        else delete_tree_where_is_need(t->left);
        //t->left = NULL;
    }
    if (t->right != NULL) {
        if (t->right->need_to_delete) {
            delete_tree_where_is_need(t->right);
            t->right = NULL;
        }
        else delete_tree_where_is_need(t->right);
        //t->right = NULL;
    }
}


bool check(Node* root, int* z, int i=0) {
    // check z which we got from algorythm A1
    return true;
}

// преобразование путей от корня до листьев в массивы vector <int>
void tree_to_vectors(Node* root, vector < vector <int> > &s, vector <int> &t) { 
    Node* p = root;
    if (p->left != NULL) {
        t.push_back(0);
        tree_to_vectors(p->left, s, t);
    }
    if (p->right != NULL) {
        t.push_back(1);
        tree_to_vectors(p->right, s, t);
    }
    if (p->left == NULL && p->right == NULL) {
        s.push_back(t);
        //t.pop_back();
    }
   if(t.size())t.pop_back();
}

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
    for (int i = 0; i < 4; i++)x1[i] = (i+1)%8;
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
    // ==========================================================
    // = = = =      С Т Р О И М      А В Т О М А Т      = = = =  
    // ========================================================== 
    int pN = 2;   
    int pM = 2;
    int N = pow(2, pN); //int pN = 2;
    int M = pow(2, pM); //int pM = 2;
    int INPUTS = 2;
    int OUTPUTS = 2;
    int* g1 = new int[N];
    int* f1 = new int[N];
    f1[0] = 1; f1[1] = 0; f1[2] = 1; f1[3] = 1;     // 1 0 1 1 из диплома рис10
    //f1[4] = 1; f1[5] = 1; f1[6] = 1; f1[7] = 1;
    for (int i = 0; i < N; i++)g1[i] = (i + 1) % N;

    int** g2 = new int*[INPUTS];
    int** f2 = new int*[INPUTS];
    for (int i = 0; i < INPUTS; i++) {
        g2[i] = new int[M];
        f2[i] = new int[M];
    }                                       //  ПРИМЕРНЫЙ АВТОМАТ(из диплома рис10 вроде):
    g2[0][0] = 1;   g2[1][0] = 0;           // 1 0
    g2[0][1] = 2;   g2[1][1] = 1;           // 2 1
    g2[0][2] = 0;   g2[1][2] = 3;           // 0 3
    g2[0][3] = 3;   g2[1][3] = 2;           // 3 2
  
    f2[0][0] = 0;   f2[1][0] = 1;           // 0 1
    f2[0][1] = 0;   f2[1][1] = 1;           // 0 1
    f2[0][2] = 0;   f2[1][2] = 1;           // 0 1
    f2[0][3] = 0;   f2[1][3] = 0;           // 0 0              1 1 - мой вариант макс. периода



    Automata_with_trans A1(N, g1, f1, 0);
    FSM_with_trans A2(N, INPUTS, g2, f2, 0);
    vector <int> z;
    for (int i = 0; i < pow(2, pN + pM); i++) {
        z.push_back(A2.get_output(A1.get_output(A1.get_current_state())));// system("pause");
        A2.transit(A1.get_output(A1.get_current_state()));
        A1.transit();
    }
    for (int i = 0; i < pow(2, pN + pM); i++)z.push_back(z[i]);
    for (int i = 0; i < z.size(); i++)cout << z[i] << ' ';
    int res_per = 1;            // =========================================
    int sub_per = 1;            // С Ч И Т А Е Т    П Е Р И О Д (вроде) с точностью до непериодичности( 00 11 -> период = 2 и 01 01 период = 2)
    int probably_sub_per = 1;
    int i = 0;
    int j = 0;
    int quantity_of_sub_pers = z.size() / sub_per;
    for (sub_per = 1; sub_per <= z.size() / 2; sub_per++) { // цикл по размеру подпериода
        for (quantity_of_sub_pers = 1; quantity_of_sub_pers < z.size() / sub_per; quantity_of_sub_pers++) { // цикл по кол-ву подпериодов
            int k = 0;
            for (k = 0; k < sub_per; k++) {
                if (z[k] != z[k + sub_per * quantity_of_sub_pers]) {
                    break;
                }
            }
            if (k == sub_per)probably_sub_per = sub_per; else { break;  }
        }
        if (quantity_of_sub_pers != z.size() / sub_per)res_per = sub_per; else {
            res_per = probably_sub_per; break;
        }
    }
    cout << endl<< "Period: "<<res_per << endl;
    //============================================================
    //============================================================
    /*
    for (int ST = 0; ST < N; ST++) {
        cout << "CURRENT START_STATE = " << ST << endl;
        A1.set_current_state(ST);
        cout << "outputs1:    ";
        for (int i = 0; i < pow(2, pN + pM); i++) {
            cout << A2.get_output(A1.get_output(A1.get_current_state())) << "  ";// system("pause");
            A2.transit(A1.get_output(A1.get_current_state()));
            A1.transit();
        }
        cout << endl;
        cout << "outputs2:    ";
        for (int i = 0; i < pow(2, pN + pM); i++) {
            cout << A2.get_output(A1.get_output(A1.get_current_state())) << "  ";// system("pause");
            A2.transit(A1.get_output(A1.get_current_state()));
            A1.transit();
        }
        cout << endl;
        cout << "transits A2: ";
        for (int i = 0; i < pow(2, pN + pM); i++) {
            cout << A2.get_current_state() << "  ";
            A2.transit(A1.get_output(A1.get_current_state()));
            A1.transit();
        }
        cout << endl;/*
        cout << "transits A1: ";
        for (int i = 0; i < pow(2, pN + pM); i++) {
            cout << A1.get_current_state()<<"  ";
            A1.transit();
        }
        cout << endl;
        cout << "outputs A1:  ";
        for (int i = 0; i < pow(2, pN + pM); i++) {
            cout << A1.transit() << "  ";
        }
        cout << endl << endl; */       
    //}
    
    
    for (int kkk = 0; kkk < pow(2, pM); kkk++) {
        A1.set_current_state(0);
        A2.set_current_state(kkk);
        cout << kkk << endl;
        /*if (kkk == 2) {
            kkk = kkk;
        }
        */
        string zz;
        cin >> zz;
        int size = 0;
        for (size = 0; size < zz.size(); size++);
        /*if (size == 5) {
            kkk = kkk;
        }*/
        int* z = new int[size];
        for (int i = 0; i < size; i++)z[i] = zz[i] - 48;
        Node* root = new Node; root->back = NULL; root->left = root->right = NULL; root->need_to_delete = false; root->s = A2.get_current_state();
        bool ded_end = false;
        Node* ff = new Node;
        /*if (zz == "10001011") {
            zz = zz;
        }*/
        Node* ROoTT = rev(root, 0, z, A2, pow(2,pN), root, ded_end);
        Node* br = ROoTT;
        if (ROoTT == nullptr)cout << "NULLPTR" << endl;
        /*if (zz == "10001011") {
            zz = zz;
        }*/
        delete_tree_where_is_need(ROoTT);
        vector <vector <int>> s;
        vector <int> t;
        if (ROoTT == NULL)cout << "NO"; else
        {
            //if(zz=="10001011")

            Output_TreeLKP(ROoTT, size); cout << endl << endl;
            tree_to_vectors(ROoTT, s, t);
            for (int j = 0; j < s.size(); j++) {
                for (int k = 0; k < pow(2, pN); k++)cout << s[j][k];
                cout << endl;
            }
            //tree_to_vectors(ROoTT, )
        }
        delete_tree(ROoTT);
    }
    
    /*               //перестановки
    vector <int> gv1; gv1.push_back(1); gv1.push_back(2); gv1.push_back(0); gv1.push_back(3);
    vector <int> gv2; gv2.push_back(0); gv2.push_back(1); gv2.push_back(3); gv2.push_back(2);
    vector <int> gv3; gv3.push_back(1); gv3.push_back(3); gv3.push_back(0); gv3.push_back(2);
    Perm GGG(gv3, 4);
    GGG.output();
    GGG = GGG * GGG * GGG * GGG;
    GGG.output();
    return 0;
    Perm G1(gv1, 4);
    Perm G2(gv2, 4);
    cout << "0: "; G1.output(); cout << endl;
    cout << "1: "; G2.output(); cout << endl;
    char byte = 0;
    unsigned short counter4 = 0;
    while (byte < 16) {
        Perm G3(4);
        while (counter4 < 4) {
            if (1 & (byte >> counter4)) {
                G3 = G3 * G2; G3.output(); cout << " 1" << endl;
            }
            else {
                G3 = G3 * G1; G3.output(); cout << " 0" << endl;
            }
            counter4++;
        }
        cout << endl;
        byte++;
        counter4 = 0; 
    }*/
    /*
    int g1[4] = { 2,3,1,4 };
    int g2[4] = { 1,2,4,3 };
    int gu[4] = { 0,0,0,0 };
    char byte = 0;
    unsigned short counter4 = 0;
    while (byte < 16) {
        while (counter4 < 4) {
            if()
        }
    }
    */
    

    /*
    int s = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int zz[4] = { 0,0,1,1 }; int L = 4;
    int** u = new int* [pow(2, M)];
    for (i = 0; i < pow(2, M); i++) {
        u[i] = new int[L];
        for (j = 0; j < L; j++)u[i][j] = 0;
    }
    int LLL[4] = { 0,0,0,0 };
    j = 0;
    for (k = 0; k < pow(2, M); k++) {   // цикл по состояниям А2
        for (i = 0; i < L; i++) {       // цикл по zz(t)
            if (f2[0][s] == zz[i]) {
                u[k][i] = 0;
                A2.transit(0);
                s = A2.get_current_state();
            }
            else {
                if (f2[1][s] == zz[i]) {
                    u[k][i] = 1;
                    A2.transit(1);
                    s = A2.get_current_state();
                }
                else cout << "NO";
            }
        }
    }
    for (k = 0; k < pow(2, M); k++) {
        for (i = 0; i < L; i++) {

        }
    }

    */
    system("pause");
    return 0;
    // ==================================================
    // П О Л Е З Н А Я      Ш Т У К А
    // ==================================================
    // определятор периода l последовательности z длины NN
    //vector <int> z;
    //int NN = 30;
    /*for (int i = 0; i < NN; i++) {
        z.push_back((int)((i % 3) == 0));
        //z.push_back(A2.transit(A1.transit()));
        //z.push_back((int)((i % 11) > 0));
        cout << z[i] << ' ';
    }*/
    /*
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            z.push_back(1);
            z.push_back(0);
            z.push_back(1);
            z.push_back(0);
            z.push_back(0);
            z.push_back(1);
        }
        z.push_back(1);
        z.push_back(1);
        z.push_back(1);
    }
    for (int i = 0; i < NN; i++)cout << z[i] << ' ';
    */
    //vector <int> buff;
    //int l = 1;
    /*while (l < NN / 2) {  // ОПРЕДЕЛЯТОР первого попавшегося(минимального) ПЕРИОДА ПОСЛЕДОВАТЕЛЬНОСТИ
        int i = 0;
        for (i = 0; i < l && z[i] == z[i + l]; i++) {}
        if (i != l) l++; else break;
    }
    */
    cout << endl;
    /*for (int i = 0; i < l; i++)cout << "  ";
    cout << '.';
    cout << l << endl;
    */
    /*
    int true_l = 1;
    for (int l = 1; l < NN / 2; l++) { 
        int j = 0;
        int i = 0;
        for (i = 0; i < NN / l; i++) {
            for (j = 0; j < l; j++) {
                if (z[j] != z[j + l * i])break;
            }
            if (j != l)break;
        }
        if (i != NN / l);
    }
    */
    //=================================================
    
    /*cout << endl << endl;
    float l[4] = { 0.0, 0.0, 0.0, 0.0 };
    float h[4] = { 1.0, 0.0, 0.0, 0.0 };
    float a[4] = { 0.3, 0.0, 0.5, 0.9 };
    float b[4] = { 0.5, 0.3, 0.7, 1.0 };
    char c[4] = { 'K', 'O', 'V', '.' };

    for (int i = 1; i < 4; i++) {
        l[i] = l[i - 1] + a[i-1] * (h[i - 1] - l[i - 1]);
        h[i] = l[i - 1] + b[i-1] * (h[i - 1] - l[i - 1]);
     }
    for (int i = 0; i < 4; i++) {
        cout <<c[i]<<'\t'<< l[i] << '\t' << h[i] << endl;
    }
    */
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

class Node {
public:
    Node* left;
    Node* right;
    Node* back;
    int s;
    bool chet; //= false; // чётность ветви (будет проверятся в листьях) 1 - нечётн.
    bool need_to_delete; // = false;
    Node(Node* s);
    Node();
    ~Node();
};

// класс перестановка (permutation)
class Perm {
    std::vector <int> p;
    int n;  // размер
public:
    Perm(int sn, int t);
    Perm(std::vector <int> s);
    Perm operator*(Perm s);
    Perm(const std::string&);

    int size();
    int& operator[](int i);
    void output();
};


class FSM_with_trans {
private:
    FSM fsm;
    int current_state;
public:
    // конструктор по умолчанию
    FSM_with_trans();
    // деструктор
    ~FSM_with_trans();
    // конструктор по массивам
    // N - число состояний, M - число входов
    // int **s - функция переходов, **o - функция выходов
    // int st_s - начальное состояние
    FSM_with_trans(int N, int M, int** s, int** o, int st_s);
    // конструктор по перестановкам
    FSM_with_trans(Perm g20, Perm g21, int* f20, int* f21, int m, int curr_st=0);
    // конструктор по перемещению
    FSM_with_trans(FSM_with_trans&& s);
    // конструктор копирования
    FSM_with_trans(FSM_with_trans& s);
    // оператор присваивания
    FSM_with_trans operator =(FSM_with_trans& s);
    // функция перехода, изменяется current_state 
    FSM_with_trans transit(int input);
    // функция-геттер для получения выходного бита из текущего состояния по входному символу input
    int get_output(int input);
    // функция-геттер для получения следующего состояния из текущего состояния по входному символу input
    int get_next_cond(int input);
    // функция-геттер для получения выходного бита из состояния state по входному символу input
    int get_output_from_state_s(int input, int state);
    // функция-геттер для получения следующего состояния из состояния state по входному символу input  
    int get_next_cond_from_state_s(int input, int state);
    // переход по вхъодной последовательности 
    std::vector <int> transit_by_sequence(std::vector<int> s, int len);
    std::vector<int> transit_by_short_sequence(int s, int len);
    
    void set_current_state(int i);
    int get_current_state();

    // Вывести все возможные выходы из y(0):
    void Output_all_z_from_y0(int st, int len);
};


// Node *root - корень дерева
// int *z - выходная последовательность
// int i - шаг рекурсии
// A2 - автомат
// int wall - глубина рекурсии (высота дерева, длина u(t))
Node* get_u_from_z(Node* root, int* z, int i, FSM_with_trans& A2, int wall) {
    if (i < wall) {
        Node* left = NULL;
        Node* right = NULL;
      // если по входному биту 0: f2(0, y(i)) == z[i]
        if (A2.get_output(0) == z[i]) {
            left = new Node;
            left->back = root;
            left->chet = root->chet;
            left->s = A2.get_next_cond(0);
            root->left = left;
        }
      // если по входному биту 1: f2(1, y(i)) == z[i]
        if (A2.get_output(1) == z[i]) {
            right = new Node;
            right->back = root;
            right->chet = !root->chet;
            right->s = A2.get_next_cond(1);
            root->right = right;
        }
      // продолжение рекурсии налево
        if (root->left != NULL) {
            FSM_with_trans next_A2_0 = A2;
            next_A2_0.set_current_state(left->s);
            get_u_from_z(left, z, i + 1, next_A2_0, wall);
        }
      // продолжение рекурсии направо
        if (root->right != NULL) {
            FSM_with_trans next_A2_1 = A2;
            next_A2_1.set_current_state(right->s);
            get_u_from_z(right, z, i + 1, next_A2_1, wall);
        }
      // иначе из текущего состояния невозможно продолжить z(t), отбрасываем (помечаем need_to_delete = true)
        if (root->left == NULL && root->right == NULL) {
            root->need_to_delete = true;
            return root;
        }
    }
    else {
      // если полученная u(t) имеет чётный вес, то помечаем для удаления (need_to_delete = true)
        if (!root->chet)root->need_to_delete = true; 
        }
    return root;
}


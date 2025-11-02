#include <iostream>
#include "FSM.h"




template <class T> void Swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}
// Шаблон-функция для перемешивания с получением полноцикловой перестановки вектора-чисел
template <typename standardType> void shuffle_full_cycle(std::vector < standardType >& hexa) {
	int size = hexa.size();
	hexa.clear();
	std::vector<standardType> cache;
	//a.clear();
	for (int i = 0; i < size - 1; i++) {
		cache.push_back(i + 1); hexa.push_back(0);
	}
	hexa.push_back(0);

	int wall = size - 1;
	int i = 0;
	int j = 0;
	for (wall; wall > 0; wall--) {
		j = rand() % wall;
		hexa[i] = cache[j];
		i = cache[j];
		Swap(cache[j], cache[wall - 1]);
	}
}



// деструктор
Permut::~Permut() {}

// конструктор по умолчанию + конструктор выборочной генерации( (0 - тождественная (01234...n-1)     1 - случайная полноцикловая ) )
Permut::Permut(unsigned n, unsigned int t) {
	size = n;
	if (n == 0)return;

	if (t == 0)for (int i = 0; i < size; i++)hexa.push_back(i);
	else {
		std::vector<unsigned int> cache;
		//a.clear();
		for (int i = 0; i < size - 1; i++) {
			cache.push_back(i + 1); hexa.push_back(0);
		}
		hexa.push_back(0);

		int wall = size - 1;
		int i = 0;
		int j = 0;
		for (wall; wall > 0; wall--) {
			j = rand() % wall;
			hexa[i] = cache[j];
			i = cache[j];
			Swap(cache[j], cache[wall - 1]);
		}
	}
}

// конструктор копирования
Permut::Permut(Permut& s) {
	hexa = s.hexa;
	size = s.size;
}

// конструктор по перемещению
Permut::Permut(Permut&& s) {
	hexa = s.hexa;
	size = s.size;
}

// конструктор по вектору
Permut::Permut(std::vector < unsigned int > s) {
	size = s.size();
	hexa = s;
}

// конструктор по массиву
Permut::Permut(unsigned int n, unsigned int* s) {
	size = n;
	if (size == 0)return;
	for (int i = 0; i < size; i++)hexa.push_back(s[i]);
}

//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =  


// перегрузка " = "
Permut Permut::operator=(const Permut& s) {
	if (this == &s)return *this;
	hexa = s.hexa;
	size = s.size;
	return *this;
}

// перегрузка " * "
Permut Permut::operator*(Permut s) {
	if (this->size != s.size) { throw "Unqueal sizes!"; return Permut(0); }
	Permut local(size);
	for (int i = 0; i < size; i++)
		local[i] = s[hexa[i]];
	return local;
}

// перегрузка " [] "
unsigned int& Permut::operator[](int i) {
	if (i < 0 || i >= size) { throw "Permut: Out of range"; return hexa[0]; }
	return hexa[i];
}

// перегрузка " >> "
Permut Permut::operator>>(unsigned int k) {
	Permut local = *this;
	std::vector<unsigned int> buf;
	int wall = k % (this->size);
	for (int i = 0; i < wall; i++) {
		buf.push_back(local.hexa[local.size - 1 - i]);
	}
	for (int i = this->size - 1; i >= wall; i--) {
		local[i] = local[i - wall];
	}
	for (int i = 0; i < wall; i++) {
		local[i] = buf[buf.size()-1];
		buf.pop_back();
	}
	return local;
}

// перегрузка " << "
Permut Permut::operator<<(unsigned int k) {
	Permut local = *this;
	std::vector<unsigned int> buf;
	int wall = k % (this->size);
	if (wall == 0)
		return local;
	for (int i = 0; i <= wall; i++) {
		buf.push_back(local.hexa[i]);
	}
	for (int i = 0; i < this->size-wall; i++) {
		local[i] = local[i + wall];
	}
	for (int i = this->size-wall; i < this->size; i++) {
		local[i] = buf[i-this->size+wall];
	}
	return local;
}

// перегрузка " == "
bool Permut::operator==(const Permut& s) {
	bool flag = true;
	if (size != s.size)return false;
	for (int i = 0; i < size; i++) {
		if (hexa[i] != s.hexa[i]) { flag = false;  break; }
	}
	return flag;
}

// Степень
Permut Permut::pow(int power) {
	Permut local(size, 0u);
	Permut prav = (power >= 0) ? *this : this->reverse();
	
	for (unsigned int i = 0; i < power; i++) {
		local = local * prav;
	}
	
	return local;
}

// Convert to std::vector<unsigned int>
std::vector<unsigned int> Permut::To_Vector() {
	return hexa;
}

//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =  


// shuffle_full_cycle() - функция "перемешивания". Выход: случайная полноцикловая перестановка
void Permut::shuffle_full_cycle() {
	hexa.clear();
	std::vector<unsigned int> cache;
	//a.clear();
	for (int i = 0; i < size - 1; i++) {
		cache.push_back(i + 1); hexa.push_back(0);
	}
	hexa.push_back(0);

	int wall = size - 1;
	int i = 0;
	int j = 0;
	for (wall; wall > 0; wall--) {
		j = rand() % wall;
		hexa[i] = cache[j];
		i = cache[j];
		Swap(cache[j], cache[wall - 1]);
	}
}

// shuffle() - функция "перемешивания". Выход: случайная перестановка
void Permut::shuffle() {
	int wall = size << 1;
	for (int i = 0; i < wall; i++) {
		int l = rand() % size;
		int r = rand() % size;
		Swap(hexa[l], hexa[r]);
	}
}

// Нахождение обратной перестановки
Permut Permut::reverse() {
	Permut local_this = *this;
	Permut result(size, 0u);
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (local_this.hexa[j] > local_this.hexa[j + 1]) {
				Swap(local_this[hexa[j]], local_this.hexa[j + 1]);
				Swap(result.hexa[j], result.hexa[j + 1]);
			}
		}
	}
	return result;
}

//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =  


// Геттер размера
unsigned int Permut::Size() { return size; }

// вывод
void Permut::Output() {
	//for (int i = 0; i <size; i++)std::cout << i << '\t';
	//std::cout << '\n';
	for (int i = 0; i < size; i++)std::cout << "--\t";
	std::cout << '\n';
	for (int i = 0; i < size; i++)std::cout << i << '\t';
	std::cout << '\n';
	for (int i = 0; i < size; i++) {
		std::cout << hexa[i] << '\t';
	}
	std::cout << '\n';
	for (int i = 0; i < size; i++)std::cout << "--\t";
	std::cout << '\n';
}

// Ввод (по порядку)
void Permut::Input() {
	std::cout << "Input size of permutation: ";
	hexa.clear();
	std::cin >> size;
	unsigned int t = 0;
	for (int i = 0; i < size; i++) {
		std::cout << "Input p[" << i << "]: ";
		std::cin >> t;
		hexa.push_back(t);
	}
}







// Деструктор
A1::~A1() { }	// отработает встроенный в std::vector<> деструктор


// конструктор по умолчанию
A1::A1(unsigned int NN, int cur_st, std::vector<unsigned int> gg1, std::vector<unsigned int> ff1) {
	N = NN;
	unsigned int Pn = (N < 5) ? 1 : 1 << (N - 5);
	f1_size = Pn;
	current_state = cur_st;
	if (NN == 0) { return; }
	//g1 = new unsigned int[1 << N];
	g1 = gg1;
	ff1 = ff1;
	//f1 = new unsigned int[Pn];

	//for (unsigned int i = 0; i < Pn; i++)f1.push_back(ff1[i]);//f1[i] = ff1[i];
	//Pn = 1 << N;
	//for (unsigned int i = 0; i < Pn; i++)g1.push_back(gg1[i])//g1[i] = gg1[i];
}


// конструктор копирования
A1::A1(A1& s) {
	current_state = s.current_state;
	N = s.N;
	unsigned int Pn	 = (  N < 5) ? 1 : 1 << (  N - 5);
	f1_size = Pn;
	//unsigned int sPn = (s.N < 5) ? 1 : 1 << (s.N - 5);
	//f1 = new unsigned int[Pn];
	f1 = s.f1;
	g1 = s.g1;
	//g1 = new unsigned int[1 << N];

	//for (unsigned int i = 0; i < Pn; i++)f1[i] = s.f1[i];
	//Pn = 1 << N;
	//for (unsigned int i = 0; i < Pn; i++)g1[i] = s.g1[i];
	
}


// конструктор по перемещению
A1::A1(A1&& s) {
	N = s.N;
	f1 = s.f1;
	g1 = s.g1;
	current_state = s.current_state;
}


// конструктор для генерации, t=0 - g1 - 234...(n-1)1 | f1 = 0000..001
//                            t=1 - g1 - randmized | f1 - randomized НЕДОДЕЛАН
A1::A1(unsigned int NN, unsigned int cur_st, int t){
	N = NN;
	current_state = cur_st;
	if (N == 0) { return; }

	f1_size = (N < 5) ? 1 : 1 << (N - 5);
	//g1 = new unsigned int[1 << N];
	//f1 = new unsigned int[f1_size];


}


// перегрузка " = "
A1 A1::operator=(A1& s) {
	if (this == &s) {
		return *this;	
	}
	g1.clear();
	f1.clear();
	current_state = s.current_state;
	N = s.N;
	unsigned int Pn = (N < 5) ? 1 : 1 << (N - 5);
	//unsigned int sPn = (s.N < 5) ? 1 : 1 << (s.N - 5);
	f1 = s.f1;	// new unsigned int[Pn];
	g1 = s.g1;	// new unsigned int[1 << N];

	return *this;
	//for (unsigned int i = 0; i < Pn; i++)f1[i] = s.f1[i];
	//Pn = 1 << N;
	//for (unsigned int i = 0; i < Pn; i++)g1[i] = s.g1[i];

}


// Получить выход из текущего состояния
unsigned int A1::get_output() {
	return ((f1[current_state >> 5] >> (current_state & 31)) & 1);
}


// Получить выход из состояния state
unsigned int A1::get_output_from(unsigned int state) {
	//if(state > )
	//return ((f1[state>> 5] >> (state & 31)) & 1);
	return 1;

}


// Получить следующее состояние из текущего состояния
int get_next_state();


// Получить следующее состояние из состояния state
int get_next_state_from();


// Инициирование перерхода из текущего состояние в следующее
void transit();



//	=	=	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
//	=	=	*			О П И С А Н И Е		А В Т О М А Т А		А2					*
//	=	=	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*



// Деструктор
A2::~A2() {
	//delete[] g20;
	//delete[] g21;
	//delete[] f20;
	//delete[] f21;
}

// Конструктор по умолчанию
A2::A2(std::vector<unsigned int> gg20, std::vector<unsigned int> gg21,
	   std::vector<unsigned int> ff20, std::vector<unsigned int> ff21,
	   unsigned int MM, unsigned int cur_st){
	M = MM;
	f2_size = (M < 5) ? 1 : 1 << (M - 5);
	g2_size = 1 << M;
	current_state = cur_st;
	if (M == 0) {
		//g20 = nullptr;
		//g21 = nullptr;
		//f20 = nullptr;
		//f21 = nullptr;
		return;
	}
	g20 = gg20;//g20 = new unsigned int[1 << M];
	g21 = gg21;//g21 = new unsigned int[1 << M];
	
	f20 = ff20;//f20 = new unsigned int[f2_size];
	f21 = ff21;//f21 = new unsigned int[f2_size];
	
	//for (unsigned int i = 0; i < f2_size; i++) { f20[i] = ff20[i];  f21[i] = ff21[i]; }
	//for (unsigned int i = 0; i < g2_size; i++) { g20[i] = gg20[i];  g21[i] = gg21[i]; }

}

// Конструктор копирования
A2::A2(A2& s) {
	M = s.M;
	f2_size = s.f2_size;
	g2_size = s.g2_size;
	current_state = s.current_state;
	g20 = s.g20;//g20 = new unsigned int[g2_size];
	g21 = s.g21;//g21 = new unsigned int[g2_size];
	f20 = s.f20;//f20 = new unsigned int[f2_size];
	f21 = s.f21;//f21 = new unsigned int[f2_size];
	//for (unsigned int i = 0; i < f2_size; i++) { f20[i] = s.f20[i];  f21[i] = s.f21[i]; }
	//for (unsigned int i = 0; i < g2_size; i++) { g20[i] = s.g20[i];  g21[i] = s.g21[i]; }

}

// Конструктор по перемещению
A2::A2(A2&& s) {
	M = s.M;
	f2_size = s.f2_size;
	g2_size = s.g2_size;
	g20 = s.g20;
	g21 = s.g21;
	f20 = s.f20;
	f21 = s.f21;

}

/* // Конструктор для построения пустого или случайно_сгенерированного автомата 
	t = 0:
		g20 = g21 = e (тождественная перестановка)
		f20 = 1000 0000 ... 0000
		f21 = 0000 0000 ... 0000 ~ 0

*/
A2::A2(unsigned int MM, unsigned int cur_st, int t, unsigned int w_f2) {
	int pM = 1 << MM;
	if (w_f2 >= (pM<<1))w_f2 = (pM<<1) - 1;
	M = MM;
	current_state = cur_st;
	f2_size = (M < 5) ? 1 : 1 << (M - 5);
	g2_size = 1 << M;
	if (M == 0 || current_state >= (1<<M)) {
		std::cout << "Incorrect A2 (from A2(uint MM, uint cur_st, int t) )\n";
		current_state = 0;
		//g20 = nullptr;
		//g21 = nullptr;
		//f20 = nullptr;
		//f21 = nullptr;
		return;
	}

	//f20 = new unsigned int[f2_size];
	//f21 = new unsigned int[f2_size];

	//g20 = new unsigned int[g2_size];
	//g21 = new unsigned int[g2_size];

	if (t == 0) {
		for (unsigned int i = 0; i < g2_size; i++) {
			g20[i] = i;
			g21[i] = i;
		}
		//g20[g2_size - 1] = g21[g2_size - 1] = 0;
		for (unsigned i = 0; i < f2_size; i++) {
			f20[i] = 0;
			f21[i] = 0;
		}
		f20[0] = 1<<31;	// f2(0,0) = 1 все нули, кроме 0-го состояния по входному биту 0
	}
	else {
		//shuffle_full_cycle(g20);
		Permut perm_g20(g2_size, 1u);
		g20 = perm_g20.To_Vector();

		int power = rand() % g2_size;
		power = (power >> 1) << 1;		// чтобы была чётной
		perm_g20 = perm_g20.pow(power);
		g21 = perm_g20.To_Vector();
		/*unsigned int* cache = new unsigned int[g2_size];
		for (int i = 0; i < g2_size; i++)cache[i] = i;
		int wall = g2_size;
		for (int i = 0; i < g2_size; i++) {
			unsigned int index = ((rand() << 16) | rand() ) % wall;
			unsigned int qst = cache[index];		// qst - queued state (очередное состояние)
			g20.push_back(qst);
			if (qst == 0 && i==0) {
				qst = qst;
			}
			Swap(cache[index], cache[wall - 1]);
			wall--;
		}
		for (int i = 0; i < g2_size; i++)cache[i] = i;
		wall = g2_size;
		for (int i = 0; i < g2_size; i++) {
			unsigned int index = ((rand() << 16) | rand()) % wall;
			unsigned int qst = cache[index];		// qst - queued state (очередное состояние)
			g21.push_back(qst);
			if (qst == 0 && i == 0) {
				qst = qst;
			}
			Swap(cache[index], cache[wall - 1]);
			wall--;
		}
		*/
		//		-		-		-		-		-
		for (int i = 0; i < f2_size; i++) {
			f20.push_back(0);	//((rand() << 16) | rand()));
			f21.push_back(0);	//((rand() << 16) | rand()));
		}
		int index=0;
		int direct = 0;
		int array_stepper = (M > 5);
		// index = [0, 2^(M-1) - 1] - заносим единицу в f20
		// index = [2^(M-1), 2^M - 1] - заносим единицу в f21
		for (int i = 0; i < w_f2; i++) {
			do {
				index = rand() % pM;
				//direct = rand() % 2;
				//index -> f20
				//index = (index >> (array_stepper));
				if (f20[index >> 5] & (1 << (31 - (index & 31))));
				else {
					direct = 0; break;
				}
				
				//index = index >> 1;
				if (f21[index >> 5] & (1 << (31 - (index & 31))));
				else {
					direct = 1; break;
				}
			} while (true);
			//index = (index >> (array_stepper));
			if (direct==0) {	// index -> f20
				f20[index >> 5] = f20[index >> 5] | (1 << (31 - (index & 31)));
			}
			else {				// index -> f21
				f21[index >> 5] = f21[index >> 5] | (1 << (31 - (index & 31)));
			}
		}
	}
}

// Перегрузка " = "
A2 A2::operator=(A2& s) {
	if (this == &s) {
		return *this;
	}
	g20.clear();//delete[] g20;
	g21.clear();// delete[] g21;
	f20.clear();// delete[] f20;
	f21.clear();//delete[] f21;

	g2_size = s.g2_size;
	f2_size = s.f2_size;

	current_state = s.current_state;
	M = s.M;
	g20 = s.g20;
	g21 = s.g21;

	f20 = s.f20;
	f21 = s.f21;
	return *this;
	//for (unsigned int i = 0; i < g2_size; i++) {
	//	g20[i] = s.g20[i];	
	//	g21[i] = s.g21[i];
	//}
	//for (unsigned int i = 0; i < f2_size; i++) {
	//	f20[i] = s.f20[i];
	//	f21[i] = s.f21[i];
	//}
}



//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   

	// Получить СЛЕД. СОСТОЯНИЕ из текущего состояния по входу input
unsigned int A2::get_next_state(unsigned char input) {
	if (input == 0)	return g20[current_state];
	else			return g21[current_state];
}

// Получить ВЫХОД из текущего состояния по входу input
unsigned int A2::get_output(unsigned char input) {
	if (input == 0)	return (f20[current_state>>5 ]>> (31 - (current_state & 31))) & 1;
	else			return (f21[current_state>>5] >> (31 - (current_state & 31))) & 1;
}

// Получить СЛЕД. СОСТОЯНИЕ из состояния state по входу input
unsigned int A2::get_next_state_from(unsigned int state, unsigned char input) {
	if (input == 0)	return g20[state];
	else			return g21[state];
}

// Получить ВЫХОД из состояния state по входу input
unsigned int A2::get_output_from(unsigned int state, unsigned char input) {
	if (input == 0)	return ((f20[state >> 5] >> (31 - (state & 31))) & 1);
	else			return ((f21[state >> 5] >> (31 - (state & 31))) & 1);
}

// получить ТЕКУЩЕЕ состояние по входу input
unsigned int A2::get_current_state() {
	return current_state;
}

// Инициировать переход из текущего состояния по входу input
void A2::transit(unsigned char input) {
	current_state = this->get_next_state(input);
}

// Получение размера (порядка)
unsigned int A2::get_M() {
	return M;
}

// Получение размера (кол-ва состояний)
unsigned int A2::get_size() {
	return 1 << M;
}


// Получение g(0, •)
std::vector<unsigned int> A2::get_g20() {
	return g20;
}

// Получение g(1, •)
std::vector<unsigned int> A2::get_g21() {
	return g21;
}

//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   

   // Вывод g20
void A2::Output_g20() {
	for (int i = 0; i < g2_size; i++) {
		std::cout << g20[i] << '\t';
	}
}

// Вывод g21
void A2::Output_g21() {
	for (int i = 0; i < g2_size; i++) {
		std::cout << g21[i] << '\t';
	}
}

// Вывод f20
void A2::Output_f20() {
	if(M>=5)
		for (int i = 0; i < f2_size; i++)
			for (int j = 31; j >=0; j--)
				std::cout << ((f20[i] >> j) & 1) << '\t';	
	else {
		unsigned int wall = 1 << M;
		for (int i = 0; i < wall; i++)
			std::cout << ((f20[0] >> (31 - i)) & 1) << '\t';
	}
}

// Вывод f21
void A2::Output_f21() {
	if(M>=5)
		for (int i = 0; i < f2_size; i++)
			for (int j = 31; j >= 0; j--)
				std::cout << ((f21[i] >> j) & 1) << '\t';
	else {
		unsigned int wall = 1 << M;
		for (int i = 0; i < wall; i++)
			std::cout << ((f21[0] >> (31 - i)) & 1) << '\t';
	}
}

// Вывод g2
void A2::Output_g2() {
	std::cout << "g2(0): "; this->Output_g20();
	std::cout << '\n';
	std::cout << "g2(1): "; this->Output_g21();
}

// Вывод f2
void A2::Output_f2() {
	std::cout << "f2(0): "; this->Output_f20();
	std::cout << '\n';
	std::cout << "f2(1): "; this->Output_f21();
}

// Вывод Всего автомата А2
void A2::Output() {
	std::cout << "       ";
	for (int i = 0; i < g2_size; i++)std::cout << i << '\t';
	std::cout << '\n'; this->Output_g2();
	std::cout << '\n'; this->Output_f2();
}

//  =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   =   

// заменить функцию f20
void A2::change_f20(std::vector<unsigned int> ff20) {
	if (f20.size() == ff20.size())
		f20 = ff20;
	else std::cout << "Error: size is unequal: " << f20.size() << ' ' << ff20.size() << '\n';
}

// заменить функцию f21
void A2::change_f21(std::vector<unsigned int> ff21) {
	if (f21.size() == ff21.size())
		f21 = ff21;
	else std::cout << "Error: size is unequal: " << f21.size() << ' ' << ff21.size() << '\n';
}


// заменить g20
void A2::change_g20(std::vector<unsigned int> gg20) {
	g20 = gg20;
}

// заменить g21
void A2::change_g21(std::vector<unsigned int> gg21) {
	g21 = gg21;
}



//============================================================================================================
/*	// Функция обращения автомата А2 по z(t) для первых 2^N бит 
	A2 А -  заданный автомат А2
	vector<uint> zt - выходная последовательность автомата А2, по ней выполняется обращение
	ut - управляющая последовательность u(t)(булев вектор)		( пока что длиной до 32 бит )
	ut_size - длина u(t)	[1, 32]
	i - шаг рекурсии
*/
void Reverse_from_zt_only_first_2pow_N_bits(A2 &A, R_Tree* &root, std::vector<unsigned int> zt, int ut_size, int i) {
	if (i < ut_size) {
		// Если f2(0, xi) == z[i]	то продолжаем ветку налево
		if (A.get_output_from(root->s, 0) == ((zt[i>>5] >> (31 - i)) & 1)) {	// ( ut >> (31 - i ) )&1) == 0) {
			R_Tree* l = new R_Tree;
			l->left = l->right = NULL;
			l->back = root;
			l->chet = root->chet;
			l->s = A.get_next_state_from(root->s, 0);

			root->left = l;
		}
		// Если f2(1, xi) == z[i]	то продолжаем ветку направо
		if (A.get_output_from(root->s, 1) == ((zt[i>>5] >> (31 - i)) & 1)) {	// ( ut >> (31 - i ) )&1) == 0) {
			R_Tree* r = new R_Tree;
			r->left = r->right = NULL;
			r->back = root;
			r->chet = !root->chet;
			r->s = A.get_next_state_from(root->s, 1);

			root->right = r;
		}
		if (root->left != NULL) {
			//A2 temp_A2 = A;
			//temp_A2.transit(0);
			Reverse_from_zt_only_first_2pow_N_bits(A, root->left, zt, ut_size, i + 1);
		}
		if (root->right != NULL) {
			//A2 temp_A2 = A;
			//temp_A2.transit(1);
			Reverse_from_zt_only_first_2pow_N_bits(A, root->right, zt, ut_size, i + 1);
		}

		//  Разбор случаев
		if (root != NULL) {
			// доделать удаление ветвей вверх для неподходящих ветвей
			R_Tree *r_back = root->back;
			// Если нет потомков
			if ((root->left == NULL) && (root->right == NULL)) {
				// Пока не поднялись до корня
				while (r_back->back != NULL && ( (root->left == NULL) ^ (root->right == NULL))) {
					root = r_back;
					r_back = root->back;
					/*// если у текущего узла (root) два потомка, то удаляем поддерево root
					if ((root->left == nullptr) != (root->right == nullptr)) {
						//DeleteTree(root);
						break;
					}// иначе поднимаемся выше: root = root->back; r_back = r_back -> back;
					else {
						root = r_back;
						r_back = root->back;
					}*/
				}
				bool direct = r_back->left == root;
				DeleteTree(root);
				root = NULL;
				if (direct)r_back->left = NULL; else r_back->right == NULL;
			}
		}

	}
}


















// Вывод дерева R_Tree, начиная с узла *root
// с оступом k
void PrintTree(R_Tree* root, int k) {
	//if (root == nullptr) return;
	// Налево
	if(root->right != NULL)
	PrintTree(root->right, k + 5); 

	for (int i = 0; i < k; i++) std::cout << '-';
	std::cout << (root->s)<<'\n';
	// Направо
	if (root->left != NULL)
	PrintTree(root->left, k + 5);
	
}

// Удалить дерево с корнем *root
void DeleteTree(R_Tree* &root) {
	if (root->left != NULL) {
		DeleteTree(root->left); root->left = NULL;
	}
	if (root->right != NULL) {
		DeleteTree(root->right); root->right = NULL;
	}
	root->back = NULL;
	delete root;

	root = NULL;
}

// Подсчитать число листьев у дерева R_Tree с корнем *root
unsigned int Number_of_Leafs(R_Tree* root, unsigned int *counter) {
	if (root->left != NULL) {
		Number_of_Leafs(root->left, counter);
	}
	if (root->right != NULL) {
		Number_of_Leafs(root->right, counter);
	}
	if (root->left == NULL && root->right == NULL) {
		*counter = *counter + 1;
		return *counter + 1;
	}
	else return *counter;
}




// Генерация случайной u(t) с заданным весом W и длины N
unsigned int Generate_Random_ut(unsigned int W, unsigned int N) {
	int j = 0;
	if (N < 1 || N>32) { std::cout << "Incorrect N in Generate_Random_ut: " << N << '\n'; return 1; }
	if (W > N)return ~(0);
	unsigned int result = 0;
	for (int i = 0; i < W; i++) {
		unsigned int index = rand()%N;			
		while ((result >> (31 - index)) & 1) {
			index = rand() % N;
			j++;
			if (j == 1000) {
				j = j;
			}
		}
		result = result | (1 << (31 - index));
	}
	return result;
}
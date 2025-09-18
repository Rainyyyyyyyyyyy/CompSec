#pragma once
#define BASE  unsigned char
#define size_of_base (sizeof(BASE))
#define D_BASE unsigned short	// DOUBLE_BASE
#define Q_BASE unsigned int		// QUADRO_BASE
#include <iostream>
#include <vector>
using namespace std;

class BM {
	vector <BASE> hexa; // BASE* coef
	int Len;	// число функциональных разрядов
	bool minus = false;
	//int maxLen;	// максимальное число разрядов ( сколько элементов hexa )
	//bool is_negative;  // флажок на минус

public:
	/*
	1) Конструкторы •, деструктор •, =	•		DONE • fully [accepted]
	2) 16-ый ввод и вывод•						DONE • fully [accepted]
	3) Сравнение БЧ							    DONE • fully [accepted]
	4) Сложение									DONE • fully [accepted]
	5) Вычитание								DONE • fully [accepted]
	6) Умножение								DONE • fully [accepted]
	7) Деление на цифру. 10-ый ввод и вывод		DONE • fully [accepted]
	8) Деление									DONE • fully [accepted]
	9) Тест										DONE • fully [accepted]
	*/
	BM(int len, int t);	// конструктор нули или рандом		DONE with BASE	
	BM(int s);
	BM(BM&);					// конструктор копирования			DONE 
	BM(const string);			// конструктор по строке			DONE
	BM(BM&& s);
	~BM();
	int size();

	BM operator=(const BM&);// DONE •
	BM operator=(BASE s);   // DONE •

	BM operator+(BM);		// DONE	•
	BM operator-(BM);		// DONE •

	BM operator*(BM);		// DONE •
	BM operator*(BASE);		// DONE •

	BM operator/(BM);		// DONE •
	BM operator/(BASE);		// DONE •
	BM operator%(BM);		// DONE •
	BM operator%(BASE);	// DONE •

	BM operator+=(BM);		// DONE •
	BM operator-=(BM);		// DONE •
	BM operator*=(BM);		// DONE •
	BM operator*=(BASE);	// DONE •

	// {
	BM operator<<(int k);   // DONE • [didn't present]
	BM operator>>(int k);   // DONE • [didn't present]
	// ОЧЕНЬ НУЖНО СДЕЛАТЬ ДЛЯ ТЕОРЕТИКО_ЧИСЛОВЫХ МЕТОДОВ В КРИПТОГРАФИИ!!!!!!!!!!!!!!
	BM operator<<=(int k);  // UNDONE			x
	BM operator>>=(int k);  // UNDONE			x



	BM sqr();				// DONE • [didn't present]
	BM pow(int k);			// DONE • [didn't present] // вариант "справа-налево"
	BM pow(BM k);			// DONE • [didn't present] // возможно корректно, проверка была неполной
	// }


	bool operator ==(BM);	// DONE •
	bool operator !=(BM);	// DONE •
	bool operator <=(BM);	// DONE •
	bool operator > (BM);	// DONE •
	bool operator < (BM);	// DONE •
	bool operator >=(BM);	// DONE •

	
	bool is_zero();			// DONE •

	void OutputHEX();		// DONE •
	void InputHEX();		// DONE •
	void OutputDEC();		// DONE	• 
	void InputDEC();		// DONE • 
	BM take_last_n_digits(int n);
	BM take_first_n_digits(int n);

	BM abs();




	// X % M, where s = M, *this = X, z = BASE.pow(2 * m.size()) / m;
	// z = основание в степени 2k и разделить на m, k = число цифр в m
	// x.size() <= 2k
	BM Barretts_modula(BM s, BM z);



	BM pow_modula(BM power, BM mod);



	BM sub_Barrets_z(BM& m);


	void set_random_less_than_M(const BM& M);

	//Лабораторная работа №4.Тест Ферма проверки числа на простоту. Оценить вероятность ошибки.
	// n>3, n - odd,
	// t - параметр надёжности
	bool Ferma_test_primality(int t);

	



	int Jacobi_symbol(BM n);
	//
	//Лабораторная работа №5.Тест Миллера - Рабина И Соловея - Штрассена проверки числа на
	//	простоту.Оценить вероятность ошибки.Сравнить.
	bool Miller_Rabin_test_primality(int t);
	bool Solovey_Strassen_test_primality(int t);



	// лаба 1. Пахомова Е.Г. "Теоретико-числовые методы в криптографии" 4 курс 1 семестр
	// метод пробных делений
/*
	Вход: число n > 1 ,  последовательность пробных
		делителей { d1 , d2 , … , ds-1 }
	Выход: представление n в виде n = p1  p2  …  pt ,
		где pi– простые, не обязательно различные.
	1. Полагаем t = 0,  k = 1 ( t– номер делителя pt ,  k
				номер пробного делителя dk )
	2. Если n = 1  – выход.
	3. Поделить n на dk с остатком:  n = dk  q + r .
	4. Если r = 0 : а)  увеличить t на 1,
					б)  положить pt = dk ,
					в)  положить n = q ,
					г)  перейти к п. 2.
	5. Если q > dk :	а) увеличить k на 1,
						б) перейти к п. 3.
		Иначе:
					а)  увеличить t на 1,
					б)  положить pt = n ,
					в)  выход (факторизация завершена).
*/

	std::vector <BM> trial_divisions_method(bool& final);

	
	// извлечение целой части корня из числа
	/*
	Вход: а
	Выход: [√a]
		1. Выбрать каким-либо способом начальное приближение х, 
			удовлетворяющее условию x^2 > a
		2. Положить х0 = х,	х = [([a/x]+x)/2]
		3. Если x >= x0, то выход, ответ: х0.
			Иначе: переход к шагу 2.
	*/
	// целочисленный квадратный корень
	BM integer_sqrt();
	

	// целочисленный корень степени n
	/*
	* x(k+1) = 1/n * ( (n-1)*x(k) + [a / x(k) ^ (n-1)] )
	* a - число под корнем
	* n - степень корня
	* x(0) = a
	* x(0) > x(1) > x(2) > ... > x(k) <= x(k+1)
	*						значит ответ: [ ^n√a ] = x(k).
	*/
	BM integer_sqrt_n(int n);


	// Алгоритм Олвея нахождения нетривиального делителя числа
	/*
		Вход: нечётное n, нечётное d >= (2 * ^3√n) + 1
		Выход: делитель р числа n, удаовлетворяющий
			условию dd < p <= √n, либо ответ 
			"Делителя в указанном диапазоне нет".
		Обозначения: r1 = r(k),	r2 = r(k-1), q = -4 Δq(k)
		1. r1 = n mod d.	r2 = n mod (d-2),
			q = 4(q2 - q1) = 4 ( [n/(d-2)] - [n/d] ),
			s = [√n]
		2. d = d+2
			Если d>s - выход. Ответ: "делителя нет".
		3. r = 2r1 - r2 + q,	r2 = r1,	r1 = r
		4. Если r1 < 0, то	r1 = r1 + d
						   	q = q + 4
		5. Пока r1 >= d,	r1 = r1 - d
							q = q - 4
		6. Если r1 = 0, то выход. Ответ: p = d
			Иначе goto 2.
	*/
	BM Alway_algorithm(bool& success);



	
	//Алгоритм Ферма поиска ближайших к √n делителей числа n
	/*
	Вход:  n – нечётное.
	Выход: a,b - делители n, или ответ: "n - простое"
		1. Вычислить
			Если х^2 = n – выход (ответ: а = b = х).
		2. Увеличить  x  на 1.
		3. Если  x = (n+1) / 2 – выход (ответ: «n простое»).
			Иначе – вычислить z = x^2 – n, y = [√z]
		4. Если  у^2 = z  – выход (ответ: а = х + у ,  b = х – у ).
			Иначе переход к п.2.
*/	// flag = true - n = primal, else n = a*b
	std::vector <BM> Ferma_method_factor(bool &primal);
};


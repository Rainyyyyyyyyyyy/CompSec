#define BASE  unsigned char
#define size_of_base (sizeof(BASE))
#define D_BASE unsigned short	// DOUBLE_BASE
#define Q_BASE unsigned int		// QUADRO_BASE
#include <iostream>
#include <vector>
#include "BigNumber.h"
using namespace std;

//class BM {	// старшие разряды в конце. hexa[0] - самый младший разряд
	//vector <BASE> hexa; // BASE* coef
	//int Len;	// число функциональных разрядов
	//int maxLen;	// максимальное число разрядов ( сколько элементов hexa )
	//bool is_negative;  // флажок на минус

//public:
	/*
	1) Конструкторы •, деструктор •, =	•		DONE • fully [accepted]
	2) 16-ый ввод и вывод•						DONE • fully [accepted]
	3) Сравнение БЧ							    DONE • fully [accepted]
	4) Сложение									DONE • fully [accepted]
	5) Вычитание								DONE • fully [accepted]
	6) Умножение								DONE • fully [accepted]
	7) Деление на цифру. 10-ый ввод и вывод		DONE • fully [didn't presented]
	8) Деление									DONE • fully [accepted]		// (зачем нужна нормировка с помощью множителя d?)
	9) Тест										DONE • fully [didn't presented]
	*/
	//BM(int len = 1, int t = 0);	// конструктор нули или рандом		DONE with BASE	
	//BM(BM&);					// конструктор копирования			DONE 
	//BM(const string);			// конструктор по строке			DONE
	BM::BM(BM&& s) {// конструктор по перемещению
		//is_negative = s.is_negative;
		hexa = s.hexa;
		Len = s.Len;
		//s.hexa.clear();
	}
	BM::~BM() {
		hexa.~vector();
	}
	int size();

	//BM BM::operator=(const BM&);// DONE •
	BM BM::operator=(BASE s) {
		hexa.clear();
		hexa.push_back(s);
		Len = 1;
		return *this;
	}	
	/*
	BM operator+(BM);		// DONE	•
	BM operator-(BM);		// DONE •

	BM operator*(BM);		// DONE •
	BM operator*(BASE);		// DONE •

	BM operator/(BM);		// DONE •
	BM operator/(BASE);		// DONE •
	BM operator%(BM);		// DONE •
	BM operator%(D_BASE);	// DONE •

	BM operator+=(BM);		// DONE •
	BM operator-=(BM);		// DONE •
	BM operator*=(BM);		// DONE •
	BM operator*=(BASE);	// DONE •
	
	// {
	BM operator<<(int k);   // DONE • [didn't present]  (ошибок пока что не обнаружено)
	BM operator>>(int k);   // DONE • [didn't present]  (ошибок пока что не обнаружено)
	// ОЧЕНЬ НУЖНО СДЕЛАТЬ ДЛЯ ТЕОРЕТИКО_ЧИСЛОВЫХ МЕТОДОВ В КРИПТОГРАФИИ!!!!!!!!!!!!!!
	BM operator<<=(int k);  // UNDONE			x 
	BM operator>>=(int k);  // UNDONE			x
	// }
	BM sqr();				// DONE • [didn't present]
	BM pow(int k);			// DONE • [didn't present] // вариант "справа-налево"
	BM pow(BM k);			// DONE • [didn't present] // возможно корректно, проверка была неполной

	bool operator ==(BM);	// DONE •
	bool operator !=(BM);	// DONE •
	bool operator <=(BM);	// DONE •
	bool operator > (BM);	// DONE •
	bool operator < (BM);	// DONE •
	bool operator >=(BM);	// DONE •
	*/
	bool BM::is_zero() {
		int i = Len - 1;
		while (i >= 0 && !hexa[i])i--;
		return (i < 0);
	}

	//void OutputHEX();		// DONE •
	//void InputHEX();		// DONE •
	//void OutputDEC();		// DONE	•
	//void InputDEC();		// DONE •
//};
bool BM::operator ==(BM s) {	// DONE
	if (Len != s.Len)return false;
	for (int i = s.Len - 1; i >= 0; i--)if (hexa[i] != s.hexa[i])return false;
	return true;
}
bool BM::operator !=(BM s) {
	if (Len != s.Len)return true;
	for (int i = Len - 1; i >= 0; i--)if (hexa[i] != s.hexa[i])return true;
	return false;
}	// DONE
bool BM::operator <=(BM s) {
	if (Len < s.Len) return true;
	if (Len > s.Len) return false;

	int i = Len - 1;
	for (i; i >= 0; i--)if (hexa[i] < s.hexa[i])return true; else if (hexa[i] != s.hexa[i])return false;
	return true;
}	// DONE
bool BM::operator > (BM s) {
	if (Len < s.Len)return false;
	if (Len > s.Len)return true;
	int i = Len - 1;
	for (i; i >= 0; i--) if (hexa[i] < s.hexa[i])return false; else if (hexa[i] != s.hexa[i])return true;
	return false;
}
bool BM::operator < (BM s) {
	if (Len < s.Len)return true;
	if (Len > s.Len)return false;
	int i = Len - 1;
	for (i; i >= 0; i--) if (hexa[i] > s.hexa[i])return false; else if (hexa[i] != s.hexa[i])return true;
	return false;
}// DONE
bool BM::operator >=(BM s) {
	if (Len < s.Len)return false;
	if (Len > s.Len)return true;
	int i = Len - 1;
	for (i; i >= 0; i--)if (hexa[i] > s.hexa[i])
	{
		return true;
	}
	else
		if (hexa[i] != s.hexa[i]) {
			return false;
		}
	return true;
}




BM BM::operator-(BM s) {
	bool flag = (*this < s);
	 // работаем только с положительными числами, 
	 // значит если результат будет отрицательный, но флаг минуса не возвращается (пока что)

	int iterator = 0; // s.hexa.size();
	int bigger_iterator = 0; // hexa.size();
	if (flag) {
		iterator = hexa.size();
		bigger_iterator = s.hexa.size();
	}
	else {
		iterator = s.hexa.size();
		bigger_iterator = hexa.size();
	}


	BM result = (flag)? s : *this;
	BM min = (flag) ? *this : s;
	int i = 0;
	bool k = 0;	// 0 - нет нехватки, 1 - есть нехватка(занимаем)
	for (i; i < iterator; i++) {
		D_BASE temp = ((D_BASE)((D_BASE)1 << (size_of_base << 3)) | (D_BASE)result.hexa[i]);
		result.hexa[i] = temp = temp - (D_BASE)min.hexa[i] - (D_BASE)k;
		k = !(temp >> (size_of_base << 3));	// если произошло занимание из разряда слева
		// то единица слева встанет в 0 (0000 00... 0001 0000 0000 ... 0000
		//												[size_of_base * 8 нулей]
	}
	if (k) {
		while (i < bigger_iterator && !result.hexa[i]) { result.hexa[i] = (~0);  i++; }
		result.hexa[i]--;
	}
	i = result.hexa.size() - 1;
	while (i > 0 && !result.hexa[i]) { result.hexa.pop_back(); i--; }
	result.Len = result.hexa.size();
	return result;
}
BM BM::operator+(BM s) {

	D_BASE k = 0;
	bool bigger_flag = (hexa.size() > s.hexa.size());
	int iterator = (bigger_flag) ? s.hexa.size() : hexa.size(); // обходит меньшее число
	int bigger_iterator = (bigger_flag) ? hexa.size() : s.hexa.size(); // обходит большее число

	BM result = (bigger_flag) ? *this : s;
	int i = 0;
	for (i = 0; i < iterator; i++) {
		D_BASE temp = (D_BASE)hexa[i] + (D_BASE)s.hexa[i] + k;
		result.hexa[i] = temp;
		k = temp >> (size_of_base << 3);
	}
	if (iterator == bigger_iterator) {
		if (k) result.hexa.push_back(1);
		result.Len = result.hexa.size();
		return result;
	}
	if (k) {
		while (i < bigger_iterator && result.hexa[i] == (BASE)(~0)) {
			result.hexa[i] = 0; i++;
		}
		if (i == bigger_iterator) {
			result.hexa.push_back(1);
			result.Len++;
		}
		else {
			result.hexa[i]++;
		}
	}
	result.Len = result.hexa.size();
	return result;
}
BM BM::operator*(BM s) {			// rework
	BM result(0, 0);
	for (int i = 0; i < hexa.size() + s.hexa.size() - 1; i++)result.hexa.push_back(0);
	result.Len = result.hexa.size();
	int i = 0;
	int j = 0;
	D_BASE temp = 0;	// результат на одной итерации умножения
	// содержит в своей правой части рез-т для записи
	// в левой - переполнение
	BASE k = 0;	// переполнение с прошлого шага (для добавления к текущему)
	for (i = 0; i < s.hexa.size(); i++) {
		if (s.hexa[i])
			for (j = 0; j < hexa.size(); j++) {
				temp = (D_BASE)((D_BASE)s.hexa[i] * (D_BASE)hexa[j]) + (D_BASE)result.hexa[i + j] + (D_BASE)k;
				k = temp >> (size_of_base << 3);
				result.hexa[i + j] = temp;
			}
		if (k) { result.hexa[i + j] += k; k = 0; }	// обработка последнего переполнения
		//for (int g = i + j; g < result.hexa.size() && k; g++) {
		//	result.hexa[g] = temp = (D_BASE)result.hexa[g] + (D_BASE)k;
		//	k = temp >> (size_of_base << 3);
		//}

	}
	i = result.hexa.size() - 1;	// нормировка длины (удаление незначащих нулей)
	while (i && !result.hexa[i]) { result.hexa.pop_back(); i--; }
	result.Len = result.hexa.size();
	return result;
}
BM BM::operator*(BASE s) {			// resork
	if (s == 0)return BM(1, 0);	// если ноль, то return 0
	BM result(hexa.size() + 1, 0);
	for (int i = 0; i < hexa.size() + 1; i++)result.hexa.push_back(0);
	D_BASE temp = 0;
	int  j = 0;
	BASE k = 0;	// переполнение с прошлого шага (для добавления к текущему)
	for (j = 0; j < hexa.size(); j++) {
		temp = (D_BASE)((D_BASE)s * (D_BASE)hexa[j]) + (D_BASE)result.hexa[j] + (D_BASE)k;
		k = temp >> (size_of_base << 3);
		result.hexa[j] = temp;
	}
	if (k) { result.hexa[j] += k; }	// обработка последнего переполнения



	j = result.hexa.size() - 1;	// нормировка длины (удаление незначащих нулей)
	while (j && !result.hexa[j]) { result.hexa.pop_back(); j--; }
	result.Len = result.hexa.size();
	return result;


}

BM BM::operator/(BM s) {
	if (s.hexa.size() == 1)return *this / s.hexa[0];
	if (s.is_zero()) {
		cout << "NNNOOOOOOO DIVISON BY ZERO!!!!!!" << endl;
		return BM(1, 1);		// случай деления на 0
	}
	if (*this < s)return BM(1, 0);
	if (*this == s) {
		BM result(1, 0);
		result.hexa[0] = 1;
		return result;
	}
	//if (s.Len == 1 && s.hexa[0] == 0)return BM(1, 0);
	D_BASE b = ((D_BASE)1 << (D_BASE)((D_BASE)size_of_base << 3));
	int m = hexa.size() + 1 - s.hexa.size(); // size of result
	int n = s.hexa.size();	// size of second operand
	BM result(0, 0);	// создаём число-результат
	for (int i = 0; i < m - 1; i++)result.hexa.push_back(0);

	BASE d = D_BASE(b / ((D_BASE)(s.hexa[n - 1] + 1))); // d = [ b/(v[n-1] + 1) ]

	BM local_this = (d == 1) ? *this : (*this) * d;
	if (local_this.hexa.size() == this->hexa.size())local_this.hexa.push_back(0);
	s = s * d;

	int j = m - 1;
	for (j; j >= 0; j--) {
		// ============			D3
		D_BASE temp_q = D_BASE(	// q' = [ (u[j+n]*b + u[j+n-1]) / v[n-1] ]
			D_BASE(
				((D_BASE)local_this.hexa[j + n] << ((D_BASE)size_of_base << 3))
				+ local_this.hexa[j + n - 1])
			/ s.hexa[n - 1]);
		D_BASE temp_r = D_BASE(	// r' = [ (u[j+n]*b + u[j+n-1]) % v[n-1] ]
			D_BASE(
				((D_BASE)local_this.hexa[j + n] << ((D_BASE)size_of_base << 3))
				+ local_this.hexa[j + n - 1])
			% s.hexa[n - 1]);
		while (temp_r < b) {
			if (temp_q == b || temp_q * s.hexa[n - 2] > ((D_BASE)temp_r << ((D_BASE)size_of_base << 3)) + local_this.hexa[j + n - 2]) {
				temp_q--;
				temp_r += s.hexa[n - 1];
			}
			else break;
		}

		// ===========		D4
		BM temp_this(0, 0);
		temp_this.hexa.pop_back();
		//for (int i = 0; i < n; i++)temp_this.hexa.push_back(0);
		for (int i = 0; i <= n; i++)temp_this.hexa.push_back(local_this.hexa[i + j]);
		temp_this.Len = n + 1;
		BM h = s * temp_q;
		if (temp_this.hexa[temp_this.hexa.size() - 1] == 0) {
			temp_this.hexa.pop_back();
		}
		temp_this.Len = temp_this.hexa.size();
		if (temp_this < h) {
			temp_q--; h -= s;
		}

		int temp_len_of_temp_this = n + 1;			// current len of temp_this
		temp_this = temp_this - h;
		int i = 0;
		for (i; i < temp_this.hexa.size(); i++) {
			local_this.hexa[i + j] = temp_this.hexa[i];
		}
		if (temp_this.hexa.size() < temp_len_of_temp_this)
			for (i; i <= n; i++)local_this.hexa[i + j] = 0;
		result.hexa[j] = temp_q;
		// if( q'*v > local_this[j:j+n]{ q'--; k=1} -> коррекция q' на шаге D6

	}
	for (int i=result.hexa.size()-1; i>0; i--){
		if (result.hexa[i] == 0)result.hexa.pop_back();
		else break;
	}

	result.Len = result.hexa.size();
	return result;
	// fafefbcda / 7 65 = 2 1F 18 70			( 2 1F 18 71 ) •
	// 10 00 00 00	/ 2 56 = 5 66 00			( 6 D9 78 ) •
	// BA CE DA BC / D EF = 	D 67 14			( D 68 32)	•	
	// DFAEFADE323456 / 823DEF = 1 B7 AA 8F 46 •
}
BM BM::operator%(BM s) {
	//std::cout << "in %: this.size(): " << this->hexa.size() << " s.size(): " << s.hexa.size() << '\n';;
	//this->OutputDEC(); std::cout << ' '; s.OutputDEC(); std::cout << '\n';
	//std::cout << "Enter in %\n";
	//std::cout << "this: "; this->OutputDEC(); std::cout << "s: "; s.OutputDEC(); std::cout << '\n';
	//std::cout << this->size() << ' ' << s.size();
	if (s.hexa.size() == 1)return *this % s.hexa[0];
	int e = 0;
	if (s.is_zero()) {
		cout << "NNNOOOOOOO DIVISON BY ZERO!!!!!!" << endl;
		return BM(1, 1);		// случай деления на 0
	}
	if (*this < s)return *this;
	if (*this == s)return BM(1, 0);
	//if (s.Len == 1 && s.hexa[0] == 0)return BM(1, 0);
	D_BASE b = ((D_BASE)1 << (D_BASE)((D_BASE)size_of_base << 3));
	int m = hexa.size()  +1 - s.hexa.size(); // size of result
	int n = s.hexa.size();	// size of second operand
	//BM result(m, 0);	// создаём число-результат

	BASE d = D_BASE(b / ((D_BASE)((D_BASE)s.hexa[n - 1] + 1))); // d = [ b/(v[n-1] + 1) ]

	BM local_this = (d == 1) ? *this : (*this) * d;
	if (local_this.hexa.size() == this->hexa.size())local_this.hexa.push_back(0);
	s = s * d;

	int j = m - 1;
	for (j; j >= 0; j--) {
		//std::cout << "in % D3\n";
		// ============			D3
		D_BASE temp_q = D_BASE(	// q' = [ (u[j+n]*b + u[j+n-1]) / v[n-1] ]
			D_BASE(
				((D_BASE)local_this.hexa[j + n] << ((D_BASE)size_of_base << 3))
				+ local_this.hexa[j + n - 1])
			/ s.hexa[n - 1]);
		D_BASE temp_r = D_BASE(	// r' = [ (u[j+n]*b + u[j+n-1]) % v[n-1] ]
			D_BASE(
				((D_BASE)local_this.hexa[j + n] << ((D_BASE)size_of_base << 3))
				+ local_this.hexa[j + n - 1])
			% s.hexa[n - 1]);
		while (temp_r < b) {
			if (temp_q == b || temp_q * s.hexa[n - 2] > ((D_BASE)temp_r << ((D_BASE)size_of_base << 3)) + local_this.hexa[j + n - 2]) {
				temp_q--;
				temp_r += s.hexa[n - 1];
			}
			else break;
		}

		// ===========		D4
		//std::cout << "int % D4\n";
		BM temp_this(0, 0);
		temp_this.hexa.pop_back();
		//for(int i=0; i<n+1; i++)
		for (int i = 0; i <= n; i++)temp_this.hexa.push_back(local_this.hexa[i + j]);
		temp_this.Len = n + 1;
		BM h = s * temp_q;
		if (temp_this.hexa[temp_this.hexa.size() - 1] == 0) {
			temp_this.hexa.pop_back();
		}
		temp_this.Len = temp_this.hexa.size();
		if (temp_this < h) {
			temp_q--; h -= s;
		}
		//std::cout << "in % D4 f \n";
		int temp_len_of_temp_this = n + 1;			// current len of temp_this
		temp_this = temp_this - h;
		int i = 0;
		for (i; i < temp_this.hexa.size(); i++) {
			local_this.hexa[i + j] = temp_this.hexa[i];
		}
		if (temp_this.hexa.size() < temp_len_of_temp_this)
			for (i; i <= n; i++)local_this.hexa[i + j] = 0;
		//result.hexa[j] = temp_q;
		// if( q'*v > local_this[j:j+n]{ q'--; k=1} -> коррекция q' на шаге D6

	}
	//std::cout << "Out from %\n";
	//while (local_this.hexa[local_this.hexa.size() - 1] == 0)local_this.hexa.pop_back();
	for (int i = local_this.hexa.size()-1; i > 0; i--) {
		if (local_this.hexa[i] == 0)local_this.hexa.pop_back();
		else break;
	}
	local_this.Len = local_this.hexa.size();
	return local_this / d;
}
BM BM::operator/(BASE s) {
	if (!s) {
		cout << "NO DIVISION BY ZERO!!!!!!!!!!!" << endl;
		return BM(1, 1);
	}
	BM local_this = *this;
	int n = local_this.hexa.size();	// size of result = n or n-1
	//local_this.hexa.push_back(0);
	BM result(0, 0);
	for (int i = 0; i < n - 1; i++)result.hexa.push_back(0);
	int j = n - 2;		// чтобы запустить цикл от предпоследней цифры(след. за самой старшей)

	if (j == -1) {		// если делим цифру на цифру
		result.hexa[0] = local_this.hexa[0] / s;
		result.Len = 1;
		return result;
	}
	if (local_this.hexa[n - 1] >= s) {
		result.hexa[n - 1] = (local_this.hexa[n - 1] / s);
		local_this.hexa[n - 1] = (local_this.hexa[n - 1] % s);
	}

	for (j; j >= 0; j--) {
		D_BASE temp_round = (D_BASE)((D_BASE)local_this.hexa[j] | ((D_BASE)local_this.hexa[j + 1] << ((D_BASE)size_of_base << 3)));
		BASE temp_q = temp_round / s;
		//BASE temp_r = temp_round % s;
		result.hexa[j] = temp_q;
		local_this.hexa[j] = temp_round - temp_q * s;

	}
	j = result.hexa.size() - 1;
	
	for (int i = result.hexa.size() - 1; i > 0; i--) {
		if (result.hexa[i] == 0)result.hexa.pop_back();
		else break;
	}
	result.Len = result.hexa.size();
	return result;

}
BM BM::operator%(BASE s) {
	if (hexa.size() == 0) {
		BASE hh = hexa[0] % s;
		BM resu(1, 0);
		resu.hexa[0] = hh;
		return hh;
	}
	if (!s) {
		cout << "NO DIVISION BY ZERO!!!!!!!!!!!" << endl;
		return 0;
	}
	BM local_this = *this;
	int n = local_this.hexa.size();	// size of result = n or n-1
	//local_this.hexa.push_back(0);
	BM result(0, 0); result.hexa.clear();
	for (int i = 0; i < n; i++)result.hexa.push_back(0);
	if (local_this.hexa[n - 1] >= s) {
		result.hexa[n-1] = (local_this.hexa[n - 1] / s);
		local_this.hexa[n - 1] = local_this.hexa[n - 1] % s;
	}
	else result.hexa.pop_back();
	int j = local_this.hexa.size() - 2;
	for (j; j >= 0; j--) {
		D_BASE temp_round = (D_BASE)((D_BASE)local_this.hexa[j] + ((D_BASE)local_this.hexa[j + 1] << ((D_BASE)size_of_base << 3)));
		BASE temp_q = temp_round / s;
		//BASE temp_r = temp_round % s;
		result.hexa[j] = temp_q;
		temp_round = temp_round - temp_q * s;
		local_this.hexa[j] = temp_round;
	}
	BM res_r(1, 0); res_r.hexa[0] = local_this.hexa[0];
	return res_r;
	//return local_this.hexa[0];
}

BM BM::operator+=(BM s) {
	*this = *this + s;
	return *this;
}
BM BM::operator-=(BM s) {
	*this = *this - s;
	return *this;
}
BM BM::operator*=(BM s) {
	*this = *this * s;
	return *this;
}
BM BM::operator*=(BASE s) {
	*this = *this * s;
	return *this;
}


BM::BM(int len, int t) {			// КОНСТРУКТОР ПО РАЗМЕРУ
	hexa.clear();
	if (len == 0 || t == 0) {
		if (len != 0) {
			for (int i = 0; i < len; i++)hexa.push_back(0);
			Len = len; 
			return;
		}
		Len = 1;
		hexa.push_back(0);
		return;
	}
	else {
		Len = len;
		if (size_of_base >> 2)
			for (len; len > 0; len--)hexa.push_back((rand() << 16 | rand()));
		else for (len; len > 0; len--)hexa.push_back(rand());
		// заполняет int(неявным преобразованием срезает левую часть для меньших типов данных)
		for (Len = hexa.size() - 1; !hexa[Len] && Len > 0; Len--)hexa.pop_back();
		Len++;
	}
}

BM::BM(int s) {
	if (s < 0)s = -s;
	//int g = s;
	for (Len = 0; s; Len++) {
		hexa.push_back(s % (1<<(size_of_base << 3)));
		s = s / (1<<(size_of_base << 3));
	}
}
BM::BM(BM& s) {
	Len = s.Len;
	hexa = s.hexa;
	//for (int i = 0; i < s.hexa.size(); i++)hexa.push_back(s.hexa[i]);
}
BM::BM(const string s) {
	int s_len = s.length();	// кол-во символов в вводе
	int wall = (s_len % (size_of_base << 1)) ? (s_len / (size_of_base << 1)) + 1 : (s_len / (size_of_base << 1));
	for (int i = 0; i < wall; i++)hexa.push_back(0); // создаем сразу достаточно ячеек
	// теперь используем её для прохода по строке
	char counter = 0; // 0 - up to size_of_base * 2;
	for (int i = 0, j = s_len - 1; j >= 0; i++) {		// проходим строку с конца (пока не конец строки)
		for (counter = 0; counter < (size_of_base << 1) && j >= 0; counter++, j--) {	// пока находимся в одной цифре по основанию 2^(size_of_base*8)
			char b = s[j];
			if (b >= '0' && b <= '9')b = b - 48;
			else if (b >= 'A' && b <= 'F')b = b - 55;
			else if (b >= 'a' && b <= 'f')b = b - 87;// >:C
			else { cout << "Error with input! got: _" << b << ((int)b) << '_' << endl; }
			hexa[i] |= b << ((counter % (size_of_base << 1)) * 4);
		}
	}
	int i = wall - 1;
	while (i && !hexa[i]) { hexa.pop_back(); i--; }


	Len = wall;
}

BM BM::operator=(const BM& s) {
	if (this == &s)return *this;
	Len = s.Len;
	hexa = s.hexa;
	return *this;
}

void BM::InputHEX() {
	hexa.clear();	// начинаем перезаписывать объект, значит чистим что там было до этого
	string s;		// ввод
	cin >> s;
	int s_len = s.length();	// кол-во символов в вводе
	int wall = (s_len % (size_of_base << 1)) ? (s_len / (size_of_base << 1)) + 1 : (s_len / (size_of_base << 1));
	for (int i = 0; i < wall; i++)hexa.push_back(0); // создаем сразу достаточно ячеек
	// теперь используем её для прохода по строке
	char counter = 0; // 0 - up to size_of_base * 2;
	for (int i = 0, j = s_len - 1; j >= 0; i++) {		// проходим строку с конца (пока не конец строки)
		for (counter = 0; counter < (size_of_base << 1) && j >= 0; counter++, j--) {	// пока находимся в одной цифре по основанию 2^(size_of_base*8)
			char b = s[j];
			if (b >= '0' && b <= '9')b = b - 48;
			else if (b >= 'A' && b <= 'F')b = b - 55;
			else if (b >= 'a' && b <= 'f')b = b - 87;// >:C
			else { cout << "Error with input! got: _" << b << ((int)b) << '_' << endl; }
			hexa[i] |= b << ((counter % (size_of_base << 1)) * 4);
		}
	}
	int i = wall - 1;
	while (i && !hexa[i]) { hexa.pop_back(); i--; }


	Len = wall;
}
void BM::OutputHEX() {
	if (hexa.size() == 1 && !hexa[0]) {
		cout << '0'; return;
	}
	int start = (hexa.size() - 1); /// (size_of_base * 2);
	while (start && !hexa[start])start--;
	if (!start && !hexa[start]) {
		cout << '0'; return;
	}
	BASE mask = 15 << ((size_of_base << 3) - 4);
	int j = 0;
	while (!(hexa[start] & mask)) { j++; mask >>= 4; }
	for (j; mask; mask >>= 4, j++) {
		char b = (hexa[start] & mask) >> (((size_of_base << 3) - (j << 2)) - 4);
		if (b <= 9)cout << char(b + 48);
		else cout << char(b + 55);
		//mask >>= 4;
	}
	cout << ' ';
	mask = 15 << ((size_of_base << 3) - 4);
	char double_base_size = size_of_base * 2;
	for (int i = start - 1; i >= 0; i--) {
		for (int j = 0; j < double_base_size; j++) {
			char b = (hexa[i] & mask) >> (((size_of_base << 3) - (j << 2)) - 4);
			if (b <= 9)cout << char(b + 48);
			else cout << char(b + 55);
			mask >>= 4;
		}
		mask = 15 << ((size_of_base << 3) - 4);
		cout << ' ';
	}

}
void BM::OutputDEC() {			// DONE
	BM temp(1, 0);
	temp.hexa[0] = 9;//temp.hexa.push_back(9);
	BM local_this = *this;
	vector <BASE> out;
	int i = 0;
	//D_BASE b = (D_BASE)1 << ((D_BASE)size_of_base << 3);
	while (local_this > temp) {
		out.push_back((local_this % 10).hexa[0]);
		local_this = local_this / 10;
		i++;
	}
	out.push_back(local_this.hexa[0] % 10);
	for (int j = 0; i >= 0 && j < out.size() % 3; j++, i--) {
		cout << (int)out[i];
	}
	if(out.size() % 3)cout << ' ';
	for (i; i >= 0;) {
		for (int j = 0; j < 3 && i >= 0; j++, i--) {
			cout << (int)out[i];
		}
		cout << ' ';
	}
}
void BM::InputDEC() {
	string s;
	cin >> s;
	const int n = s.length();
	if (n == 0) { *this = BM(1, 0); return; }
	hexa.clear();
	hexa.push_back(0);
	BM temp(1, 0);
	for (int i = 0; i < n; i++) {
		temp = (s[i] - 48);
		*this = *this * 10 + temp;

	}
	Len = this->hexa.size();
}

// работает лишь только для k = 0,1,...,size_of_base*8
BM BM::operator<<(int k) {
	if (k < 0)return *this;
	BM local = *this;
	int prev_size = local.hexa.size();
	int place_with_bits = 0;
	for (place_with_bits; local.hexa[local.hexa.size() - 1] >> (place_with_bits); place_with_bits++);
	//int place_for_zeros = (size_of_base << 3) - place_with_bits; // кол-во битов нулей слева в самом старшем разряде
	int extra_cells = (k+place_with_bits) / (size_of_base << 3); // кол-во доп. ячеек для сдвига
	for (int i = 0; i < extra_cells; i++)local.hexa.push_back(0);
	int ger_shift = k / (size_of_base << 3);
	//int diff = local.size() - ger_shift;
	//if (ger_shift > local.hexa.size()) {
	//	for (int i = local.hexa.size(); i < ger_shift; i++)local.hexa.push_back(0);
	//}
	int mod_shift = k % (size_of_base << 3);
	if (ger_shift) {
		for (int i = local.hexa.size() - 1; i >= ger_shift; i--) {
			local.hexa[i] = local.hexa[i - ger_shift];
		}
		for (int i = 0; i < ger_shift; i++) {
			local.hexa[i] = 0;
		}
	}
	
	//BASE mask = 0;
	BASE k_mask = (~0) << ((size_of_base << 3) - mod_shift);
	int back_shift = ((size_of_base << 3) - mod_shift);
	for (int i = local.hexa.size() - 1; i > 0; i--) {
		local.hexa[i] = local.hexa[i] << mod_shift | ((k_mask & local.hexa[i-1]) >> back_shift);
		//mask = hexa[i-1] & 
	}
	local.hexa[0] <<= mod_shift;
	local.Len = local.hexa.size();
	while (local.Len && !local.hexa[local.Len - 1]) {
		local.hexa.pop_back(); local.Len--;
	}
	return local;
}
BM BM::operator>>(int k) {
	if (k < 0)return *this;
	BM local = *this;
	int prev_size = local.hexa.size();
	int place_with_bits = 0;
	for (place_with_bits; local.hexa[local.hexa.size() - 1] >> (place_with_bits); place_with_bits++);
	//int place_for_zeros = (size_of_base << 3) - place_with_bits; // кол-во битов нулей слева в самом старшем разряде
	int extra_cells = (k + place_with_bits) / (size_of_base << 3); // кол-во доп. ячеек для сдвига
	//for (int i = 0; i < extra_cells; i++)local.hexa.push_back(0);
	int ger_shift = k / (size_of_base << 3);
	//int diff = local.size() - ger_shift;
	//if (ger_shift > local.hexa.size()) {
	//	for (int i = local.hexa.size(); i < ger_shift; i++)local.hexa.push_back(0);
	//}
	
	int mod_shift = k % (size_of_base << 3);
	if (ger_shift){
		for (int i = 0; i < ((int)local.hexa.size() - ger_shift); i++) {
			local.hexa[i] = local.hexa[i + ger_shift];
		}
		if (ger_shift >= local.hexa.size()) {
			return BM(1, 0);
		}
		for (int i = 0; i < ger_shift; i++) {
			local.hexa.pop_back();
		}
	}

	//BASE mask = 0;
	BASE k_mask = (~0) >> ((size_of_base << 3) - mod_shift);
	int back_shift = ((size_of_base << 3) - mod_shift);
	for (int i = 0; i <local.hexa.size()-1; i++) {
		local.hexa[i] = local.hexa[i] >> mod_shift | ((k_mask & local.hexa[i + 1]) << back_shift);
		//mask = hexa[i-1] & 
	}
	local.hexa[local.hexa.size()-1] >>= mod_shift;
	//local.Len = local.hexa.size();
	while (local.hexa.size() > 0 && local.hexa[local.hexa.size() - 1] == 0)local.hexa.pop_back();
	local.Len = local.hexa.size();
	return local;
}
int BM::size() {
	return hexa.size();
}



// возведение в квадрат по алгоритму из учебника "числовые методы в криптографии"
BM BM::sqr() {
	long long n = hexa.size();
	BM result((n << 1) + 1, 0);	// размер результата <= 2n, +1 ячейка т.к. в алгоритме допущение обращение к этому разряду
	BASE c = 0, u = 0, v = 0;		// коэф-ты c, u, v
	D_BASE uv = 0;			// скреплённые числа из коэф-ов c, u, v
	D_BASE cu = 0;
	BASE mask_right = (BASE)(~0);										// 00...00 00...00 00...00 11...11
	// [size_of_base*4*8] [size_of_base*8]
	D_BASE mask_middle = (D_BASE)(mask_right) << (size_of_base << 3);	// 00...00 00...00 11...11 00...00
	Q_BASE mask_left = (Q_BASE)(mask_middle) << (size_of_base << 3);	// 00...00 11...11 00...00 00...00
	for (long long i = 0; i < n; i++) {
		D_BASE uv = result.hexa[i << 1] + hexa[i] * hexa[i]; // шаг 2.1
		c = 0;
		u = uv >> (size_of_base << 3);
		cu = c << (size_of_base << 3) | u;
		result.hexa[i << 1] = v = (uv & ((BASE)(~0)));
		for (long long j = i + 1; j < n; j++) {	// j = i+1, ... n-1 шаг 2.2
			Q_BASE cuv = (Q_BASE)result.hexa[i + j] + ((Q_BASE)((Q_BASE)hexa[i] * (Q_BASE)hexa[j]) << 1) + (Q_BASE)cu;
			c = (cuv & mask_left) >> (size_of_base << 4);//(cuv >> (size_of_base << 4))<< (size_of_base << 4);
			u = (cuv & mask_middle) >> (size_of_base << 3);//((cuv >> (size_of_base << 3)) << (size_of_base << 4)) >> (size_of_base << 3);
			v = cuv & mask_right; //cuv & ((~0) >> (size_of_base << 3));
			//uv = ((D_BASE)u << (size_of_base << 3)) | v;//cuv >> (size_of_base << 3);
			cu = ((D_BASE)c << (size_of_base << 3)) | u;//cuv >> (size_of_base << 4);
			result.hexa[i + j] = v;
			//std::cout << cuv<<'\n';
		}
		// шаг 2.3
		result.hexa[i + n + 1] += c;
		result.hexa[i + n] += u;
		//v = cuv & mask_right;
		uv = ((D_BASE)u << (size_of_base << 3)) | v;
	}
	while (result.hexa[result.hexa.size() - 1] == 0)result.hexa.pop_back();
	result.Len = result.hexa.size();
	//result.hexa.pop_back(); // убираем лишний левый разряд (он равен нулю)
	return result;
}


// БЧ в степени цифры (Дихотомический)
BM BM::pow(int k) {
	if (k < 0)return *this;	// если степень отрицательная, то ничего не делаем
	if (k == 0) {			// если степень = 0, то return BM("1");
		return BM("1");
	}
	int i = 31;		// int = 4 bytes	// проход по всем 32 битам типа int
	for (i; i >= 0 && !((k >> i) & 1); i--);	// отступ с левой стороны до первой единицы
	BM result(1, 0);			// z = 1
	result.hexa[0] = 1;
	if (k & 1) {			// если y[0] == 1, то z = x, else z = 1
		result = *this;
	}
	BM q = *this;		// промежуточное q, : x^i
	for (int j = 1; j <= i; j++) {
		q = q.sqr();
		if ((k >> j) & 1) {
			result = result * q; // если i-й бит = 1, то домножаем результат z эту степень числа x
		}
	}
	while (result.hexa[result.hexa.size() - 1] == 0)result.hexa.pop_back();
	result.Len = result.hexa.size();
	return result;
}

// БЧ в степени БЧ (Дихотомический)
BM BM::pow(BM k) {		// аналогично для цифры int (здесь проход по всем разрядам со смещением вправо и просмотром бита в hexa[0]>>i
	//if (k < 0)return *this;
	if (k.is_zero()) {
		BM result(1, 0);
		result.hexa[0] = 1;
		return result;
	}
	int n = k.hexa.size();
	int i = size_of_base << 3;		// int = 4 bytes
	for (i; i >= 0 && !((k.hexa[n - 1] >> i) & 1); i--); // отступ с левой стороны до первой единицы
	i += (n - 1) * (size_of_base << 3);		// добавляем к этому (кол-во бит в разряде) * (число разрядов) 
	BM result(1, 0);		// далее аналогично для цифры типа int
	result.hexa[0] = 1;
	if (k.hexa[0] & 1) {
		result = *this;
	}
	BM q = *this;
	for (int j = 1; j <= i; j++) {
		q = q.sqr();
		if ((k.hexa[j >> 3] >> (j & 7)) & 1) {
			result = result * q;
		}
	}
	while (result.hexa[result.hexa.size() - 1] == 0)result.hexa.pop_back();
	result.Len = result.hexa.size();
	return result;
}

// правые n цифр
BM BM::take_last_n_digits(int n) {
	if (n < 0 || n >= hexa.size())return *this;
	if (n == 0)return BM(1, 0);
	BM local(n, 0);
	//local.hexa[0] = hexa[0];
	for (int i = 0; i < n; i++)local.hexa[i] = hexa[i];
	local.Len = n;
	return local;
}

// левые n цифр
BM BM::take_first_n_digits(int n){
	if (n >= hexa.size())return *this;
	if (n <= 0)return BM(1, 0);
	BM local(n, 0);
	for (int i = hexa.size() - 1, j=n-1; i > hexa.size() - 1 - n; i--, j--) {
		local.hexa[j] = hexa[i];
	}
	local.Len = n;
	return local;
}



// x % m
// *this % s, where s = M, *this = X, z = BASE.pow(2 * m.size()) / m;
// z = основание в степени 2k и разделить на m, k = число цифр в m
// x.size() <= 2k 
BM BM::Barretts_modula(BM s, BM z) {
	if (s.is_zero()) { return BM(1, 0); }
	if (s.hexa.size() == 1 && s.hexa[0] == 1) { return BM(1, 0); }
	// 1.
	BM B(1, 0);
	if (size_of_base == 1)B = BM("100");
	else if (size_of_base == 2)B = BM("10000");
	else if (size_of_base == 4)B = BM("100000000");
	int k = s.hexa.size();
	BM bb = B;
	B = BM(k, 0); B.hexa[B.hexa.size() - 1] = 1;//B = B.pow(k - 1);
	BM q = ((this->take_first_n_digits(this->size() - (k - 1))) * z);
	q = q.take_first_n_digits(q.size()-(k + 1)); // q = [([x / b^(k-1)]*z)/b^(k+1)]
	// 2.
	BM r1 = this->take_last_n_digits(k + 1);
	BM sub_r2 = q * s;
	BM r2 = sub_r2.take_last_n_digits(k + 1);/*
	*/
	// 3.
	BM r3(1, 0);
	if (r1 >= r2) {
		r3 = r1 - r2;
	}
	else {
		r3 = B * (bb.sqr()) + r1 - r2;
	}
	// 4.
	while (r3 >= s) {
		r3 = r3 - s;
	}
	// 5.
	return r3;


}



BM BM::sub_Barrets_z(BM& m) {
	int k = m.size();
	BM a((k = (k << 1) + 1), 0);
	a.hexa[k - 1] = 1;
	return a / m;
}



//Лабораторная работа №4.Тест Ферма проверки числа на простоту.Оценить вероятность ошибки.
// n>3, n - odd,
// t - параметр надёжности
// НЕ РАБОТАЕТ 
bool BM::Ferma_test_primality(int t) {
	srand(time(NULL));
	if ((hexa[0] & 1) == 0 || (hexa.size() == 1 && hexa[0] == 1))return false;
	if (hexa.size() == 1 && hexa[0] <= 3)return true;
	BM dva("2");
	BM one("1");
	BM a(1, 0);
	while (t) {
		std::cout <<"t = " << t << '\n';
		//std::cout << "a.set_random_less_than_M(*this-dva)";
		//a.set_random_less_than_M(*this - dva);
		BM a(this->hexa.size(), 0);
		// шаг 2.1
		a = a % (*this - (one + dva)) + dva;

		//std::cout << "a.set_random_less_than_M(*this-dva) finish\n";
		if (a.hexa.size() == 1 && a.hexa[0]<2 || a.is_zero())a.hexa[0] += 2;
		//std::cout << "Ferma: "; a.OutputDEC(); std::cout << '\n';
		BM r = a.pow_modula(*this - one, *this);
		//std::cout << "Ferma's a: "; a.OutputDEC(); std::cout << '\n';
		//std::cout << "Ferma's r: "; r.OutputDEC(); std::cout << '\n';
		//BM r = a.pow(*this - one) % (*this); // Barretts_modula(*this, z);
		//BM r = a.pow(*this - one);
		//std::cout << t << ":   a: "; a.OutputDEC();
		//r = r % (*this);
		//std::cout << "\ta.pow(*this-one) % *this: "; r.OutputDEC(); std::cout << '\n';
		//std::cout << t << " a: "; a.OutputDEC(); std::cout << "    r: "; r.OutputDEC(); std::cout << endl;
		t--;
		if (r != one) {
			//std::cout << "FERMA FALSE: "<<(r == (a.pow(*this - one) % (*this))) << '\n';
			std::cout << "Ferma:   r != one   - false";
			return false;
		}
		//a = a - one;
	}
	return true;
}




// this меняется на рандом%М
void BM::set_random_less_than_M(const BM& M) {
	int size;
	if (M.hexa.size() != 1)size = rand() % M.hexa.size() + 1;
	else size = 1;
	if (size == 1) {
		this->hexa.clear();
		hexa.push_back(rand() % M.hexa[M.hexa.size() - 1]);
		Len = 1;
		return;
	}
	this->hexa.clear();
	//*this = BM(size, 0);
	for (int i = 0; i < size ; i++) {
		hexa.push_back(rand());
	}
	hexa[hexa.size() - 1] = rand() % M.hexa[size - 1];
	//std::cout << "after cycle 1\n";
	for (int i = hexa.size() - 1; i > 0; i--) {
		if (hexa[i] == 0)hexa.pop_back();
	}

	//std::cout << "after cycle 2\n";
	Len = hexa.size();
	//hexa[Len - 1] = rand() % M.hexa[M.hexa.size() - 1];
	//return local;
}


//
bool BM::Miller_Rabin_test_primality(int t) {
	if (hexa.size() == 0 && hexa[0] < 4)return true;
	if ((hexa[0] & 1) == 0 || (hexa.size()==1 && hexa[0] == 1))return false;
	BM r(1, 0);
	int s=1;
	// шаг 1
	while (((*this >> s).hexa[0] & 1) == 0)s++;
	r = *this >> s;
	BM two("2");
	BM one("1");
	BM n1 = *this - one;

	BM rand_iterator = two;
	// шаг 2
	while (t) {
		std::cout << "t = " << t << '\n';
		//std::cout << t << '\n';
		BM b(this->hexa.size() , 0);
		// шаг 2.1
		b = b % (*this - (one + two)) + two;
		//b.set_random_less_than_M(*this - two);
		//std::cout << "MR called randomizer succesfully\n";
		if (b < two || b.is_zero())b.hexa[0]+=2;
		//std::cout << "Rabin: "; b.OutputDEC(); std::cout << '\n';
		// шаг 2.2
		//BM y = b.pow(r)%*this;
		BM prev_b = b;
		BM y = b.pow_modula(r, *this);
		BM prev_y = y;
		// шаг 2.3
		if (y != n1 && y != one) {
			//std::cout << "in if(y!=n1 && y!=one){\n";
			// шаг 2.3.1
			int j = 1;
			// шаг 2.3.2
			while (j < s && y != n1) {
				/*-*/	y = y.sqr();
						y = y % (*this);
				/*-*/	if (y == one) {
							//std::cout << "Rabin: y == one	- false";
							//std::cout << "y = b.pow_mod(r, *this);   y - "; y.OutputDEC();
							//std:: cout << "	r - "; r.OutputDEC();
							//std::cout << '\n';
							return false;
						}
				/*-*/	j++;
			}
			if (y != n1) {

				//std::cout << "Rabin: y != n1	- false";
				//std::cout << "y = "; y.OutputDEC();
				//std::cout << "	n1 = "; n1.OutputDEC();
				//std::cout << '\n';
				return false;
			}
		}
		t--;
	}
	return true;
}

int BM::Jacobi_symbol(BM n) {
	if (this->is_zero())return 0;
	if (*this == BM("1"))return 1;
	int k = 0;
	for (k = 0; k < hexa.size() * (size_of_base << 3) &&
		(((hexa[k / (size_of_base << 3)] >> (k % (size_of_base << 3))) & 1) == 0); k++);
	BM a1 = ((*this) >> k);
	a1.Len = a1.hexa.size();
	int s = 0;
	if ((k & 1) == 0)s = 1;
	else if ((n.hexa[0] & 7) == 1 || (n.hexa[0] & 7) == 7)s = 1;
	else s = -1;
	if (((n.hexa[0] & 3) == 3) && ((a1.hexa[0] & 3) == 3))s = -s;
	if (a1.size() == 1 && a1.hexa[0] == 1)return s;
	else {
		BM perc = n % a1;
		while (perc.hexa[perc.hexa.size() - 1] == 0)perc.hexa.pop_back();
		return s * perc.Jacobi_symbol(a1);
	
	}
}

// (a/n) = Jacobi's symbol
bool BM::Solovey_Strassen_test_primality(int t) { 
	BM one("1");
	BM two("2");
	if (hexa.size() == 0 && hexa[0] < 3)return true;
	if (hexa[0] & 1 == 0 || (hexa.size() == 1 && hexa[0] == 1))return false;
	while (t) {
		std::cout << "t = " << t << '\n';
		//BM a(1, 0);
		//a.set_random_less_than_M(*this - two);
		BM a(this->hexa.size(), 0);
		// шаг 2.1
		a = a % (*this - (one + two)) + two;
		if (a < two || a.is_zero())a = a + two;
		BM r = a.pow_modula((*this - one) >> 1, *this);
		//r.Len = r.hexa.size();
		//if (!(((r != one) && (r == (*this - one))) || ((r != (*this - one)) && r == one))) {
		if(!((r == one) || (r == (*this-one)))){
			std::cout << "Strasen: big if()    - false";
			return false;
		}
		int s = a.Jacobi_symbol(*this);
		BM s_BM((s < 0) ? (*this - one) : s);
		if ((r % (*this)) != s_BM) {
			std::cout << "Starssen:   r % this != s_BM    -   false";
			return false;
		}
		t--;
	}
	return true;
}



BM BM::pow_modula(BM power, BM mod) {
	BM BB(1, 0);
	if (size_of_base == 1)BB = BM("100");
	else if (size_of_base == 2)BB = BM("10000");
	else if (size_of_base == 4)BB = BM("100000000");
	BM z(2 * mod.size(), 0);
	z.hexa[z.hexa.size() - 1] = 1;
	z = z / mod;
	if (power.is_zero()) {
		BM result(1, 0);
		result.hexa[0] = 1;
		return result;
	}
	int n = power.hexa.size();
	int i = size_of_base << 3;		// int = 4 bytes
	for (i; i >= 0 && !((power.hexa[n - 1] >> i) & 1); i--); // отступ с левой стороны до первой единицы
	i += (n - 1) * (size_of_base << 3);		// добавляем к этому (кол-во бит в разряде) * (число разрядов) 
	BM result(1, 0);		// далее аналогично для цифры типа int
	result.hexa[0] = 1;
	if (power.hexa[0] & 1) {
		result = *this;
	}
	BM q = *this;
	for (int j = 1; j <= i; j++) {
		q = q.sqr();
		q = q % mod;
		if ((power.hexa[j >> 3] >> (j & 7)) & 1) {
			result = result * q;
			result = result % mod;
		}
	}
	int jj = result.hexa.size()-1;
	while (jj && result.hexa[jj] == 0) { result.hexa.pop_back(); jj--; }
	result.Len = result.hexa.size();
	return result;

}


std::vector <BM> BM::trial_divisions_method(bool &final) {
	
	
	/* 2 */
	if (this->hexa.size() == 1 && this->hexa[0] == 1) {
		std::vector <BM> res;
		//BM ad = *this;
		res.emplace_back(*this);
		final = true;
		return res;
	}
	BM two("2");
	std::vector <BM> result;	// рез-т метода пробного деления (разложение)
	BM local = *this;
	while (!local.is_zero() && !(local.hexa[0] & 1)) {
		local = local >> 1;
		result.emplace_back(two);
	}
	//while()
	BM d("3");		// начальный элемент посл-ти { ds }
	BM six("6");	// вспомогательное число для продолжения { ds }	
	BM wall = this->integer_sqrt();
	BM prev_d("1");
	bool flag_l_r = true;
	/* 1 */
	int t = 0;		// Номер делителя из разложения
	int k = 0;		// Номер пробного делителя из { ds }
	
	BM one("1");
	do
	{
		/* 3 */
		BM q = local / d;
		BM r = local - d * q;
		/* 4 */
		if (r.is_zero()) {
			//t++;
			result.emplace_back(d);
			local = q;
			if (local == one) {
				final = true;
				return result;
			}
		}
		else
			if (q > d) {
				//k++;
				if (flag_l_r) {
					d = prev_d * six - one;
					flag_l_r = false;
					prev_d = prev_d + one;
				}
				else {
					d = d + one + one;// prev_d* six + one;
					flag_l_r = true;
				}
			}
			else {
				//t++;
				result.emplace_back(local);
				final = true;
				return result;
			}
	} while (d <= wall);
	result.emplace_back(local);
	final = false;
	return result;
}





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
BM BM::integer_sqrt() {
	BM x = this->sqr();
	BM x0(1,0);
	BM two("2");
	do
	{
		x0 = x;
		x = ((*this / x) + x) / two;
		//std::cout << "x: "; x.OutputDEC(); std::cout << "x0: "; x0.OutputDEC();
		//std::cout << '\n';
	} while (x < x0);
	return x0;
}



// целочисленный корень степени n
	/*
	* x(k+1) = 1/n * ( (n-1)*x(k) + [a / x(k) ^ (n-1)] )
	* a - число под корнем
	* n - степень корня
	* x(0) = a
	* x(0) > x(1) > x(2) > ... > x(k) <= x(k+1)
	*						значит ответ: [ ^n√a ] = x(k).
	*/
BM BM::integer_sqrt_n(int n) {
	BM xk(1,0);
	BM xk_1 = *this;
	int i = 0;

	do {
		i++;
		xk = xk_1;
		//xk_1 = ((double)1 / n) * ((n - 1) * xk + (int)(a / pow(xk, n - 1)));
		xk_1 = (xk * (n-1) + (*this / xk.pow(n-1))) / n;
		//std::cout << i << ' '; xk_1.OutputDEC(); std::cout << '\t'; xk.OutputDEC(); std::cout<< '\n';
	} while (xk > xk_1);
	return xk;

}



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
BM BM::Alway_algorithm(bool& success) {
	BM local = *this;
	BM result(1, 0);
	while (!local.is_zero() && !(local.hexa[0] & 1)) {
		local = local >> 1;
	}
	BM one("1");
	BM two("2");
	BM four("4");
	BM d = local.integer_sqrt_n(3) * 2 + one;
	BM d_sub = d - two;
	BM r(1, 0);
	bool minus_flag = false;
	//BM s = local.integer_sqrt();
	/* d < p < √n */
	/* d >= 2 * ^3√n + 1, √n = wall/
	
	/* 1 */
	BM r1 = local % d;							// r1 = n % d
	BM r2 = local % (d_sub);					// r2 = n % (d-2)
	BM q = ((local / d_sub) - (local / d))<<2;	// q = 4*(q2-q1)
	std::cout << "q = "; q.OutputDEC();
	BM s = local.integer_sqrt();
	std::cout << "s = [sqrt(n)] = "; s.OutputDEC(); std::cout << '\n';
	BM ttt("8F");
	/* 2 */
	while (!r1.is_zero()) {
		d = d + two;								// d = d + 2
		if (d == ttt) {
			std::cout << ' ';
		}
		if (d > s) { success = false; return BM(1, 0); }

		/* 3 */
		r = (r1 << 1) + q - r2;						// r = 2r1 - r2 + q
		minus_flag = (r2 > ((r1 << 1) + q));
		r2 = r1;
		r1 = r;

		/* 4 */
		if (minus_flag) {
			r1 = d - r1;
			q = q + four;
		}

		/* 5 */
		while (r1 >= d) {
			r1 = r1 - d;
			q = q - four;
		}

		/* 6 */
		if (r1.is_zero()) {
			success = true;
			return d;
		}
	}
	return d;

}



/*
	Алгоритм Ферма поиска ближайших к
		делителей числа n
	Вход:  n – нечётное.
	Выход: a,b - делители n, или ответ: "n - простое"
		1. Вычислить
			Если х^2 = n – выход (ответ: а = b = х).
		2. Увеличить  x  на 1.
		3. Если  x = (n+1) / 2 – выход (ответ: «n простое»).
			Иначе – вычислить z = x^2 – n, y = [√z] 
		4. Если  у^2 = z  – выход (ответ: а = х + у ,  b = х – у ).
			Иначе переход к п.2.  
*/
std::vector <BM> BM::Ferma_method_factor(bool &primal) {
	BM local = *this;
	while (!local.is_zero() && !(local.hexa[0] & 1)) {
		local = local >> 1;
	}
	BM one("1");
	BM step_3_cmp = (local + one) >> 1;
	//BM z(1, 0);
	//BM prev_z = z;
	BM y(1, 0);
	/* 1 */
	std::vector <BM> result;
	BM x = local.integer_sqrt();
	if (x.sqr() == local) {
		primal = true;
		result.emplace_back(x);
		result.emplace_back(x);
		return result;
	}
	BM z = (1, 0); // x.sqr();// - local;
	/* 2 */
	do {
		
		x = x + one;

		/* 3 */	// Если х = (n+1)/2	то n - простое. выход.
		if (x == step_3_cmp) {
			primal = false;
			result.emplace_back(one);
			result.emplace_back(one);
			return result;
		}
		else {
			z = x.sqr() - local;
			//z = z + (x << 1) - one - local;
			y = z.integer_sqrt();
		}

		/* 4 */
		if (y.sqr() == z) {
			result.emplace_back(x + y);
			result.emplace_back(x - y);
			primal = true;
			return result;
		}

	} while (true);




}



// P(0) Метод Полларда факторизации чисел
	/*
	*	Вход: составное n.
	*	Выход: d - нетривиальный делитель n, или отказ
	*		1. Положить a=2, b=2
	*		2. Положиить a = f(a), b = f(f(b)), где f(x) = (x^2 + 1) mod n
	*		3. Если a=b - выход без результата (достигнут конец периода)
	*		4. Вычислить d = НОД(|a-b|, n)
	*			Если d=1, переход к шагу 2.
	*			Иначе выход - Ответ: d
	*/	// flag = false -> отказ,	else return d
BM BM::P0_Pollard_method_factor(bool& final) {

	BM one("1");
	//BM local = *this;
	if (this->Miller_Rabin_test_primality(20)) {
		final = false;;
		return *this;
	}


	BM d(1, 0);
	/* 1 */
	BM a("2");
	BM b("2");
	int i = 0;
	do {
		i++;
		if (i == 12) {
			std::cout << ' ';
		}
		/* 2 */
		a = (a.sqr() + one) % *this;							// a = f(a) % n
		b = (((b.sqr() + one) % *this).sqr() + one) % *this;	// b = f(f(b) % n) % n
		/* 3 */
		if (a == b) {
			final = false;
			return BM(1, 0);
		}
		/* 4 */
		d = (a - b).NOD(*this);	//d = NOD(n, a - b);
		std::cout << "d = NOD("; (a - b).OutputDEC(); std::cout << ',';
		this->OutputDEC(); std::cout << ')' << "  =  "; d.OutputDEC();
		std::cout << '\n';
	} while (d == one);
	final = true;
	return d;
}

// НОД(this, b) методом Евклида
BM BM::NOD(BM s) {
	if (this->is_zero())return BM(1, 0);
	BM a = *this;
	BM t(1, 0);
	while (!a.is_zero()) {
		a = a % s;
		if (a.is_zero())return s;
		t = a;
		a = s;
		s = t;
	}
	return s;
}




// Р1 метод Полларда поиска нетривиального делителя
/*	Вход: составное n
*	Выход: d - нетривиальный делитель, или отказ.
*	1. Выбрать границу гладкости B
*	2. выбрать случайное 2 <= a <= n-2, вычислить d=NOD(a,n);
*		Если d>1, выход, ответ d
*	3. Для всех простых q<B:
*		3.1 Вычислить e = [ln <2> n / ln <2> q] ~ [log <q> (n)] - можно к числителю добавить +1 и тогда алгоритм будет отрабатывать как нужно
*		3.2 Положить a = a^(q^e) mod n
*		3.3 Если a = 1 - Выход. отказ.
*			Иначе найти d = НОД(a-1, n)
*			Если d != 1 - выход. Ответ: d
*	4. Если d=1 - отказ.
*		Иначе ответ: d
*/
BM BM::P1_Pollard_method_factor(bool& final) {
	/* 1 */
	BM B(1, 0);					// граница гладкости
	BM one("1");
	BM two("2");
	BM t100("64");	// = 100 
	std::vector <BM> q_primals;

	B.set_random_less_than_M(t100-two);
	B = B + two;
	std::cout << "B:\t\t"; B.OutputDEC(); std::cout << '\n';
	//	=	=	=	=	=	
	//			ГЕНЕРАЦИЯ { qi } последовательности простых чисел до B методом
	//				"РЕШЕТО ЭРАТОСФЕНА"
	//	=	=	=	=	=	=	=	=	=	=	=	=	=
	int N = B.hexa[0];
	bool* isPrime = new bool[N];
	for (int i = 2; i * i < N; i++) {
		if (isPrime[i]) {
			for (int j = i * i; j < N; j += i) {
				isPrime[j] = false;
			}
		}
	}
	for (int i = 2; i < N; i++)if (isPrime[i])q_primals.emplace_back(i);

	BM d(1, 0);		// NOD
	/* 2 */
	BM a(1, 0);						// Выбрать случайное 2 <= a <= n-2
	a.set_random_less_than_M(*this - two);
	a = a + two;
	d = NOD(a);					// Вычислить НОД(a, n)
	if (d > one) { final = true; return d; }	// Если d > 1, то выход, Ответ: d
	/* 3 */
	
	for (BM i : q_primals) {
		std::cout << " trying: q = "; i.OutputDEC(); std::cout << '\n';
		/* 3.1 */ // e = log <q> n
		int e1 = size_of_base << 3;		// log <2> (q)
		int e2 = e1;					// log <2> (n)
		BASE mask = BASE(~BASE(BASE(~0) >> 1));	// 1000000...000
		while ((mask & i.hexa[i.hexa.size() - 1]) == 0) {
			e1--; mask >>= 1;
		}
		e1 = e1 + (size_of_base << 3) * (i.hexa.size() - 1);
		mask = BASE(~BASE(BASE(~0) >> 1));
		while ((mask & hexa[hexa.size() - 1]) == 0) {
			e2--;
			mask >>= 1;
		}
		e2 = e2 + (size_of_base << 3) * (hexa.size() - 1);

		int e = (e2 + 1) / e1;
		/* 3.2 */	//a = a^(q^e)
		BM qe = i.pow(e);
		a = a.pow_modula(qe, *this);
		/* 3.3 */	// если а=1 - отказ
		if (a == one) { final = false; return BM(1, 0); }
		else {
			d = NOD(a - one);		// D = NOD(n, a-1)
			if (d != one) { final = true; return d; }
		}
		/* 4 */
	}
	
	
	if (d == one) { final = false; return BM(1, 0); }
	else { final = true; return d; }
}




/*
	// Алгоритм Гельфонда поиска дискретного логарифма
		Вход: G = <g> – циклическая группа, | G | = n, а  G.
		Выход:  x = log <g> (a)
			1. Вычислить h = [√n] + 1
			2. Вычислить  b = g^h.
			3. Построить две таблицы:
				{b^u ,   u = 1, 2, …, h }  («шаги великана»)
				{a * g^v ,   v = 1, 2, …, h }  («шаги ребёнка»)
			4. Найти в таблицах одинаковые элементы   bu = a  gv
				и вычислить из этого равенства  x = hu – v .
			5. Ответ:  x .
 */
BM Discrete_log_Gendels_method(G Group, BM a) {
	// если N % g == 0, то значит N и g - не взаимно простые, и значит <g> - не группа
	if (Group.mod % Group.p == BM(1, 0)) {
		std::cout << "g = "; Group.p.OutputDEC();
		std::cout << "cannot produce <g>\n";
		return BM(1, 0);
	}
	/* 1 */
	BM hh = Group.size.integer_sqrt() + 1;
	BM one("1");
	/* 2 */
	BM b = Group.p.pow(hh);
	b = b % Group.mod;
	std::vector<BM> BU;
	int i1 = 0;
	/* 3 */
	for (BM i("1"); i <= hh; i = i + one) {
		BU.emplace_back(b.pow_modula(i, Group.mod));
		i1++;
	}
	std::cout << "---------\n";
	for (int i = 1; hh >= i; i++) {
		BM agv = (a * Group.p.pow_modula(i, Group.mod)) % Group.mod;
		for (int j = 0; j < BU.size(); j++) {
			/* 4 */
			if (agv == BU[j]) {
				BM result(1, 0);
				std::cout << "(u,v): " << i << ',' << j << '\n';
				std::cout << "\nX = hu - v = "; (result = ((hh * (j + 1) - (i)) % Group.mod)).OutputDEC();
				std::cout << '\n';
				return result;
			}
		}
	}	
}

// taskkill /F /IM ConsoleApplication1.exe

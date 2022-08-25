#include <iostream>
#include <conio.h>
#include "MatBasica.hpp"
#include "MatAuxiliar.hpp"


std::string Calcular(std::string num1, std::string num2, char op) {
	std::string resp;
	bool neg1 = num1.size() ? num1[0] == '-' : 0;
	bool neg2 = num2.size() ? num2[0] == '-' : 0;

	for (size_t i = 0; i < num1.size(); i++) {
		if (num1[i] != '0' && num1[i] != '-') break;
		i--;
		num1.erase(0, 1);
	}
	for (size_t i = 0; i < num2.size(); i++) {
		if (num2[i] != '0' && num2[i] != '-') break;
		i--;
		num2.erase(0, 1);
	}
	if (!num1.size()) num1 = "0";
	if (!num2.size()) num2 = "0";

	switch (op) {
	case '+':
		if (neg1 == neg2) {			
			resp = Soma(num1, num2);
			if (neg1) resp = '-' + resp;
		}
		else {
			resp = Subtracao(num1, num2);
			if (neg1) {
				if (resp[0] == '-') resp.erase(0, 1);
				else resp = '-' + resp;
			}
		}
		break;
	case '/':
		resp = Divisao(num1, num2);
		if (neg1 != neg2) resp = '-' + resp;
		break;
	case '*':
		resp = Multi(num1, num2);
		if (neg1 != neg2) resp = '-' + resp;
		break;
	case '^':
		resp = Potencia(num1, num2);
		break;
	case 'R':
		resp = Raiz(num2, num1);
		break;
	}
	if (!resp.size()) resp = "0";

	return resp;
}

std::string Verifica(std::string frase, char op1, char op2) {
	std::string resp = "0";
	std::string num1 = "";
	std::string num2 = "";
	bool number1 = 1;
	char val = 0;
	size_t ponto = 0;
	for (size_t j = 0; j < frase.size(); j++) {
		if ((frase[j] >= '0' && frase[j] <= '9') || (frase[j] == '-' && number1) || frase[j] == '.') {
			if (frase[j] == '-' && num1.size() && (op1 == '+' || op2 == '+')) {
				number1 = false;
				val = '+';
			}
			if (number1) num1 += frase[j];
			else num2 += frase[j];

			continue;
		}
		if ((frase[j] == op1 || frase[j] == op2) && number1) {
			number1 = false;
			val = frase[j];
		}
		else if (!number1) {
			number1 = 1;
			resp = Calcular(num1, num2, val);
			std::string aux = frase.substr(j, frase.size() - j);
			frase = frase.substr(0, ponto);
			frase += resp + aux;
			num1.clear();
			num2.clear();
			j = ponto - 1;
		}
		else {
			num1.clear(); ponto = j + 1;
		}
	}
	if (!number1) {
		number1 = 1;
		resp = Calcular(num1, num2, val);
		frase = frase.substr(0, ponto);
		frase += resp;
	}
	return frase;
}

std::string CalcularParenteses(std::string frase) {
	std::string p;
	int ponto = 0;
	bool parenteses = false;
	for (size_t i = 0; i < frase.size(); i++) {
		if (frase[i] != '(' && !parenteses) continue;
		if (frase[i] == '(' && !parenteses) {
			ponto = i++;
		}
		parenteses = !(frase[i] == ')');
		if (!parenteses) {
			std::string aux = CalcularParenteses(p);
			p.clear();
			std::string sub = frase.substr(i + 1, frase.size() - i - 1);
			std::string sub2 = frase.substr(0, ponto - 1);
			frase = sub2 + aux + sub;
		}
		else p += frase[i];
	}
	frase = Verifica(frase, '^', 'R');
	frase = Verifica(frase, '*', '/');
	frase = Verifica(frase, '+', 0);
	return frase;
}

int main() {
	std::string frase;
	std::string fraseCopia;
	std::string calc;
	int ponto = 0;
	frase.clear();
	while (1) {
		char c = _getch();
		if (c >= '0' && c <= '9') {
			frase += c;
		}
		switch (c) {
		case '+':
		case '-':
		case '(':
		case ')':
		case '/':
		case '*':
		case '.':
		case '^':
		case 'R':
			frase += c;
			break;
		case 8:
			if(frase.size() > 0)
				frase.pop_back();
			break;
		case 27:
			exit(0);
			break;
		}
		system("cls");
		std::cout << frase;
		//fraseCopia = frase;

		fraseCopia = CalcularParenteses(frase);
		//fraseCopia = Verifica(fraseCopia, '*', '/');
		//fraseCopia = Verifica(fraseCopia, '+', '-');

		std::cout << "\n" << fraseCopia;
	}
}
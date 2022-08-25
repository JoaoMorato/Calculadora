#ifndef _MAT_AUXILIAR_
#define _MAT_AUXILIAR_

#include <sstream>

size_t Disima(std::string num) {
	for (size_t i = 0; i < 10; i++) {
		if (i >= num.size()) break;
		char val = num[i];
		for (size_t j = i + 1; j < num.size(); j++) {
			if (val == num[j]) return j;
		}
	}
	return 0;
}


std::string ZeroEsquerda(std::string val) {
	if (!val.size()) return val;
	bool menos = val[0] == '-';
	while (val.size()) {
		if (val[0] != '0' && val[0] != '-') break;
		val.erase(0, 1);
	}
	if (!val.size()) val = "0";
	if (menos) val = '-' + val;
	return val;
}

std::string ZeroDireita(std::string val) {
	long long i = val.size() - 1;
	for (; i > 0; i--) {
		if (val[i] == '0') continue;
		val.erase(i, val.size() - i - 1);
		break;
	}
	if (i == -1) return "0";
	if (!i && val[0] == '-') return "-0";
	return val;
}

void Separa(std::string val, std::string* num, std::string* ponto) {
	if (!num && !ponto) return;
	if (num) *num = val;
	if (ponto) *ponto = "0";

	long long virgula = -1;
	for (size_t i = 0; i < val.size(); i++) {
		if (val[i] != '.') continue;
		virgula = i;
		break;
	}
	if (virgula == -1) {
		return;
	}

	if (num) {
		num->clear();
		if (!virgula) *num = "0";
		else *num = val.substr(0, virgula);
		if (val[0] == '-') *num = '-' + *num;
	}
	if (ponto) {
		ponto->clear();
		*ponto = val.substr(virgula + 1, val.size() - 1 - virgula);
		if (!ponto->size()) *ponto = "0";
	}


}

char CompNum(std::string num1, std::string num2) {
	bool num1Negativo = num1[0] == '-';
	bool num2Negativo = num2[0] == '-';

	if (num1Negativo != num2Negativo) return num1Negativo ? 2 : 1;

	num1 = ZeroEsquerda(num1);
	num2 = ZeroEsquerda(num2);
	char maior = 0;

	std::string aux1, aux2;
	std::string v1, v2;
	Separa(num1, &aux1, &v1);
	Separa(num2, &aux2, &v2);
	if (aux1.size() > aux2.size()) maior = 1;
	if (aux1.size() < aux2.size()) maior = 2;
	if (!maior) {
		for (size_t i = 0; i < aux1.size(); i++) {
			if (aux1[i] == aux2[i]) continue;
			maior = aux1[i] > aux2[i] ? 1 : 2;
			break;
		}
		if (!maior) {
			if (v1.size() > v2.size()) maior = 1;
			if (v1.size() < v2.size()) maior = 2;
			if (!maior) {
				for (size_t i = 0; i < v1.size(); i++) {
					if (v1[i] == v2[i]) continue;
					maior = v1[i] > v2[i] ? 1 : 2;
					break;
				}
			}
		}
	}

	if (num1Negativo && maior)
		maior = maior == 1 ? 2 : maior == 2 ? 1 : 0;
	return maior;
}

#endif // !_MAT_AUXILIAR_

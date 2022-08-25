#pragma once
#ifndef _MAT_BASICO_
#define _MAT_BASICO_

#include <sstream>
#include "MatAuxiliar.hpp"

std::string Divisao(std::string, std::string);

std::string Soma(std::string num1, std::string num2) {
	std::string val1 = "", val2 = "";
	std::string ponto1, ponto2;
	Separa(num1, &val1, &ponto1);
	Separa(num2, &val2, &ponto2);

	std::string resp;
	std::string aux = "";
	char falta = 0;
	size_t i = 0;
	while (1) {
		if (!(i < val1.size() && i < val2.size())) {
			char result;
			while (i < val1.size()) {
				result = val1[val1.size() - i - 1] + falta - '0';
				falta = result / 10;
				aux.insert(aux.begin(), (result % 10) + '0');
				i++;
			}
			while (i < val2.size()) {
				result = val2[val2.size() - i - 1] + falta - '0';
				falta = result / 10;
				aux.insert(aux.begin(), (result % 10) + '0');
				i++;
			}
			break;
		}
		char n1 = val1[val1.size() - i - 1] - '0';
		char n2 = val2[val2.size() - i - 1] - '0';
		char result = n1 + n2 + falta;
		aux.insert(aux.begin(), (result % 10) + '0');
		falta = result / 10;
		i++;
	}
	resp.clear();
	if (falta) aux.insert(aux.begin(), falta + '0');
	resp = aux;
	if (ponto1 != "0" || ponto2 != "0") {

		if (ponto1.size() > ponto2.size()) {
			aux = ponto1.substr(0, ponto2.size());
			aux = Soma(aux, ponto2);
			if (aux.size() > ponto2.size()) {
				aux.erase(0, 1);
				resp = Soma(resp, "1");
				aux += ponto1.substr(ponto2.size() - 1, ponto1.size() - ponto2.size());
			}
		}
		else {
			aux = ponto2.substr(0, ponto1.size());
			aux = Soma(aux, ponto1);
			if (aux.size() > ponto1.size()) {
				aux.erase(0, 1);
				resp = Soma(resp, "1");
				aux += ponto2.substr(ponto1.size() - 1, ponto2.size() - ponto1.size());
			}
		}
		for (long long i = aux.size() - 1; i >= 0; i--) {
			if (aux[i] != '0') break;
			aux.pop_back();
		}
		if (aux.size())
			resp += '.' + aux;

	}


	return resp;
}

std::string Subtracao(std::string num1, std::string num2) {
	bool menor = 0;
	std::string ponto1, ponto2;

	Separa(num1, &num1, &ponto1);
	Separa(num2, &num2, &ponto2);

	char resp = CompNum(num1, num2);
	if (!resp) return "0";

	std::string numMaior = num1;
	std::string numMenor = num2;

	if (resp == 2) {
		numMaior = num2;
		numMenor = num1;
	}

	std::string aux = "";
	long long i = numMaior.size() - 1;
	long long j = numMenor.size() - 1;

	while (1) {

		if (j < 0) {
			while (i >= 0) {
				//aux = numMaior[i--] + aux;
				aux.insert(aux.begin(), numMaior[i--]);
			}
			break;
		}
		char n1 = numMaior[i] - '0';
		char n2 = numMenor[j] - '0';
		if (n1 < n2) {
			int cont = 1;
			while (numMaior[i - cont] == '0') {
				numMaior[i - cont] = '9';
				cont++;
			}
			numMaior[i - cont] -= 1;
			n1 += 10;
		}
		char result = n1 - n2;
		aux = char(result + '0') + aux;
		i--;
		j--;
	}

	aux = ZeroEsquerda(aux);

	if ((ponto1 != "0" || ponto2 != "0") && CompNum(ponto1, ponto2)) {
		size_t maior = 0;
		bool aplica = 0;

		if (CompNum(ponto1, ponto2) == 1) {
			maior = ponto1.size();
			size_t i = ponto1.size() - ponto2.size();
			ponto2.insert(ponto2.end(), i, '0');
		}
		else {
			maior = ponto2.size();
			size_t i = ponto2.size() - ponto1.size();
			ponto1.insert(ponto1.end(), i, '0');
		}
		std::string ponto = Subtracao(ponto1, ponto2);

		if (ponto[0] == '-') {
			ponto.erase(0, 1);

			aplica = resp == 1;
		}
		else aplica = resp == 2;

		if (aplica) {
			aux = Subtracao(aux, "1");
			if (aux[0] == '-') aux.erase(0, 1);
			std::string diff = "10";
			diff.insert(diff.end(), maior - 1, '0');
			ponto = Subtracao(diff, ponto);

			if (ponto[0] == '-') ponto.erase(0, 1);
		}

		if (ponto.size() < maior) {
			ponto.insert(ponto.begin(), maior - ponto.size(), '0');
		}

		ponto = ZeroDireita(ponto);
		aux += '.' + ponto;
	}
	if (resp == 2) aux = '-' + aux;
	if (!aux.size()) aux = "0";
	return aux;
}

std::string Multi(std::string num1, std::string num2) {
	std::string resp = "0";
	if (!num2.size() || num2 == "0") return "0";
	if (!num1.size() || num1 == "0") return "0";

	std::string m1, ponto;
	Separa(num2, &m1, &ponto);
	size_t count = 0;

	while (m1.size()) {
		std::string aux = "";
		aux += m1[m1.size() - 1];
		m1.erase(m1.size() - 1, 1);
		std::string cont = "0";
		while (CompNum(aux, "0") == 1) {
			cont = Soma(cont, num1);
			aux = Subtracao(aux, "1");
		}
		cont.insert(cont.end(), count, '0');
		resp = Soma(cont, resp);
		count++;
	}

	std::string resp2 = "0";
	size_t quant = ponto.size();
	int a = CompNum(ponto, "0");
	while (a == 1) {
		resp2 = Multi(num1, ponto);
	}

	if (CompNum(resp2, "0") == 1) {
		std::string div = "1";
		div.insert(div.end(), quant, '0');
		resp2 = Divisao(resp2, div);
		resp = Soma(resp, resp2);
	}
	return resp;
}

std::string Divisao(std::string num1, std::string num2) {
	if (!num2.size() || num2 == "0") return num1;
	if (!num1.size()) return "0";
	std::string aux = "";
	std::string resp = "0";
	std::string ponto;
	Separa(num1, &aux, &ponto);
	while (CompNum(aux, num2) != 2) {
		aux = Subtracao(aux, num2);
		resp = Soma(resp, "1");
	}
	if (aux == "0" && ponto == "0") return resp;
	resp += '.';
	std::string resp2 = "";
	aux += ponto[0];
	ponto.erase(0, 1);
	std::string rPonto = "0";
	while (aux != "0") {
		rPonto = "0";
		while (CompNum(aux, num2) != 2) {
			aux = Subtracao(aux, num2);
			rPonto = Soma(rPonto, "1");
		}
		//size_t posi = Disima(resp2);
		if (resp2.size() > 20) {
			resp2.pop_back();
			break;
		}
		if (ponto.size()) {
			aux += ponto[0];
			ponto.erase(0, 1);
		}
		else aux = Multi(aux, "10");
		resp2 += rPonto;
	}
	return resp + resp2;
}

std::string Potencia(std::string num1, std::string quant) {
	std::string resp = "1";
	bool menor = 0;
	if (quant[0] == '-') {
		menor = 1;
		quant.erase(0, 1);
	}
	while (CompNum(quant, "0") == 1) {
		quant = Subtracao(quant, "1");
		resp = Multi(resp, num1);
	}
	if (menor) {
		resp = Divisao("1", resp);
	}
	return resp;
}

std::string Raiz(std::string radicando, std::string indice) {
	if (!indice.size() || indice == "0" || indice == "1") indice = "2";
	if (!radicando.size() || radicando == "0") return "0";
	if (radicando == "1") return "1";

	std::string resp = "0";
	std::string div = "1";
	std::string ponto = "";

	Separa(radicando, NULL, &ponto);
	if (ponto != "0") {
		div.insert(div.end(), ponto.size(), '0');
		radicando.erase(radicando.size() - 1 - ponto.size(), 1);
	}

	std::string val;
	std::string pot = "1";
	pot.insert(pot.end(), radicando.size() / 2, '0');

	int divisoes = 0;
	char virgula = 0;
	while (1) {
		char result = CompNum(Potencia(resp, indice), radicando);

		if (!result) return resp;
		else if (result == 1) {
			resp = Subtracao(resp, pot);
			pot = Divisao(pot, "10");
			printf("\nD: %s", pot.c_str());
			divisoes = virgula ? divisoes++ : divisoes;
			if (divisoes > 3) return resp;
			if (CompNum(pot, "1") == 2 && !virgula) virgula = 1;
			resp = Soma(resp, pot);
			continue;
		}
		resp = Soma(resp, pot);
	}
	return resp;
}

#endif // !_MAT_BASICO_

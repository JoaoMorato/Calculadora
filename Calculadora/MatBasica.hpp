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

	std::string resp = "";
	std::string aux = "";
	char sobe = 0;

	if (ponto1.size() > ponto2.size())
		ponto2.insert(ponto2.end(), ponto1.size() - ponto2.size(), '0');
	else if (ponto1.size() < ponto2.size())
		ponto1.insert(ponto1.end(), ponto2.size() - ponto1.size(), '0');

	for (size_t i = 1;; i++) {
		if (ponto1.size() < i) break;

		char sum = ponto1[ponto1.size() - i] + ponto2[ponto2.size() - i] - '0';

		if (sobe) sum++;
		sobe = 0;
		if (sum > '9') {
			sobe = 1;
			sum -= 10;
		}
		aux = sum + aux;
	}


	for (size_t i = 1;; i++) {
		
		if (val1.size() < i) {
			for (size_t j = i;j <= val2.size(); j++) {
				resp.insert(resp.begin(), (char)(val2[val2.size() - j] + sobe));
				sobe = 0;
			}
			break;
		}
		else if (val2.size() < i) {
			for (size_t j = i;j <= val1.size(); j++) {
				resp.insert(resp.begin(), (char)(val1[val1.size() - j] + sobe));
				sobe = 0;
			}
			break;
		}

		
		char sum = (char)val1[val1.size() - i] + (char)val2[val2.size() - i] - '0';

		if (sobe) sum++;
		sobe = 0;
		if (sum > '9') {
			sobe = 1;
			sum -= 10;
		}
		resp = sum + resp;
	}

	if (sobe) resp = '1' + resp;

	if(aux != "0")
		resp += '.' + aux;
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

	if (!num2.size() || num2 == "0") return "0";
	if (!num1.size() || num1 == "0") return "0";

	std::string resp = "0";
	std::string m1, ponto;
	Separa(num2, &m1, &ponto);
	size_t count = 0;

	while (CompNum(m1, "0")) {
		m1 = Subtracao(m1, "1");
		resp = Soma(resp, num1);
	}

	std::string resp2 = "0";
	size_t quant = ponto.size();

	if (CompNum(ponto, "0") == 1) {
		ponto = ZeroDireita(ponto);
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

	while (CompNum(aux, "0")) {
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
		else aux += '0';
		resp2 += rPonto;
	}
	return resp + resp2;
}

std::string Mod(std::string num1, std::string mod) {
	char menor = CompNum(mod, "0");
	if (!menor|| CompNum(num1, "0")) return "0";
	if (menor == 2) menor = 1;
	std::string resto = "0";
	while (CompNum(resto, num1) == 2) {
		resto = Soma(resto, mod);
	}

	if (!CompNum(resto, num1)) {
		if (menor) resto.insert(resto.begin(), '-');
		return resto;
	}

	resto = Subtracao(resto, mod);
	resto = Subtracao(num1, resto);
	if(menor) resto.insert(resto.begin(), '-');
	return resto;
}

std::string Potencia(std::string num1, std::string quant) {
	std::string resp = "1";
	bool menor = 0;
	std::string par = Mod(quant, "2");
	if (quant[0] == '-') {
		menor = par != "0" ? 1 : 0;
		quant.erase(0, 1);
	}
	while (CompNum(quant, "0") == 1) {
		quant = Subtracao(quant, "1");
		resp = Multi(resp, num1);
	}
	if (menor) {
		resp.insert(resp.begin(), '-');
	}
	return resp;
}

std::string Raiz(std::string radicando, std::string indice) {
	if (!indice.size() || indice == "0" || indice == "1") indice = "2";
	if (!radicando.size() || radicando == "0") return "0";
	if (radicando == "1") return "1";

	std::string rad;
	Separa(radicando, &rad, NULL);
	
	std::string pot = "1";
	pot.insert(pot.end(), rad.length() / 2, '0');
	std::string aux;
	std::string resp = "0";
	int div = 0;
	while (1) {
		resp = Soma(resp, pot);
		aux = Potencia(resp, indice);
		int result = CompNum(aux, radicando);
		if (!result) return resp;
		else if (result == 1) {
			div++;
			resp = Subtracao(resp, pot);
			pot = Divisao(pot, "10");
			if (div == 7) return resp;
			continue;
		}
	}
}

#endif // !_MAT_BASICO_

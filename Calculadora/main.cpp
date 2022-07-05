#include <iostream>
#include <conio.h>

//Prototipo
std::string Divisao(std::string, std::string);
///

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

size_t Disima(std::string num) {
	for (size_t i = 0; i < 10; i++) {
		if (i >= num.size()) break;
		char val = num[i];
		for (size_t j = i+1; j < num.size(); j++) {
			if (val == num[j]) return j;
		}
	}
	return 0;
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
	
	num->clear();
	ponto->clear();
	if (num) {
		if (!virgula) *num = "0";
		else *num = val.substr(0, virgula);
		if (val[0] == '-') *num = '-' + *num;
	}
	if (ponto) {
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
		if(aux.size())
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

	size_t quant = (radicando.size() / 2);
	pot.insert(pot.end(), quant, '0');

	int divisoes = 0;
	while (1) {
		val = Potencia(resp, indice);
		char result = CompNum(val, radicando);
		
		if (!result) return resp;
		else if (result == 1) {
			resp = Subtracao(resp, pot);
			pot = Divisao(pot, "10");
			//if (divisoes > 7) break;
		}
		resp = Soma(resp, pot);
	}
	return resp;
}

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
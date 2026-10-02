/******************************* Arquivo agenda.cpp ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) a)*******/

#include "agenda.h"

Agenda::Agenda (int t) {
	tamMaxAgenda = t;
	tamMaxNome = 10;
	nomeArquivo = "arquivocontatos.txt";

	lerArquivo ();
}

void Agenda::insereContato (string n, string p, int i) {
	static int contaTentativas = 1;

	if (v.size() < tamMaxAgenda) {
		if (existeContato (n)) {
			cout << "[CONTATO EXISTENTE] " << contaTentativas
				<< "a tentativa de insercao (" << n
				<< ") NAO foi bem sucedida...\n" << endl;
		} else {
			Contato contato (verificaNome (n), p, i);
			
			v.push_back (contato);
			
			cout << "[CONTATO INSERIDO] " << contaTentativas
				<< "a tentativa de insercao (" << n
				<< ") foi bem sucedida...\n" << endl;
		}
	
	} else {
		cout << "[AGENDA CHEIA] " << contaTentativas
			<< "a tentativa de insercao (" << n
			<< ") NAO foi bem sucedida...\n" << endl;
	}
	
	contaTentativas++;
}

void Agenda::removeContato (string n) {
	for (unsigned i = 0; i < v.size(); i++) {
		/* Usa o nome como critério de busca e,
		em seguida usa o método da classe vector
		para remover o contato */

		if (!v.at(i).getNome ().compare(n.substr (0, tamMaxNome))) {
		v.erase (v.begin() + i);
		cout << "[CONTATO REMOVIDO] " << n << " removido!" << endl;
		}
	}
}

bool Agenda::existeContato (string n) {
	for (unsigned i = 0; i < v.size(); i++) {

		/* Usa o nome como critério de busca e,
		em seguida usa o método da classe vector
		para verificar se o contato existe */

		if (!v.at(i).getNome ().compare(n.substr (0, tamMaxNome)))
			return true;

	}
	return false;
}

void Agenda::editaIdadeContato (string n, int i_nova) {
	for (unsigned i = 0; i < v.size(); i++) {

		/* Usa o nome como critério de busca e,
		em seguida usa o método da classe vector
		para editar o contato */

		if (!v.at(i).getNome ().compare(n.substr (0, tamMaxNome))) {
			v.at (i).setIdade (i_nova);
			cout << "[CONTATO EDITADO] idade do contato " << n << " editado!" << endl;
		}
	}
}

void Agenda::editaProfissaoContato (string n, string p_nova) {
	for (unsigned i = 0; i < v.size(); i++) {
	
		/* Usa o nome como critério de busca e,
		em seguida usa o método da classe vector
		para editar o contato */

		if (!v.at(i).getNome ().compare(n.substr (0, tamMaxNome))) {
			v.at (i).setProfissao (p_nova);
			cout << "[CONTATO EDITADO] profissao do contato "
			<< n << " editado!" << endl;
		}
	}
}

void Agenda::mostraTodos () {
	cout << endl;
	cout << left << setw(15) << "Nome:"
		<< setw(15) << "Profissao:"
		<< setw(5) << "Idade:" << endl;

	for (unsigned i = 0; i < v.size(); i++)
		cout << setw(15) << v.at(i).getNome ()
			<< setw(15) << v.at(i).getProfissao ()
			<< setw(5) << v.at(i).getIdade () << endl;
	
	cout << endl;
}

string Agenda::verificaNome (string n) {
	if (n.length() > tamMaxNome) {
		cout << "[CUIDADO] Nome muito comprido!" << endl;
		cout << "Nome truncado a partir do " << tamMaxNome
			<< "o caracter \"" << n [tamMaxNome]
				<< "\": " << n.substr(0, tamMaxNome) << endl;
	}

	return n.substr(0, tamMaxNome);
}

void Agenda::lerArquivo () {
	string n, p;
	int i;

	file.open(nomeArquivo, fstream::in);

	if (!file.is_open()) {
		cout << "Arquivo nao existe." << endl;
		return;
	}

	while (file.good()) {
		file >> n >> p >> i;
		insereContato (n, p, i);
	}

	file.close();
}

void Agenda::escreveArquivo () {
	file.open(nomeArquivo, fstream::out);

	for (unsigned i = 0; i < v.size(); i++)
		file << v.at(i).getNome ()
			<< " " << v.at(i).getProfissao ()
			<< " " << v.at(i).getIdade () << endl;
	
	file.close();
}

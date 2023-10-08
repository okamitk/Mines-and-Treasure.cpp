//PROJETO LABORAT�RIO DE PROGRAMA�� I
// *VETOR EST�TICO/DIN�MICO
// *MATRIZ/MATRIZ DIN�MICA
// *STRUCT
// *CONDICIONAL/LA�OS/FUN��ES


#include <iostream>
using namespace std;
#include<stdlib.h>

struct infor {
	string palavra;
	int erros;
	string respf;
};

void desenho(int erros, string boneco[6][5]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			boneco[i][j] = ' ';
		}
	}
	boneco[0][0] = '-', boneco[1][0] = '|', boneco[2][0] = '|', boneco[3][0] = '|';
	boneco[4][0] = '|', boneco[5][0] = '|', boneco[0][1] = '-', boneco[0][2] = '-';
	boneco[0][3] = '-', boneco[1][3] = '|';

	if (erros == 1) {
		boneco[2][3] = 'O';
	}
	else if (erros == 2) {
		boneco[2][3] = 'O', boneco[3][3] = '|', boneco[4][3] = '|';
	}
	else if (erros == 3) {
		boneco[2][3] = 'O', boneco[3][3] = '|', boneco[4][3] = '|', boneco[3][2] = '/';
	}
	else if (erros == 4) {
		boneco[2][3] = 'O', boneco[3][3] = '|', boneco[4][3] = '|', boneco[3][2] = '/', boneco[3][4] = '\\';
	}
	else if (erros == 5) {
		boneco[2][3] = 'O', boneco[3][3] = '|', boneco[4][3] = '|', boneco[3][2] = '/', boneco[3][4] = '\\';
		boneco[5][2] = '/';
	}
	else if (erros == 6) {
		boneco[2][3] = 'O', boneco[3][3] = '|', boneco[4][3] = '|', boneco[3][2] = '/', boneco[3][4] = '\\';
		boneco[5][2] = '/', boneco[5][4] = '\\';
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5; j++) {
			cout << boneco[i][j];
		}
		cout << endl;
	}
}

void quant_letras(string* vetquantp, int* quantletras, int quantp) {
	for (int i = 0; i < quantp; i++) {
		cout << "Digite a " << i + 1 << " palavra: ";
		cin >> vetquantp[i];
		quantletras[i] = vetquantp[i].length();
	}
}

void imprimir_tela(char* vetortela, int tamvt, int erros, string boneco[6][5]) {
	desenho(erros, boneco);
	cout << endl;
	for (int i = 0; i < tamvt; i++) {
		cout << vetortela[i];
	}
}

void verif_letra(string palavra, int tam, char respchr, char* vetortela, int& erros, int& parada) {
	int tem = 0;
	for (int i = 0; i < tam; i++) {
		if (palavra[i] == respchr) {
			vetortela[i] = respchr;
			tem += 1;
			parada += 1;
		}
	}
	if (tem == 0) {
		erros += 1;
	}
}

void preencher_matd(infor** matd, int quantp) {
	for (int i = 0; i < quantp; i++) {
		matd[i] = new infor[2];
	}
}

void valores_matd(infor** matd, string palavra, int erros, int h, int z) {
	matd[z][h].palavra = palavra;
	matd[z][h].erros = erros;
	if (erros == 6) {
		matd[z][h].respf = "ERROU";
	}
	else {
		matd[z][h].respf = "ACERTOU";
	}
}

void imprimir_matd(infor** matd, int quantp) {
	cout << "---------\n";
	cout << "JOGADOR 1!\n\n";
	for (int i = 0; i < quantp; i++) {
		cout << "Palavra:" << matd[i][0].palavra << "   " << "ERROS:" << matd[i][0].erros << "   " << "RESPOSTA:" << matd[i][0].respf << endl << endl;
	}
	cout << "---------\n";
	cout << "JOGADOR 2!\n\n";
	for (int i = 0; i < quantp; i++) {
		cout << "PALAVRA:" << matd[i][1].palavra << "   " << "ERROS:" << matd[i][1].erros << "   " << "RESPOSTA:" << matd[i][1].respf << endl << endl;
	}
	string vet[3];
	vet[0] = "FIM", vet[1] = "DE", vet[2] = "JOGO";
	cout << "------------------\n";
	cout << "  " << vet[0] << " " << vet[1] << " " << vet[2] << "!\n";
	cout << "------------------\n\n";
}

int main() {
	int erros = 0;
	int parada = 0;
	int quantp;
	cout << "JOGO DA FORCA!\n";
	cout << endl << "Digite a quantidade de palavras para a brincadeira: ";
	cin >> quantp;
	string boneco[6][5];
	infor** matd = new infor * [quantp];
	string* vetquantp = new string[quantp];
	int* quantletras = new int[quantp];
	quant_letras(vetquantp, quantletras, quantp);
	system("clear");
	preencher_matd(matd, quantp);
	for (int h = 0; h < 2; h++) {
		cout << "---------------\n";
		cout << "  JOGADOR " << h + 1 << "!\n";
		cout << "---------------\n";
		system("pause");
		system("clear");
		for (int z = 0; z < quantp; z++) {
			char* vetortela = new char[quantletras[z]];
			int tamvt = quantletras[z];
			for (int j = 0; j < quantletras[z]; j++) {
				vetortela[j] = '_';
			}
			char respchr;
			while ((erros < 6) && (parada < quantletras[z])) {
				imprimir_tela(vetortela, tamvt, erros, boneco);
				cout << endl << endl << "Digite uma letra: ";
				cin >> respchr;
				verif_letra(vetquantp[z], quantletras[z], respchr, vetortela, erros, parada);
				system("clear");
			}
			imprimir_tela(vetortela, tamvt, erros, boneco);
			cout << endl << endl;
			system("pause");
			system("clear");
			valores_matd(matd, vetquantp[z], erros, h, z);
			erros = 0;
			parada = 0;
			delete[]vetortela;

		}
	}
	imprimir_matd(matd, quantp);




	return 0;
}
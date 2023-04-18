#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <iomanip>
#include <Windows.h>

using namespace std;


/**********************************
* Nome: Matheus Rodrigues Salomão *
* RA: 1840482212016               *
***********************************/


/*
Corresponde a matriz que será exibida pelo progrma
0 = vazio
minusculo = branca
maiusculo = preta
*/
char tab[8][8]={    {'t','c','b','a','e','b','c','t'},
					{'p','p','p','p','p','p','p','p'},
					{'0','0','0','0','0','0','0','0'},
					{'0','0','0','0','0','0','0','0'},
					{'0','0','0','0','0','0','0','0'},
					{'0','0','0','0','0','0','0','0'},
					{'P','P','P','P','P','P','P','P'},
					{'T','C','B','A','E','B','C','T'}};

/*
Corresponde a matriz dos movimentos, quando selecionada uma peca essa matriz
sera manipulada para determinar os possiveis movimentos que ela podera realizar
0 = nao pode mover
1 = pode mover
2 = peca que esta sendo movida
3 = pecas que pode comer
*/
int PosMove[8][8];

unsigned char GetColorCode ( unsigned char colorBackground,
                             unsigned char colorForeground );
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int vez=1, n, m;
char l;

void tabuleiro();
void converte();

void peao(char cor, int x, int y);
void rei(char cor, int x, int y);
void torre(char cor, int x, int y);
void cavalo(char cor, int x, int y);
void bispo(char cor, int x, int y);
void rainha(char cor, int x, int y);

void marcaComi(char cor, int x, int y);
void fazMovimento(int x, int y);
void limpaPosMove();
void verificaConflito(char cor, int x, int y, int tipo);
void limpaConflito(int x, int y, int i, int j, int modif);

/*
para encerrar o loop manualmente deve-se escrever "0S" ou "0s"
*/
int main(void){
	int continua=1, reiB=0, reiP=0;

	do{
		reiB = reiP = 0;
		for(int i=0; i<=7; i++)
			for(int j=0; j<=7; j++){
				if( tab[i][j] == 'e' )
					reiB++;
				if( tab[i][j] == 'E' )
					reiP++;
			}
		if( !reiB ){
			system("cls");
			cout << "Rei Preto Ganhou!!!" << endl;
			system("PAUSE");
			break;
		}
		if( !reiP ){
			system("cls");
			cout << "Rei Branco Ganhou!!!" << endl;
			system("PAUSE");
			break;
		}

		system("cls");
		if(vez == 1){
			SetConsoleTextAttribute( hConsole, 0xF0);
			cout << "--Vez do Branco--" << endl;
		}else{
			SetConsoleTextAttribute( hConsole, 0x0F);
			cout << "--Vez do Preto---" << endl;
		}
		tabuleiro();
        cout << "Entre com a peca que deseja mover(Numero Letra): ";
        
		cin >> n >> l;
		if( n == 0 && (l == 's' || l == 'S') ){
			continua = 0;
			break;
		}
		converte();
		if( (isupper(tab[m][n-1]) && vez == 1) || (islower(tab[m][n-1]) && vez == 0) ){
			cout << endl << "Cor errada, escolha novamente" << endl;
			system("PAUSE");
			continue;
		}else{
			if( vez )
				switch( tab[m][n-1] ){
					case 'p':
						peao('B',m,n-1);
						break;
					case 'e':
						rei('B',m,n-1);
						break;
					case 't':
						torre('B',m,n-1);
						break;
					case 'c':
						cavalo('B',m,n-1);
						break;
					case 'b':
						bispo('B',m,n-1);
					case 'a':
						rainha('B',m,n-1);
						break;
					default:
						cout << "Casa vazia, escolha novamente" << endl;
						system("PAUSE");
						system("cls");
						vez = !vez;
						break;
				}
			else
				switch( tab[m][n-1] ){
					case 'P':
						peao('P',m,n-1);
						break;
					case 'E':
						rei('P',m,n-1);
						break;
					case 'T':
						torre('P',m,n-1);
						break;
					case 'C':
						cavalo('P',m,n-1);
						break;
					case 'B':
						bispo('P',m,n-1);
						break;
					case 'A':
						rainha('P',m,n-1);
						break;
					default:
						cout << "Casa vazia, escolha novamente" << endl;
						system("PAUSE");
						system("cls");
						vez = !vez;
						break;
				}
		}
		vez = !vez;
	}while(continua);
	return 0;
}

void tabuleiro(){
	SetConsoleTextAttribute( hConsole, 0x0F);
	cout << "  1 2 3 4 5 6 7 8";
	
	for(int i=0; i<8; i++){
		printf("\n%c", i+65);
		for(int j=0; j<8; j++){
			switch( PosMove[i][j] ){
				case 0:
					if((j+i)%2)
						if(tab[i][j] == '0'){
							SetConsoleTextAttribute( hConsole, 0x77);
							cout << "  ";
						}else{
							if(isupper(tab[i][j]))
								SetConsoleTextAttribute( hConsole, 0x70);
							else
								SetConsoleTextAttribute( hConsole, 0x7F);
							cout << tab[i][j] << " ";
						}
					else
						if(tab[i][j] == '0'){
							SetConsoleTextAttribute( hConsole, 0x88);
							cout << "  ";
						}else{
							if(isupper(tab[i][j]))
								SetConsoleTextAttribute( hConsole, 0x80);
							else
								SetConsoleTextAttribute( hConsole, 0x8F);
							cout << tab[i][j] << " ";
						}
					break;
				case 1:
					SetConsoleTextAttribute( hConsole, 0x10);
					cout << "  ";
					break;
				case 2:
					SetConsoleTextAttribute( hConsole, 0xE0);
					cout << tab[i][j] << " ";
					break;
				case 3:
					SetConsoleTextAttribute( hConsole, 0x40);
					cout << tab[i][j] << " ";
					break;
			}
		}
		SetConsoleTextAttribute( hConsole, 0x0F);
    }
	
	cout << endl;
}

void peao(char cor, int x, int y){
	switch(cor){
		case 'B':
			if( isupper(tab[x+1][y+1]) )
				PosMove[x+1][y+1] = 3;
			if( isupper(tab[x+1][y-1]) )
				PosMove[x+1][y-1] = 3;

			PosMove[x+1][y] = 1;
			if(	x == 1 )
				PosMove[x+2][y] = 1;
			break;
		case 'P':
			if( islower(tab[x-1][y-1]) )
				PosMove[x-1][y-1] = 3;
			if( islower(tab[x-1][y+1]) )
				PosMove[x-1][y+1] = 3;

			PosMove[x-1][y] = 1;
			if(	x == 6 )
				PosMove[x-2][y] = 1;
			break;
	}

	PosMove[x][y] = 2;

	verificaConflito('P', x, y,1);
	verificaConflito('B', x, y,1);

	system("cls");
	tabuleiro();
	
	fazMovimento(x,y);

	char mudaPeao;
	if( m == 7 ){
		cout << "Entre com a peca desejada (em minusculo): ";
		cin >> mudaPeao;
		switch(mudaPeao){
			case 'a':
				tab[m][n-1] = 'a';
				break;
			case 't':
				tab[m][n-1] = 't';
				break;
			case 'c':
				tab[m][n-1] = 'c';
				break;
			case 'b':
				tab[m][n-1] = 'b';
				break;
		}
	}
	if( m == 0 ){
		cout << "Entre com a peca desejada (em maiusculo): ";
		cin >> mudaPeao;
		switch(mudaPeao){
			case 'A':
				tab[m][n-1] = 'A';
				break;
			case 'T':
				tab[m][n-1] = 'T';
				break;
			case 'C':
				tab[m][n-1] = 'C';
				break;
			case 'B':
				tab[m][n-1] = 'B';
				break;
		}
	}

	limpaPosMove();
}

void rei(char cor, int x, int y){
	for(int i=x-1; i<=x+1; i++){
		for(int j=y-1; j<=y+1; j++){
			if( i<=7 && i>=0 && j<=7 && j>=0 ){
				PosMove[i][j] = 1;
				if( cor == 'P' && islower(tab[i][j]) )
					PosMove[i][j] = 3;
				if( cor == 'B' && isupper(tab[i][j]) )
					PosMove[i][j] = 3;
			}
		}
	}
	PosMove[x][y] = 2;

	verificaConflito(cor, x, y,1);
	
	system("cls");
	tabuleiro();
	
	fazMovimento(x, y);
	
	limpaPosMove();
}

void torre(char cor, int x, int y){
	for(int i=x, j=0; j<=7; j++)
		PosMove[i][j] = 1;
	for(int i=0, j=y; i<=7; i++)
		PosMove[i][j] = 1;

	verificaConflito(cor, x, y,1);

	marcaComi(cor,x,y);

	verificaConflito(cor, x, y,1);
	
	system("cls");
	tabuleiro();
	
	fazMovimento(x, y);
	
	limpaPosMove();
}

void cavalo(char cor, int x, int y){
	int mov[8][2] = {{-1,-2},{1,-2},{2,1},{2,-1},{-1,2},{1,2},{-2,-1},{-2,1}};
	for(int i=0; i<=7; i++)
		if( (x+mov[i][0])<=7 && (x+mov[i][0])>=0 && (y+mov[i][1])<=7 && (y+mov[i][1])>=0 )
			PosMove[(x+mov[i][0])][(y+mov[i][1])] = 1;

	for(int i=0; i<=7; i++){
		for(int j=0; j<=7; j++){
			if( PosMove[i][j] == 1 ){
				if( cor == 'P' ){
					if( islower(tab[i][j]) )
						PosMove[i][j] = 3;
					else if( tab[i][j] != '0' )
						PosMove[i][j] = 0;
				}
				if( cor == 'B' ){
					if( isupper(tab[i][j]) )
						PosMove[i][j] = 3;
					else if( tab[i][j] != '0' )
						PosMove[i][j] = 0;
				}
			}
		}
	}
	PosMove[x][y] = 2;
	
	system("cls");
	tabuleiro();
	
	fazMovimento(x, y);
	
	limpaPosMove();
}

void bispo(char cor, int x, int y){	
	for( int i=x-1, j=y-1; i>=0 && j>=0; i--, j-- )
		PosMove[i][j] = 1;

	for( int i=x+1, j=y+1; i<=7 && j<=7; i++, j++ )
		PosMove[i][j] = 1;

	for( int i=x-1, j=y+1; i>=0 && j<=7; i--, j++ )
		PosMove[i][j] = 1;

	for( int i=x+1, j=y-1; i<=7 && j>=0; i++, j-- )
		PosMove[i][j] = 1;

	verificaConflito(cor, x, y,1);

	marcaComi(cor,x,y);

	verificaConflito(cor, x, y,2);

	system("cls");
	tabuleiro();
	
	fazMovimento(x, y);
	
	limpaPosMove();
}

void rainha(char cor, int x, int y){
	for(int i=x, j=0; j<=7; j++)
		PosMove[i][j] = 1;
	for(int i=0, j=y; i<=7; i++)
		PosMove[i][j] = 1;
	
	for( int i=x-1, j=y-1; i>=0 && j>=0; i--, j-- )
		PosMove[i][j] = 1;
	for( int i=x+1, j=y+1; i<=7 && j<=7; i++, j++ )
		PosMove[i][j] = 1;

	for( int i=x-1, j=y+1; i>=0 && j<=7; i--, j++ )
		PosMove[i][j] = 1;
	for( int i=x+1, j=y-1; i<=7 && j>=0; i++, j--)
		PosMove[i][j] = 1;
	
	verificaConflito(cor, x, y,1);

	marcaComi(cor,x,y);

	verificaConflito(cor, x, y,2);

	system("cls");
	tabuleiro();

	fazMovimento(x, y);
	
	limpaPosMove();
}


/*
Ira verificar se ha alguma peca no meio do caminho do possivel movimento ou apos uma peca
que pode comer e ira tirar o todo movimento da linha em relacao a peca que vai ser movida 
ou que pode ser comida
*/
void verificaConflito(char cor, int x, int y, int tipo){
	switch (tipo){
	case 1:
		int defineCor;
		for(int i=0; i<=7; i++)
			for(int j=0; j<=7; j++){
				switch(cor){
					case 'P':
						defineCor = isupper(tab[i][j]);
						break;
					case 'B':
						defineCor = islower(tab[i][j]);
						break;
				}
				if( defineCor && PosMove[i][j] == 1 )
					limpaConflito(x,y,i,j,0);
			}
		break;
	case 2:
		for(int i=0; i<=7; i++)
			for(int j=0; j<=7; j++){
				if( PosMove[i][j] == 3 )
					limpaConflito(x,y,i,j,1);
			}
		break;
	}
}

void limpaConflito(int x, int y, int i, int j, int modif){
	if( y == j ){
		if( x > i )
			for( int k=i-modif; k>=0; k-- )
				PosMove[k][j] = 0;
		if( x < i )
			for( int k=i+modif; k<=7; k++ )
				PosMove[k][j] = 0;
	}
	if( x == i ){
		if( y < j )
			for( int k=j+modif; k<=7; k++ )
				PosMove[i][k] = 0;
		if( y > j )
			for( int k=j-modif; k>=0; k-- )
				PosMove[i][k] = 0;
	}

	if( y < j && x > i )
		for( int k=i-modif, l=j+modif; k>=0 && l<=7; k--, l++ )
			PosMove[k][l] = 0;

	if( y > j && x > i )
		for( int k=i-modif, l=j-modif; k>=0 && l>=0; k--, l-- )
			PosMove[k][l] = 0;

	if( y > j && x < i )
		for( int k=i+modif, l=j-modif; k<=7 && l>=0; k++, l-- )
			PosMove[k][l] = 0;

	if( y < j && x < i )
		for( int k=i+modif, l=j+modif; k<=7 && l<=7; k++, l++ )
			PosMove[k][l] = 0;

}

/*
Quando houver uma peca de outra cor nos movimentos possiveis ela sera marcada 
como pode comer (nao e chamada por todas as pecas pelo fato de que em alguns
casos e mais facil colocar essa verificacao no proprio movimento)
*/
void marcaComi(char cor, int x, int y){
	for(int i=0; i<=7; i++){
		for(int j=0; j<=7; j++){
			if( PosMove[i][j] == 1 ){
				if( cor == 'P' && islower(tab[i][j]) )
					PosMove[i][j] = 3;
				
				if( cor == 'B' && isupper(tab[i][j]) )
					PosMove[i][j] = 3;
				
			}
		}
	}
	PosMove[x][y] = 2;
}

void fazMovimento(int x, int y){
	int haMov=0;
	for(int i=0; i<=7; i++)
		for(int j=0; j<=7; j++)
			if( PosMove[i][j] == 1 || PosMove[i][j] == 3 )
				haMov++;
	
	if( !haMov ){
		cout << "Nao ha movimentos para essa peca" << endl;
		vez = !vez;
		system("PAUSE");
		return;
	}

	cout << "Escolha o movimento: ";
	cin >> n >> l;
	converte();
	char controle;
	controle = tab[x][y];
	tab[x][y] = '0';
	tab[m][n-1] = controle;
}

void limpaPosMove(){
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			PosMove[i][j] = 0;
}

void converte(){
	switch( toupper(l) ){
		case 'A':
			m = 0;
			break;
		case 'B':
			m = 1;
			break;
		case 'C':
			m = 2;
			break;
		case 'D':
			m = 3;
			break;
		case 'E':
			m = 4;
			break;
		case 'F':
			m = 5;
			break;
		case 'G':
			m = 6;
			break;
		case 'H':
			m = 7;
			break;
	}
}
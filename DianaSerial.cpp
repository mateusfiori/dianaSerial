#include <stdio.h>
#include <stdlib.h>

//Grupos de elementos(objetos) ser�o identificados por n�meros come�ando do 0 (ZERO)
//Portanto o primeiro grupo ser� o grupo 0 
//A estrutura funciona da seguinte forma: float estrutura[grupo][elementos do grupo][informa��o de cada elemento -> 0 => x, 1 => y, 2 => index]

void preencheEstrutura(float cuboDeDados[][100][3]) {
	
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 100; j++)
				for (int k = 0; k < 3; k++) 
					cuboDeDados[i][j][k] = 4; 	
	
}

void insereDadosExternos (float cuboDeDados[][100][3], int dadosExternos[][2]) {
	
	int index = 0; //identifica��o �nica dos elementos come�a no 0 (zero) 	
	
	for (int i = 0; i < 90; i++) {
		
		for (int j = 0; j < 2; j++)
			cuboDeDados[0][i][j] = dadosExternos[i][j];
		
		cuboDeDados[0][i][2] = index++;
	}
} //fim da fun��o

void coletaDadosExternos(int dadosExternos[][2]) {
	
	FILE *arqExterno;
	
	arqExterno = fopen("duun.txt", "r"); //arquivo cedido pela Hethini (90 pontos)
	
	//rotina de erro de abertura de arquivo
	if (arqExterno == NULL)
    {
        printf("Error Reading File\n");
        exit (0);
    }
    
    for(int i = 0; i < 90; i++) 
    	for(int j = 0; j < 2; j++)    		
			fscanf(arqExterno, "%d ", &dadosExternos[i][j]);

} //fim da fun��o

void mostraElementosDoGrupo(float cuboDeDados[][100][3], int grupo) {
	
	printf("X [0]\tY [1]\tINDEX [2]\n\n"); //cabe�alho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 3; j++)
			printf ("%.2f\t", cuboDeDados[grupo][i][j]); //print de todos os elementos do grupo desejado
		
		printf("\n");
	
	}
				
} //fim da fun��o

void insereDadosG(float grupoG[][3], int dadosExternos[][2]) {
	
	int index = 0;
	
	for (int i = 0; i < 90; i++) {
		
		for (int j = 0; j < 2; j++)
			grupoG[i][j] = dadosExternos[i][j];
		
		grupoG[i][2] = index++;
	}
	
}

void mostraMatrix(float matrix[][3]) {
	
	
	printf("X [0]\tY [1]\tINDEX [2]\n\n"); //cabe�alho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 3; j++)
			printf ("%.2f\t", matrix[i][j]); //print de todos os elementos de uma matrix
		
		printf("\n");
	
	}
	
}

int main () {
	
	float cuboDeDados[5][100][3]; //estrutura principal, x, y e index de cada elemento de cada grupo (AGt)
	float matrizDissimilaridade[90][90]; //estatica por�m pode ser implementada din�mica
	float grupoG[90][3]; //grupo a ser trabalhado no la�o do algoritmo (G) => (x, y, index)
	float grupoTempG[90][3]; //grupo auxiliar utilizado para divis�o de grupos
	int dadosExternos[90][2]; // matriz que armazena os dados vindo externamente (arquivo .txt) (X)
	int maxGrupos, it;
	
	//defini��es de vari�veis
	maxGrupos = 10; //numero maximo de grupos
	it = 1; //numero de itera��es

	//Preenche as caracteristicas de cada dado com um valor especificado
	//preencheEstrutura(cuboDeDados);
			
	//pega os dados de um arquivo e coloca na matriz dadosExternos (X), matriz que vai ser posta na estrutura posteriormente	
	coletaDadosExternos(dadosExternos); //(X)
	
	//insere os dodos externos na estrutura, todos os elementos est�o em um s� grupo
	insereDadosExternos(cuboDeDados, dadosExternos); // ** (AGt <- X) **
	
	//insere os dados externos (X) no grupo G (grupoG)
	insereDadosG(grupoG, dadosExternos); // **(G <- X)**
	
	//mostra elementos da matrix (grupoG)
	mostraMatrix(grupoG);
	
	//mostra na tela os elementos de um grupo em especifico
	//mostraElementosDoGrupo(cuboDeDados, 0); 
	
	//****at� este momento os dados est�o todos agrupados em um s� grupo***//
	
	/*
	do{
	
		//montar um matriz de dissimilaridade
		
		for (int i = 0; i < 90; i++)
			for (int j = 0; j < 90; j++)
				matrizDissimilaridade[i][j] = (grupoG[i][0] op grupo[j][0]) ^ (grupoG[i][1] op grupo[j][1]); opera��es com x e y
	
	
	
	
	
		
	}while(it < maxGrupos); // repete at� que o numero de itera��es seja o maxGrupos
	*/
	
	//mostra a estrutura final com os grupos e seus elementos
	
} //fim da int main

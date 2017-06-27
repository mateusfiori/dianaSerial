#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Grupos de elementos(objetos) serão identificados por números começando do 0 (ZERO)
//Portanto o primeiro grupo será o grupo 0 
//A estrutura funciona da seguinte forma: float estrutura[grupo][elementos do grupo][informação de cada elemento -> 0 => x, 1 => y, 2 => index]

void preencheEstrutura(float cuboDeDados[][100][3]) {
	
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 100; j++)
				for (int k = 0; k < 3; k++) 
					cuboDeDados[i][j][k] = -1; 	
	
}

void insereDadosExternos (float cuboDeDados[][100][3], int dadosExternos[][2]) {
	
	int index = 0; //identificação única dos elementos começa no 0 (zero) 	
	
	for (int i = 0; i < 90; i++) {
		
		for (int j = 0; j < 2; j++)
			cuboDeDados[0][i][j] = dadosExternos[i][j];
		
		cuboDeDados[0][i][2] = index++;
	}
} //fim da função

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

} //fim da função

void mostraElementosDoGrupo(float cuboDeDados[][100][3], int grupo) {
	
	printf("X [0]\tY [1]\tINDEX [2]\n\n"); //cabeçalho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 3; j++)
			printf ("%.2f\t", cuboDeDados[grupo][i][j]); //print de todos os elementos do grupo desejado
		
		printf("\n");
	
	}
				
} //fim da função

void insereDadosG(float grupoG[][3], int dadosExternos[][2]) {
	
	int index = 0;
	
	for (int i = 0; i < 90; i++) {
		
		for (int j = 0; j < 2; j++)
			grupoG[i][j] = dadosExternos[i][j];
		
		grupoG[i][2] = index++;
	}
	
}

void mostraMatrix(float matrix[][3]) {
	
	
	printf("X [0]\tY [1]\tINDEX [2]\n\n"); //cabeçalho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 3; j++)
			printf ("%.2f\t", matrix[i][j]); //print de todos os elementos de uma matrix
		
		printf("\n");
	
	}
	
}

void preencheMatrizDiss(float matrizDissimilaridade[][91], float grupoG[][3], int qteElementos) {
	
	//montar uma matriz de dissimilaridade
	//matrizes de dissimilaridade são preenchidas com distâncias euclidianas
		
	for (int i = 0; i < qteElementos; i++) {
	
		for (int j = 0; j < qteElementos; j++)
			matrizDissimilaridade[i][j] = sqrt((grupoG[i][0] - grupoG[j][0]) * (grupoG[i][0] - grupoG[j][0]) +
													 (grupoG[i][1] - grupoG[j][1]) * (grupoG[i][1] - grupoG[j][1])); // distancia euclidiana
		
		matrizDissimilaridade[i][qteElementos] = grupoG[i][2]; //ultima posição é reservada para a identificação do elemento
	}
}

void mostraMatrixDiss(float matrix[][91]) {
	
	
	printf("X [0]\tY [1]\tINDEX [2]\n\n"); //cabeçalho dos elementos
	for (int i = 0; i < 50; i++) {
	
		for (int j = 80; j < 91; j++)
			printf ("%.2f\t", matrix[i][j]); //print de todos os elementos da matrix
		
		printf("\n");
	
	}
	
}

void preencheMatrizAVG(float matrizDissimilaridade[][91], float avgDiss[][2], int qteElementos) {
	
	float soma = 0.0;
	
	for (int i = 0; i < qteElementos; i++) {
		
		for (int j = 0; j < qteElementos; j++)
			soma += matrizDissimilaridade[i][j]; 
		
		avgDiss[i][0] = soma;
		avgDiss[i][1] = matrizDissimilaridade[i][qteElementos];
		soma = 0.0;
		}
		
}

void mostraMatrixAVG(float matrix[][2]) {
	
	
	printf("Media [0]\tINDEX [1]\n\n"); //cabeçalho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 2; j++)
			printf ("%.2f\t\t", matrix[i][j]); //print de todos os elementos de uma matrix
		
		printf("\n");
	
	}
	
}

float identificaMaiorDiss(float avgDiss[][2], int qteElementos) {
	
	float maiorDiss = avgDiss[0][0];
	float id = 0;
	
	for (int i = 0; i < qteElementos; i++) 
		if(avgDiss[i][0] > maiorDiss)
			id = avgDiss[i][1];
			
	return id;		
}

void inicializaMatrizNegativo(float matrizG[][3]) {
	
	for(int i = 0; i < 90; i++)
		for(int j = 0; j < 3; j++)
			matrizG[i][j] = -1;
	
}

void deletaElementoDiss(float grupoG[][3], float elementoMaisDissimilar, int *qteElementos, float elementoAux[]) {
	
	for (int i = 0; i < *qteElementos; i++) {
		
		if(grupoG[i][2] == elementoMaisDissimilar){
			
			//salva em uma estrutura o elemento
			elementoAux[0] = grupoG[i][0];
			elementoAux[1] = grupoG[i][1];
			elementoAux[2] = grupoG[i][2];
			
			//deleta o elemento com o index desejado do grupo
			for (int j = i; j < *qteElementos-1; j++) {
				grupoG[j][0] = grupoG[j+1][0];
				grupoG[j][1] = grupoG[j+1][1];
				grupoG[j][2] = grupoG[j+1][2];
			}
		
		//deleta o ultimo elemento	
		grupoG[*qteElementos-1][0] = -1.0; //coloca -1 na ultima posição e depois diminui a quantidade de elementos	
		grupoG[*qteElementos-1][1] = -1.0;
		grupoG[*qteElementos-1][2] = -1.0; //coloca -1 na ultima posição e depois diminui a quantidade de elementos
		qteElementos--;
		break;
		}
		
	}//fim do for de delete
	
}

void colocaElementoTempG(float tempG[][3], float elementoAux[]) {
	
	for (int i = 0; i < 90; i++)
		if (tempG[i][0] < 0) {
			
			tempG[i][0] = elementoAux[0];
			tempG[i][1] = elementoAux[1];
			tempG[i][2] = elementoAux[2];
			break;
		}
	
}

int main () {
	
	float cuboDeDados[10][100][3]; //estrutura principal, x, y e index de cada elemento de cada grupo (AGt)
	float matrizDissimilaridade[91][91]; //estática porém pode ser implementada dinâmica e possui 90+1 espaços pois o ultimo espaço é reservado para o index do elemento
	float grupoG[90][3]; //grupo a ser trabalhado no laço do algoritmo (G) => (x, y, index)
	float tempG[90][3]; //grupo que armazena os elementos que não fazem parte do grupoG
	float grupoTempG[90][3]; //grupo auxiliar utilizado para divisão de grupos
	float avgDiss[90][2]; //matriz que armazena as medias de dissimilaridade de cada elemento
	float maiorDiss[2]; //estrutura que armazena a maior distancia e qual elemento ela pertence
	float elementoAux[3];//estrutura que guarda o elemento que sera deletado e colocado em tempG
	int dadosExternos[90][2]; // matriz que armazena os dados vindo externamente (arquivo .txt) (X)
	int maxGrupos, it, qteElementos;
	
	//definições de variáveis
	maxGrupos = 10; //numero maximo de grupos
	it = 1; //numero de iterações
	qteElementos = 90; //quantidade de elementos existentes no grupoG
	
	//Preenche as caracteristicas de cada dado com um valor especificado (-1)
	preencheEstrutura(cuboDeDados);
			
	//pega os dados de um arquivo e coloca na matriz dadosExternos (X), matriz que vai ser posta na estrutura posteriormente	
	coletaDadosExternos(dadosExternos); //(X)
	
	//insere os dodos externos na estrutura, todos os elementos estão em um só grupo
	insereDadosExternos(cuboDeDados, dadosExternos); // ** (AGt <- X) **
	
	//insere os dados externos (X) no grupo G (grupoG)
	insereDadosG(grupoG, dadosExternos); // **(G <- X)**
	
	//mostra elementos da matrix (grupoG)
	//mostraMatrix(grupoG);
	
	//mostra na tela os elementos de um grupo em especifico
	//mostraElementosDoGrupo(cuboDeDados, 0); 
	
	//****até este momento os dados estão todos agrupados em um só grupo***//
	
	//Aqui começa o laço principal (do while)
	
	//preenche a matriz de dissimilaridade (ultima posição reservada para o index do elemento)
	preencheMatrizDiss(matrizDissimilaridade, grupoG, qteElementos);
	
	//mostra a matriz de dissimilaridade
	//mostraMatrixDiss(matrizDissimilaridade);
	
	//preenche a matriz com as médias de distancia de cada elemento
	preencheMatrizAVG(matrizDissimilaridade, avgDiss, qteElementos); //average linkage -> tera que trocar por centroid linkage	
	
	//mostra a matrix de medias de distancias
	//mostraMatrixAVG(avgDiss);
	
	//função para encontrar o elemento com a maior media de distancias	
	printf("\nMaior dissimilaridade: %d <- INDEX", (int) identificaMaiorDiss(avgDiss, qteElementos));
	
	//inicializa tempG com valores negativos
	inicializaMatrizNegativo(tempG); //todos as posições de tempG estão preenchidas com numeros negativos
	
	//identifica o elemento de maior dissimilaridade, o deleta do grupoG e salva o elemento em elementoAux para depois ser posto no grupo tempG
	deletaElementoDiss(grupoG, identificaMaiorDiss(avgDiss, qteElementos), &qteElementos, elementoAux);
	//coloca o elemento em tempG 
	colocaElementoTempG(tempG, elementoAux);
	
	//proximo passo é pegar cada elemento de grupoG e fazer a media de distancia com relação a todos os elementos de G e com relação a cada elemento de tempG
	//depois deve-se tirar essas duas medias e armazenar em D(x), o elemento que obtiver maior D(x) sera tirado do grupoG 
	
	
	printf ("\n\nX: %f\tY: %f\tINDEX: %f\tQTE ELEMENTOS: %d\n\n", elementoAux[0], elementoAux[1], elementoAux[2], qteElementos);
	
	mostraMatrix(tempG);
	
	
	//antes de preencher qualquer matriz é necessário reseta-la, ou seja, preenche-la com numeros negativos
	/*
	do{
	
			
	}while(it < maxGrupos); // repete até que o numero de iterações seja o maxGrupos
	*/
	
	//mostra a estrutura final com os grupos e seus elementos
	
} //fim da int main

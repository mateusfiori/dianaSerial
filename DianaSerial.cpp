#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Grupos de elementos(objetos) ser�o identificados por n�meros come�ando do 0 (ZERO)
//Portanto o primeiro grupo ser� o grupo 0 
//A estrutura funciona da seguinte forma: float estrutura[grupo][elementos do grupo][informa��o de cada elemento -> 0 => x, 1 => y, 2 => index]

void preencheEstrutura(float cuboDeDados[][100][3]) {
	
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 100; j++)
				for (int k = 0; k < 3; k++) 
					cuboDeDados[i][j][k] = -1; 	
	
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

void mostraMatrixDx(float matrix[][2]) {
	
	
	printf("Media [0]\tINDEX [1]\n\n"); //cabe�alho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 2; j++)
			printf ("%.2f\t\t", matrix[i][j]); //print de todos os elementos de uma matrix
		
		printf("\n");
	
	}
	
}

void preencheMatrizDiss(float matrizDissimilaridade[][91], float grupoG[][3], int qteElementos) {
	
	//montar uma matriz de dissimilaridade
	//matrizes de dissimilaridade s�o preenchidas com dist�ncias euclidianas
		
	for (int i = 0; i < qteElementos; i++) {
	
		for (int j = 0; j < qteElementos; j++)
			matrizDissimilaridade[i][j] = sqrt((grupoG[i][0] - grupoG[j][0]) * (grupoG[i][0] - grupoG[j][0]) +
													 (grupoG[i][1] - grupoG[j][1]) * (grupoG[i][1] - grupoG[j][1])); // distancia euclidiana
		
		matrizDissimilaridade[i][qteElementos] = grupoG[i][2]; //ultima posi��o � reservada para a identifica��o do elemento
	}
}

void mostraMatrixDiss(float matrix[][91]) {
	
	
	printf("X [0]\tY [1]\tINDEX [2]\n\n"); //cabe�alho dos elementos
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
	
	
	printf("Media [0]\tINDEX [1]\n\n"); //cabe�alho dos elementos
	for (int i = 0; i < 90; i++) {
	
		for (int j = 0; j < 2; j++)
			printf ("%.2f\t\t", matrix[i][j]); //print de todos os elementos de uma matrix
		
		printf("\n");
	
	}
	
}

float identificaMaiorDiss(float avgDiss[][2], int qteElementos) {
	
	float maiorDiss = avgDiss[0][0];
	float id = 0;
	
	for (int i = 0; i < qteElementos; i++) {
		if(avgDiss[i][0] > maiorDiss){
			maiorDiss = avgDiss[i][0];
			id = avgDiss[i][1];
		}
	}
	
	return id;		
}

float identificaMaiorDx(float Dx[][2], int qteElementos) {
	
	float maiorDx = Dx[0][0];
	float id = 0;
	
	for (int i = 0; i < qteElementos; i++) {

		if(Dx[i][0] > maiorDx) {
			maiorDx = Dx[i][0];	
			id = Dx[i][1];
		}
	}
	
	if(maiorDx < 0) return -1; //retorna negativo se o maior valor for negativo e portanto para o loop
		else	return id;			
}

void inicializaMatrizNegativo(float matrizG[][3]) {
	
	for(int i = 0; i < 90; i++)
		for(int j = 0; j < 3; j++)
			matrizG[i][j] = -1;
	
}

//inicializa a matriz Dx com -99999.99, numero que � improvavel de acontecer
void inicializaMatrizDx(float Dx[][2]) {
	
	for(int i = 0; i < 90; i++)
		for(int j = 0; j < 2; j++)
			Dx[i][j] = -99999.99;
	
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
		grupoG[*qteElementos-1][0] = -1.0; //coloca -1 na ultima posi��o e depois diminui a quantidade de elementos	
		grupoG[*qteElementos-1][1] = -1.0;
		grupoG[*qteElementos-1][2] = -1.0; //coloca -1 na ultima posi��o e depois diminui a quantidade de elementos
		*qteElementos -= 1;
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

//partindo do principio que o max de elementos � 90, quando aumentar a quantidade de dados tem que mudar essa funcao
int contaElementosTempG (float tempG[][3]) {
	
	int quantidade = 0;
		
	for (int i = 0; i < 90; i++) {
	
		if (tempG[i][0] < 0)
			break;
		else {
			quantidade++;
		}
	
	}
	
	return quantidade;
}

void preencheDx(float Dx[][2], float grupoG[][3], float tempG[][3], int qteElementos, int qteElementosTempG) {
	
	float somaG, distG, somaTempG, distTempG;
	
	somaTempG = 0;
	somaG = 0;
	distTempG = 0;
	distG = 0;
	
	for (int i = 0; i < qteElementos; i++) {
		
		somaTempG = 0;
		somaG = 0;
		
		//esse for ira somar as distancias de i com rela��o a todos os elementos do grupoG
		for (int j = 0; j < qteElementos; j++) {
			
			if(tempG[j][0] >= 0) {
				
				distTempG = sqrt((grupoG[i][0] - tempG[j][0]) * (grupoG[i][0] - tempG[j][0]) +
													 (grupoG[i][1] - tempG[j][1]) * (grupoG[i][1] - tempG[j][1]));
				somaTempG += distTempG;
			} //fim do if
			
			distG = sqrt((grupoG[i][0] - grupoG[j][0]) * (grupoG[i][0] - grupoG[j][0]) +
													 (grupoG[i][1] - grupoG[j][1]) * (grupoG[i][1] - grupoG[j][1]));
			somaG += distG;
				
		} //fim do segundo for
		
		//atribui��o da diferen�a da soma a estrutura D(x)
		somaG /= (qteElementos-1); // qteElementos-1 pois n�o se leva em considera��o a distancia do elemento de g com rela��o a ele mesmo
		somaTempG /= qteElementosTempG;
		
		Dx[i][0] = somaG-somaTempG; //diferen�a das distancias
		Dx[i][1] = grupoG[i][2]; //index do elemento
	
	} //fim do primeiro for
	
}

int main () {
	
	float cuboDeDados[10][100][3]; //estrutura principal, x, y e index de cada elemento de cada grupo (AGt)
	float matrizDissimilaridade[91][91]; //est�tica por�m pode ser implementada din�mica e possui 90+1 espa�os pois o ultimo espa�o � reservado para o index do elemento
	float grupoG[90][3]; //grupo a ser trabalhado no la�o do algoritmo (G) => (x, y, index)
	float tempG[90][3]; //grupo que armazena os elementos que n�o fazem parte do grupoG
	float grupoTempG[90][3]; //grupo auxiliar utilizado para divis�o de grupos
	float avgDiss[90][2]; //matriz que armazena as medias de dissimilaridade de cada elemento
	float maiorDiss[2]; //estrutura que armazena a maior distancia e qual elemento ela pertence
	float elementoAux[3];//estrutura que guarda o elemento que sera deletado e colocado em tempG
	float Dx[90][2]; //matriz que armazenara a diferen�a das somas das distancias e o index do elemento
	int dadosExternos[90][2]; // matriz que armazena os dados vindo externamente (arquivo .txt) (X)
	int maxGrupos, it, qteElementos, qteElementosTempG;
	
	//defini��es de vari�veis
	maxGrupos = 10; //numero maximo de grupos
	it = 1; //numero de itera��es
	qteElementos = 90; //quantidade de elementos existentes no grupoG
	qteElementosTempG = 0; //valor inicial, sera mudado posteriormente pela fun��o contaElementosTempG
	
	//Preenche as caracteristicas de cada dado com um valor especificado (-1)
	preencheEstrutura(cuboDeDados);
			
	//pega os dados de um arquivo e coloca na matriz dadosExternos (X), matriz que vai ser posta na estrutura posteriormente	
	coletaDadosExternos(dadosExternos); //(X)
	
	//insere os dodos externos na estrutura, todos os elementos est�o em um s� grupo
	insereDadosExternos(cuboDeDados, dadosExternos); // ** (AGt <- X) **
	
	//insere os dados externos (X) no grupo G (grupoG)
	insereDadosG(grupoG, dadosExternos); // **(G <- X)**
	
	//mostra elementos da matrix (grupoG)
	//mostraMatrix(grupoG);
	
	//mostra na tela os elementos de um grupo em especifico
	//mostraElementosDoGrupo(cuboDeDados, 0); 
	
	//****at� este momento os dados est�o todos agrupados em um s� grupo***//
	
	//Aqui come�a o la�o principal (do while)
	
	//preenche a matriz de dissimilaridade (ultima posi��o reservada para o index do elemento)
	preencheMatrizDiss(matrizDissimilaridade, grupoG, qteElementos);
	
	//mostra a matriz de dissimilaridade
	//mostraMatrixDiss(matrizDissimilaridade);
	
	//preenche a matriz com as m�dias de distancia de cada elemento
	preencheMatrizAVG(matrizDissimilaridade, avgDiss, qteElementos); //average linkage -> tera que trocar por centroid linkage	
	
	//mostra a matrix de medias de distancias
	//mostraMatrixAVG(avgDiss);
	
	//fun��o para encontrar o elemento com a maior media de distancias	
	printf("\nMaior dissimilaridade: %d <- INDEX", (int) identificaMaiorDiss(avgDiss, qteElementos));
	
	//inicializa tempG com valores negativos
	inicializaMatrizNegativo(tempG); //todos as posi��es de tempG est�o preenchidas com numeros negativos
	
	//identifica o elemento de maior dissimilaridade, o deleta do grupoG e salva o elemento em elementoAux para depois ser posto no grupo tempG
	deletaElementoDiss(grupoG, identificaMaiorDiss(avgDiss, qteElementos), &qteElementos, elementoAux);
	//coloca o elemento em tempG 
	colocaElementoTempG(tempG, elementoAux);
	
	//conta quantos elementos tem em tempG
	qteElementosTempG = contaElementosTempG(tempG);
	
	printf ("\n\nX: %f\tY: %f\tINDEX: %f\nQteElementos em grupoG: %d\tQteElementos em tempG: %d\n\n", elementoAux[0], elementoAux[1], elementoAux[2], qteElementos, qteElementosTempG);
	
	//a partir de agora come�a o segundo la�o que rodara ate que n�o existam mais valores Dx positivos
	
	inicializaMatrizDx(Dx);
	
	//matriz que cont�m a diferen�a das m�dias das distancias de cada elemento do grupoG 
	//com rela��o aos elementos do grupoG menos as medias das distancias do elementos em rela��o aos elementos do grupo tempG
	preencheDx(Dx, grupoG, tempG, qteElementos, qteElementosTempG); //Dx -> (diferen�a das medias, index)	
	
	//o elemento que obtiver maior D(x) sera tirado do grupoG e colocado no grupo tempG
	//identifica o maior Dx, se o valor do index for negativo � porque todos os valores de Dx s�o negativos, portanto deve-se sair do la�o
	printf("\nMaior elemento de Dx: %.2f <- INDEX\n\n", identificaMaiorDx(Dx, qteElementos));

	//proximo passo � retirar o elemento encontrado do grupoG e coloca-lo em tempG
	//deleta elemento do grupoG
	deletaElementoDiss(grupoG, identificaMaiorDx(Dx, qteElementos), &qteElementos, elementoAux);
	//adiciona elemento em tempG
	colocaElementoTempG(tempG, elementoAux);
	
	//mostraMatrixDx(Dx);
	mostraMatrix(tempG);
		
	//antes de preencher qualquer matriz � necess�rio reseta-la, ou seja, preenche-la com numeros negativos
	/*
	do{
	
			
	}while(it < maxGrupos); // repete at� que o numero de itera��es seja o maxGrupos
	*/
	
	//mostra a estrutura final com os grupos e seus elementos
	
} //fim da int main

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void mostraMatriz(FILE *arqv_saida, int tam, int mat[tam][tam]) {
	int i, j;
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			fprintf(arqv_saida,"%i ", mat[i][j]);
		}
		fprintf(arqv_saida, "\n");
	}
}

int somaDiagonalPrincipal(int tam, int mat[tam][tam]) {
	int i, soma = 0;
	for (i = 0; i < tam; i++) {
		soma += mat[i][i];
	}
	return soma;
}

int somaDiagonalSecundaria(int tam, int mat[tam][tam]) {
	int i, soma = 0;
	for (i = 0; i < tam; i++) {
		soma += mat[i][tam-i-1];
	}
	return soma;
}

void mostraVetor(FILE *arqv_saida, int vet[], int tam) {
	int i;
	for (i = 0; i < tam; i++) {
		fprintf(arqv_saida,"%i ", vet[i]);
	}
}

void somaLinhas(int tam, int mat[tam][tam], int vet[]) {
	int i, j;
	for (i = 0; i < tam; i++) {
		vet[i] = 0;
		for (j = 0; j < tam; j++) {
			vet[i] += mat[i][j];
		}
	}
}

void somaColunas(int tam, int mat[tam][tam], int vet[]) {
	int i, j;
	for (j = 0; j < tam; j++) {
		vet[j] = 0;
		for (i = 0; i < tam; i++) {
			vet[j] += mat[i][j];
		}
	}
}

int testaIgualidadeVetor(int vet[], int tam) {
	int i;
	for (i = 1; i <  tam; i++) {
		if (vet[i] != vet[i-1]) {
			return 0;
		}
	}
	return 1;
}

int main(void) {
	int n;
	char nomedoarqv1[20], nomedoarqv[20];
	FILE*entrada;

	printf("\nDigite o nome do arquivo de entrada: ");
  	scanf("%s", nomedoarqv1);


  	if((entrada=fopen(nomedoarqv1,"r"))==NULL){
    	printf("\nNao foi possivel abrir o arquivo");
  		return 0;
	}

  fscanf(entrada, "%d", &n);
	int mat[n][n];
	int l, c;
	for (l=0; l<n ;l++){
    	for (c=0; c<n; c++){
      		fscanf(entrada, "%d", &mat[l][c]);
    	}
	}
	
	fclose(entrada);

	FILE*saida;

	printf("\nDigite o nome do arquivo de saida: ");
  	scanf("%s", nomedoarqv);

	if((saida=fopen(nomedoarqv,"w"))==NULL){
    	printf("\nNao foi possivel abrir o arquivo");
  		return 0;
	}

	mostraMatriz(saida, n, mat);
	
	int somaDP = 0, somaDS = 0;
	somaDP = somaDiagonalPrincipal(n,mat);  //soma da diagonal principal
	somaDS = somaDiagonalSecundaria(n,mat); //soma da diagonal secundaria

	//soma linhas
	int vetL[n];
	somaLinhas(n, mat, vetL);
	fprintf(saida, "\nSoma das linhas: ");
	mostraVetor(saida, vetL, n);

	//soma colunas
	int vetC[n];
	somaColunas(n, mat, vetC);
	fprintf(saida, "\nSoma das colunas: ");
	mostraVetor(saida, vetC, n);
	
	fprintf(saida, "\nSoma diagonal principal %i e secundaria %i\n", somaDP, somaDS);

	int testaL, testaC;
	testaL = testaIgualidadeVetor(vetL, n);
	testaC = testaIgualidadeVetor(vetC, n);

	if (testaL && testaC && somaDP == somaDS && somaDP == vetL[0]) {
		fprintf(saida, "Quadrado magico");
	} else {
		fprintf(saida, "Quadrado nao magico");
	}

	return 0;
}
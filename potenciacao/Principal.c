#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

/* Função para decompor inteiro na lista */
void carregarValor(Lista * l, int v) {
	int mod = 0;
	while (v != 0)
	{
		mod = v % 10;
		v = v / 10;
		inserir_primeiro(l, mod);
	}
}

/* Função para calcular a potenciação */
void calcPonteciacao(Lista * lBase, Lista * lExpoente) {
	Lista * lResultadoPotenciacao = criar();
	Lista * lSoma1 = criar();
	Lista * lSoma2 = criar();
	
	long long int j, w, vExpoente = 0;
	int i, k, y, q, x, tamExpoente = tamanho(lExpoente), overflow = 0, valor = 0, cont = 0, posSoma2 = 0;
	
	/* Copiar lBase para lResultadoPotenciacao  */
	for (i = 0; i < tamanho(lBase); i++) {
		inserir_ultimo(lResultadoPotenciacao, ler_pos(lBase, i));
	}
	
	/* Lê posição a posição do lExpoente e determina o valor seja unidade, dezena ou centena */
	for (i = tamExpoente - 1, j = 1; i >= 0; i--, j *= 10) {
		vExpoente = ler_pos(lExpoente, i) * j;

		/* Se for a primeira posição vExpoente recebe o valor da unidade - 1 */
		if (i == 0) {
			vExpoente = vExpoente - 1;
		}

		/* Repete o bloco de código w vezes de acordo com o valor de vExpoente */
		for (w = 0; w < vExpoente; w++) {
			/* Lê posição a posição do lBase para utilizar na multiplicação */
			for (k = tamanho(lBase) - 1; k >= 0; k--) {
				/* Lê posição a posição do lResutadoPoteciacao para utilizar na multiplicação */
				for (y = tamanho(lResultadoPotenciacao) - 1; y >= 0; y--) {
					valor = (ler_pos(lResultadoPotenciacao, y) * ler_pos(lBase, k)) + overflow;
					overflow = valor / 10;
					inserir_primeiro(lSoma1, valor % 10);
				}
				if (overflow != 0) {
					inserir_primeiro(lSoma1, overflow);
				}
				overflow = 0;
				valor = 0;

				/* Soma o resultado da multiplação de cada número do lBase com os números do lResultadoPotenciacao */
				for (q = tamanho(lSoma1) - 1, posSoma2 = tamanho(lSoma2) - 1; q >= 0; q--, posSoma2--) {
					if (ler_pos(lSoma2, posSoma2) == -1) {
						if (ler_pos(lSoma1, q) + overflow < 10) {
							inserir_primeiro(lSoma2, ler_pos(lSoma1, q) + overflow);
						}
						else {
							inserir_primeiro(lSoma2, ler_pos(lSoma1, q) + overflow % 10);
							inserir_primeiro(lSoma2, ler_pos(lSoma1, q) + overflow / 10);
						}
						overflow = 0;
					}
					else {
						valor = ler_pos(lSoma2, posSoma2) + ler_pos(lSoma1, q) + overflow;
						overflow = valor / 10;
						escrever_pos(lSoma2, posSoma2, valor % 10);
					}
				}
				if (overflow != 0) {
					inserir_primeiro(lSoma2, overflow);
				}
				limpar(lSoma1);

				overflow = 0;

				cont++;
				/* Acrescenta zeros para que a soma dos termos da multiplicação seja realizada corretamente */
				for (x = 0; x < cont; x++) {
					inserir_primeiro(lSoma1, 0);
				}
			}
			limpar(lResultadoPotenciacao);

			/* Copia o resultado da multiplicação até esse momento */
			for (q = 0; q < tamanho(lSoma2); q++) {
				inserir_ultimo(lResultadoPotenciacao, ler_pos(lSoma2, q));
			}
			limpar(lSoma1);
			limpar(lSoma2);
			cont = 0;
		}
	}
	imprimir(lResultadoPotenciacao);

	destruir(lSoma1);
	destruir(lSoma2);
	destruir(lResultadoPotenciacao);
}

int main(int argc, char *argv[]) {
	int opcao = 1;
	long int vBase, vExpoente;
	Lista * lBase = criar();
	Lista * lExpoente = criar();

	while (opcao != 4) {
		printf("================================Menu de opcoes================================\n");
		printf("1\. Definir o valor da base\n"
			"2\. Definir o valor do expoente\n"
			"3\. Mostrar o resultado da potenciacao\n"
			"4\. Sair do programa\n");
		printf("===============================================================================\n");
		printf("\nQual opcao do menu deseja executar?\n");
		scanf("%d", &opcao);
		if (opcao == 1) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|      Valor da Base     |\n"
				"|                        |\n"
				"--------------------------\n");
			printf("\nValor da base: ");
			scanf("%d", &vBase);
			limpar(lBase);
			carregarValor(lBase, vBase);
			imprimir(lBase);
		}
		if (opcao == 2) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|   Valor do expoente    |\n"
				"|                        |\n"
				"--------------------------\n");
			printf("\nValor do expoente: ");
			scanf("%d", &vExpoente);
			limpar(lExpoente);
			carregarValor(lExpoente, vExpoente);
			imprimir(lExpoente);
		}
		if (opcao == 3) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|       Resultado        |\n"
				"|                        |\n"
				"--------------------------\n");
			printf("%d \^ %d = ", vBase, vExpoente);
			calcPonteciacao(lBase, lExpoente);
		}
		if (opcao == 4) {
			system("cls");
			printf("\n\n============================");
			printf("A operacao foi encerrada.");
			printf("===========================\n\n\n");
			getch();
		}
		if (opcao < 1 || opcao > 4) {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================\n");
		}
	}

	destruir(lBase);
	destruir(lExpoente);
}
#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

#define TAM_MAX 50

struct lista {
	int itens[TAM_MAX];
	int ini, fim;
};

Lista * criar() {
	Lista * l = (Lista *)malloc(sizeof(Lista));
	l->ini = 0;
	l->fim = 0;
	return l;
}

void destruir(Lista * l) {
	if (l != NULL) {
		free(l);
	}
}

void limpar(Lista * l) {
	l->ini = l->fim = 0;
}

void imprimir(Lista * l) {
	int i;
	printf("[ ");
	for (i = l->ini; i<l->fim; i++) {
		printf("%d ", l->itens[i]);
	}
	printf("]\n");
}

int tamanho(Lista * l) {
	return l->fim - l->ini;
}

int esta_vazia(Lista * l) {
	return tamanho(l) == 0;
}

int ler_pos(Lista * l, int p) {
	if (p < 0 || p >= tamanho(l)) {
		//printf("Posicao invalida!\n");
		return -1;
	}

	return l->itens[l->ini + p];
}

int primeiro(Lista * l) {
	return ler_pos(l, 0);
}

int ultimo(Lista * l) {
	return ler_pos(l, tamanho(l) - 1);
}

int buscar(Lista * l, int v) {
	int i;

	for (i = l->ini; i < l->fim; i++) {
		if (l->itens[i] == v) {
			return i - l->ini;
		}
	}
	return -1;

	/*
	for (i = 0; i < tamanho(l); i++) {
	if (ler_pos(l, i) == v) {
	return i;
	}
	}
	return - 1;
	*/
}

void escrever_pos(Lista * l, int p, int v) {
	if (p < 0 || p >= tamanho(l)) {
		//printf("Posicao invalida!\n");
		return;
	}
	l->itens[l->ini + p] = v;
}

void inserir_pos(Lista * l, int p, int v) {
	if (p < 0 || p > tamanho(l)) {
		//printf("Posicao invalida!\n");
		return;
	}
	if (tamanho(l) == TAM_MAX) {
		printf("Lista cheia");
		return;
	}
	//Desloca esquerda
	if (l->fim == TAM_MAX) {
		int i;
		for (i = l->ini - 1; i < (l->ini + p); i++) {
			l->itens[i] = l->itens[i + 1];
		}
		l->itens[i] = v;
		l->ini--;

		/* P/inicio
		int i, j;
		for (i = 0, j = l->ini; i < p; i++, j++) {
		l->itens[i] = l->itens[j];
		}
		l->itens[i++] = v;
		for (; j < l->fim; i++, j++) {
		l->itens[i] = l->itens[j];
		}
		l->ini = 0;
		l->fim = i;
		*/
	}
	//Desloca direita
	else {
		int i;
		for (i = l->fim; i > (l->ini + p); i--) {
			l->itens[i] = l->itens[i - 1];
		}
		l->itens[i] = v;
		l->fim++;
	}
}

void inserir_primeiro(Lista * l, int v) {
	inserir_pos(l, 0, v);
}

void inserir_ultimo(Lista * l, int v) {
	inserir_pos(l, l->fim, v);
}

int remover_pos(Lista * l, int p) {
	if (p < 0 || p >= tamanho(l)) {
		printf("Posicao invalida!\n");
		return;
	}
	int i, v = l->itens[l->ini + p];
	for (i = l->ini + p; i < l->fim; i++) {
		l->itens[i] = l->itens[i + 1];
	}
	l->fim--;
	return v;
}

int remover_primeiro(Lista * l) {
	return remover_pos(l, 0);
}

int remover_ultimo(Lista * l) {
	return remover_pos(l, tamanho(l) - 1);
}

void remover(Lista * l, int v) {
	int p = buscar(l, v);
	if (p != -1) {
		remover_pos(l, p);
	}
}

void remover_todos(Lista * l, int v) {
	int i, j;

	int p = buscar(l, v);
	if (p != -1) {
		for (i = j = p; i < l->fim; i++) {
			if (l->itens[i] != v) {
				l->itens[j++] = l->itens[i];
			}
		}
		l->fim = j;
	}
}
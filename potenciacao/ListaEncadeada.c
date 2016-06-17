#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no No;

struct no {
	int info;
	No * prox;
};

struct lista {
	int tam;
	No * ini, *fim;
};

Lista * criar() {
	Lista * l = (Lista *)malloc(sizeof(Lista));
	l->ini = NULL;
	l->fim = NULL;
	l->tam = 0;
	return l;
}

void destruir(Lista * l) {
	if (l != NULL) {
		limpar(l);
		free(l);
	}
}

void limpar(Lista * l) {
	No * aux = l->ini;
	while (aux != NULL) {
		No * aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
	l->ini = NULL;
	l->fim = NULL;
	l->tam = 0;
}

void imprimir(Lista * l) {
	No * aux = l->ini;
	printf("[ ");
	while (aux != NULL) {
		printf("%d ", aux->info);
		aux = aux->prox;
	}
	printf("]\n");
}

int tamanho(Lista * l) {
	return l->tam;
}

int esta_vazia(Lista * l) {
	return tamanho(l) == 0;
}

int ler_pos(Lista * l, int p) {
	int i;
	No * aux = l->ini;
	if (p < 0 || p >= tamanho(l)) {
		//printf("Posicao invalida!\n");
		return -1;
	}
	for (i = 0; i < p; i++) {
		aux = aux->prox;
	}

	return aux->info;
}

int primeiro(Lista * l) {
	return ler_pos(l, 0);
}

int ultimo(Lista * l) {
	return ler_pos(l, tamanho(l) - 1);
}

int buscar(Lista * l, int v) {
	int i, p = 0;
	No * aux = l->ini;

	for (i = 0; i < tamanho(l); i++) {
	if (ler_pos(l, i) == v) {
	return i;
	}
	}
	return - 1;
}

void escrever_pos(Lista * l, int p, int v) {
	int i;
	No * aux = l->ini;
	if (p < 0 || p >= tamanho(l)) {
		//printf("Posicao invalida!\n");
		return ;
	}
	for (i = 0; i < p; i++) {
		aux = aux->prox;
	}

	aux->info = v;
}

void inserir_pos(Lista * l, int p, int v) {
	int i;
	No * aux = l->ini;
	No * aux2;
	if (p < 0 || p > tamanho(l)) {
		//printf("Posicao invalida!\n");
		return;
	}
	aux2 = (No *)malloc(sizeof(No));
	aux2->info = v;
	aux2->prox = NULL;

	if (p > 0 && p < l->tam) {
		for (i = 0; i < p - 1; i++) {
			aux = aux->prox;
		}
		aux2->prox = aux->prox;
		aux->prox = aux2;
	}
	else {
		if (p == 0) {
			aux2->prox = l->ini;
			l->ini = aux2;
		}
		if (p == l->tam) {
			if (l->fim != NULL) {
				l->fim->prox = aux2;
			}
			l->fim = aux2;
		}
	}
	l->tam++;
}

void inserir_primeiro(Lista * l, int v) {
	inserir_pos(l, 0, v);
}

void inserir_ultimo(Lista * l, int v) {
	inserir_pos(l, tamanho(l), v);
}

int remover_pos(Lista * l, int p) {
	int i, v;
	No * aux = l->ini;
	No * aux2;
	if (p < 0 || p >= tamanho(l)) {
		printf("Posicao invalida!\n");
		return;
	}
	if (p > 0) {
		for (i = 0; i < p - 1; i++) {
			aux = aux->prox;
		}
		aux2 = aux->prox;
		aux->prox = aux2->prox;
	}
	else {
		aux = NULL;
		aux2 = l->ini;
		l->ini = aux2->prox;
	}
	if (p == l->tam - 1) {
		l->fim = aux;
	}

	v = aux2->info;
	free(aux2);
	l->tam--;
	return v;
}

int remover_primeiro(Lista * l) {
	return remover_pos(l, 0);
}

int remover_ultimo(Lista * l) {
	return remover_pos(l, tamanho(l) - 1);
}

void remover(Lista * l, int v) {
	/*int p = buscar(l, v);
	if (p != -1) {
	return remover_pos(l, p);
	}
	*/
	No * aux = NULL, *aux2 = l->ini;
	while (aux2 != NULL && aux2->info != v)
	{
		aux = aux2;
		aux2 = aux2->prox;
	}
	if (aux2 != NULL) {
		if (aux2 != l->ini) {
			aux->prox = aux2->prox;
		}
		else {
			l->ini = aux2->prox;
		}
		if (aux2 == l->fim) {
			l->fim = aux;
		}
		free(aux2);
		l->tam--;
	}
}

void remover_todos(Lista * l, int v) {
	No * aux = NULL, *aux2 = l->ini;

	while (aux2 != NULL)
	{
		while (aux2 != NULL && aux2->info != v)
		{
			aux = aux2;
			aux2 = aux2->prox;
		}
		if (aux2 != NULL) {
			if (aux2 != l->ini) {
				aux->prox = aux2->prox;
			}
			else {
				l->ini = aux2->prox;
			}
			if (aux2 == l->fim) {
				l->fim = aux;
			}
			free(aux2);
			aux2 = aux != NULL ? aux->prox : l->ini;
			l->tam--;
		}
	}
	/*
	while (aux2 != NULL)
	{
	if (aux2->info != v) {
	aux = aux2;
	aux2 = aux2->prox;
	}
	else {
	No * aux3 = aux2;
	aux2 = aux2->prox;
	if (aux3 != NULL) {
	if (aux3 != l->ini) {
	aux->prox = aux3->prox;
	}
	else {
	l->ini = aux3->prox;
	}
	if (aux3 == l->fim) {
	l->fim = aux;
	}
	free(aux3);
	l->tam--;
	}
	}
	}
	free(aux2);
	*/
}
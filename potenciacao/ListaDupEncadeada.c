#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct no No;

struct no {
	int info;
	No * prox;
	No * ant;
};

struct lista {
	int tam;
	No * ini, *fim;
};

Lista * criar() {
	Lista * l = (Lista *)malloc(sizeof(Lista));
	l->ini = (No *)malloc(sizeof(No));
	l->fim = (No *)malloc(sizeof(No));
	l->ini->prox = l->fim;
	l->ini->ant = NULL;
	l->fim->ant = l->ini;
	l->fim->prox = NULL;
	l->tam = 0;
	return l;
}

void destruir(Lista * l) {
	if (l != NULL) {
		limpar(l);
		free(l->ini);
		free(l->fim);
		free(l);
	}
}

void limpar(Lista * l) {
	No * aux = l->ini->prox;
	while (aux != l->fim) {
		No * aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
	l->ini->prox = l->fim;
	l->fim->ant = l->ini;
	l->tam = 0;
}

void imprimir(Lista * l) {
	No * aux = l->ini->prox;
	printf("[ ");
	while (aux != l->fim) {
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
	No * aux = l->ini->prox;
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
	No * aux = l->ini->prox;

	while (aux != l->fim && aux->info != v) {
		return
			aux = aux->prox;
		p++;
	}
	return aux != l->fim ? p : -1;

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
	int i;
	No * aux = l->ini->prox;
	if (p < 0 || p >= tamanho(l)) {
		//printf("Posicao invalida!\n");
		return -1;
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

	for (i = 0; i < p; i++) {
		aux = aux->prox;
	}
	aux2->prox = aux->prox;
	aux->prox->ant = aux2;
	aux->prox = aux2;
	aux2->ant = aux;
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
	for (i = 0; i < p; i++) {
		aux = aux->prox;
	}
	aux2 = aux->prox;
	aux->prox = aux2->prox;
	aux->prox->ant = aux;

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
	No * aux2 = l->ini->prox;
	while (aux2 != l->fim && aux2->info != v)
	{
		aux2 = aux2->prox;
	}
	if (aux2 != l->fim) {
		aux2->ant->prox = aux2->prox;
		aux2->prox->ant = aux2->ant;

		free(aux2);
		l->tam--;
	}
	/*
	No * aux = NULL, *aux2 = l->ini;
	while (aux2 != l->fim && aux2->info != v)
	{
	aux = aux2;
	aux2 = aux2->prox;
	}
	aux2 = aux->prox;
	aux->prox = aux2->prox;
	aux->prox->ant = aux;

	v = aux2->info;
	free(aux2);
	l->tam--;
	*/
}

void remover_todos(Lista * l, int v) {
	No *aux, *aux2 = l->ini->prox;

	while (aux2 != l->fim)
	{
		while (aux2 != l->fim && aux2->info != v)
		{
			aux2 = aux2->prox;
		}
		if (aux2 != l->fim) {
			aux2->ant->prox = aux2->prox;
			aux2->prox->ant = aux2->ant;
			aux = aux2->prox;
			free(aux2);
			aux2 = aux;
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

void inverter(Lista * l) {
	No * aux = l->ini->prox, *aux2 = l->fim->ant;

	if (l->tam % 2 == 0) {
		while (aux->ant->info != aux2->info) {
			No *aux3 = (No *)malloc(sizeof(No));
			aux3->info = aux->info;
			aux->info = aux2->info;
			aux2->info = aux3->info;

			aux = aux->prox;
			aux2 = aux2->ant;
			free(aux3);
		}
	}
	else {
		while (aux->info != aux2->info) {
			No *aux3 = (No *)malloc(sizeof(No));
			aux3->info = aux->info;
			aux->info = aux2->info;
			aux2->info = aux3->info;

			aux = aux->prox;
			aux2 = aux2->ant;
			free(aux3);
		}
	}
}

void inverterProf(Lista * l) {
	No * aux = l->ini->prox, *aux2 = l->fim->ant;
	int i, tmp;

	for (i = 0; i < l->tam / 2; i++) {
		tmp = aux->info;
		aux->info = aux2->info;
		aux2->info = tmp;

		aux = aux->prox;
		aux2 = aux2->ant;
	}
}

void inverterProf2(Lista * l) {
	No * aux = l->ini->prox, *aux2 = l->fim->ant;
	int i;

	for (i = 0; i < l->tam; i++) {
		No * ant1 = aux->ant, *prox1 = aux->prox;
		No * ant2 = aux2->ant, *prox2 = aux2->prox;

		aux->prox = prox2;
		aux->ant = ant2;
		aux2->prox = prox1;
		aux2->ant = ant1;
		ant1->prox = aux2;
		prox1->ant = aux2;
		ant2->prox = aux;
		prox2->ant = aux;
	}
}
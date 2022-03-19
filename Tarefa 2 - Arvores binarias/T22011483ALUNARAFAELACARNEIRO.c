/*
Maria Beatriz de Lima e Silva Sobreira - 2010953
Rafaela Maria Souza Carneiro - 2011483
*/

#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
	int altura;
	struct nodo* pai;
    struct nodo* esq;
    struct nodo* dir;
};
typedef struct nodo Nodo;

struct lista {
	Nodo* p_no;
	struct lista* corr;
	struct lista* prox;
};
typedef struct lista Fila;

Nodo* insereNo(Nodo* no, int val) {				// recebe uma arvore e um valor a ser inserido
    Nodo* aux;	
	static Nodo* p = NULL;
	if (!no) {									// se a arvore eh vazia, cria um no, coloca o valor nele e retorna
        aux = (Nodo*) malloc(sizeof(Nodo));
        aux->esq = NULL;
        aux->dir = NULL;
        aux->info = val;
		aux->pai = p;
        return aux;
    }
	else {
		p = no;
		if (no->info > val) {					// se o valor for menor que a raiz, ele vai entrar a esquerda
			no->esq = insereNo(no->esq, val);  	// entrando recursivamente na subarvore esquerda
		}
		else if (no->info <= val) {				// se o valor for maior/igual a raiz, ele vai entrar a direita
			no->dir = insereNo(no->dir, val);	// entrando recursivamente na subarvore direita
		}
	}
    return no;									// retorna a arvore com o valor inserido
}

void calcula_altura(Nodo* no){
	static int h;
	if (no == NULL)
		return;
	h++;
	calcula_altura(no->esq);
	calcula_altura(no->dir);
	h--;
	no->altura = h;
}

void percorre_em_nivel(Nodo* no){
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->p_no = no;                            // primeiro da fila apontando p raiz
    fila->prox = NULL;
    fila->corr = fila;
    Fila* ini = fila;
    while(ini) {
        if(no->esq){                            // se o no tem filho esquerdo
            fila->corr->prox = (Fila*) malloc(sizeof(Fila));
            fila->corr = fila->corr->prox;
            fila->corr->p_no = no->esq;
        }
        if(no->dir){                            // se o no tem filho esquerdo
            fila->corr->prox = (Fila*) malloc(sizeof(Fila));
            fila->corr = fila->corr->prox;
            fila->corr->p_no = no->dir;
        }
        
        printf("%d\n",ini->p_no->info);
        if (ini->prox == NULL)
            break;
        ini = ini->prox;
        no = ini->p_no;
    }
}

void exibe_arvore(Nodo* no){
    if (!no)
        return;
    exibe_arvore(no->esq);
    exibe_arvore(no->dir);
    printf("no = %p; chave = %d; altura = %d; pai = %p; esq = %p; dir = %p\n", no, no->info, no->altura, no->pai, no->esq, no->dir);
}

int main() {
	Nodo* arvore = NULL;
	int vetor[] = {15, 10, 20, 5, 18, 25, 16, 19, 22, 30, 21};
	int i; 
	for(i=0;i<11;i++) 
		arvore=insereNo(arvore, vetor[i]);	
	calcula_altura(arvore);
	printf("ITENS 1, 2 E 3 - exibindo arvore com ponteiro para o pai e altura dos nos\n");
	exibe_arvore(arvore);
	printf("******************************************\n");
	printf("ITEM 4 - percorrendo a arvore em nivel\n");
	percorre_em_nivel(arvore);
	return 0;
}
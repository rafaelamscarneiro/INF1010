#include <stdio.h>
#include <stdlib.h>

#define RET 0
#define TRI 1
#define CIR 2
#define PI 3.14156

struct retangulo {
	float b;
	float h;
};
typedef struct retangulo Retangulo;

struct triangulo {
	float b;
	float h;
};
typedef struct triangulo Triangulo;

struct circulo {
	float r;
};
typedef struct circulo Circulo;

struct lista_het {
	int tipo;
	void *info;
	struct lista_het *prox;
	struct lista_het *ant;
};
typedef struct lista_het ListaHet;

/* função para cálculo da área de um retângulo */
static float ret_area (Retangulo* r) {
	return r->b * r->h;
}
/* função para cálculo da área de um triângulo */
static float tri_area (Triangulo* t) {
	return (t->b * t->h) / 2;
}
/* função para cálculo da área de um círculo */
static float cir_area (Circulo* c) {
	return PI * c->r * c->r;
}

static float area (ListaHet* p) {
	float a;
	switch (p->tipo) {
		case RET:
			a = ret_area((Retangulo*)p->info);
			break;
		case TRI:
			a = tri_area((Triangulo*)p->info);
			break;
		case CIR:
			a = cir_area((Circulo*)p->info);
			break;
	}
	return a;
}

ListaHet * lista_cria() {
	return NULL;
}

ListaHet * lista_insere(ListaHet *lista, void *forma, int n) {
	ListaHet *novo = (ListaHet *)malloc(sizeof(ListaHet));
	novo->tipo = n;
	novo->info = forma;
	if (lista == NULL) {
		lista = novo;
		novo->prox = NULL;
		novo->ant = NULL;
		
	}
	else {
		lista->ant = novo;
		novo->prox = lista;
		novo->ant = NULL;
	}
	return novo;
}
void exibe(ListaHet *lista) {
	char *vet[] = {"RET", "TRI", "CIR"};
	printf("%s com area %.2f\n", vet[lista->tipo], area(lista));
}


void exibe_tudo(ListaHet *lista) {
	if (lista == NULL)
		printf("vazia\n");
	while (lista != NULL) {
		exibe(lista);
		lista = lista->prox;
	}
	return;
}

void exibe_area_maior(ListaHet *lista, float val) {
	while (lista) {
		if (area(lista) > val)
			exibe(lista);
		lista = lista->prox;
	}
}
ListaHet* lst2_busca (ListaHet* lst, int val)
{
    ListaHet* p;
    for (p=lst; p!=NULL; p=p->prox){
        if (area(p) <= val)
            return p;
    }
    return NULL; /* não achou o elemento */
}
/* função retira: remove elemento da lista */
ListaHet* lst2_retira (ListaHet* lst, int val)
{
    ListaHet* p = lst2_busca(lst,val); /* busca elemento */
    //printf("\narea(p) = %f\n",area(p));
    if (p == NULL)
        return lst; /* não achou: retorna lista inalterada */
    /* retira elemento (apontado por p) do encadeamento */
    if (lst == p) /* testa se é o primeiro elemento */
        lst = p->prox;
    else
        p->ant->prox = p->prox;
    if (p->prox != NULL)    /* testa se é o último elemento */
        p->prox->ant = p->ant;
    free(p);
    return lst;
}

void lst_imprime_rec_inv (ListaHet* lst)
{
    if (lst!=NULL) {
        /* imprime sub-lista */
        lst_imprime_rec_inv(lst->prox);
        /* imprime ultimo elemento */
        exibe(lst);
    }
}


int main() {
    int valor = 17; 
    //cria os retangulos
	Retangulo *ret1 = (Retangulo *) malloc(sizeof(Retangulo));
	ret1->b = 2;
	ret1->h = 7;
	Retangulo *ret2 = (Retangulo *) malloc(sizeof(Retangulo));
	ret2->b = 3;
	ret2->h = 8;
	//cria os triangulos
	Triangulo *tri1 = (Triangulo *) malloc(sizeof(Triangulo));
	tri1->b = 6;
	tri1->h = 2;
	Triangulo *tri2 = (Triangulo *) malloc(sizeof(Triangulo));
	tri2->b = 9;
	tri2->h = 5;
	//cria os circulos
	Circulo *cir1 = (Circulo *) malloc(sizeof(Circulo));
	cir1->r = 8;
	Circulo *cir2 = (Circulo *) malloc(sizeof(Circulo));
	cir2->r = 2;
	
	ListaHet *lista = lista_cria();
	//insere os retangulos
	lista = lista_insere(lista, ret1, RET);
	lista = lista_insere(lista, ret2, RET);
    //insere os triangulos
    lista = lista_insere(lista, tri1, TRI);
    lista = lista_insere(lista, tri2, TRI);
    //insere os circulos 
    lista = lista_insere(lista, cir1, CIR);
    lista = lista_insere(lista, cir2, CIR);
    
    printf("Item (c): Exibindo a estrutura completa, do inicio para o final:\n");
    exibe_tudo(lista); 
    printf("\nItem (d): Exibindo os elementos da lista com area maior do que o valor dado:\n");
    exibe_area_maior(lista, valor); 
    // retirando os elementos com area menor do que o valor dado
    lista = lst2_retira(lista,valor);
    lista = lst2_retira(lista,valor);
    lista = lst2_retira(lista,valor);
    printf("\nItem (f): Exibindo os a estrutura completa, do fim para o inicio:\n");
    lst_imprime_rec_inv(lista); 
	
	return 0;
}
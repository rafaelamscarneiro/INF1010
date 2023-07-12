static void corrige_abaixo(Heap* heap){
int pai=0;
while (2*pai+1 < heap->pos)				// o filho esquerdo for menor do que a proxima posicao vazia
{
	int filho_esq=2*pai+1;
	int filho_dir=2*pai+2;
	int filho;
	if (filho_dir >= heap->pos) filho_dir=filho_esq;				// se a pos do filho direito for maior/igual a 1a pos vazia do heap, entao ele nem existe
	if (heap->prioridade[filho_esq]>heap->prioridade[filho_dir])	// se filho esq > filho direito, temos que trocar o pai pelo filho esq
		filho=filho_esq;
	else															// senao, temos que trocar o pai pelo filho dir
		filho=filho_dir;											
	if (heap->prioridade[pai]<heap->prioridade[filho])				// se pai < filho, troca pai pelo filho
		troca(pai,filho,heap->prioridade);
	else															// senao, o heap ja ta direito
		break;
	pai=filho;														// desce
	}
}
/* Maria Beatriz de Lima e Silva Sobreira - 2010953
Rafaela Maria Souza Carneiro - 2011483 
*/

#include <stdio.h>
#include <time.h>
#include <string.h>

unsigned int hash2(char *str){
  return ((str[3]-'0')*1000+(str[4]-'0')*100+(str[5]-'0')*10+str[6]-'0') % 1109;
}

int main(){
	
    FILE* arq = fopen("placas.txt", "r");
    int res=1, indice, colisao=0, cont=0,n=100;
    struct timeval t1, t2;
    char placa[8];
	char tabela[1109][8];
	int i;
	for (i=0;i<1109;i++){
		tabela[i][0]='@';
	}
	gettimeofday(&t1, NULL);
	while(res){
		res = fread(placa, 8*sizeof(char), 1, arq);
		placa[7] = '\0';
		indice = hash2(placa);
		if(tabela[hash2(placa)][0] != '@'){
      		while(tabela[indice][0] != '@'){
        		indice = (indice+1) % 1109;        
      		}			
			colisao++;
		}
		strcpy(tabela[indice], placa);
		cont++;
		if(cont==100){
			gettimeofday(&t2, NULL);
    		printf("Tempo de execucao para inserir %d placas: %d microssegundos\n",n, (t2.tv_usec - t1.tv_usec));
   			cont=0;
   			n+=100;
		}
	}
    printf("Colisoes = %d\n", colisao);
	return 0;
}

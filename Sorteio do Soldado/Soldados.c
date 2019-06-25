#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct reg celula;
struct reg{
	int conteudo;
	celula *prox;
};

int iniciar(celula **inicio);
int insere (int x, celula **p, celula **ult);
int lista (celula *inicio);

int main (void) {
   int x = 10;
   int info, pos, sorteio;
   celula *ini;
   celula *ult;
   iniciar(&ini);
   
  time_t timer;
  struct tm *horarioLocal;
  
   
   while (x!=0)
   {
   	    system("cls");
   	    printf("ESCOLHA UMA OPCAO: ");
        printf("\n1- Inserir soldado.");
        printf("\n2- Soldados na lista.");
        printf("\n3- Sortear soldado.");
        printf("\n");
    	printf("Digite uma opcao: ");
   	    scanf("%d", &x);
   	
   	switch(x){
   		case 1:
   			printf("Insira um valor: \n");
   			scanf("%d", &info);
   			insere(info, &ini, &ult);
   			break;
   			
		case 2:
		    lista(ini);
		    printf("\n");
			system("pause");
			break;
		case 3:
			printf("Digite um numero: \n");
		    scanf("%d", &pos);
		    time(&timer); // Obtem informações de data e hora
            horarioLocal = localtime(&timer); // Converte a hora atual para a hora local
		    sorteio = horarioLocal->tm_sec;
		    remover(&ini, pos, sorteio);
		    system("pause");
		    x=0;
			break;			
	   }
   }
   
   return 0;
}
int iniciar (celula **inicio)
{
	*inicio= NULL;
	return 0; /* sem erro */
}

int insere (int x, celula **p, celula **ult)
{
   celula *nova, *aux;
   aux = *ult;
   nova = (celula *) malloc(sizeof (celula));
   nova->conteudo = x;
   if (*p==NULL)
   {    // insercao em lista vazia
	    nova->prox = nova;
	    *p = nova;
	    *ult = nova;
   }
   else
   {
   	    aux->prox = nova;
   	    nova->prox = *p;
   	    *p = nova;
   }
}

int remover (celula **inicio, int pos, int sorteio)
{
	int pos_aux = 0, i;
	celula *aux, *proximo;
	aux = *inicio;
	for(i=0;i<sorteio;i++)
	{
		aux = aux->prox;
	}
	
	printf("Soldado sorteado: %d\n", aux->conteudo);
	
	while(aux->prox!=aux)
	{
     	while(pos_aux!=(pos-1))
	    {
		pos_aux++;
		aux = aux->prox;
	    }  
        proximo = aux->prox; 
    	aux->prox = proximo->prox;
    	printf("Soldado excluido: %d\n", proximo->conteudo);
		free(proximo);
		aux = aux->prox;
    }
    
    printf("Soldado escolhido: %d\n", aux->conteudo);
}

int lista (celula *inicio)
{
	celula *aux = inicio;
	if (inicio==NULL) //LISTA COM UM ELEMENTO
	{
		return 1;
	}
	else
	{
		do
	   {
	        printf("|%d|", aux->conteudo);
		    aux = aux->prox;		
	   }while(aux!=inicio);
	   
    }
}

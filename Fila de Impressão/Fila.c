#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct celula {
	int conteudo;
	char nome[20];
	struct celula *prox;
} Celula;

int iniciar(Celula **inicio);
int insere (int x, char n[], Celula **p, int tam);
int lista (Celula *inicio, int tam);
int tamanho (Celula *inicio);

int main (void) {
   int x = 10;
   char nome[20];
   int info, tam;
   Celula *ini;
   iniciar(&ini);


   while (x!=0)
   {
   		tam = tamanho(ini);
   	    system("cls");
   	    printf("ESCOLHA UMA OPCAO: ");
        printf("\n1- Enviar impressao.");
        printf("\n2- Lista de impressoes.");
        printf("\n");
    	printf("Digite uma opcao: ");
    	scanf("%d", &x);

   	switch(x){
   		case 1:
   			printf("Insira o nome: \n");
   			scanf("%s", nome);
   			fflush(stdin);
   			printf("Insira o nivel de prioridade: \n");
   			scanf("%d", &info);
			if(info != 1 && info != 2 && info != 3) printf("Prioridade invalida.");
   			else insere(info, nome, &ini, tam);
   			break;

		case 2:
		    lista(ini, tam);
		    printf("\n");
			system("pause");
			break;
	   }
   }

   return 0;
}
int iniciar (Celula **inicio)
{
	*inicio= NULL;
	return 0; /* sem erro */
}

int insere (int x, char n[], Celula **p, int tam)
{
   Celula *nova, *aux, *ant;
   nova = (Celula *) malloc(sizeof (Celula));
   nova->conteudo = x;
   strcpy(nova->nome,n);
   aux = *p;

   	if (tam==0)
    {
    	nova->prox = NULL;
    	*p = nova;
    }
    else if (tam==1)
    {
    	if(aux->conteudo > x)
    	{
    		aux->prox = nova;
    		nova->prox = NULL;
		}
		else
		{
			*p=nova;
			nova->prox = aux;
		}
    }
    else
    {
    	if (x == 3)
    	{
    		nova->prox = aux;
    		*p = nova;
		}
		while(x < aux->conteudo)
    	{
    		ant = aux;
    		aux = aux->prox;
	 }

		ant->prox = nova;
		nova->prox = aux;
   	}
}

int lista (Celula *inicio, int tam)
{
	if (inicio==NULL) //LISTA COM UM ELEMENTO
	{
		return 1;
	}
	else
	{
		while(inicio!=NULL)
	   {

			printf("%d - %s ", tam, inicio->nome);
			switch(inicio->conteudo)
			{
				case 1:
					printf("- Diretor\n");
					break;
				case 2:
					printf("- Gerente\n");
					break;
				case 3:
					printf("- Auxiliar\n");
					break;
			}
		    inicio = inicio->prox;
			tam--;
	   }

    }
}

int tamanho (Celula *inicio)
{
	int x = 0;
	if (inicio==NULL) return 0;
	else
	{
		while(inicio!=NULL)
			{
				x++;
				inicio = inicio->prox;
			}
		return x;
	}
}

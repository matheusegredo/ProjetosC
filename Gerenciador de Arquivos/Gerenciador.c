/*
Nome: Enzo Eduardo - RA:201710074
Nome: Felipe Alves - RA:201710627
Nome: Matheus Segredo - RA:201710576
Nome: Ricieri Martins - RA:201710069
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gerenciador {
	int id;
	int altura;
	char data[9];
	char hora[9];
	char nome[20];
	struct gerenciador *prox;
} Gerenciador;

typedef struct caminho
{
	int num;
	struct caminho *prox;
} Caminho;

struct Usuarios
{
	char user[8];
	struct gerenciador *end;
	int id;
	int status;
};

struct Usuarios usuarios[10];

/*******************USUARIOS*******************/
int acesso(char user[], int *id_user, Gerenciador **inicio, Gerenciador **atual);
int cadastro(int id_user, int id, char user[]);
int delete(int id_user, int id, char user[]);
int dados(char user[]);
int lista_usuarios();
int bloquear(char user[], int j);
int carrega_usuarios(int *id);

/******************GERENCIADOR*****************/
int iniciar(Gerenciador **inicio, Gerenciador **atual);
int insere (int x, char n[], Gerenciador *atual);
int tree (Gerenciador *inicio);
int remover (Gerenciador *atual, char pasta[]);
int acessar (Gerenciador **atual, char pasta[], Gerenciador *ini, Caminho *percorre);
int listar (Gerenciador *atual, char user[]);
int iniciar_caminho(Caminho **inicio);
int pwd(Caminho *caminho, Gerenciador *pasta, int x);
int grava(Gerenciador *inicio, char user[]);


int main(int argc, char *argv[]) {

	char command[10], diretorio[10];
	int x = 10, i;
    char nome[20], user[8];
    char data[9], hora[9];
    int info=0, tam, id=1, status=1;
    char user_atual[8];
    int id_user;
    Gerenciador *ini, *atual;
    Caminho *prim;
    int pin, opc=0;

    carrega_usuarios(&id);

    iniciar(&ini, &atual);
    iniciar_caminho(&prim);

    while(status!=0)
	{
		printf(":::::::::::::::::GERENCIADOR DE ARQUIVOS:::::::::::::::::\n");
		printf(":::::::::::ESCOLA DE ENGENHARIA DE PIRACICABA::::::::::::\n");
		printf("Login: ");
		scanf("%s", user);
		strlwr(user);
		status = acesso(user, &id_user, &ini, &atual);
		if(status==2) 
			{
				printf("Usuario bloqueado. Acesso como root para desbloquear\n");
				system("pause");
			}
		else system("cls");
	}
	

	while(opc!=1)
	{
		pwd(prim, ini, 1);
		printf(">");
		scanf("%s", command); // A função scanf interrompe a leitura ao encontrar o primeiro espaço em branco
		gets(diretorio);     // E como o scanf já armazenou o comando antes do espaço em branco, o gets pega o restante.
		int x=0, h=0, aux=1;

		for (i=0;i<10;i++) diretorio[i] = diretorio[i+1]; // O gets pega tudo após o espaço em branco, incluindo o mesmo, então nesse for corrigimos isso.

		if (strcmp(command,"mkdir")==0)
		{
			info++;
   			insere(info, diretorio, atual);
		}
		else if (strcmp(command,"rmdir")==0) remover(atual, diretorio);

		else if (strcmp(command,"cd")==0) acessar(&atual, diretorio, ini, prim);

		else if (strcmp(command,"ls")==0) listar(atual, user);

		else if(strcmp(command,"tree")==0) tree(ini);

		else if (strcmp(command,"pwd")==0) pwd(prim, ini, 0);

		else if(strcmp(command,"adduser")==0) id = cadastro(id_user, id, diretorio);
		
		else if(strcmp(command,"deluser")==0) id = deletar(id_user, id, diretorio);

		else if(strcmp(command,"id")==0) dados(diretorio);

		else if(strcmp(command,"lock")==0) id_user == 0 ? bloquear(diretorio, id) : printf("Usuario sem permissao\n");
		
		else if(strcmp(command,"unlock")==0) id_user == 0 ? bloquear(diretorio, id) : printf("Usuario sem permissao\n");
		
		else if(strcmp(command,"date")==0) printf("%s\n", _strdate(data));
		
		else if(strcmp(command,"time")==0) printf("%s\n", _strtime(hora));
		
		else if(strcmp(command,"clear")==0) system("cls");
		
		else if(strcmp(command,"copyright")==0) printf("Nome: Enzo Eduardo - RA:201710074\nNome: Felipe Alves - RA:201710627\nNome: Matheus Segredo - RA:201710576\nNome: Ricieri Martins - RA:201710069\n");
			
		else if (strcmp(command,"poweroff")==0)
        {
            if(id_user==0)
			{
            	printf("Encerrando...");
            	grava(ini, user);
            	opc=1;
			}
			else printf("Usuario sem permissao\n");
		}

		else if(strcmp(command,"logout")==0)
		{
			status=1;
				system("cls");
				grava(ini, user);
				acessar(&atual, "/", ini, prim);
				while(status!=0)
				{
					printf(":::::::::::::::::GERENCIADOR DE ARQUIVOS:::::::::::::::::\n");
					printf(":::::::::::ESCOLA DE ENGENHARIA DE PIRACICABA::::::::::::\n");
					printf("Login: ");
					scanf("%s", user);
					strlwr(user);
					status = acesso(user, &id_user, &ini, &atual);
					if(status==2) 
					{
						printf("Usuario bloqueado. Acesso como root para desbloquear\n");
						system("pause");
					}					
					else system("cls");
				}
				
		}

		else printf("Comando nao encontrado\n");

	}
	return 0;
}

int pwd(Caminho *caminho, Gerenciador *pasta, int x)
{
	while(caminho!=NULL)
	{
		if(caminho->num==pasta->id)
		{
			printf("/%s", pasta->nome);
			caminho=caminho->prox;
		}
		pasta=pasta->prox;
	}
	if(x==0) printf("\n");
}

int acessar(Gerenciador **atual, char pasta[], Gerenciador *ini, Caminho *percorre)
{
	int erro=1;
	Gerenciador *inicio;
	Caminho *aux, *nova;
	inicio = *atual;

	if (strcmp(pasta,"/")==0)
	{
		if(inicio->id!=0)
		{
			*atual = ini;
			aux=percorre;
			percorre=percorre->prox;
			aux->prox=NULL;
			percorre=percorre->prox;
			while(percorre!=NULL)
			{
				aux = percorre;
				percorre=percorre->prox;
				free(aux);
			}
		}
		erro = 0;
	}
	else if(strcmp(pasta,"..")==0)
	{
		if((*atual)->id==0) return;

		while(percorre->prox!=NULL)
		{
			aux=percorre;
			percorre=percorre->prox;
		}
		while(ini->id!=aux->num) ini=ini->prox;
		*atual = ini;
		aux->prox = NULL;
		free(percorre);
		erro = 0;
	}
	else
	{
		while(inicio!=NULL)
		{
			if (inicio->altura==(*atual)->altura+1)
			{
				if (strcmp(inicio->nome,pasta)==0)
				{
					*atual=inicio;
					while(percorre->prox!=NULL) percorre=percorre->prox;
					nova = (Caminho *) malloc(sizeof (Caminho));
					nova->prox=NULL;
					nova->num=inicio->id;
					percorre->prox = nova;
					erro=0;
					break;
				}
			}
			inicio = inicio->prox;
		}
	}

	if(erro==1) printf("Diretorio nao encontrado.\n");

	return;
}

int iniciar_caminho(Caminho **inicio)
{
	*inicio = (Caminho *) malloc(sizeof (Caminho));
	(*inicio)->num = 0;
	(*inicio)->prox = NULL;
}

int iniciar(Gerenciador **inicio, Gerenciador **atual)
{
	int id, altura, i=0;
	Gerenciador *nova, *ant;
	char nome[20], data[9];
	FILE *arq;
	arq=fopen("root","r");
	*inicio = (Gerenciador *) malloc(sizeof (Gerenciador));
	ant = *inicio;
	usuarios[0].id=0;
	usuarios[0].end= *inicio;
	usuarios[0].status=0;
	strcpy(usuarios[0].user,"root");
	if(arq)
	{
		while((fscanf(arq,"%d %s %s %d", &id, nome, data, &altura))!=EOF)
		{
			if(i==0)
			{
				strcpy((*inicio)->nome,nome);
				(*inicio)->altura = altura;
				(*inicio)->id = id;
				(*inicio)->prox = NULL;
				_strdate((*inicio)->data);
				_strtime((*inicio)->hora);
				*atual = *inicio;
				i=1;
			}
			else
			{
				nova = (Gerenciador *) malloc(sizeof (Gerenciador));
				strcpy(nova->nome, nome);
				nova->altura = altura;
				nova->id = id;
				nova->prox = NULL;
				_strdate(nova->data);
				_strtime(nova->hora);
				ant->prox = nova;
				ant = nova;
			}
		}
	}
	else
	{
		strcpy((*inicio)->nome,"root");
		(*inicio)->altura = 0;
		(*inicio)->id = 0;
		(*inicio)->prox = NULL;
		_strdate((*inicio)->data);
		_strtime((*inicio)->hora);
		*atual = *inicio;
	}

	fclose(arq);

	return 0; /* sem erro */
}

int insere(int x, char n[], Gerenciador *atual)
{
   Gerenciador *nova, *percorre;
   percorre = atual->prox;
   int erro=0;

   while(percorre!=NULL)
   {
   		if(percorre->altura==atual->altura+1)
   		{
   			if(strcmp(percorre->nome,n)==0)
			{
				erro = 1;
   				break;
   			}
		}
		percorre = percorre->prox;
   }
   if(erro==1) printf("Diretorio ja existente.\n");
   else
   {
        nova = (Gerenciador *) malloc(sizeof (Gerenciador));
   		nova->id = x;
   		_strdate(nova->data);
   		_strtime(nova->hora);
   		strcpy(nova->nome,n);
   		nova->prox = atual->prox;
   		atual->prox = nova;
   		nova->altura = atual->altura + 1;
	}
}

int remover(Gerenciador *atual, char pasta[])
{
	Gerenciador *aux, *ant;
	aux = atual->prox;
	ant = atual;
	int erro = 1;

	if(aux->prox==NULL)
	{
		atual->prox = NULL;
		free(aux);
	}
	else
	{
		while(aux!=NULL)
		{
			if(aux->altura==atual->altura+1)
			{
				if(strcmp(aux->nome,pasta)==0)
				{
					if(aux->prox==NULL) erro = 0;
					else if(aux->altura<(aux->prox)->altura) erro = 2;
					else erro = 0;
					break;
				}
			}
			ant = aux;
			aux = aux->prox;
		}

		if(erro==1) printf("Diretorio inexistente\n");
		else if(erro==2) printf("Diretorio precisa estar vazio\n");
		else
		{
			ant->prox = aux->prox;
			free(aux);
		}
	}
}

int tree(Gerenciador *inicio)
{
	int i;
	if (inicio==NULL) //LISTA COM UM ELEMENTO
	{
		return 1;
	}
	else
	{
		while(inicio!=NULL)
	   {
	        for(i=0;i<inicio->altura;i++)
			{
				printf("|");
				if (i==inicio->altura-1) printf("-----");
				else printf("     ");
			}
			printf("%s\n", inicio->nome);
			inicio = inicio->prox;
	   }

    }
}

int listar(Gerenciador *atual, char user[])
{
	Gerenciador *aux;

	if (atual->prox==NULL) printf("Diretorio vazio.\n", atual->nome);
	else
	{
	 	aux = atual->prox;
		//printf("%s\n", atual->nome);
		while(aux->altura>atual->altura)
		{
		    if(aux->altura==atual->altura+1) printf("	%s	%s - %s	%s\n", aux->nome, aux->data, aux->hora, user);
			aux = aux->prox;
			if(aux==NULL) break;
		}
	}
}

int grava(Gerenciador *inicio, char user[])
{
	FILE *arq;
	char id[3];
	char altura[3];
	char idu[20];
    char nomeu[20];
    char datau[20];
    char altu[20];
	int i;

    if(!(arq=fopen(user,"w")))
    {
        printf("Erro ao salvar o arquivo !\n");
    	exit(1);
    }
    else
    {
    	strcpy(idu  , " ");
    	strcpy(nomeu, " ");
    	strcpy(datau, " ");
    	strcpy(altu , " ");
    }

		while(inicio!=NULL)
	   {
	       		sprintf(id, "%i", inicio->id);
                sprintf(altura, "%i", inicio->altura);
                strcat(altura, "\n" );
                fputs(id,arq);
                fputs(strcat(nomeu, inicio->nome), arq);
                fputs(strcat(datau, inicio->data), arq);
                fputs(strcat(altu, altura), arq);
     			strcpy(idu  , " ");
                strcpy(nomeu, " ");
                strcpy(datau, " ");
                strcpy(altu , " ");
                inicio = inicio->prox;
        }
	fclose(arq);
}

/*****************USUARIOS*******************/

int acesso(char user[], int *id_user, Gerenciador **inicio, Gerenciador **atual)
{
	int i, x=0, login=1;
	int id, altura;
	char nome[20], data[9];
	Gerenciador *nova, *ant;
	FILE *arq;
	arq=fopen(user,"r");
	
	 for(i=0;i<10;i++)
		{
			if(strcmp(usuarios[i].user, user)==0)
			{
				if(usuarios[i].status==1)
				{
					login=2;					
					break;
				}
				if(usuarios[i].status==3) break;
				else
				{
					login=0;
                    *inicio = (Gerenciador *) malloc(sizeof (Gerenciador));
                    ant = *inicio;
                    if(arq)
                    {
                        while((fscanf(arq,"%d %s %s %d", &id, nome, data, &altura))!=EOF)
                        {
                            if(x==0)
                            {
                                strcpy((*inicio)->nome,nome);
                                (*inicio)->altura = altura;
                                (*inicio)->id = id;
                                (*inicio)->prox = NULL;
                                _strdate((*inicio)->data);
                                _strtime((*inicio)->hora);
                                *atual = *inicio;
                                x=1;
                            }
                            else
                            {
                                nova = (Gerenciador *) malloc(sizeof (Gerenciador));
                                strcpy(nova->nome, nome);
                                nova->altura = altura;
                                nova->id = id;
                                nova->prox = NULL;
                                _strdate(nova->data);
                                _strtime(nova->hora);
                                ant->prox = nova;
                                ant = nova;
                            }
                        }
                    }
                else
                    {
                        strcpy((*inicio)->nome,user);
                        (*inicio)->altura = 0;
                        (*inicio)->id = 0;
                        (*inicio)->prox = NULL;
                        _strdate((*inicio)->data);
                        _strtime((*inicio)->hora);
                    }

                    *id_user = i;
                    usuarios[i].end = *inicio;
                    *atual = *inicio;
                }
            break;
            }
		 }       
   
    return login;
}

int cadastro(int id_user, int id, char user[])
{
	FILE *arq;
	int x, i, cond=1;
	Gerenciador *nova;
	strlwr(user);
	if(usuarios[id_user].id==0)
	{
			for(i=0;i<10;i++)
			{
				if(strcmp(usuarios[i].user,user)==0)
				{
					if(usuarios[i].status!=3)
					{
						printf("Usuario ja cadastrado.\n");
						return;
				 }
					else 
					{
						usuarios[i].status = 0;
						cond=0;
					}
				}
			}
			
			if(cond==1)
			{
				nova = (Gerenciador *) malloc(sizeof (Gerenciador));
				nova->prox=NULL;
				strcpy(usuarios[id].user, user);
				usuarios[id].end = nova;
				usuarios[id].id = id;
				usuarios[id].status=0;
				strcpy(nova->nome,user);
				nova->altura = 0;
				nova->id = 0;
				_strdate(nova->data);
				_strtime(nova->hora);
				id++;
			}
			
			if(!(arq=fopen("users","w")))
			{
				printf("Erro ao salvar o arquivo !\n");
			}
			else
			{
				for(i=0;i<id;i++)
				{
					fprintf(arq, "%s %d %d\n", usuarios[i].user, usuarios[i].id, usuarios[i].status);
				}
			}
			
			printf("Usuario cadastrado com sucesso!\n");			
	}
	else printf("Usuario sem permissao\n");
	
	fclose(arq);
	return id;
}

int deletar(int id_user, int id, char user[])
{
	FILE *arq;
	int x, i;
	Gerenciador *nova;
	strlwr(user);
	arq=fopen("users", "w");
	if(usuarios[id_user].id==0)
	{
		for(i=0;i<id;i++)
		{
			if(strcmp(usuarios[i].user,user)==0)
			{
				usuarios[i].end = NULL;
				usuarios[i].status=3;		
						
				if(!(arq=fopen("users","w")))
				{
					printf("Erro ao salvar o arquivo !\n");
				}
				else
				{
					for(i=0;i<id;i++)
					{
						fprintf(arq, "%s %d %d\n", usuarios[i].user, usuarios[i].id, usuarios[i].status);
					}
				}
				
				printf("Usuario excluido com sucesso!\n");
				remove(user);			
			}
		}
	}
	else printf("Usuario sem permissao\n");
	
	fclose(arq);
	return id;
}

int dados(char user[])
{
	Gerenciador *teste;
	strlwr(user);
	int i, erro=1;
	for(i=0;i<10;i++)
	{
		if(strcmp(usuarios[i].user, user)==0)
		{
			erro = 0;
			if(usuarios[i].status==3) erro=2;
			break;
		}
	}
	teste=usuarios[i].end;

	if(erro==0)	printf("Ola %s.\nID:%d\nStatus:%d\n", usuarios[i].user, usuarios[i].id, usuarios[i].status);
	else if(erro==2) printf("Usuario excluido\n");
	else printf("Usuario nao encontrado\n");
}
	
int lista_usuarios()
{
	int i;
	for(i=0;i<10;i++) printf("ID: %d | Nome: %s | Endereco: %d | Status: %d\n", usuarios[i].id, usuarios[i].user, usuarios[i].end, usuarios[i].status);
	system("pause");
}

int bloquear(char user[], int j)
{
	FILE *arq;
	int i, erro=1;
	arq=fopen("users", "w");
	for(i=0;i<10;i++)
	{
		if(strcmp(usuarios[i].user, user)==0)
		{
			erro=0;
			break;
		}
		erro = 1;
	}
	if(erro==0)
		{
			if(usuarios[i].status==1) usuarios[i].status=0;
			else usuarios[i].status=1;
			
			for(i=0;i<j;i++)
			{
				fprintf(arq, "%s %d %d\n", usuarios[i].user, usuarios[i].id, usuarios[i].status);
			}
		}	
	else printf("Usuario inexistente\n");
}

int carrega_usuarios(int *id)
{
	FILE *arq;
	int i=0, id_user, status;
	char user[8];
	arq=fopen("users","r");
	if(arq)
	{
		while((fscanf(arq,"%s %d %d", user, &id_user, &status))!=EOF)
		{
			strcpy(usuarios[i].user, user);
			usuarios[i].id = id_user;
			usuarios[i].status = status;			
 			i++;
		}
		*id = i;
	}
	else
	{
		fclose(arq);
		//char root="root 0 0";
		if(!(arq=fopen("users","w")))
    	{
        	printf("Erro ao salvar o arquivo !\n");
    		exit(1);
    	}
   		else
   		{
   	 		fputs("root 0 0\n", arq);
    	}
		fclose(arq);
	}
}

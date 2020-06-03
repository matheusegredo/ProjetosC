// Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
// Define uma constante
// Define a constant
#define MAX 100
 
// Protótipo da função de ordenação
// Ordination function prototype
void shellsort_Shell(int *vet, int *vet_ini, int count);
void shellsort_Knuth(int *vet, int *vet_ini, int count);
void shellsort_Hibbards(int *vet, int *vet_ini, int count);
void MontaVetor(int *vet, int *vet_ini, int *tam);
void shellsort_ShellRapida(int *vet, int *vet_ini, int count);
void shellsort_KnuthRapida(int *vet, int *vet_ini, int count);

void delay(float number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
} 
 
// Função main
// Main Function
int main(int argc, char** argv)
{
 int i, vet[MAX], vet_ini[MAX], opc = 1, tam;
 int opc_exb;
 
 while(opc!=0)
 {
    system("cls");
	printf("Escolha o metodo de execucao: \n");
    printf("1. Metodo Shell.\n2. Metodo Knuth\n3. Metod Hibbards\n0. Encerrar.\n");
    scanf("%d", &opc);
 
     switch(opc)
     {
         case 1:
            system("cls");
            MontaVetor(vet, vet_ini, &tam);
            printf("Escolha o metodo de exibicao: \n");
            printf("1. Rapida.\n2. Passo-a-Passo\n");
            printf("OPC: ");
            scanf("%d", &opc_exb);
            
            if (opc_exb == 1) shellsort_Shell(vet, vet_ini, tam);
            else shellsort_ShellRapida(vet, vet_ini, tam);
            printf("\n");
            system("pause");
            break;
        case 2:
            system("cls");
            MontaVetor(vet, vet_ini, &tam);
            printf("Escolha o metodo de exibicao: \n");
            printf("1. Rapida.\n2. Passo-a-Passo\n");
            printf("OPC: ");
            scanf("%d", &opc_exb);
            
            
            if (opc_exb == 1) shellsort_Knuth(vet, vet_ini, tam);
            else shellsort_KnuthRapida(vet, vet_ini, tam);     
			printf("\n");       
            system("pause");
            break;
        case 3:
            system("cls");
            MontaVetor(vet, vet_ini, &tam);   
            shellsort_Hibbards(vet, vet_ini, tam);               
			printf("\n");       
            system("pause");
            break;
     }
 }

 return 0;
}
 
void MontaVetor(int *vet, int *vet_ini, int *tam)
{
    int tam_vetor, i;
    srand(time(NULL));
    
    printf("Escolha o tamanho do vetor(0 - 100): ");
    scanf("%d", &tam_vetor);
    
    *tam = tam_vetor;    
    system("cls");
    printf("Vetor inicial: \n");
    for(i=0;i<tam_vetor;i++)
    {
        vet[i] = rand() % 100;
        vet_ini[i] = vet[i];
        printf("[%d]", vet[i]);
    }
    printf("\n");
    system("pause");
    system("cls");    
}

void shellsort_Shell(int *vet, int *vet_ini, int count) 
{
    int i , j , value, x, passos=0, vtroca = 0; 
    int gap = count; 
    
    while ( gap > 1) 
    { 
        gap /= 2;
        printf("Salto = %d\n\n", gap);
        
        for(i = gap; i < count; i++) 
        { 
            passos++;
            value = vet[i]; 
            j = i - gap;
            int posini = i;
            int posfim = j;
            int troca = 0;
            while (j >= 0 && value < vet[j]) 
            { 
                vet [j + gap] = vet[j];
                j -= gap;
                troca = 1;
			} 
            vet [j + gap] = value;
            for(x = 0; x < count; x++)
            {
                if (x == posini || x == posfim)
                {
                    printf("[*%d]", vet[x]);
                }
                else
                {
                    printf("[%d]", vet[x]);
                }
            }
            printf(" Passo nr.: %d -", passos);
            if (troca == 1)
            {
                printf(" Houve troca.\n");
                vtroca++;
            }
            else
            {
                printf(" Nao houve troca.\n");
            }
            printf("\n");
        } 
    }
    
    printf("ANALISE FINAL:\n");    
    printf("PASSOS: %d\n", passos);
    printf("TROCAS: %d\n", vtroca);
    printf("VETOR INICIAL: ");    
    for(x=0;x<count;x++) printf("[%d]", vet_ini[x]);
    printf("\nVETOR ORDENADO: ");
    for(x=0;x<count;x++) printf("[%d]", vet[x]);
}

void shellsort_ShellRapida(int *vet, int *vet_ini, int count) 
{
    int i , j , value, x, passos=0, vtroca = 0; 
    int gap = count; 
    
    while ( gap > 1) 
    { 
        gap /= 2;
                
        for(i = gap; i < count; i++) 
        { 
            passos++;
            value = vet[i]; 
            j = i - gap;
            int posini = i;
            int posfim = j;
            int troca = 0;
            while (j >= 0 && value < vet[j]) 
            { 
                vet [j + gap] = vet[j];
                j -= gap;
                troca = 1;
			} 
            vet [j + gap] = value;            
        	printf("Salto = %d\n\n", gap);
            for(x = 0; x < count; x++)
            {
                if (x == posini || x == posfim)
                {
                    printf("[*%d]", vet[x]);                    
                }
                else
                {
                    printf("[%d]", vet[x]);
                }
            }
            //for(x=0; x<10000; x++) printf("");
            if (troca == 1)
            {
                printf(" \nHouve troca.");    
				vtroca++;            
            }
            else
            {
                printf(" \nNao houve troca.");
            }
            delay(0.4);
            system("cls");           

        } 
    }
    
    printf("ANALISE FINAL:\n");
    printf("PASSOS: %d\n", passos);
    printf("TROCAS: %d\n", vtroca);
    printf("VETOR INICIAL: ");    
    for(x=0;x<count;x++) printf("[%d]", vet_ini[x]);
    printf("\nVETOR ORDENADO: ");
    for(x=0;x<count;x++) printf("[%d]", vet[x]);
}

void shellsort_Knuth(int *vet, int *vet_ini, int count) 
{
    int i , j , value, x, passos=0, vtroca = 0; 
    int gap = 1; 
    while(gap < count) 
    { 
        gap = 3*gap+1; 
    }
    while ( gap > 1) 
    { 
        gap /= 3;        
        printf("Salto = %d\n\n", gap);        
        for(i = gap; i < count; i++) 
        { 
            passos++;
            value = vet[i]; 
            j = i - gap;
            int posini = i;
            int posfim = j;
            int troca = 0;
            while (j >= 0 && value < vet[j]) 
            { 
                vet [j + gap] = vet[j];
                j -= gap;
                troca = 1;
			} 
            vet [j + gap] = value;
            for(x = 0; x < count; x++)
            {
                if (x == posini || x == posfim)
                {
                    printf("[*%d]", vet[x]);
                }
                else
                {
                    printf("[%d]", vet[x]);
                }
            }
            printf(" Passo nr.: %d -", passos);
            if (troca == 1)
            {
                printf(" Houve troca.\n");
                vtroca++;
            }
            else
            {
                printf(" Nao houve troca.\n");
            }
            printf("\n");
        }
    } 
    printf("ANALISE FINAL:\n");
    printf("PASSOS: %d\n", passos);
    printf("TROCAS: %d\n", vtroca);
    printf("VETOR INICIAL: ");    
    for(x=0;x<count;x++) printf("[%d]", vet_ini[x]);
    printf("\nVETOR ORDENADO: ");
    for(x=0;x<count;x++) printf("[%d]", vet[x]);
}

void shellsort_KnuthRapida(int *vet, int *vet_ini, int count) 
{
    int i , j , value, x, passos=0, vtroca = 0; 
    int gap = 1;
    while(gap < count) 
    { 
        gap = 3*gap+1; 
    }
    
    while ( gap > 1) 
    { 
        gap /= 3;
                
        for(i = gap; i < count; i++) 
        { 
            passos++;
            value = vet[i]; 
            j = i - gap;
            int posini = i;
            int posfim = j;
            int troca = 0;
            while (j >= 0 && value < vet[j]) 
            { 
                vet [j + gap] = vet[j];
                j -= gap;
                troca = 1;
			} 
            vet [j + gap] = value;            
        	printf("Salto = %d\n\n", gap);
            for(x = 0; x < count; x++)
            {
                if (x == posini || x == posfim)
                {
                    printf("[*%d]", vet[x]);                    
                }
                else
                {
                    printf("[%d]", vet[x]);
                }
            }
            //for(x=0; x<10000; x++) printf("");
            if (troca == 1)
            {
                printf(" \nHouve troca.");    
				vtroca++;            
            }
            else
            {
                printf(" \nNao houve troca.");
            }
            delay(0.4);
            system("cls");  
        } 
    }
    
    printf("ANALISE FINAL:\n");
    printf("PASSOS: %d\n", passos);
    printf("TROCAS: %d\n", vtroca);
    printf("VETOR INICIAL: ");    
    for(x=0;x<count;x++) printf("[%d]", vet_ini[x]);
    printf("\nVETOR ORDENADO: ");
    for(x=0;x<count;x++) printf("[%d]", vet[x]);
}

void shellsort_Hibbards(int *vet, int *vet_ini,int count)
{
    int i , j, h, value, x, passos=0, vtroca = 0, aux = 0;
    int gap[100], hibbards = 1, hibbards_count = 0;
    
  while(pow(2,hibbards) - 1 < count - 1)
  {
    gap[hibbards] = pow(2,hibbards) - 1;      
    hibbards++;   
  }
   
    hibbards--;    
    while (gap[hibbards] >= 1)
    {
        printf("---------------------------------------//--------------------------------------\n");        
        printf("Salto = %d\n\n", gap[hibbards]);
        for(i = gap[hibbards]; i < count; i++)
        {
            passos++;
            value = vet[i];
            j = i - gap[hibbards];
            int posini = j;
            int posfim = i;
            int troca = 0;
            while (j >= 0 && value < vet[j])
            {
                vet [j + gap[hibbards]] = vet[j];
                j -= gap[hibbards];
                troca = 1;
            }
            vet [j + gap[hibbards]] = value;
            for(x = 0; x < count; x++)
            {
                if (x == posini || x == posfim)
                {
                    printf("[*%d]", vet[x]);
                }
                else
                {
                    printf("[%d]", vet[x]);
                }
            }
            printf(" Passo nr.: %d -", passos);
            if (troca == 1)
            {
                printf(" Houve troca.\n");
                vtroca++;
            }
            else
            {
                printf(" Nao houve troca.\n");
            }
            printf("\n");           
        }
        hibbards--;
    }
   
    printf("ANALISE FINAL:\n");
    printf("PASSOS: %d\n", passos);
    printf("TROCAS: %d\n", vtroca);
    printf("\nVETOR INICIAL: ");
    for(x=0;x<count;x++) printf("[%d]", vet_ini[x]);
    printf("\nVETOR ORDENADO: ");
    for(x=0;x<count;x++) printf("[%d]", vet[x]);
}


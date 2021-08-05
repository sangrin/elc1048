#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void thread_01(void);
void thread_02(void);
void thread_03(void);
void thread_04(void);
void thread_05(void);
void thread_06(void);
void suspende_threads(void);

//void produtor(void);
//void consumidor(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3     	(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4     	(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5     	(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6     	(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_SUS     	(TAM_MINIMO_PILHA + 24)


//#define TAM_PILHA_PRODUTOR     	(TAM_MINIMO_PILHA + 24)
//#define TAM_PILHA_CONSUMIDOR   	(TAM_MINIMO_PILHA + 24)
//#define TAM_BUFFER 10




#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_5[TAM_PILHA_5];
uint32_t PILHA_TAREFA_6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_SUS[TAM_PILHA_SUS];


//tarefa produtor-consumidor
//uint32_t PILHA_PRODUTOR[TAM_PILHA_PRODUTOR];
//uint32_t PILHA_CONSUMIDOR[TAM_PILHA_CONSUMIDOR];
//uint32_t buffer[TAM_BUFFER];
//uint8_t i=0;
//uint8_t f=0;

//semáforos
//semaforo_t cheio;
//semaforo_t vazio;

uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];



/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(thread_01, "Thread 1", PILHA_TAREFA_1, TAM_PILHA_1, 5);
	
	CriaTarefa(thread_02, "Thread 2", PILHA_TAREFA_2, TAM_PILHA_2, 4);
        
        CriaTarefa(thread_03, "Thread 3", PILHA_TAREFA_3, TAM_PILHA_3, 3);
        
        CriaTarefa(thread_04, "Thread 4", PILHA_TAREFA_4, TAM_PILHA_4, 2);
        
        CriaTarefa(thread_05, "Thread 5", PILHA_TAREFA_5, TAM_PILHA_5, 1);
         
        CriaTarefa(thread_06, "Thread 6", PILHA_TAREFA_6, TAM_PILHA_6, 6);
         
        CriaTarefa(suspende_threads, "Suspende Threads", PILHA_TAREFA_SUS, TAM_PILHA_SUS, 7); 

         
         
//        CriaTarefa(produtor, "Produtor", PILHA_PRODUTOR, TAM_PILHA_PRODUTOR, 2);
//        
//        CriaTarefa(consumidor, "Consumidor", PILHA_CONSUMIDOR, TAM_PILHA_CONSUMIDOR, 1);


	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}
//Contadores

volatile uint16_t a,b,c,d,e;

void suspende_threads(void){
        TarefaSuspende(1);
        TarefaSuspende(2);
        TarefaSuspende(3);
        TarefaSuspende(4);
        TarefaSuspende(7);
    
}

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void thread_01(void) //prioridade 5 - id_01
{
                
	for(;;)
	{
		a++;
		TarefaSuspende(1);
	
	}
}

void thread_02(void) //prioridade 4 - id_02
{
	
	for(;;)
	{
		b++;
                TarefaContinua(1);
                TarefaSuspende(2);
			
	}
}

void thread_03(void) //prioridade 3 - id_03
{
	for(;;)
	{
		c++;
                TarefaContinua(2);
                TarefaSuspende(3);
	}
}

void thread_04(void) //prioridade 2 - id_04
{
	for(;;)
	{
		d++;
                TarefaContinua(3);
                TarefaSuspende(4);
                 
	}
}

void thread_05(void) //prioridade 1 - id_05
{               
	for(;;)
	{
		e++;
                TarefaContinua(4);
               
		
	}
}

void thread_06(void)
{
	volatile uint16_t soma = 0;
	for(;;)
	{
		soma = a+b+c+d+e;
                printf("A soma dos contadores eh: %d", soma);
                TarefaEspera(30);
	}
}


//* Produtor-Consumidor*//
//////////////////////////

//int produz(){
//    return rand()%100;
//}
//
//int consome(int valor){
//  return valor;
//}
//
//void produtor(void){
//   
//  for(;;){
//    SemaforoAguarda(&vazio);
//    buffer[f]=produz();
//    f = (f+1)%TAM_BUFFER;
//    SemaforoLibera(&cheio);
//    
//  }
//}
//
//void consumidor(void){
//  
//  for(;;){
//  SemaforoAguarda(&cheio);
//  consome(buffer[i]);
//  i=(i+1)%TAM_BUFFER;
//  SemaforoLibera(&vazio);
//  } 
//  }

//////////////////////////
#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include "BlackTime/BlackTime.h"
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "display.h"
#include <mutex> 
#include <stdio.h>
#include <string.h>
#include <pthread.h> // biblioteca pthread
#include <semaphore.h>

#define UNIT_MS 1000
#define UNIT_SEC 1000000

using namespace std;

/****************** Variaveis Globais ***********************/
pthread_mutex_t work_mutex;

// Display
Display display(BlackLib::GPIO_65, BlackLib::GPIO_45,
					BlackLib::GPIO_69, BlackLib::GPIO_60, BlackLib::GPIO_27, BlackLib::GPIO_66,
					BlackLib::GPIO_49, BlackLib::GPIO_115,
					BlackLib::GPIO_20, BlackLib::GPIO_47,
					BlackLib::GPIO_48, BlackLib::GPIO_46);
		
		

void *thread_trem1(void *arg);
void *thread_trem2(void *arg);

/****************** FIM de Globais ***********************/

int main()
{
	int res, valor=0;
	pthread_t trem1, trem2;
	void * statusFinalizacao;
	
	printf("Programa principal criando thread consumidor...\n");
	res = pthread_create(&trem1, NULL, thread_trem2, (void *)&valor);
	if (res != 0)
	{
		perror("A Craição da Thread consumidor falhou");
		exit(EXIT_FAILURE);
	}


	printf("Programa principal criando thread trem2...\n");
	res = pthread_create(&trem2, NULL, thread_trem1, (void *)&valor);
	if (res != 0)
	{
		perror("A Craição da Thread trem2 falhou");
		exit(EXIT_FAILURE);
	}


	printf("Programa principal esperando pelo término das threads...\n");
    res = pthread_join(trem1, &statusFinalizacao);
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
    
	res = pthread_join(trem2, &statusFinalizacao);
	
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
   
    exit(EXIT_SUCCESS);
}

void *thread_trem1(void *valor)
{
	float perc1;
	ADC pot1(AIN0); 

	while (1)
	{
		perc1 = pot1.getPercentValue();
		 
		if(perc1 < 1) perc1 = 1;
		 
		display.turnOn(1);
		usleep(perc1  * 10 *  UNIT_MS);
		display.turnOff(1); 
		
		display.turnOn(2);
		usleep(perc1  * 10 *  UNIT_MS);
		
		pthread_mutex_lock(&work_mutex); // Entrando na região crítica
		display.turnOff(2); 
		display.turnOn(7);
		usleep(perc1  * 10 *  UNIT_MS);
		display.turnOff(7); 
		pthread_mutex_unlock(&work_mutex); // saindo de região critica 
		
		display.turnOn(6);
		usleep(perc1  * 10 *  UNIT_MS);
		display.turnOff(6); 
							
	}

}

void *thread_trem2(void *valor)
{
	
	float perc2;
	ADC pot2(AIN1);
	
	while (1)
	{
		
		perc2 = pot2.getPercentValue();
		
		if(perc2 < 1) perc2 = 1;
		 
		display.turnOn(4);
		usleep(perc2  * 10 *  UNIT_MS);
		display.turnOff(4); 
		
		display.turnOn(5);
		usleep(perc2  * 10 *  UNIT_MS); 
		
		pthread_mutex_lock(&work_mutex); // Entrando na região crítica
		display.turnOff(5);
		display.turnOn(7);
		usleep(perc2  * 10 *  UNIT_MS);
		display.turnOff(7); 
		pthread_mutex_unlock(&work_mutex); // saindo de região critica 
		
		display.turnOn(3);
		usleep(perc2  * 10 *  UNIT_MS);
		display.turnOff(3); 
		
	}

}

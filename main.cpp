#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
//#include "BlackTime/BlackTime.h"
//#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
//#include "display.h"
#include <mutex> 
#include <stdio.h>
#include <string.h>
#include <pthread.h> // biblioteca pthread

#define UNIT_MS 1000
#define UNIT_SEC 1000000

using namespace std;

/****************** Variaveis Globais ***********************/
std::mutex mtx;
// Display
/*Display display(BlackLib::GPIO_65, BlackLib::GPIO_45,
					BlackLib::GPIO_69, BlackLib::GPIO_60, BlackLib::GPIO_27, BlackLib::GPIO_66,
					BlackLib::GPIO_49, BlackLib::GPIO_115,
					BlackLib::GPIO_20, BlackLib::GPIO_47,
					BlackLib::GPIO_48, BlackLib::GPIO_46);
		*/
void *thread_tren2(void *arg);
void *thread_tren1(void *arg);

/****************** FIM de Globais ***********************/

int main()
{
	int res, valor=0;
	pthread_t consumdior, produtor;
	void * statusFinalizacao;
	
	//display.showNumber(0000);

	printf("Programa principal criando thread consumidor...\n");
	res = pthread_create(&consumdior, NULL, thread_tren2, (void *)&valor);
	if (res != 0)
	{
		perror("A Craição da Thread consumidor falhou");
		exit(EXIT_FAILURE);
	}


	printf("Programa principal criando thread produtor...\n");
	res = pthread_create(&produtor, NULL, thread_tren1, (void *)&valor);
	if (res != 0)
	{
		perror("A Craição da Thread produtor falhou");
		exit(EXIT_FAILURE);
	}


	printf("Programa principal esperando pelo término das threads...\n");
    res = pthread_join(consumdior, &statusFinalizacao);
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
	res = pthread_join(produtor, &statusFinalizacao);
    if (res != 0) {
        perror("O thread_join falhou");
        exit(EXIT_FAILURE);
    }
   
    exit(EXIT_SUCCESS);
}

void *thread_tren1(void *valor)
{
	//BlackLib::BlackGPIO trenzinho1(BlackLib::GPIO_68, BlackLib::input, BlackLib::SecureMode);
	while (1)
	{
		//while(trenzinho1.getValue() == "1");

		// SET L1 high
		//sleep(trenzinho1);
		//SET L1 low;
		//sleep(trenzinho1);
		//SET L4 high
		//sleep(trenzinho1);
		//SET L4 low
		//sleep(trenzinho1);
		mtx.lock();
		//SET L3 high
		//sleep(trenzinho1);
		//SET L3 low
		mtx.unlock();
		//sleep(trenzinho1);
		//SET L4 high
		//sleep(trenzinho1);
		//SET L4 low							
	}

}

void *thread_tren2(void *valor)
{
	
	//BlackLib::BlackGPIO trenzinho2(BlackLib::GPIO_68, BlackLib::input, BlackLib::SecureMode);
	while (1)
	{
		//while(trenzinho2.getValue() == "1");
		// SET L6 high
		//sleep(trenzinho2);
		//SET L6 low;
		//sleep(trenzinho2);
		//SET L5 high
		//sleep(trenzinho2);
		//SET L5 low
		//sleep(trenzinho2);
		mtx.lock();
		//SET L3 high
		//sleep(trenzinho2);
		//SET L3 low
		mtx.unlock();
		//sleep(trenzinho2);
		//SET L3 high
		//sleep(trenzinho2);
		//SET L3 low	
	}

}
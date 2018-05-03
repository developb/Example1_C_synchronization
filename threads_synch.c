/*
	This code uses POSIX threads, POSIX semaphores for synchronization 

	Simple example illustration of synchronization required when multithreading, irrespective of single core or multicore platform, on Linux.
	
	NUMTHREADS = number of threads
	NUM = number of times all threads need synchronized access to resource/s

	ie, Each thread prints its number, 0 to NUMTHREADS-1 in increasing order (though scheduler may schedule randomly),  and that printing of each thread's number happens for NUM number of times.
	The syncronization needs a mutual exclusive access to a global variable that is achieved using mutex. Synchronization among threads is achieved using a semaphore of maximum count = NUMTHREADS

*/



#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#define NUMTHREADS 5
#define NUM 4 

static int syncvar;
static pthread_mutex_t lock; 

sem_t sem;
int test_val;

void* handler(void* data)
{
	int i=0;
	int thread_num = *(int*)data;
#ifdef DEBUG
	printf("DEBUG: Thread_num %d started \n", thread_num);
#endif
	while(i < NUM)
	{
#ifdef DEBUG
		printf("DEBUG: i=%d,thread_num =%d,syncvar =%d \n",i,thread_num,syncvar);
#endif
		sem_wait(&sem);
		pthread_mutex_lock(&lock);
		if(thread_num == syncvar)
		{
			printf("i= %d,thread num %d\n",i,thread_num);
			syncvar++;
			if(syncvar > (NUMTHREADS-1))
			{ 
				syncvar=0;
			}
			i++;
			pthread_mutex_unlock(&lock);
			sem_post(&sem);
			//usleep(2);
		}
		else
		{
			pthread_mutex_unlock(&lock);
			sem_post(&sem);
			//usleep(2);
		}
	}
}

int main()
{
	int i=0,j=0;
	pthread_t thread[NUMTHREADS];
	int arr[NUMTHREADS];
	
	for(i=0;i<NUMTHREADS;i++)
		arr[i] = i;
	
	sem_init(&sem,0,NUMTHREADS);

	if(pthread_mutex_init(&lock,NULL) != 0)
		printf("Error in initializing mutex\n");
	for(i=0;i<NUMTHREADS;i++)
	{
		
		pthread_create(&thread[i], NULL,handler, (void*) (&arr[i]));
		//usleep(1);
	}
	for(j=0;j<NUMTHREADS;j++)
		pthread_join(thread[j],NULL);
	
	pthread_mutex_destroy(&lock);
	return 0;
}

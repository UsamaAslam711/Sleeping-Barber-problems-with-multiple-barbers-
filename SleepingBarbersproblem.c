#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#include<fcntl.h>
#include<pthread.h>
#include<time.h>
#include<assert.h>
#include<errno.h>
#include<unistd.h>
sem_t semb[3];
sem_t semch[3];
sem_t mutex;
int sal1=0;
int sal2=0;
int sal3=0;
void *gotoshop(void *param);
void scheduler(int *cut);
void rescheduler(int *c);
void cutting(int *cut);
void main()
{
	printf("----------------------------------------------------------------------------\n");
	printf("		O P E R A T I N G   S Y S T E M   L A B \n");
	printf("----------------------------------------------------------------------------\n");

	printf("\n\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("		SLEEPING BARBER PROBLEM WITH MULTIPLE BARBERS\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n\n");
	
	printf("Project Created by:\n\t\t");
	printf("1. MUHAMMAD USAMA. 2020-CS-652\n");
	printf("1. MOHAMMAD MUJEEB SUBHANI. 2020-CS-698\n");
	printf("1. SYED HAMZA. 2020-CS-671\n\n\n");	
	printf("_______________________________________________________________\n\n\n");
	int i;
	int j;
	int **cut;
	cut=(int **)malloc(40*sizeof(int*));
	for(int i=0;i<40;i++)
	{
		cut[i]=(int **)malloc(2*sizeof(int));
	}
	i=0;
	pthread_t tid[40];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	sem_init(&semb[0],0,1);
	sem_init(&semb[1],0,1);
	sem_init(&semb[2],0,1);
	sem_init(&semch[0],0,10);
	sem_init(&semch[1],0,10);
	sem_init(&semch[2],0,10);
	sem_init(&mutex,0,1);
	while(1)
	{
		i++;
		printf("^^^^^^^^^^^^^^^^^^^^^\n");
		printf("W E L C O M E\n");
		printf("^^^^^^^^^^^^^^^^^^^^^\n\n");
		printf("\n\n Customer No. %d\n.Enter the type of Haircut.\n\n\t1. Side Puff\n\t2. Bald\n\t3. Simple\n\nOtherwise Exit\n\n\n",i);
		scanf("%d",cut[i-1]);
		*(cut[i-1]+1)=i;
		fflush(stdin);
		if ((*cut[i-1] !=1)&&(*cut[i-1] !=2)&&(*cut[i-1] !=3))
		{
			printf("Thanks for coming...!!!\n\n\n");
			break;
		}
		pthread_create(&tid[i-1],&attr,gotoshop,(void *)cut[i-1]);
	}
	
	for (int j=0;j<i-1;j++)
	{
		pthread_join(tid[j],NULL);
	}
		
	sem_destroy(&semb[1]);
	sem_destroy(&semb[2]);
	sem_destroy(&semb[3]);
	sem_destroy(&semch[0]);
	sem_destroy(&semch[1]);
	sem_destroy(&semch[2]);
	
}

void *gotoshop(void *param)
{
	int *cut=(int*) param;
	int s;
	if ((s=sem_trywait(&semb[*cut-1]))==-1)
	{
		scheduler(cut);
		
	}
	printf("\n\n #############################\n");
	printf("\n Waking up Barber no. #%d\n",*cut);
	cutting(cut);
}

void scheduler(int *cut)
{
	int val;
	int s;
	struct timespec ts;
	if ((s=sem_trywait(&semch[*cut-1]))==-1)
	{
		printf("\n\n****************************************************************\n");
		printf("\n Customer #%d is leaving the shop because the shop is full.\n\n",*(cut+1));
		pthread_exit(0);
	}
	if(clock_gettime(CLOCK_REALTIME,&ts)==-1)
	{
		perror("clock_gettime");
	}
	ts.tv_sec+=30;
	
	if ((s=sem_timedwait(&semb[*cut-1],&ts))==-1)
	{
		if(errno==ETIMEDOUT)
		{
			rescheduler(cut);
		}
		else
		{
			perror("sem_timedwait");
		}
	}
	sem_post(&semch[*cut-1]);
	cutting(cut);
}

void rescheduler(int *cut)
{
	int ch1,ch2,ch3;
	int *i;
	i=(int*)malloc(2*sizeof(int));
	sem_wait(&mutex);
	sem_getvalue(&semch[0],&ch1);
	sem_getvalue(&semch[1],&ch2);
	sem_getvalue(&semch[2],&ch3);	
	sem_post(&mutex);
	if((ch1>=ch2)&&(ch1>=ch3))
	{
		*i=1;
	}
	else if((ch2>=ch1)&&(ch2>=ch3))
	{
		*i=2;
	}
	else
	{
		*i=3;
	}
	printf("Customer # %d waited for 20 sec and went to barber #%d\n",*(cut+1),*i);
	*(i+1)=*(cut+1);
	sem_post(&semch[*cut-1]);
	gotoshop((void*)i);
	
	return;
}



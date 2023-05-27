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

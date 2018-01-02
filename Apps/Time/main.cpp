//传统互斥量加锁方式 lock.cpp
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "timer.h"

pthread_mutex_t mutex_lock;
static volatile int count = 0;
void *test_func(void *arg)
{
        int i = 0;
        for(i = 0; i < 2000000; i++)
		{
                pthread_mutex_lock(&mutex_lock);
                count++;
                pthread_mutex_unlock(&mutex_lock);
        }
        return NULL;
}

int main(int argc, const char *argv[])
{
	Timer timer; // 为了计时，临时封装的一个类Timer。
	timer.Start();	// 计时开始
	pthread_mutex_init(&mutex_lock, NULL);
	pthread_t thread_ids[10];
	int i = 0;
	for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++)
	{
		pthread_create(&thread_ids[i], NULL, test_func, NULL);
	}

	for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++)
	{
		pthread_join(thread_ids[i], NULL);
	}

	timer.Stop();// 计时结束
	timer.Cost_time();// 打印花费时间
	printf("结果:count = %d\n",count);

	return 0;
}

//不加锁的形式  nolock.cpp
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "timer.h"

int mutex = 0;
int lock = 0;
int unlock = 1;

static volatile int count = 0;
void *test_func(void *arg)
{
        int i = 0;
        for(i = 0; i < 2000000; i++)
	{
		while (!(__sync_bool_compare_and_swap (&mutex,lock, 1) ))usleep(100000);
		 count++;
		 __sync_bool_compare_and_swap (&mutex, unlock, 0);
        }
        return NULL;
}

int main(int argc, const char *argv[])
{
	Timer timer;
	timer.Start();
	pthread_t thread_ids[10];
	int i = 0;

	for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++)
	{
			pthread_create(&thread_ids[i], NULL, test_func, NULL);
	}

	for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++)
	{
			pthread_join(thread_ids[i], NULL);
	}

	timer.Stop();
	timer.Cost_time();
	printf("结果:count = %d\n",count);

	return 0;
}

//原子函数进行统计方式 atomic.cpp
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "timer.h"

static volatile int count = 0;
void *test_func(void *arg)
{
        int i = 0;
        for(i = 0; i < 2000000; i++)
        {
	        __sync_fetch_and_add(&count, 1);
        }
        return NULL;
}

int main(int argc, const char *argv[])
{
	Timer timer;
	timer.Start();
	pthread_t thread_ids[10];
	int i = 0;

	for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++){
			pthread_create(&thread_ids[i], NULL, test_func, NULL);
	}

	for(i = 0; i < sizeof(thread_ids)/sizeof(pthread_t); i++){
			pthread_join(thread_ids[i], NULL);
	}

	timer.Stop();
	timer.Cost_time();
	printf("结果:count = %d\n",count);
    return 0;
}




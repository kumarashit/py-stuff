#include<sched.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

typedef struct Exec_Info {
	int cpu_id;
	long thread_id;
	char* message;
} Execinfo;

int get_cpu_id() {
	int cpu = sched_getcpu();
	return cpu;
}

void *thread_func(void *args) {
	char* message = (char*) args;
	Execinfo* execinfo = (Execinfo*)malloc(sizeof(Execinfo));
	execinfo->cpu_id = get_cpu_id();
	execinfo->thread_id = pthread_self();
	execinfo->message = malloc(sizeof(message));
	strcpy(execinfo->message, message);
	execinfo->message[strlen(execinfo->message)] = '\0';
	pthread_exit(execinfo);
}

void freeme(Execinfo *res) {
	free(res);
}



Execinfo* cpu_thread_func(void) {
	pthread_t thr;
	Execinfo *res;
	char* message = "Here is your result: ";
	pthread_create(&thr, NULL, &thread_func, (void*)message);
	pthread_join(thr, (void**)&res);
	return res;
	//printf("%s \n Thread ID is [%ld]\n CPU Id [%d]\n", res->message, res->thread_id, res->cpu_id);
}



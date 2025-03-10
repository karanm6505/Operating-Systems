#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>

#define NUM 5
void *runner(void *param);
int main(int argc, char *argv[])
{
    int i,scope;
    pthread_t tid[NUM];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    if(pthread_attr_getscope(&attr,&scope) != 0)
    {
        fprintf(stderr,"Unable to figure out scheduling scope\n");
    }
    else
    {
        if(scope == PTHREAD_SCOPE_PROCESS)
        {
            printf("PTHREAD_SCOPE_PROCESS");
        }
        else if(scope == PTHREAD_SCOPE_SYSTEM)
        {
            printf("PTHREAD_SCOPE_SYSTEM");
        }
        else
            fprintf(stderr,"Illegal scope value\n");
    }

    pthread_attr_setscope(&attr,PTHREAD_SCOPE_PROCESS);
    for(int i = 0; i<NUM; i++)
    {
        pthread_create(&tid[i],&attr,runner,NULL);
    }
    for(int i = 0; i<NUM; i++)
    {
        pthread_join(tid[i],NULL);
    }
}

void *runner(void *param)
{
    wait(NULL);
    pthread_exit(0);
}
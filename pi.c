#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<math.h>
#define slice 1000

double XtoY(double x);
double getDiff();
void thread(void *id);
int numCPU = 1;

double PI = 3.14159265359;


int main(int argc, char** argv){
    numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    //printf("%d\n", numCPU);
    if(argc == 2)
        int accuracy = atoi(argv[1]);
    else
        printf("Error: ./pi num\n");

    pthread_t *tid = (pthread_t*)malloc(sizeof(pthread_t)*numCPU);

    for (int i = 0; i < numCPU; i++){
        pthread_create(&tid[i], NULL, (void *)thread, (void *)i);
    }

    for (int i = 0; i < numCPU; i++){
        pthread_join(tid[i], NULL);
    }

    double tot = 0;

    for (int i = 0; i < numCPU; i++){
        tot += area[i];
    }

    double diff = getDiff();

    double ans = (tot - diff)*4;

    printf(ans);

    free(numCPU);
    return 0;
}

double area[numCPU];

void thread(void *id){
    int a = id*slice, b = id*slice+1000
    double lg =  1 / numCPU*slice;
    double first = a * lg;
    double now = first;
    area[id] = 0;
    for (int i = 0; i < slice; i++){
        area[id] = XtoY(now);
        now += lg;
    }

    area[id] *= lg;
}

double XtoY(double x){
    return sqrt(1 - x * x);
}

double getDiff(){
    double lg =  1 / numCPU*slice;
    double high = 1 - XtoY(numCPU * slice-1);
    return lg * high;
}

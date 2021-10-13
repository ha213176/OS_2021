#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


int main(int argc, char** argv){
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("%d\n", numCPU);
}
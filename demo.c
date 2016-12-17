#include <stdio.h>
#include <assert.h>
#include "MemoryManager.h"

#define MAX_SIZE 1024*1024

int main(){

    InitMemoryManager(MAX_SIZE);

    printf("I did something\n");

}

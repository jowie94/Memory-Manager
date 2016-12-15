#ifndef _MEMORYMANAGER_H
#define _MEMORYMANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

void InitMemoryManager(size_t max_size);

void* MyMalloc(size_t size);

void MyFree(void* block);

#ifdef __cplusplus
}
#endif

#endif // _MEMORYMANAGER_H


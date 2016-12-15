#include "stdlib.h"
#include "assert.h"

#include "MemoryManager.h"

#define HEAD(block) ((Head*)(block))
#define OFFSET sizeof(Head)
#define NEXT_BLOCK(block) block + HEAD(block)->size + OFFSET
#define NEXT_HEAD(head) HEAD(NEXT_BLOCK((char*)head))

void printf(const char* str, ...);

typedef struct Head Head;

struct Head
{
	char in_use;
	size_t size;
	Head* left;
};

union MemoryMap
{
	char* memory_block;
	Head* first_head;
};

struct
{
	size_t max_size;
	//size_t memory_used;
	union MemoryMap map;
} Memory = { 0, { NULL } };

void* alloc(Head* head, size_t size)
{
	head->in_use = 1;
	if (head->size > size + OFFSET)
	{
		size_t old_size = head->size;
		head->size = size;
		Head* next = NEXT_HEAD(head);
		next->size = old_size - size - OFFSET;
		next->in_use = 0;
		next->left = head;
	}

	//memory_used += head->size;

	return ++head;
}

void cleanup(Head* head)
{
	head->in_use = 0;
	
	Head* next = NEXT_HEAD(head);
	while (!next->in_use)
	{
		head->size += next->size + OFFSET;
		next = NEXT_HEAD(next);
	}

	next = head->left;
	while (next && !next->in_use)
	{
		head->size += next->size + OFFSET;
		next = next->left;
	}
}

void InitMemoryManager(size_t max_size)
{
	Memory.map.memory_block = malloc(max_size);
	Memory.max_size = max_size - OFFSET;

	// Create the first head element
	Head* first = Memory.map.first_head;
	first->in_use = 0;
	first->size = max_size - OFFSET;
	first->left = NULL;
}

void* MyMalloc(size_t size)
{
	assert(Memory.map.memory_block != NULL);
	if (Memory.map.memory_block == NULL)
		return NULL;

	char* block = Memory.map.memory_block;
	char found;
	Head* curr = Memory.map.first_head;
	while (!((found = !curr->in_use && curr->size >= size)) && block < Memory.map.memory_block + OFFSET)
	{
		block = NEXT_BLOCK(block);
		curr = HEAD(block);
	}

	return found ? alloc(curr, size) : NULL;
}

void MyFree(void* block)
{
	assert(block != NULL);
	char* blk = (char*)block;
	Head* head = HEAD(blk - OFFSET);
	cleanup(head);
}

void StopMemoryManager()
{
#ifdef _DEBUG
	if (Memory.map.first_head->size != Memory.max_size)
		printf("[DEBUG] Memory not fully cleaned!");
#endif

	free(Memory.map.memory_block);
	Memory.max_size = 0;
}

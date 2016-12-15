#include "stdlib.h"
#include "assert.h"

#include "MemoryManager.h"

#define HEAD(block) ((Head*)(block))
#define OFFSET sizeof(Head)
#define NEXT_BLOCK(block) block + HEAD(block)->size + OFFSET
#define NEXT_HEAD(head) HEAD(NEXT_BLOCK((char*)head))

struct
{
	size_t max_size;
	//size_t memory_used;
	char* memory_block;
} Memory = { 0, NULL };

typedef struct Head Head;

struct Head
{
	char in_use;
	size_t size;
	Head* left;
};

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

	return ++head;
}

void InitMemoryManager(size_t max_size)
{
	Memory.memory_block = malloc(max_size);
	Memory.max_size = max_size;
	Memory.max_size = max_size - OFFSET;

	// Create the first head element
	Head* first = HEAD(Memory.memory_block);
	first->in_use = 0;
	first->size = max_size - OFFSET;
	first->left = NULL;
}

void* MyMalloc(size_t size)
{
	assert(Memory.memory_block != NULL);
	if (Memory.memory_block == NULL)
		return NULL;

	char* block = Memory.memory_block;
	char found = 0;
	Head* curr = NULL;
	while (!found && block < Memory.memory_block + OFFSET)
	{
		curr = HEAD(block);
		if (!curr->in_use && curr->size >= size)
			found = 1;
		else
			block += curr->size + OFFSET;
	}

	return found ? alloc(curr, size) : NULL;
}

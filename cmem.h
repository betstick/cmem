#ifndef CMEM__
#define CMEM__

#include <string.h> //memcpy
#include <stdbool.h> //bools
#include <stdlib.h> //free

typedef struct 
{
	char* src;
	size_t size;
	long position;
	bool err;
	bool eod; //end of data
} MEM;

//Open arbitrary data for RW operations, not thread safe :^)
MEM* mopen(char* src, size_t size);

//Read data like with fread()
size_t mread(void* dest, size_t size, size_t n, MEM* source);

size_t mwrite(char* source, size_t size, size_t count, MEM* dest);

//Set position like with fseek()
void mseek(MEM* mem, long offset, int whence);

//Returns current position in data
long mtell(MEM* mem);

//Close the data or something
void mclose(MEM* mem);

//If end of data has been reached
int meod(MEM* mem);

//If an error has occurred
int merror(MEM* mem);

//Return pointer to position in memory
char* mtellptr(MEM* mem);

MEM* mopen(char* src, size_t size)
{
	MEM* mem = (MEM*)malloc(sizeof(MEM));

	mem->src = src;
	mem->size = size;
	mem->position = 0;
	mem->eod = false;
	mem->err = false;

	return mem;
};

size_t mread(void* dest, size_t size, size_t count, MEM* source)
{
	memcpy(dest,mtellptr(source),size*count);
	size_t ret = 0;

	if(source->position + (size * count) > source->size)
	{
		source->eod = true; //set EOF to true

		//hacky int magic math
		ret = ((size * count) / (source->size - source->position));
		source->position = size; //set pos to end
	}
	else
	{
		source->position += size * count;
		ret = count;
	}
	
	//fsize is 8, pos is 2, req is 7. 8-2=6, 6/7 = 1
	return ret;
};

size_t mwrite(char* source, size_t size, size_t count, MEM* dest)
{
	memcpy(mtellptr(dest),source,size*count);
	size_t ret = 0;

	if(dest->position + (size * count) > dest->size)
	{
		dest->eod = true;

		ret = ((size * count) / (dest->size - dest->position));
		dest->position = size; //set pos to end
	}
	else
	{
		dest->position += size * count;
		ret = count;
	}

	return ret;
};

void mseek(MEM* mem, long offset, int whence)
{
	switch(whence)
	{
		case 0: mem->position = offset; break;
		case 1: mem->position += offset; break;
		case 2: mem->position = mem->size + offset; break;
		default: mem->position = 0;
	}

	if(mem->position > mem->size)
		mem->eod = true;
};

long mtell(MEM* mem)
{
	return mem->position;
};

//Frees the MEM or something.
void mclose(MEM* mem)
{
	free(mem);
};

//Returns pointer to memory at the position  
char* mtellptr(MEM* mem)
{
	return &mem->src[mem->position];
};

int meod(MEM* mem)
{
	return (mem->eod);
};

int merror(MEM* mem)
{
	return (mem->err);
};

#endif
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * Edited by AllenClown
 */

//definition struct of cache line

typedef struct{
	unsigned char validBit;
	unsigned long flag;
	unsigned int timeFromLastUsed;
} *cacheLinePoint, cacheLine;




void string2UnsignedInt(char *, unsigned int *);
void cacheInitialization( int numOfSets, int associativity, cacheLinePoint cache[numOfSets][associativity]);
void updateTime(int numOfSets, int associativity, cacheLinePoint cache[numOfSets][associativity]);
int lineMatching(int numOfSets, int associativity,cacheLinePoint cache[numOfSets][associativity], unsigned long flagBits, unsigned int indexOfSet);
int isEviction(int numOfSets, int associativity,cacheLinePoint cache[numOfSets][associativity], unsigned long flagBits, unsigned int indexOfSet);

// test functions
void printCache(int numOfSets, int associativity,cacheLinePoint cache[numOfSets][associativity]){
	printf("******************************************************************************************\n");
	for(int i=0; i<numOfSets; i++)
		for(int j=0; j<associativity; j++)
			printf("num of sets: %2d, vailidBit: %d, flag: %lx, time: %d\n",i, cache[i][j]->validBit, cache[i][j]->flag, cache[i][j]->timeFromLastUsed);
	printf("******************************************************************************************\n");
}
//global variables
char *usage = "Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n"
			  "• -h: Optional help flag that prints usage info\n"
			  "• -v: Optional verbose flag that displays trace info\n"
 			  "• -s <s>: Number of set index bits (S = 2 s is the number of sets)\n"
			  "• -E <E>: Associativity (number of lines per set)\n"
			  "• -b <b>: Number of block bits (B = 2 b is the block size)\n"
			  "• -t <tracefile>: Name of the valgrind trace to replay\n";





int main(int numOfArgs, char **args)
{
	unsigned int numOfSetIndexBits, numOfBlockBits, numOfFlagBits, associativity, vebose;
	char *fileName ;
	vebose = 0;
	switch(numOfArgs){
		case 9:
			string2UnsignedInt(args[2], &numOfSetIndexBits);
    	    string2UnsignedInt(args[4], &associativity);
        	string2UnsignedInt(args[6], &numOfBlockBits);
        	numOfFlagBits = 64 - numOfBlockBits - numOfSetIndexBits;
        	fileName = args[8];
			break;
		case 10:
			if(args[1][1] == 'v'){
				string2UnsignedInt(args[3], &numOfSetIndexBits);
        		string2UnsignedInt(args[5], &associativity);
        		string2UnsignedInt(args[7], &numOfBlockBits);
        		numOfFlagBits = 64 - numOfBlockBits - numOfSetIndexBits;
        		fileName = args[9];
				vebose = 1;
				break;
			}
		default:
			printf("Error: more than 10 arguments\n%s",usage);
        	return 1;


	}


	if(vebose)
	printf("%d %d %d %s\n", numOfSetIndexBits, numOfBlockBits, associativity, fileName);
	unsigned int numOfSets = 1 << numOfSetIndexBits;
//cache initialization
	cacheLinePoint cache[numOfSets][associativity];
	cacheInitialization(numOfSets, associativity,cache);


// reading a file
	FILE *file = fopen(fileName, "r"); // open file for reading
	if(!file){
		printf("Error: file %s is not exsited.\n", fileName);
		return 1;
	}
	
	char accessType;
	unsigned long address;
	unsigned int  size, hits, misses, evictions;
	hits = misses = evictions = 0;
	while(fscanf(file, " %c %lx, %u", &accessType, &address, &size) > 0){
	
		if(accessType == 'I') continue;
		unsigned int indexOfSet = (address << numOfFlagBits) >> (numOfFlagBits + numOfBlockBits);
		unsigned long flagBits = address >> (numOfSetIndexBits +  numOfBlockBits );
		updateTime( numOfSets, associativity,cache);

		int lineMatchingValue = lineMatching( numOfSets, associativity,cache, flagBits, indexOfSet);	
		if(!lineMatchingValue){
			misses++;
			evictions += isEviction( numOfSets, associativity, cache,flagBits, indexOfSet);
		}else{
			hits++;
		}
		if(accessType == 'M') hits++;

		//test
		if(vebose){
		printCache(numOfSets, associativity, cache);
		printf("%c %lx,%u\n", accessType, address, size);
		printSummary(hits, misses, evictions);
		}
//		getchar();
	}
    printSummary(hits, misses, evictions);
//delocate
	for(int i=0; i<numOfSets; i++){
		for(int j=0; j<associativity; j++)
		free(cache[i][j]);
}
    return 0;
}






//Implementation of functions

void string2UnsignedInt(char *str, unsigned int *dst){
	unsigned int maxLen = 50;
	unsigned int result = 0;
	char c;
	for(int i=0; i < maxLen &&  (c = str[i]) != '\0'; i++){
		result += c - '0';
		result *=10;
	}
	*dst = result / 10;
}


void cacheInitialization(int numOfSets, int associativity,cacheLinePoint cache[numOfSets][associativity] ){
	for(int i=0; i<numOfSets; i++){
		for(int j=0; j<associativity; j++){
			cache[i][j] = (cacheLinePoint)malloc(sizeof(cacheLine));
			if(cache[i][j] == NULL) {
				printf("Error: allocated memory error!");
				return ;
			}
			cache[i][j]->validBit = 0;
		}
	}
}

void updateTime(int numOfSets, int associativity,  cacheLinePoint cache[numOfSets][associativity]){
//update time
	for(int i=0; i<numOfSets; i++){
   		for(int j=0; j<associativity; j++)
  			if(cache[i][j]->validBit)
				cache[i][j]->timeFromLastUsed ++;
	}
}


int lineMatching( int numOfSets, int associativity, cacheLinePoint cache[numOfSets][associativity], unsigned long flagBits, unsigned int indexOfSet){
		//line matching
	int lineMatching = 0;
	for(int i =0; i< associativity; i++){
		if(!cache[indexOfSet][i]->validBit) continue;
		if(cache[indexOfSet][i]->flag == flagBits){
			lineMatching = 1;
			cache[indexOfSet][i]->timeFromLastUsed = 1; // update time
			break;
		}
	}

	return lineMatching;
}

int isEviction(int numOfSets, int associativity, cacheLinePoint cache[numOfSets][associativity], unsigned long flagBits, unsigned int indexOfSet){
	//find a cacheline to load block
	int index_j,max, eviction;
	max = 0;
	eviction =1;// set 1 if can not find spareroom for new cache line
	
   	for(int j=0; j<associativity; j++){
		if(!cache[indexOfSet][j]->validBit){// to find spare room
			index_j = j;
			eviction = 0;
	//		printf("%d, %d\n", indexOfSet, j);
			break;
		}
		//find the least recently used cache line

        index_j = max < cache[indexOfSet][j]->timeFromLastUsed ? j: index_j;
		max = max < cache[indexOfSet][j]->timeFromLastUsed ? cache[indexOfSet][j]->timeFromLastUsed : max;
	}
	
	cache[indexOfSet][index_j]->validBit = 1; // set validBit
	cache[indexOfSet][index_j]->flag = flagBits;//load flag index bits
	cache[indexOfSet][index_j]->timeFromLastUsed = 1;//update time
	return eviction;
}

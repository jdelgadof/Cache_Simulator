// CacheSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Cache.h"
#include "Memory.h"

void stats(Cache &c)
{
	int hits  = c.getHits();
	int misses =c.getMisses();
	int total = hits + misses;
	std::cout << "hit rate: " << (double) hits / total << " miss rate:" << (double) misses / total << std::endl;
	std::cout << "hits:" << hits << " misses: " << misses  << std::endl;
}


int _tmain(int argc, _TCHAR* argv[])
{

	char operation;
	uint64_t address;
	uint64_t count;
	uint64_t atime = 0;
	uint64_t acount = 0;

	std::cout << "Start\tFile: twolf.trace" << std::endl;

	std::ifstream infile("twolf.trace");
	if(!infile) {
		std::cout << "Can't open file" << std::endl;
		return 1;
	}
/*original
	Memory mainMemory(90);
	Cache cacheL2(10, 8196, 16, 4, &mainMemory);
	Cache cacheL1(4, 2048, 16, 2, &cacheL2);

//Intel Penryn all calculation in cycles
    Memory mainMemory(160);
    Cache cacheL2(15, 6*1024*1024, 64, 8, &mainMemory);
    Cache cacheL1(3, 64*1024, 64, 2, &cacheL2);
// Intel Penryn:    L1 2-way, 64Kb, 3 cycles, 0,031-->we will assume 64 bytes block size
//                  L2 8-way, 6Mb, 15cycles, 0,004-->we will assume 64 bytes block size
//                  main memory 160
*/
//Intel Nehalem all calculation in cycles
    Memory mainMemory(107);
    Cache cacheL3( 39, 8*1024*1024, 64, 8, &mainMemory);
    Cache cacheL2(11, 256*1024, 64, 4, &cacheL3);
    Cache cacheL1(4, 64*1024, 64, 2, &cacheL2);
// Intel Nehalem:   L1 2-way, 64Kb, 4 cycles, 0,031 -->we will assume 64 bytes block size
//                  L2 4-way, 256Kb, 11 cycles, 0,012 -->we will assume 64 bytes block size
//                  L3 8-way, 8Mb, 39 cycles, 0,004 -->we will assume 64 bytes block size
//                  main memory 107*/
	atime = 0;
	acount = 0;

	while(infile.good()) {
		infile >> operation >> std::hex >> address >> count; 
		atime += cacheL1.read(address);
		acount++;
	}
	infile.close();

	std::cout << "L1 cache: " << std::endl;
	stats(cacheL1);
	std::cout << "L2 cache: " << std::endl;
	stats(cacheL2);

	std::cout << "Access times: " << std::endl;
	std::cout << "total time: " << atime << " access count:" << acount << std::endl;
	std::cout << "average access time: " << (double) atime / acount << std::endl;

	std::cout << "End" << std::endl;

	return 0;
}


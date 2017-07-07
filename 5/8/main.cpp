#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
using namespace std;

void turnOnFromLeft(int index, int8_t &byte) {
	byte |= (1 << index);
}

void turnOnFromRight(int index, int8_t &byte) {
	byte |= (1 << (7-index));
}

void drawLine2(int8_t *A, int width, int x1, int x2, int y) {
	int start_offset = x1 % 8;
	int first_full_byte = x1 / 8;
	if (start_offset != 0) first_full_byte++;

	int end_offset = x2 % 8;
	int last_full_byte = x2 / 8;
	if (end_offset != 7) last_full_byte--;

	// Set start bytes:
	uint8_t start_mask = 0xFF >> start_offset;
	uint8_t end_mask   = 0xFF << (7-end_offset);	

	// Set start and end bytes:
	if (x1/8 == x2/8) {
		// x1 and x2 are in the same byte:
		uint8_t mask = start_mask & end_mask;
		A[x1/8 + (width / 8) * y] |= mask;	
	} else {
		if (start_offset != 0) {
			A[x1/8 + (width / 8) * y] |= start_mask;
		}
		if (end_offset != 0) {
			A[x2/8 + (width / 8) * y] |= end_mask;
		}
	}

	// Set full bytes:
	for (int b = first_full_byte; b <= last_full_byte; b++) {
		A[b + ((width / 8) * y)] = 0xFF;//~0;
	}
}

void drawLine(int8_t *A, int width, int x1, int x2, int y) {
	int numBytes = sizeof(A)/sizeof(A[0]);
	int numPixels = numBytes * 8;
	int height = numPixels / width;

	// Find where in A x1 is located:
	int byteStartIndex1 = (x1 / 8) + y*width/8;
	int byteStartMod1 = x1 % 8;
	
	int byteStartIndex2 = (x2 / 8) + y*width/8;
	int byteStartMod2 = x2 % 8;

	// Turn all points from this point until x2 on:
	if (byteStartIndex1 == byteStartIndex2) {
		while (byteStartMod1++ < byteStartMod2) {
			turnOnFromRight(byteStartMod1, A[byteStartIndex1]);
		}
	} else {
		// Fill in the current byte:
		for (int i = 0; i <= 7-byteStartMod1; i++) {
			turnOnFromRight(i, A[byteStartIndex1]);
		}

		// Fill in bytes in between:
		while (++byteStartIndex1 != byteStartIndex2) {
			A[byteStartIndex1] = ~0;
		}

		// Fill in last byte:
		for (int i = 0; i <= byteStartMod2; i++) {
			turnOnFromLeft(7-i, A[byteStartIndex2]);
		}
	}
}

int main() {

	ifstream file;
	file.open("input.txt");

	int x;
	file >> x;

	int8_t A[5] = {'a','b','c','d','e'};
	int width = 8;
	drawLine(A, width, 5, 10, 1);

	file.close();

	return 0;
}



/*
 * TSPWriterTest.cpp
 *
 *  Created on: Jul 23, 2008
 *      Author: isazi
 */

#include <tsp/TSPInstance.h>
#include <tsp/TSPWriter.h>

using namespace asd;

int main(void) {
	TSPInstance< int > gino;
	TSPWriter< int > rino(&gino);

	return 0;
}

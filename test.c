#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "vendor/svasync/svasync.h"

int main(){
	printf("Hello! Now try writing to serial.");

	if (SVAsyncInit(COM1)){
		printf("Error initialising COM1.\n");
		return 1;
	}

	SVAsyncFifoInit();

	SVAsyncSet(9600, BITS_8 | STOP_1 | NO_PARITY);
	SVAsyncHand(DTR | RTS);

	char in;
	while (1){
		if (!SVAsyncInStat()) continue;
		in = SVAsyncIn();
		if (in == 26) break;
		printf("%c", in);
	}

	return 0;
}
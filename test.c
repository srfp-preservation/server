#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <netinet/in.h>
#include "vendor/svasync/svasync.h"
#include "message.c"

int main(){
	printf("Hello! Now try writing to serial.\n");

	if (SVAsyncInit(COM1)){
		printf("Error initialising COM1.\n");
		return 1;
	}

	SVAsyncFifoInit();

	SVAsyncSet(9600, BITS_8 | STOP_1 | NO_PARITY);
	SVAsyncHand(DTR | RTS);

	while (1){
		srfp_message message = get_message();

		printf("MessageType 0x%02x, ID %d, length %d\n", message.header.type, message.header.msgid, message.header.length);

		uint32_t i;
		for (i = 0; i < message.header.length; i++){
			printf("%02x ", message.body[i]);
		}
		printf("\nChecksum 0x%08x\n", message.checksum);
		destroy_message(message);
	}

	return 0;
}
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
#include "util.c"

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
		srfp_message request = get_message();
		srfp_message response = response_from_request(request);

		switch (request.header.type){
			case 0x01: //DirectoryList
				break;
			case 0x02: //NodeInfo
				break;
			case 0x03: //FileContents
				break;
			case 0x7F: { //Version
				response.body = malloc(3);
				memcpy(response.body, "\0\0\0", 3);
				response.header.length = 3;
				break;
			}
		}

		printf("MessageType 0x%02x, ID %d, length %d\n", request.header.type, request.header.msgid, request.header.length);

		uint32_t i;
		for (i = 0; i < request.header.length; i++){
			printf("%02x ", request.body[i]);
		}
		printf("\nChecksum 0x%08x\n", request.checksum);
		printf("MessageType 0x%02x, ID %d, length %d\n", response.header.type, response.header.msgid, response.header.length);

		for (i = 0; i < response.header.length; i++){
			printf("%02x ", response.body[i]);
		}
		printf("\nChecksum 0x%08x\n", response.checksum);

		destroy_message(request);
		destroy_message(response);
	}

	return 0;
}

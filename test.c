#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <netinet/in.h>
#include "vendor/svasync/svasync.h"

#pragma pack(push, 1)
typedef struct {
	uint8_t type;
	uint16_t msgid;
	uint16_t length;
} srfp_header;
#pragma pack(pop)

typedef struct {
	srfp_header header;
	uint8_t* body;
	uint32_t checksum;
} srfp_message;

void serial_read(void *buf, size_t length){
	uint8_t *buffer = (uint8_t *) buf;
	size_t i;
	for (i = 0; i < length;){
		if (!SVAsyncInStat()) continue;
		buffer[i] = SVAsyncIn();
		i++;
	}
}

srfp_message get_message(){
	srfp_message message;
	bzero(&message, sizeof(message));
	serial_read(&message.header, sizeof(message.header));
	message.header.msgid = ntohs(message.header.msgid);
	message.header.length = ntohs(message.header.length);
	message.body = malloc(message.header.length);
	serial_read(message.body, message.header.length);
	serial_read(&message.checksum, sizeof(message.checksum));
	message.checksum = ntohl(message.checksum);

	return message;
}

void destroy_message(srfp_message m){
	free(m.body);
}

int main(){
	printf("Hello! Now try writing to serial.\n");

	if (SVAsyncInit(COM1)){
		printf("Error initialising COM1.\n");
		return 1;
	}

	SVAsyncFifoInit();

	SVAsyncSet(9600, BITS_8 | STOP_1 | NO_PARITY);
	SVAsyncHand(DTR | RTS);

	srfp_message message = get_message();

	printf("MessageType 0x%02x, ID %d, length %d\n", message.header.type, message.header.msgid, message.header.length);

	uint32_t i;
	for (i = 0; i < message.header.length; i++){
		printf("%02x ", message.body[i]);
	}
	printf("\nChecksum 0x%08x\n", message.checksum);
	destroy_message(message);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <dirent.h>
#include <mntent.h>
#include "vendor/svasync/svasync.h"
#include "message.c"
#include "util.c"

void do_directory_list(srfp_message *request, srfp_message *response){
	if (request->header.length == 0){
		// Empty request body means we need to list available volumes
		response->body = malloc(26*3); // 26 letters = max 26 volumes
		response->header.length = 0;
		// this won't segfault as DJGPP ignores these parameters
		FILE *mntentptr = setmntent(NULL, NULL);
		struct mntent *fsdetails;
		while (fsdetails = getmntent(mntentptr)){
			memcpy(response->body + response->header.length, fsdetails->mnt_dir, 2);
			response->body[response->header.length + 2] = '\0';
			response->header.length += 3;
		}
		// ignore the final null
		if (response->header.length) response->header.length--;
	} else {
		char path[request->header.length + 1];
		srfp_to_dos_path(request->body, request->header.length, path);
		response->body = malloc(65535);
		response->header.length = 0;
		DIR *dir = opendir(path);
		if (dir){
			struct dirent *entry;
			uint8_t i;
			while (entry = readdir(dir)){
				for (i = 0;;i++){
					response->body[response->header.length] = entry->d_name[i];
					response->header.length++;
					if (entry->d_name[i] == '\0') break;
				}
			}
			// ignore the final null
			if (response->header.length) response->header.length--;
			closedir(dir);
		} else {
			printf("Couldn't open directory %s", path);
			perror("");
		}
	}
}

void do_version(srfp_message *request, srfp_message *response){
	response->body = malloc(3);
	memcpy(response->body, "\0\0\0", 3);
	response->header.length = 3;
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

	while (1){
		srfp_message request = get_message();
		srfp_message response = response_from_request(request);

		switch (request.header.type){
			case 0x01: //DirectoryList
				do_directory_list(&request, &response);
				break;
			case 0x02: //NodeInfo
				break;
			case 0x03: //FileContents
				break;
			case 0x7F: { //Version
				do_version(&request, &response);
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

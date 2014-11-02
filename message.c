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
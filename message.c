#pragma pack(push, 1)
typedef struct {
	uint8_t type;
	uint16_t msgid;
	uint16_t length;
} srfp_header;
#pragma pack(pop)

typedef struct {
	srfp_header header;
	char* body;
	uint32_t checksum;
} srfp_message;

#pragma pack(push, 1)
typedef struct {
	uint8_t flags;
	uint32_t size;
	uint32_t created_time;
	uint32_t accessed_time;
	uint32_t modified_time;
} srfp_node_info;

typedef struct {
	uint32_t offset;
	uint32_t length;
} srfp_file_contents_info;
#pragma pack(pop)

void serial_read(void *buf, size_t length){
	uint8_t *buffer = (uint8_t *) buf;
	size_t i;
	for (i = 0; i < length;){
		if (!SVAsyncInStat()) continue;
		buffer[i] = SVAsyncIn();
		i++;
	}
}

void serial_write(void *buf, size_t length){
	uint8_t *buffer = (uint8_t *) buf;
	size_t i;
	for (i = 0; i < length;){
		if (SVAsyncOutStat()) continue;
		SVAsyncOut(buffer[i]);
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

void send_message(srfp_message message){
	uint16_t length = message.header.length; // hang on to this in host byte order
	message.header.msgid = htons(message.header.msgid);
	message.header.length = htons(message.header.length);
	serial_write(&message.header, sizeof(message.header));
	serial_write(message.body, length);
	message.checksum = htonl(message.checksum);
	serial_write(&message.checksum, sizeof(message.checksum));
}

void destroy_message(srfp_message m){
	free(m.body);
}

srfp_message response_from_request(srfp_message req){
	srfp_message resp;
	bzero(&resp, sizeof(resp));
	resp.header.type = req.header.type + 0x80;
	resp.header.msgid = req.header.msgid;
	return resp;
}

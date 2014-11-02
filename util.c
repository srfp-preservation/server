void srfp_to_dos_path(char *str, size_t len){
	char *strchr;
	for (strchr = str; strchr < str + len; strchr++){
		if (*strchr == '\0'){
			*strchr = '\\';
		}
	}
}

void dos_to_srfp_path(char *str, size_t len){
	char *strchr;
	for (strchr = str; strchr < str + len; strchr++){
		if (*strchr == '\\'){
			*strchr = '\0';
		}
	}
}
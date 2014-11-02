/**
Creates a **new** string with a DOS path from a buffer containing a SRFP path.

Argument 'out' is the string to copy into, which should be initialised with a
length of len + 1.
*/
void srfp_to_dos_path(char *str, size_t len, char *out){
	// we can't do this in place b/c the equivalent C string is 1 byte longer
	// due to the trailing null, so we create a new string and return that
	size_t i;
	for (i = 0; i < len; i++){
		if (str[i] == '\0'){
			out[i] = '\\';
		} else {
			out[i] = str[i];
		}
	}
	out[len] = '\0';
}

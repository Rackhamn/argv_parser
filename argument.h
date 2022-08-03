// 2022-08-03 :: Carl Blumenthal

#ifndef ARGUMENT_H
#define ARGUMENT_H

// TODO: add more types. (double, unsigned long int)

#define ARG_TYPE_INT		0
#define ARG_TYPE_FLOAT		1
#define ARG_TYPE_STRING		2
#define ARG_TYPE_CALLBACK	3
#define ARG_TYPE_MAX		3

struct argument {
	char * 	arg_str;
	int 	arg_strlen;
	int 	val_type;
	
	char * 	argv_ptr;
	int 	argv_len;
};

// TODO: make into array buffer -> reallocate
#define ARG_MAX 	32
int _argc = 0;
struct argument _arg[ARG_MAX];

int set_arg(char * string, int type) {
	int id;
	
	if(string == NULL) return -1;
	if(type < 0 || type > ARG_TYPE_MAX) return -1;
	
	if(_argc >= ARG_MAX) return -1;
	
	id = _argc;

	_arg[id].arg_str = string;
	_arg[id].arg_strlen = strlen(string);
	_arg[id].val_type = type;

	_arg[id].argv_ptr = NULL;
	_arg[id].argv_len = 0;
	
	_argc++;
	
	return id;
}

int get_arg(int id, void * val) {
	if((id < 0 || id >= ARG_MAX) /* || val == NULL */ ) return -1;
	if(_arg[id].argv_ptr == NULL || _arg[id].argv_len == 0) return -1;
	
	switch(_arg[id].val_type) {
		case ARG_TYPE_INT: {
			int temp = atoi(_arg[id].argv_ptr);
			*((int *)val) = temp;
		} break;
		case ARG_TYPE_FLOAT: {
			float temp = atof(_arg[id].argv_ptr);			
			*((float *)val) = temp;
		} break;
		case ARG_TYPE_STRING: {
			size_t bytes = sizeof(char) * (_arg[id].argv_len + 1);
			char * temp = NULL; 
			
			temp = malloc(bytes); // user has to deallocate the string
			if(temp == NULL) printf("BAD ALLOC\n");
			memcpy(temp, _arg[id].argv_ptr, bytes);
			
			// set the val correctly,
			// double dereference on val ptr
			*(char **)val = temp;
		} break;
		case ARG_TYPE_CALLBACK: {
			
			if(_arg[id].argv_ptr != NULL && _arg[id].argv_len != 0)
				*((int *)val) = 1;
			
		} break;
	};
	
	return 0;
}

int read_args(int argc, char ** argv) {
	if(argc < 1) return -1;
	if(argv == NULL) return -1;
	
	// TODO: does not handle " or \" characters.
	
	int arg_end; // end of the argv argument in '-xxx=yyy', e.g: the equals index.
	int i, j, k, arglen, tlen, vlen;
	
	i = 1;
	while(i < argc) {
		// if argument starts with correct char
		if(argv[i][0] == '-') {
			arglen = strlen(argv[i]);
			
			// find correct end value, skip the first since its already known
			arg_end = -1;
			j = 1;
			while(j < arglen) {
				if(argv[i][j] == '=') {
					arg_end = j;
					break;
				}
				j++;
			}
			
			// both beginning and end of the argument is present
			if(arg_end > -1) {
				vlen = arglen - (arg_end + 1);
				tlen = arglen - (vlen + 2);

				if(vlen > 0) {
					j = 0;
					while(j < _argc) {			
						// check if the command exists in register arg
						if(tlen == _arg[j].arg_strlen) {
						if(strncmp(argv[i] + 1, _arg[j].arg_str, _arg[j].arg_strlen) == 0) {

							// it is a real thing, add it 
							_arg[j].argv_ptr = argv[i] + arg_end + 1;
							_arg[j].argv_len = vlen; 
							
							break;
						}
						}
						
						j++;
					}
					
				}
			} else {
				// it might be a special argument or command
				tlen = arglen - 1;
				
				j = 0;
				while(j < _argc) {
					// check if the command exists in register arg
					if(tlen == _arg[j].arg_strlen) {
					if(strncmp(argv[i] + 1, _arg[j].arg_str, _arg[j].arg_strlen) == 0) {

						// printf("do special command\n");
						_arg[j].argv_ptr = argv[i] + 1;
						_arg[j].argv_len = tlen; 
						
						break;
					}
					}
					
					j++;
				}
				
			}
		}
		
		i++;
	}
}

#endif /* ARGUMENT_H */

// 2022-08-03 :: Carl Blumenthal

// COMPILE: gcc -std=c99 argument.c -O0 -o argument
// EXAMPLE:	./argument -float=3.1459 -int=1241 -string="I am using Linux and C99!"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "argument.h"

int main(int argc, char ** argv) {
	int i = 0, help = 0;
	float f = 0;
	char * s = NULL; // has to be NULL otherwise you might attempt to deallocate BS
	
	int help_arg_id = -1;
	int i_arg_id = -1;
	int f_arg_id = -1;
	int s_arg_id = -1;
	
	// REGISTER ARGUMENTS
	help_arg_id = set_arg("help", ARG_TYPE_CALLBACK);
	i_arg_id = set_arg("int", ARG_TYPE_INT);
	f_arg_id = set_arg("float", ARG_TYPE_FLOAT);
	s_arg_id = set_arg("string", ARG_TYPE_STRING);
	
	// READ ARGUMENTS
	read_args(argc, argv); 
	
	// SET ARGUMENTS IF READ
	// this is a function call -> just push to buffer via set_arg.
	get_arg(help_arg_id, &help);
	get_arg(i_arg_id, &i);
	get_arg(f_arg_id, &f);
	get_arg(s_arg_id, &s);
	
	if(help) {
		printf("ARGUMENT HELP:\n\tArguments are passed with the format \"-xxx=yyy\".\n\tExample: -fps=60 or -string=\"Hello Sailor\".\n");
	} else {
		printf("INTEGER: %i\n", i);
		printf("FLOAT:   %f\n", f);
		printf("STRING:  %s\n", s);
	}
	
	if(s != NULL) free(s);
		
	return 0;
}


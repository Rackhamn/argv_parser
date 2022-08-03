# argv_parser
Simple parser for program arguments from argc/argv in C99 for Linux.

Arguments are passed with the format "-xxx=yyy" where you can assign values to keys. (Altough the code does not utlizise any standard keys. Only simple (and slow) string matching)
Some commands can be in the format "-xxx" for callback commands like -help.

Example:
  gcc -std=c99 argument.c -O0 -o argument
  ./argument -float=3.1459 -int=1241 -string="I am using Linux and C99!"
  
Output:
  INTEGER: 1241
  FLOAT:   3.145900
  STRING:  I am using Linux and C99!

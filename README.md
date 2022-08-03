# argv_parser
Simple parser for program arguments from argc/argv in C99 for Linux.

Arguments are passed with the format "-xxx=yyy" where you can assign values to keys. (Altough the code does not utlizise any standard keys. Only simple (and slow) string matching)
Some commands can be in the format "-xxx" for callback commands like -help.

# Example:

mdFile.new_line("gcc -std=c99 argument.c -O0 -o argument");
mdFile.new_line("./argument -float=3.1459 -int=1241 -string="I am using Linux and C99!"");

  
# Output:
mdFile.new_line("INTEGER: 1241");
mdFile.new_line("FLOAT:   3.145900");
mdFile.new_line("STRING:  I am using Linux and C99!");

## Project Explanations

for the readline() i installed the readline library as below

sudo apt-get install libreadline-dev

then I used readline() to get input from user and I stored it into an char array

since I used readline library, bilshell is compiled with -lreadline extention

gcc -Wall -g -o bilshell bilshell.c -lreadline

you can use the interactive mode with invoke as

	./bilshell N 

where N is the input number that you read in a pipe each time. It could be between 1 and 4096.

after you invoke the interactive mode 

 	“bilshell-$: ” 

pops up and you have to write command or two command.

batch mode invokes as

	./bilshell 4096 infile.txt 

 

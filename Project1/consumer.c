#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int n, char* args[]){
	int count = atoi(args[1]);
	char arraychar[1];
	for(int i = 0 ; i <count ; i++){
		read(0,arraychar,1);
	}
	return 0;
}
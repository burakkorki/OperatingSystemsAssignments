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
		char alphanumeric[] ="1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
		for(int i = 0 ; i< count ; i++){
			int random = rand() % 37;
			char forwrite[1];
			forwrite[0]=alphanumeric[random];
			printf("%c",forwrite[0]);
		}
		return 0;
}
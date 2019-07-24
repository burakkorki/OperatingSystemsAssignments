/*
  Burak Korkmaz
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>

int  bilshell(char* str){
  char* temp;
  temp = readline("bilshell-$: ");
  if(strlen(temp) != 0){
    add_history(temp);
    strcpy(str,temp);
    return 0;
  }
  else
    return 1;
}

void execute(char** comlist){
  
  pid_t pid1;

  pid1 = fork();
  if(pid1 < 0){ 
    printf("Could not create pipe 1\n");
    exit(1); ;
  }
  else if (pid1 == 0){ /* Child */
    if(execvp(comlist[0],comlist) ==-1)
		printf("command is not executed\n");

  }
  else{ /* Parent */
    wait(NULL);
  }
  return ;
}

void pipeexec(char** comlist, int place,int count){

	char arraychar[count];
	char* pipecommand1[1000];
	char* pipecommand2[1000];
	
	//printf("entered pipe - 2\n");
	
	for(int i = 0 ; i < 1000;i++){
		pipecommand1[i]=NULL;
		pipecommand2[i]=NULL;
	}
	
	/*
	for(int i = 0;i < place; i++)
		pipecommand1[i] = comlist[i];
	for(int i = place + 1; comlist[i] != NULL ;i++)
		pipecommand2[i-(place+1)]=comlist[i];*/
	
	//printf("entered pipe - 3\n");
	
	/*for(int i = 0; pipecommand1[i] != NULL ;i++)
		printf("%s ",pipecommand1[i]);
	printf("\n");
	
	for(int i = 0; pipecommand2[i] != NULL ;i++)
		printf("%s ",pipecommand2[i]);
	printf("\n");
	*/
	

	
	int charactercount;
	int readcount,charcount;
	int pipe1[2],pipe2[2];
	pid_t pid1, pid2;
	
	if(pipe(pipe1) < 0){
		printf("Could not create pipe 1\n");
		exit(1);
	}
	
	if(pipe(pipe2) < 0 ){
		printf("Could not create pipe 2\n");
		exit(1);
	}
	
	pid1 = fork();

	if(pid1 == -1)	{
		printf("Could not create child -fork1");
		exit(1);		
	}
	
	else if(pid1 == 0){
		
		close(pipe1[0]);
		close(pipe2[0]);
		close(pipe2[1]);
		dup2(pipe1[1],1);
		close(pipe1[1]);
		
		if(execvp(pipecommand1[0],pipecommand1) == -1){
			printf("command is not executed\n");
		}
		
	}
	else{/*parent*/
		//wait(NULL);
		pid2 = fork();
		
		if(pid2==-1){
			printf("Could not create child-fork 2");
			exit(1);
		}
		
		else if(pid2 == 0){
			
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[1]);
			dup2(pipe2[0],0);
			close(pipe2[0]);
			
			if(execvp(pipecommand2[0],pipecommand2) == -1){
				printf("command is not executed\n");
			}	
			
		} 
		else{/* parent */	
		
			close(pipe1[1]);
			close(pipe2[0]);
			
			while((charactercount = (read(pipe1[0],arraychar,count))>0))	{
				charcount += write(pipe2[1],arraychar,count);
				readcount += charactercount;
			}
			
			close(pipe1[0]);
			close(pipe2[1]);
			
			wait(NULL);

		}
	}	
	
	printf("character-count: %i\n",charcount);
	printf("read-call-count: %i\n",readcount);
	
}

void parser(char* str,char** comlist,int* place){

  char* token;
  int i = 0;
  
  for(int i = 0 ; i < 1000;i++){
		comlist[i]=NULL;
	}
	*place = 0;
  
  token = strtok(str,"\n " );
  
  
  while(token!=NULL){
    
    
    comlist[i]= token;
	if(strcmp(comlist[i],"|")==0){
		*place = i;
		//printf("%i\n",*place);
	}
    i++;
    token = strtok(NULL,"\n ");
  }
  
	
}

void batch(char** comlist,int count){
	

 
	FILE *fl;
	size_t length = 0;
	char* inputstr ;
	fl = fopen(comlist[2], "r");
	int place = 0;
  

  while(getline(&inputstr,&length,fl) != -1){
    parser(inputstr,comlist,&place);
	for(int j = 0 ; comlist[j] != NULL ; j++)
		printf("%s ",comlist[j]);
    printf("\n");
	if(place == 0)
       execute(comlist);
   else{
	   //printf("place %i - before pipe\n", count);
	   pipeexec(comlist,place,count);
   }
  }

  fclose(fl);  
  
}



int main(int n, char* filename[]){
	char inputstr[1000];
    char*  comlist[1000];
	int place;
	//printf("%i\n",n);
	//printf("%s\n",filename[0]);
	
  while(1){
	  
	  int n = atoi(filename[1]);
	
	if(filename[2] == NULL)	{
		if(bilshell(inputstr))
			continue;
		parser(inputstr,comlist,&place);
	}
	
	/*if(place != 0)
		exit(0);*/
	
	if(filename[2] !=NULL){
		//printf("1st place - %i\n",i);
		batch(filename,n); 
		exit(1);
		//printf("finished\n");
	}
	else if(strcmp(comlist[0],"exit")==0){
		printf("Bye\n");
		exit(0) ;
	}
	else if(strcmp(comlist[0],"cd")==0)
		chdir(comlist[1]);
	if(place!=0)
		pipeexec(comlist,place,n);
	else
		execute(comlist);
    
  }
}

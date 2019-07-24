/* $Id: pipe.c,v 1.2 2015/02/26 12:51:24 korpe Exp korpe $ **/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    int fd[2];
    int pid;
    int i;
    if (pipe(fd) < 0) {
        printf ("could not create pipe\n");
        exit (1);
    }
    

    pid = fork();
    if (pid < 0) {
        printf ("could not create child\n");
        exit (1);
    }
    
    if (pid == 0) {
        close (fd[1]);
        printf ("This is the child process.\n");
        unsigned char recv_byte;
        while (read(fd[0], &recv_byte, 1) > 0)
        {
            printf ("%d ", recv_byte);
        }
        
        printf ("\n");
        fflush (stdout);
        close(fd[0]);
        printf ("child terminating\n");
    }
    else {
        close(fd[0]);
        // sent some number of bytes
        unsigned char sent_byte;
        for (i=0; i < 100; ++i)  {
            sent_byte = (unsigned char) i;
            write (fd[1], &sent_byte, 1);
        }
        
        close(fd[1]);
        printf ("parent terminating\n");
        exit (0);
    }
    
    return 0;
    
}

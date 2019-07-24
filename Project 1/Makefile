all: bilshell consumer producer
bilshell: bilshell.c consumer.c producer.c
	gcc -Wall -g -o bilshell bilshell.c -lreadline
	gcc -Wall -g -o consumer consumer.c
	gcc -Wall -g -o producer producer.c
clean:
	rm -fr bilshell bilshell.o *~
	rm -fr consumer consumer.o *~
	rm -fr producer producer.o *~

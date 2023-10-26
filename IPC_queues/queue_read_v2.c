/*
   Description
      C Program for Message Queue (Reader Process) 
   Compile
      $ gcc -o queue_read_v2 queue_read_v2.c
*/
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

// structure for message queue 
struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
  key_t key; 
  int msgid, cnt=0; 

	key = ftok("progfile", 65); 
	msgid = msgget(key, 0666 | IPC_CREAT); 

    while(1){
	   msgrcv(msgid, &message, sizeof(message), 1, 0); 
	   printf("%s\n", message.mesg_text); 
    }

	return 0; 
} 


/*
   Description
      C Program for Message Queue (Reader Process) 
   Compile
      $ gcc -o queue_read_v1 queue_read_v1.c
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
  int msgid; 

    printf("1. Create key\n");
	// ftok to generate unique key 
	key = ftok("progfile", 65); 

    printf("2. Create message queue or read one\n");
	msgid = msgget(key, 0666 | IPC_CREAT); 

    printf("3. Receive message\n");
	msgrcv(msgid, &message, sizeof(message), 1, 0); 

    printf("4. Display message\n");
	printf("Data Received is: %s\n", message.mesg_text); 

    //printf("5. Destroy message queue\n");
	//msgctl(msgid, IPC_RMID, NULL); 

	return 0; 
} 


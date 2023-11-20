/*
   Description
      C Program for Message Queue (Writer Process) 
   Compile
      $ gcc -o queue_write_v2 queue_write_v2.c
*/
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <strings.h> 
  
// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message; 
  
int main() 
{ 
    key_t key; 
    int msgid; 
    char mesg_text[100]; 
  
    key = ftok("queue", 65);
    msgid = msgget(key, 0666 | IPC_CREAT); 
    message.mesg_type = 1; 
  
    printf("Message: ");
    scanf("%s", mesg_text); 
    strcpy(message.mesg_text, mesg_text);
  
    msgsnd(msgid, &message, sizeof(message), 0); 
    printf("Message send.\n"); 
  
    return 0; 
}


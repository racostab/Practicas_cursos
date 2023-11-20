/*
   Description
      C Program for Message Queue (Writer Process) 
   Compile
      $ gcc -o queue_write_v1 queue_write_v1.c

      $ ipcs -Q Info
      $ ipcs -q List of queues
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
  
    printf("1. Create key\n");
    key = ftok("queue", 65);
     
    printf("2. Create message queue\n");
    msgid = msgget(key, 0666 | IPC_CREAT); 
    message.mesg_type = 1; 
  
    printf("3. Reading the message from keyboard: \n");
    scanf("%s", mesg_text); 
    strcpy(message.mesg_text, mesg_text);
    printf("  msg: %s\n", mesg_text); 
  
    printf("4. Sendding message\n");
    msgsnd(msgid, &message, sizeof(message), 0); 
    printf("   msg: %s\n", message.mesg_text); 
  
    return 0; 
}


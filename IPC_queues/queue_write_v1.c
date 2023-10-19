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
  
    // ftok to generate unique key 
    key = ftok("progfile", 65); 
  
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
    message.mesg_type = 1; 
  
    printf("Write message : "); 
    //scanf("%s\n", message.mesg_text); 
    //printf("Data captured: %s\n", message.mesg_text); 

    scanf("%s", mesg_text); 
    strcpy(message.mesg_text, mesg_text);
    printf("Data captured: %s\n", mesg_text); 
  
    // msgsnd to send message 
    msgsnd(msgid, &message, sizeof(message), 0); 
  
    // display the message 
    printf("Data send is : %s\n", message.mesg_text); 
  
    return 0; 
}


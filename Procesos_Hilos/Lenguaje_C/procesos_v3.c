/*
   Description
      Several process with Tabs.
   Compile
      $ gcc -o procesos_v3 procesos_v3.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

char *tabul(int);
void hijo(int);

int main()
{
  pid_t pid;
  int nh;

  for(nh=1; nh<=5; nh++)
  {
     pid = fork();
	 switch(pid){
	   case -1: // ERROR
	 	       perror("fork");
	 	       exit(1);
	   case 0: // HIJO
	 	       //printf("Child PID: %d\n", getpid() );
	           hijo(nh);
	 	       exit(1);
	   default: // PADRE
	 	       //printf("Father PID: %d\n", getpid() );
	 		   ;
	 }
  }
  return 0;
}

void hijo(int id)
{
    while(1){
       char *tabs = tabul(id);
	   printf("%s%d\n", tabs, getpid() );
	}
}

char *tabul(int id)
{
  int cnt;
  char *str=malloc(100);
    strcpy(str,""); //str="";
    if(id != 1){
	   for(cnt=1; cnt<id; cnt++){
	      sprintf(str, "%s\t", str);
		  // str += "\t";
	   }
	}
	return str;
}
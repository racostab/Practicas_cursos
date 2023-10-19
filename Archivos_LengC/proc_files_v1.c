/*
   Description
      Two process that read/write a counter in a file.
   Compile
      $ gcc -o proc_files_v1 proc_files_v1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

char *tabul(int);
void hijo(int);
FILE *fp;

int main()
{
  pid_t pid, pid1=-1, pid2=-1;
  pid_t pidm=0;
  int nh, status;

  fp = fopen("contador.txt","a");

  for(nh=1; nh<=2; nh++)
  {
     pid = fork();
	 switch(pid){
	   case -1: // ERROR
	 	       perror("fork");
	 	       exit(1);
	   case 0: // HIJO
	           if( pid1 == -1){
			     pid1 = pid;
			   }else if( pid2 == -1){
			     pid2 = pid;
			   }
	           hijo(nh);
	 	       exit(1);
	   default: // PADRE
	           printf("Father creating\n");
	 }
  }

  printf("Father waiting\n");
  waitpid(pid1, &status, 0);
  waitpid(pid2, &status, 0);
  printf("Father finishing\n");

  fclose(fp);
  return 0;
}

void hijo(int id)
{
    //while(1){
       char *tabs = tabul(id);
	   printf("%s%d\n", tabs, getpid() );
	   sleep(4);
	   fprintf(fp, "%d\n", id);
	//}
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


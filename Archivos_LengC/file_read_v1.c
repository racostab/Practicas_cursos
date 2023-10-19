/*
   Description
      Read operation of files.
   Compile
      $ gcc -o file_read_v1 file_read_v1.c
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fp;
   int c;
  
   fp = fopen("contador.txt", "r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         break ;
      }
      printf("%c", c);
   }
   fclose(fp);

   return 0;
}


/*
   Description
      Write operation of files.
   Compile
      $ gcc -o file_write_v1 file_write_v1.c
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int num=10;
  FILE *fp;

  /*
     "r"   Open a text file for reading. The file must exist.
     "w"   Create a text file for writing. If the given file exists, its contents are destroyed unless it is a logical file.
     "a"   Open a text file in append mode for writing at the end of the file. The fopen() function creates the file if it does not exist and is not a logical file.
     "r+"  Open a text file for both reading and writing. The file must exist.
     "w+"  Create a text file for both reading and writing. If the given file exists, its contents are cleared unless it is a logical file.
     "a+"  Open a text file in append mode for reading or updating at the end of the file. The fopen() function creates the file if it does not exist.
     "rb"  Open a binary file for reading. The file must exist.
     "wb"  Create an empty binary file for writing. If the file exists, its contents are cleared unless it is a logical file.
     "ab"  Open a binary file in append mode for writing at the end of the file. The fopen function creates the file if it does not exist.
     "rb+" Open a binary file for both reading and writing. The file must exist.
     "r+b"
     "wb+" Create an empty binary file for both reading and writing. If the file exists, its contents will be cleared unless it is a logical file.
     "w+b" 
     "ab+" Open a binary file in append mode for writing at the end of the file. The fopen() function creates the file if it does not exist.
     "a+b" 

     ERROR: "rw"
     FILE *fopen(const char *filename, const char *mode);
  */
  fp = fopen("contador.txt","w");
  if(fp == NULL){
      printf("Error in fopen\n");   
      exit(1);             
  }

  /*
      int fputc(int c, FILE *stream);
      int fputs(const char *string, FILE *stream);
  */
  fprintf(fp, "Cadena\n");
  fprintf(fp, "%d\n", num);
  fprintf(fp, "%x\n", num);
  fclose(fp);

  system("cat contador.txt");

  return 0;
}


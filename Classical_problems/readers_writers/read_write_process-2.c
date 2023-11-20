#include <stdio.h>
#include <unistd.h>
// file como puntero
FILE *file;
char c;
int i,k,pid;
// Funciones
void escribir();
void leer();
int main(int argc, char *argv[])
{

    for (i=0; i<2; i++){
        pid= fork(); 
        switch ( pid ){
           case -1 :
               printf("Error \n");
               return(1);
           case 0 : // HIJO
                escribir();
           default : // PADRE
                leer();
        }
    }
    return 0;
}



void escribir()
{    
    file = fopen("archivo.txt", "w");
    if(file == NULL)
    {
        printf("Error al abrir archivo");
    }
    for(i=1;i<100;i++){
       fprintf(file, "%d \n",i);
       printf("%d\n",i);
    }
    fclose(file);      
}
void leer()
{
    file = fopen("archivo.txt", "r");
    if(file == NULL)
    {
        printf("Error al abrir archivo");
    }
    while((c=fgetc(file))!=EOF){
        printf("\t\t\t %d\n",c);
    }
    fclose(file);
}

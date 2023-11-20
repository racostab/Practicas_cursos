#include <stdio.h>
#include <unistd.h>
// #include <conio.h>
// file como puntero
FILE *file;
char c;
int i,k,pid;
// Funciones
void escribir();
void leer();
int main(int argc, char *argv[])
{

    for (i=1; i<=2; i++){
        pid= fork(); 
        switch ( pid ){
           case -1 :
               printf("Error \n");
               return(1);
           case 0 :
               for (k=3; k>=1; k--){
                   printf("H=%d \n", getpid() );
               }
           default :
                   ;
        }
    }

    printf("Escribiendo archivo...\n\n");
    escribir();
    printf("Leyendo archivo...\n\n");
    leer();
//    system("pause");
    return 0;
}

//

//

void escribir()
{    
    file = fopen("archivo.txt", "w");
    if(file == NULL)
    {
        printf("Error al abrir archivo");
    }
    fprintf(file, "Hola mundo!\n");
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
        printf("%c",c);
    }
    fclose(file);
}

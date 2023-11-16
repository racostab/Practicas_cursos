/*
Programa Servidor que Abre el Socket 15005

Ahora abre una ventana de TELNET y conecta asi:

Si eres una makina de la RED, solo conectate desde TELNET a la IP donde esta activado o corriendo el Servidor
Si eres el mismo Servidor, solo tipea tu IP loopback que por lo general es: 120.0.0.1 o localhost   ;)

Coder: Diabliyo
e-mail: darkdiabliyo@hotmail.com
Nacionalidad: Reynosa, Tamaulipas, Mexico ;)
Codigo: socket_Diabliyo.c
Requisitos: Sistema
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//#pragma comment(lib, "ws2_32.lib");

#define BACKLOG 5
#define N 150
#define PORT 1616

/*Prototipos*/
int servidor_socket( int sockds );
int cliente_socket( int sockds_c, int sockds );
int recivir( char *buf, int sockds );
int enviar( char *cad, int cliente );
void chat_enviar( int i, int sockds, int sockds_max, fd_set registro, char *buf );

void chat_enviar( int i, int sockds, int sockds_max, fd_set registro, char *buf )
   {
   int j;
      
   for( j=0; j<=sockds_max; j++ )
      {
      if( FD_ISSET( j, &registro ) )
         {
         if( j!=sockds && j!=i )
            {
            if( enviar( buf, j ) == -1 )
               {
               perror( "send" );
               getchar();
               }
            }
         }
      }
   }

int enviar( char *cad, int cliente )
   {
   int bytes_n, size_c;
      
   size_c= strlen( cad );
   bytes_n= send( cliente, cad, size_c, 0 );
   return bytes_n;
   }

int recivir( char *buf, int sockds )
   {
   int bytes_n;
   
   bytes_n= recv( sockds, buf, N, 0 );
   buf[bytes_n]='\0';
   return bytes_n;
   }

int cliente_socket( int sockds_c, int sockds )
   {
   int size_c=0;
   struct sockaddr cliente;
   
   size_c= sizeof( struct sockaddr );
   if( ( sockds_c= accept( sockds, &cliente, &size_c ) ) == -1 )
      {
      perror( "accept" );
      getchar();
      return -1;
      }
   printf( "\nNueva conexion establecida ID: %i", sockds_c );
   return sockds_c;
   }

int servidor_socket( int sockds )
   {
   struct sockaddr_in servidor;

   servidor.sin_family= AF_INET;
   servidor.sin_port= htons( PORT );
   memset( &(servidor.sin_zero), '\0', 8 );
   servidor.sin_addr.s_addr= inet_addr( "127.0.0.1" );
   //inet_aton( "127.0.0.1", &(servidor.sin_addr) );
   
   if( ( sockds= socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
      {
      perror( "socket" );
      getchar();
      return -1;
      }
      
   if( bind( sockds, (struct sockaddr *)&servidor, sizeof(struct sockaddr) ) == -1 )
      {
      perror( "bind" );
      getchar();
      return -1;
      }
      
   if( listen( sockds, BACKLOG ) == -1 )
      {
      perror( "listen" );
      getchar();
      return -1;
      }
   return sockds;
   }

int main()
   {
   fd_set registro, registro_aux;
   int sockds, sockds_c, sockds_max, i, j, bytes_n;
   char buf[N];
 
   FD_ZERO( &registro );
   FD_ZERO( &registro_aux);
   
   WSADATA WSAData;
    WSAStartup(MAKEWORD(1,1), &WSAData);
      
   if( ( sockds= servidor_socket( sockds ) ) == -1 )
      exit(1);
   
   FD_SET( sockds, &registro ); /*Agregamos el socker principal al registro*/
   sockds_max= sockds; /*el contador de Descriptores de Sockets ( sockds_max ) guarda el contenido del descriptor principal ( sockds )*/
   for(;;)
      {
      registro_aux= registro; /*hacemos copia del registri principal, en "registro_aux"*/
      if( select( sockds_max+1, &registro_aux, NULL, NULL, NULL ) == -1 )
         {
         perror( "select" );
         getchar();
         exit(1);
         }
      for( i=0; i<=sockds_max; i++ )
         {
         if( FD_ISSET( i, &registro_aux ) )
            {
            if( i==sockds )
               {
               if( ( sockds_c= cliente_socket( sockds_c, sockds ) ) == -1 )  /*Acepta la conexion del cliente*/
                  exit(1);
               else
                  {
                  FD_SET( sockds_c, &registro ); /*Agrega el descriptor del cliente al registro*/
                  if( sockds_c>sockds_max )   sockds_max= sockds_c; /*Checa y actualiza el contador de descriptores ( sockds_mx )*/
                  chat_enviar( sockds, sockds, sockds_max, registro, "-------- Conexion Recivda -------\n" );
                  }
               }
            else
               {
               if( ( bytes_n= recivir( buf, i ) ) <=0 )
                  {
                  switch( bytes_n )
                     {
                     case 0:
                        printf( "\n\nEl Cliente %i Cerro la Conexion.", i );
                        chat_enviar( sockds, sockds, sockds_max, registro, "-------- Se ha Desconectado --------\n" );
                        break;
                     case -1:
                        perror( "recv" );
                        getchar();
                        break;
                     }
                  close(i);
                  FD_CLR( i, &registro );
                  }
               else
                  chat_enviar( i, sockds, sockds_max, registro, buf );
               }
            }
         }
      }
   printf( "\n\nPulsa para salir...." );
   getchar();
   close(sockds);
   return 0;
   }

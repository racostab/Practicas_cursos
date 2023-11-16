/********************************************************
 *
 * Func.: Obtener datos del host como el DNS.
 *
 ********************************************************/
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
 struct hostent *he;

   if(argc!=2){
     printf("Utilizar: %s <hostname> \n", argv[0]);
     return(-1);
   }

   // gethostbyname();
   printf("Hostname: %s \n", he->h_name);
   printf("IP address: %s \n", inet_ntoa(*((struct in_addr *)he->h_addr)));

}




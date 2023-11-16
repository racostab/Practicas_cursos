/********************************************************
 *
 * Func.: Sockets en windows.
 *   Tipo:     SOCK_STREAM
 *   Dominio:  AF_INET
 *
 ********************************************************/
#include <iostream>
#include <winsock.h>

int main()
{

SOCKET Socket;
WSADATA wsaData;
  
  int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
   if ( iResult != NO_ERROR )
   {
       WSACleanup();
       return 0;
   }
      
   Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP );
  
   if (Socket == INVALID_SOCKET )
   {
       WSACleanup();
       return 0;
   }

   struct sockaddr_in service;
   service.sin_family = AF_INET;
   service.sin_addr.s_addr = INADDR_ANY;
   service.sin_port = htons(1234);

   if (bind(Socket, (SOCKADDR*) &service,sizeof(service)) == SOCKET_ERROR)
   {
       closesocket(Socket);
       return 0;
   }

   if (listen( Socket, 1 ) == SOCKET_ERROR)
    {
      return 0;
    }
}

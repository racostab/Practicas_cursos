/*
 * . Socket server.
 *
 *  $ javac tcp_inet_srv.java
 *  $ java tcp_inet_srv
 */
import java.io.*;
import java.net.*;

public class tcp_inet_srv
{
   public static void main(String[] args)
   {
      try{
         ServerSocket server = new ServerSocket(6666);
         System.out.println("1. Socket creado");

         System.out.println("2a. Accepting conections");
         Socket client = server.accept();
         System.out.println("2b. one received");

         DataInputStream din = new DataInputStream(client.getInputStream());
         System.out.println("3. InputStream");
   
         String	str = (String)din.readUTF();
         System.out.println("4. Message: "+ str);
         server.close();
      }catch(Exception e){
         System.out.println(e);
      }
   }
}

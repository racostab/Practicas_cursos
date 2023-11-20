/*
 *   Socket client.
 *
 *  $ javac tcp_inet_clt.java
 *  $ java tcp_inet_clt
 *  $ java tcp_inet_clt 123
 *  $ java tcp_inet_clt "123 456"
 */
import java.net.*;
import java.io.*;

public class tcp_inet_clt 
{
   public static void main(String[] args)
   {
     String str;
       try{	
          System.out.println("Args: "+ args.length);
          if( args.length < 1){
            str = "[Mensaje cliente]";
          }else{
            str = args[0];
          }
          Socket client = new Socket("localhost",6666);
          System.out.println("1. Socket creado");

          DataOutputStream dout = new DataOutputStream(client.getOutputStream());
          System.out.println("2. OutputStream");
   
          dout.writeUTF(str);
          dout.flush();
          System.out.println("3. Sending msg: "+ str);
   
          dout.close();
          client.close();
          System.out.println("4. End");
       }catch(Exception e){
          System.out.println(e);
       }
    }
}

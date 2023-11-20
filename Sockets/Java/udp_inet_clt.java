/*
 *   Cliente
 *
 *      $ javac udp_inet_clt.java
 *      $ java udp_inet_clt
 */
import java.net.*;  

public class udp_inet_clt
{
   public static void main(String[] args) throws Exception
   {
     DatagramSocket ds = new DatagramSocket();  
     InetAddress ip = InetAddress.getByName("127.0.0.1");  
        
       System.out.println("1. Clt creating message");  
       String str = "[Mensaje clt]";  
       DatagramPacket dp = new DatagramPacket(str.getBytes(), str.length(), ip, 3000);  
       ds.send(dp);
       System.out.println("2. Clt messaged sent.");  

       ds.close();  
   }  
} 

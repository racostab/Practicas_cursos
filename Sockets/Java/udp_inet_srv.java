/*
 *   Cliente
 *
 *      $ javac udp_inet_srv.java
 *      $ java udp_inet_srv
 */
import java.net.*;  

public class udp_inet_srv
{
  public static void main(String[] args) throws Exception
  {
    DatagramSocket ds = new DatagramSocket(3000);  
    byte[] buf = new byte[1024];  
    DatagramPacket dp = new DatagramPacket(buf, 1024);  

      System.out.println("1. Server receiving ...");  
      ds.receive(dp);  
      System.out.println("2. Message received");  
      String str = new String(dp.getData(), 0, dp.getLength());  
      System.out.println(str);  
      ds.close();  
  }  
}

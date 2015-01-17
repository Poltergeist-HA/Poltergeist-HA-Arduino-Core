#include <Arduino.h>
#include <UIPEthernet.h>

EthernetUDP udp;

unsigned long nextBroadcast;

void markFirst(){
  nextBroadcast = millis()+BROADCAST_INTERVAL;
}

void doBroadcast(){
  int success;

  if (((signed long)(millis()-nextBroadcast))>0){
    do {
      success = udp.beginPacket(IPAddress(255,255,255,255),BROADCAST_PORT);
      //beginPacket fails if remote ethaddr is unknown. In this case an
      //arp-request is send out first and beginPacket succeeds as soon
      //the arp-response is received.
    } while (!success && ((signed long)(millis()-nextBroadcast))<0);
    if (success ){
      udp.write(CLIENT_TYPE);
      udp.write(" ");
      char port[17];
      itoa(SERVER_PORT, port, 10);
      udp.write(port);

      udp.endPacket();
    }

    udp.stop();
    nextBroadcast = millis()+BROADCAST_INTERVAL;
  }
}
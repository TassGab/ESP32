#include "NTPclass.h"
//wifi event handler
extern WiFiUDP NTPclass::udp;
extern bool NTPclass::NTP_IsConnect=false;
NTPclass::NTPclass()
{
    

}
void WiFiEvent(WiFiEvent_t event)
 {

    switch((unsigned int)event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          NTPclass::udp.begin(WiFi.localIP(),NTPclass::udpPort);
          NTPclass::NTP_IsConnect = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          NTPclass::NTP_IsConnect = false;
          break;
    }
}

void NTPclass::sendNTPpacket(const char* address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
 
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
void NTPclass::connectToWiFi(const char * ssid,const char * pwd)
{
  Serial.println("Connecting to WiFi network: " + String(ssid));
  Serial.print("NetName=");Serial.println(ssid);
  Serial.print("psw=");Serial.println(pwd);
  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}
void NTPclass::NTPconnect()
{
  Preferences pref;
  pref.begin("WiFiConf",false);
  String netname=pref.getString("networkName");
  String psw=pref.getString("networkPswd");
  
  pref.end();
  if((netname.compareTo("")!=0) & (psw.compareTo("")!=0))
  {
    const char * pnet;
    short l=netname.length();
    char pnetchar[l+1];
    netname.toCharArray(pnetchar,l+1); 
    pnet=(char *)&pnetchar;
    
    const char * ppsw;
    l=psw.length();
    char pwschar[l+1];
    psw.toCharArray(pwschar,l+1); 
    ppsw= (char *) &pwschar;    
    Serial.print("NetName =");Serial.print(netname); Serial.print("\tPointer =");Serial.println(String(*pnet));
    Serial.print("psw=");Serial.print(psw); Serial.print("\tPointer =");Serial.println(String(*ppsw));
    connectToWiFi(pnet,ppsw);
  }
}



//
unsigned long NTPclass::NTP_GetUnixTime()
{
  unsigned long epoch = 0;

 if(NTP_IsConnect){
    //Send a packet
//    udp.beginPacket(udpAddress,udpPort);
    sendNTPpacket(udpAddress);
     // wait to see if a reply is available
  delay(1000);
  if ( udp.parsePacket() ) {
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet 
                                             // into the buffer
    //the timestamp starts at byte 40 of the received packet 
    // and is four bytes, or two words, long. First, 
    // esxtract the two words:
 
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
     const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    epoch = secsSince1900 - seventyYears;
    }
    
  }
  return epoch;
}
 

/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
//#include <WiFi.h>
//#include <WiFiUdp.h>
#include "NTPclass.h"
// WiFi network name and password:
//const char * networkName = "ubx";
//const char * networkPswd = "GqpZvmK8@r5yL#AP";
//
////IP address to send UDP data to:
//// either use the ip address of the server or 
//// a network broadcast address
//const char * udpAddress = "time.nist.gov";
//const int udpPort = 8888;
//const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 
//                                // 48 bytes of the message
// 
//byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming 
//                                     //and outgoing packets
////Are we currently connected?
//boolean connected = false;
//
////The udp library class
//WiFiUDP udp;
NTPclass NTP;
void setup(){
  // Initilize hardware serial:
  Serial.begin(115200);
  Preferences pref;
  pref.begin("WiFiConf",false);
  pref.putString("networkName","ubx");
  pref.putString("networkPswd","GqpZvmK8@r5yL#AP");
  pref.end();
  //Connect to the WiFi network
  //connectToWiFi(networkName, networkPswd);
  NTP.NTPconnect();
}

void loop(){
  //only send data when connected
//  if(connected){
//    //Send a packet
////    udp.beginPacket(udpAddress,udpPort);
//    sendNTPpacket(udpAddress);
//     // wait to see if a reply is available
////  delay(1000);
//  if ( udp.parsePacket() ) {
//    // We've received a packet, read the data from it
//    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet 
//                                             // into the buffer
//    //the timestamp starts at byte 40 of the received packet 
//    // and is four bytes, or two words, long. First, 
//    // esxtract the two words:
// 
//    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
//    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
//    // combine the four bytes (two words) into a long integer
//    // this is NTP time (seconds since Jan 1 1900):
//    unsigned long secsSince1900 = highWord << 16 | lowWord;
//    Serial.print("Seconds since Jan 1 1900 = " );
//    Serial.println(secsSince1900);
// 
//    // now convert NTP time into everyday time:
//    Serial.print("Unix time = ");
//    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
//    const unsigned long seventyYears = 2208988800UL;
//    // subtract seventy years:
//    unsigned long epoch = secsSince1900 - seventyYears;
//    // print Unix time:
    if (NTPclass::NTP_IsConnect){
    unsigned long epoch=NTP.NTP_GetUnixTime();
    Serial.println(epoch);
 
 
    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich 
                                            // Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour 
                                            // (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute 
                                        // (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  }
  // wait ten seconds before asking for the time again
      //udp.endPacket();
  delay(10000);

  }
 


//void connectToWiFi(const char * ssid, const char * pwd){
//  Serial.println("Connecting to WiFi network: " + String(ssid));
//
//  // delete old config
//  WiFi.disconnect(true);
//  //register event handler
//  WiFi.onEvent(WiFiEvent);
//  
//  //Initiate connection
//  WiFi.begin(ssid, pwd);
//
//  Serial.println("Waiting for WIFI connection...");
//}

////wifi event handler
//void WiFiEvent(WiFiEvent_t event){
//    switch((unsigned int)event) {
//      case SYSTEM_EVENT_STA_GOT_IP:
//          //When connected set 
//          Serial.print("WiFi connected! IP address: ");
//          Serial.println(WiFi.localIP());  
//          //initializes the UDP state
//          //This initializes the transfer buffer
//          udp.begin(WiFi.localIP(),udpPort);
//          connected = true;
//          break;
//      case SYSTEM_EVENT_STA_DISCONNECTED:
//          Serial.println("WiFi lost connection");
//          connected = false;
//          break;
//    }
//}
//void sendNTPpacket(const char* address)
//{
//  // set all bytes in the buffer to 0
//  memset(packetBuffer, 0, NTP_PACKET_SIZE);
//  // Initialize values needed to form NTP request
//  // (see URL above for details on the packets)
//  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
//  packetBuffer[1] = 0;     // Stratum, or type of clock
//  packetBuffer[2] = 6;     // Polling Interval
//  packetBuffer[3] = 0xEC;  // Peer Clock Precision
//  // 8 bytes of zero for Root Delay & Root Dispersion
//  packetBuffer[12]  = 49;
//  packetBuffer[13]  = 0x4E;
//  packetBuffer[14]  = 49;
//  packetBuffer[15]  = 52;
// 
//  // all NTP fields have been given values, now
//  // you can send a packet requesting a timestamp:
//  udp.beginPacket(address, 123); //NTP requests are to port 123
//  udp.write(packetBuffer, NTP_PACKET_SIZE);
//  udp.endPacket();
//}

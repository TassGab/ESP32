/*
 NTPclass.h - Library for NTP client implementation on ESP32
 
 Gabriele Tasselli, January 22nd, 2018
 */
#ifndef NTPclass_h
#define NTPclass_h

//#include "Logging_class.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Preferences.h>
class NTPclass
{
  public:
  NTPclass();
  unsigned long NTP_GetUnixTime();
  void NTPconnect();
  static bool NTP_IsConnect;
  static WiFiUDP udp;
  static const int udpPort = 8888;
  private:
  static const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first
                                // 48 bytes of the message
  const char * udpAddress = "time.nist.gov";

  byte packetBuffer[NTPclass::NTP_PACKET_SIZE]; //buffer to hold incoming
  
  void sendNTPpacket(const char*);
  void connectToWiFi(const char *,const char *);  
  //void WiFiEvent(WiFiEvent_t);
};

#endif


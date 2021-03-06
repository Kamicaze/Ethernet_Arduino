/*
 Twitter SimplePost
 
 SimplePost messages to Twitter (tweet) from Aruduino with Ethernet Shield!

 Notice
 -The library uses this site as a proxy server for OAuth stuff. Your tweet may not be applied during maintenance of this site.
 -Please avoid sending more than 1 request per minute not to overload the server.
 -Twitter seems to reject repeated tweets with the same contenet (returns error 403).
 
 Reference & Lincense
 URL : http://arduino-tweet.appspot.com/
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 2011 
 by NeoCat - (ver1.3 - Support IDE 1.0)
 tested & 
 modified 13 Aug 2013 
 by Soohwan Kim - (ver1.3 - Support IDE 1.0.5)
 */
 
#include <SPI.h> // needed in Arduino 0019 or later
#include <Ethernet_v2.h>
#include "./Twitter.h" // Twitter.h in library/Ethernet folder. @diffinsight 2013-08-19

// The includion of EthernetDNS is not needed in Arduino IDE 1.0 or later.
// Please uncomment below in Arduino IDE 0022 or earlier.
//#include <EthernetDNS.h>


// Ethernet Shield Settings
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif  

// If you don't specify the IP address, DHCP is used(only in Arduino 1.0 or later).
// fill in an available IP address on your network here,
IPAddress ip(1,1,1,1);
IPAddress gw(1,1,1,1);
IPAddress snip(1,1,1,1);
IPAddress dnsip(1,1,1,1);

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter("YOUR-TOKEN-HERE");

// Message to post
char msg[] = "Hello! Tweet! Tweet! Tweet! This message is written from Arduino Pro Mini!";

void setup()
{
  delay(1000);  
  // start the Ethernet connection:
#if defined(WIZ550io_WITH_MACADDRESS)
  Ethernet.begin(ip, dnsip, gw,snip);
#else
  Ethernet.begin(mac, ip, dnsip, gw,snip);  
#endif
  // or you can use DHCP for autoomatic IP address configuration.
  // Ethernet.begin(mac);
  Serial.begin(9600);
  
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    // Specify &Serial to output received response to Serial.
    // If no output is required, you can just omit the argument, e.g.
    // int status = twitter.wait();
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}

void loop()
{
}

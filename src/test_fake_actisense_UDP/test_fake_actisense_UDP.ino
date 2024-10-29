#include <WiFi.h>
#include <WiFiUdp.h>
#include <GRGB.h>

// Configuration
const char* ssid = "WSK-1-Actisense";
const char* password = "";  // Password can be set if needed
const int udpPort = 60003;

GRGB led(COMMON_CATHODE, 22, 21, 23);

WiFiUDP udp;

String serialBuffer = "";
unsigned long nextSend = 0;
const unsigned long sendInterval = 100;  // Send interval in milliseconds

void setup() {
  // Initialize serial communication
  led.setColor(GRed);
  Serial.begin(115200);
  delay(100);

  Serial.println("Wifi AP");
  // Set WiFi mode to AP
  WiFi.mode(WIFI_AP);
  // Configure and start the Access Point
  WiFi.softAP(ssid, password);

  // Start the server
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Wait for a client to connect
  Serial.println("Waiting for a client to connect...");
  while (WiFi.softAPgetStationNum() == 0) {
    delay(500);  // Wait for 500 milliseconds before checking again
    led.setColor(GYellow);
  }
  Serial.println("Client connected");

  Serial.println("UDP begin");
  // Start UDP on specified port
  udp.begin(udpPort);
  Serial.println("UDP broadcast sender started on port " + String(udpPort));
  Serial2.begin(38400, SERIAL_8N1, 17, 16);  // Serial RS232
  led.setColor(GGreen);
}

unsigned long backToGreen = 0;
/*

//--------
unsigned long nextPeriod = 0;
int baudRates[] = {
  19200, 
  28800, 38400, 57600, 74880, 115200, 128000, 144000, 153600, 192000, 
  256000, 384000
};
int numBaudRates = sizeof(baudRates) / sizeof(baudRates[0]);
int currentIndex = -1;
//--------
*/

void loop() {
//--------
/*
  if (millis()>nextPeriod) {

    // Increment the baud rate index
    currentIndex = (currentIndex + 1) % numBaudRates;

    // Reinitialize Serial2 with the new baud rate
    Serial2.end();
    Serial2.begin(baudRates[currentIndex++], SERIAL_8N1, 17, 16);
    
    // Print the new baud rate
    Serial.println("Baud rate changed to: " + String(baudRates[currentIndex]));
    nextPeriod = millis()+5000;
  }
*/
//--------


  if(millis() > backToGreen)
  {
    led.setColor(GGreen);
  }

  // Read from Serial
  byte activeSerial = 0;
  while (millis() < nextSend) {
    if (Serial2.available())  // Priority to Serial2
    {
      char c = (char)Serial2.read();
      serialBuffer += c;

      if(c=='!')
        led.setColor(GAqua);
      /*else
        if(c==',')
          led.setColor(GAqua);*/


      //Serial.println("Serial2!");
    }
    else if (Serial.available())
      serialBuffer += (char)Serial.read();
  }

  nextSend = millis() + sendInterval;

  if (serialBuffer.length() > 0) {
    led.setColor(GBlue);
    backToGreen = millis() + 1000;
    sendUDP(serialBuffer);
    serialBuffer = "";  // Clear the buffer after sending
  }
}

void sendUDP(String data) {
  // Send UDP packet to broadcast address
  udp.beginPacket(IPAddress(255, 255, 255, 255), udpPort);  // Broadcast address
  udp.print(data);
  udp.endPacket();
  Serial.println("Sent: " + data);
}


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define DW D1 
#define DA D2
#define DS D3
#define DD D4

const char *ssid = "RC";
const char *password = "12345678";
const int port = 3305;
const int channel = 3;

WiFiUDP udp;

void setup() {
  // Set pins  
  pinMode(DW,OUTPUT);
  pinMode(DA,OUTPUT);
  pinMode(DS,OUTPUT);
  pinMode(DD ,OUTPUT);

  // Start serial
  Serial.begin(9600);
  Serial.println("Configuring access point...");

  // Start Access point on specified channel
  WiFi.softAP(ssid, password, channel);
  IPAddress myIP = WiFi.softAPIP();

  // Debug
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Start capture
  udp.begin(port);
  Serial.println("Server started");
}

void loop() {
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    char buf[packetSize];

    // Debug
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    int len = udp.read(buf, packetSize);
    if (len > 0) { buf[len] = 0; }

    // Debug
    Serial.println("Contents:");
    Serial.println(buf);
    
    if (strcmp(buf, "w") == 0) { moveForward(); }
    
    if (strcmp(buf, "s") == 0) { moveBackward(); }

    if (strcmp(buf, "a") == 0) { turnLeft(); }
    
    if (strcmp(buf, "d") == 0) { turnRight(); }  
     
    if (strcmp(buf, "b") == 0) { stopMotors(); }
    
  } else { stopMotors(); }
}

void moveForward() {
  Serial.println("W pressed");
  digitalWrite(DW,HIGH);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
}

void moveBackward() {
  Serial.println("S pressed");
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,HIGH);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
}

void turnLeft() {
  Serial.println("A pressed");
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,HIGH);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
 
}

void turnRight() {
  Serial.println("D pressed");
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,HIGH);    //使直流电机（右）GO
  

}

void stopMotors() {
  digitalWrite(DW,LOW);    //使直流电机（右）GO
  digitalWrite(DS,LOW);    //使直流电机（右）GO
  digitalWrite(DA,LOW);    //使直流电机（右）GO
  digitalWrite(DD,LOW);    //使直流电机（右）GO
}


#include <SoftwareSerial.h>
#define RX 2
#define TX 3

String AP = "mover";       // CHANGE ME
String PASS = "robo2023it"; // CHANGE ME

String HOST = "192.168.1.140";
String PORT = "8080";

int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 1;

SoftwareSerial esp8266(RX, TX);

long long last_time = 0;
#define TIME_SENT 1000

//get data from sensors
long get_latitude() {
  float latitude = 54.865945;
  return latitude * 1000000;
}

long get_longitude() {
  float longitude = 60.012678;
  return longitude * 1000000;
}

int get_charge() {
  int charge = random(1, 100);
  return charge;
}

String sensors() {
  return (String)get_latitude() + "-" + (String)get_longitude() + "-" + (String)get_charge() + "#";
}

//send ap command to esp01
void sendCommand(String command, int maxTime, char readReplay[]) {
//  Serial.print(countTrueCommand);
//  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while (countTimeCommand < (maxTime * 1))
  {
    esp8266.println(command);//at+cipsend
    if (esp8266.find(readReplay)) //ok
    {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if (found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK");
}

void loop() {
  if (millis() - last_time > TIME_SENT) {

    String getData = sensors();
    sendCommand("AT+CIPMUX=1", 5, "OK");
    sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
    sendCommand("AT+CIPSEND=0," + String(getData.length() + 2), 4, ">");
    sendCommand(getData, 5, "OK");

    countTrueCommand++;
    sendCommand("AT+CIPCLOSE=0", 5, "OK");

    last_time = millis();
  }
}

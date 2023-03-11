#include <WiFi.h>

#define J_R 34
#define J_L 32
#define LED 2
bool flag = true;

const char* ssid = "mover";
const char* password = "robo2023it";

const uint16_t port = 8080;
const char * host = "192.168.1.210";

void load_led() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED, 1);
    delay(250);
    digitalWrite(LED, 0);
    delay(250);
  }
  digitalWrite(LED, 1);
}

void setup() {
  Serial.begin(115200);
  pinMode(J_R, INPUT);
  pinMode(J_L, INPUT);
  pinMode(LED, OUTPUT);

  load_led();

  //подключение к сети
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());
}

byte right() {
  byte v = map(analogRead(J_R), 0, 4095, 0, 255);
  return v;
}

byte left() {
  byte v = map(analogRead(J_L), 0, 4095, 0, 255);
  return v;
}

void loop() {
  WiFiClient client;
  client.connect(host, port);

  if (!client.connect(host, port)) {
    Serial.println("connection to host failed");
    delay(500);
    return;
  }

  client.print(right());
  client.print('\0');
  client.print(left());
  client.print('\0');
  client.stop();
}

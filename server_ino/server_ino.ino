#include <ESP8266WiFi.h>

//настройки сети
#define ssid "mover"
#define pass "robo2023it"

//данные сервера
#define host "192.168.1.140"
#define port 80
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP address:    ");
  Serial.println(WiFi.localIP());
}

long get_latitude(){
  float latitude = 54.865945;
  return latitude*1000000;
}

long get_longitude(){
  float longitude = 60.012678;
  return longitude*1000000;
}

int get_charge(){
  int charge = random(1,100);
  return charge;
}

void loop() {
  if (!client.connect(host, port))
  {
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }
  client.println((String)get_latitude() + "-" + (String)get_longitude() + "-" + (String)get_charge() + "#");
  delay(5000);
}

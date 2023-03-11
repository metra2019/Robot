#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String ssid = "mover";
String pass = "robo2023it";
const int port = 8080;

WiFiServer server(port);
String req;

int rval = 0, lval = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP address:    ");
  Serial.println(WiFi.localIP());


  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client.available() > 0) {
    req = client.readStringUntil('\0');
    lval = req.toInt();
    req = client.readStringUntil('\0');
    rval = req.toInt();
  }
  Serial.print(lval);
  Serial.print("\t");
  Serial.println(rval);
}

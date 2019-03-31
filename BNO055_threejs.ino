#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "index.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 bno = Adafruit_BNO055(); //SDA GPIO21 //SCL GPIO22


WebServer server(80);
const char* ssid = "silvia";
const char* password = "silviahomewifi";

void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handleBNO() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  String strEuler = String(euler.x())+","+String(euler.y()) + "," +String(euler.z()) + ",0" ;
  Serial.println(strEuler);
  server.send(200, "text/plane", strEuler);
}

void setup(void) {
  Serial.begin(115200);

  Serial.println();
  Serial.println("Booting Sketch...");
  if (!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);

  //ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  //----------------------------------------------------------------

  server.on("/", handleRoot);      //This is display page
  server.on("/readBNO", handleBNO);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(1);
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include "DHT.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "2.4G_MARIDOS";  // SSID da rede
const char* password = "amorverdadeiro";  //Senha da rede


ESP8266WebServer server(80);

int momento = 0;

int situacao = 0;

float Temperature; //temp
float Humidity;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);

  Serial.println("Conectando: ");
  Serial.println(ssid);

  //CONECTAR COM A REDE WI-FI LOCAL
  WiFi.begin(ssid, password);

  //CHECAR SE A CONEXÃO WI-FI FOI REALIZADA
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Wi-Fi conectado...");
  Serial.print("Endereço IP:");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado");  
  
}

int trocar_info() {
// wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://kaa.hol.es")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);

          Serial.println("passou");
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

 
  
 
}



void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

  if (momento % 30 == 0) {
    trocar_info();
  }

  momento++;
  if (momento >= 120){ momento = 0;}
  delay(1000);
}


void handle_OnConnect() {

 Temperature = 10.5; // Gets the values of the temperature
  Humidity = 10; // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  /*String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU Weather Report</h1>\n";
  
  ptr +="<p>Temperature: ";
  ptr +=(int)Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p>Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
*/

  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<meta charset=\"utf-8\">";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Módulo 1</h1>\n";
  
  ptr +="<p>Temperatura: ";
  ptr +=(float)Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p>Humidade: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

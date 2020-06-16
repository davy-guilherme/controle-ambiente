#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


/*Put your SSID & Password*/
//const char* ssid = "hafelicidade";  // Enter SSID here
//const char* password = "ANETEMARIA";  //Enter Password here

const char* ssids = "ESP8266-Access-Point";  // Enter SSID here
const char* passwords = "12345678";  //Enter Password here

const char* ssid = "2.4G_MARIDOS";  // Enter SSID here
const char* password = "amorverdadeiro";  //Enter Password here

int momento = 0;

ESP8266WebServer server(80);
/*
// DHT Sensor
uint8_t DHTPin = D4; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 */
void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.softAP(ssids, passwords);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("\n\n");
Serial.print("AP IP address: ");
Serial.println(IP);
  
  /*pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Conectando: ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
*/
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  
 /* if (momento % 30 == 0) {
    gravar();
  }

  momento++;
  if (momento >= 120){ momento = 0;}
  delay(1000);*/
}


/*
void gravar() {
  
   * Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  
  char buf[25];
  String sTemp = dtostrf(Temperature, 5, 2, buf);
  Serial.println(sTemp);

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://stark.servicesweb.xyz/interface/enviar_temperatura.php?temp=" + sTemp + "&mod=1")) {  // HTTP


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



*/

void handle_OnConnect() {

 //Temperature = dht.readTemperature(); // Gets the values of the temperature
  //Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(2,7)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta charset=\"utf-8\">\n";
  ptr +="<title>STARK | Configuração</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Configure seu módulo STARK</h1>\n";
  
  ptr +="<p>Nome da rede: </p>";
  ptr +="<input type=\"text\" id=\"nome\" name=\"nome\">";
  ptr +="<p>Senha da rede: </p> ";
  ptr +="<input type=\"text\" id=\"senha\" name=\"senha\">";
  ptr +="<br>";
  ptr +="<input type=\"submit\" value=\"Configurar\">";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";

/*

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
  */
  return ptr;
}

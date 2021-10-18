#include <WiFi.h>
#include <Arduino.h>

#define ldr 0
#define led1 14
#define led2 12
#define led3 13

const char* ssid = "Rubbo-Wifi";
const char* password = "marbb9844";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode (ldr, INPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
 
 
  Serial.println();
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");

  IPAddress myIP = WiFi.softAPIP();
  Serial.println("Endereço de IP: ");
  Serial.println(myIP);
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("cliente encontrado");
  while(!client.connected()) {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.print(req);
  client.flush();

  if(req.indexOf("led1") != -1) {
     digitalWrite(led1, !digitalRead (led1));
  }
     if(req.indexOf("led2") != -1) {
     digitalWrite(led2, !digitalRead (led2));
  }

    if(req.indexOf("led3") != -1) {
     digitalWrite(led3, !digitalRead (led3));
 
  }
  if(req.indexOf("todos") != -1){
     digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW);
  }

  int luminosidade = analogRead (ldr);
   
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
         
          if(digitalRead (led1)){
            client.print("l1on");
          } else{
            client.println("l1of");
          }

          client.print(",");
           if(digitalRead (led2))
          {
            client.print("l2on");
          } else{
            client.println("l2of");
          }

          client.print(",");

           if(digitalRead (led3))
          {
            client.print("l3on");
          } else{
            client.println("l3of");
         
          }
          client.print(",");

          client.print(luminosidade);

  delay(1);
  }

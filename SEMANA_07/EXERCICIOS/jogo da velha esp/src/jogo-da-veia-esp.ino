#include "WiFi.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>
#include <iostream>
#include <SPI.h> 


const int ledX = 7;
const int ledO = 8;
const int buz = 16;

// Change the SSID and PASSWORD here if needed
const char * WIFI_FTM_SSID = "Inteli-COLLEGE"; // SSID of AP that has FTM Enabled
const char * WIFI_FTM_PASS = "QazWsx@123"; // STA Password



void httpRequest(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection statu
      HTTPClient http;  //Declare an object of class HTTPClient
      const char* GETCommand = "http://10.128.64.165:5500/var";
      http.begin(GETCommand);  //Specify request destination

      int httpCode = http.GET(); //Send the request
      Serial.print("Get command: ");
      Serial.println(GETCommand);
 
      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        Serial.println("payload: " + payload); 
        Serial.println(payload[11]);                     //Print the response payload 
        Serial.println(payload[12]);
        Serial.println(payload[13]);                     //Print the response payload 
                             //Print the response payload 
                            //Print the response payload 
        if (payload[11] == 'x'){
          digitalWrite(ledX,1);
          tone(buz,450,500);
          delay(1500);
          digitalWrite(ledX,0);
        }else if (payload[11] == 'o'){
          digitalWrite(ledO,1);
          tone(buz,900,500);
          delay(1500);
          digitalWrite(ledO,0);
        }else if(payload[11] == 'd'){
          digitalWrite(ledO,1);
          digitalWrite(ledX,1);
          tone(buz,300,500);
          delay(1500);
          digitalWrite(ledO,0);
          digitalWrite(ledX,0);

        }else {
          digitalWrite(ledO,0);
          digitalWrite(ledX,0);
          delay(1500);

        }
      } else {
        Serial.println("No response");
      }
      Serial.println("http code: " + String(httpCode));
      http.end();   //Close connection
      
    }
  else 
  {    
    Serial.println("--> connection failed");
  }
}



void setup() {
  // put your setup code here, to run once:
  pinMode(ledX, OUTPUT);
  pinMode(ledO, OUTPUT);
  pinMode(buz, OUTPUT);
  Serial.begin(115200);

  Serial.println("Conectando ao Wifi");
  WiFi.begin(WIFI_FTM_SSID, WIFI_FTM_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
  delay(500);


}

void loop() {
  // put your main code here, to run repeatedly:
  httpRequest();
  delay(1500);
  // digitalWrite(ledO,1);
  // tone(buz,261,500);

}

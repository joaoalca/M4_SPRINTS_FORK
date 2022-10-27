#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;


const int Led1 = 4;
const int Led2 = 5;
const int Led3 = 6;
const int Led4 = 15;
const int LDR = 8;
const int buzz = 21;
const int but1 = 18;
const int but2 = 17;


int loc = 0;
int vet[200];
int sound[15];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32-S2!");
  
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
}

int convertSensor(){
      int sensor = analogRead(LDR);
    
      Serial.println(sensor);

      int valorMin = 39;
      int valorMax = 4089;
      int div = (valorMax - valorMin)/15;
      int bin =  sensor/div;
      sound[loc] = bin;

      //Serial.println(bin);
      
      int binary = 0, remainder, product = 1, decimal = bin;

      while (decimal != 0) {
        remainder = decimal % 2;
        binary = binary + (remainder * product);
        decimal = decimal / 2;
        product *= 10;
      }
      
      return (binary);
  }

void buzzin(int i){
  int tones[15] = {100,150,200,554, 622, 698, 740, 784, 831, 880, 932, 988, 1047, 1245, 1976};
  //Serial.println(tones[i]);
  tone(buzz,tones[i],500);
  delay(500);
}
string stringfy(int val2str){
   int num = val2str;
    ostringstream str1;
    str1 << num;
    string geek = str1.str();

    size_t n = 4;
    int precision = n - min(n, geek.size());
    string s = string(precision, '0').append(geek);


  return s;
}


void loop() {

            
  if (digitalRead(but1) == LOW) {
    int binConvertd = convertSensor();
    vet[loc] = binConvertd;
    loc++;
    delay(1000);
  }

  if (digitalRead(but2) == LOW){
    for (int i = 0; i < loc; i++){
      delay(2000);
      buzzin(sound[i]);
      delay(500);
      string strNum = stringfy(vet[i]);
      if (strNum[0] == '1'){
          digitalWrite(Led1,HIGH);
      }
      if (strNum[1] == '1'){
          digitalWrite(Led2,HIGH);
      }
      if (strNum[2] == '1'){
          digitalWrite(Led3,HIGH);
      }
      if (strNum[3] == '1'){
          digitalWrite(Led4,HIGH);
      }
      delay(500);
      digitalWrite(Led1,LOW);
      digitalWrite(Led2,LOW);
      digitalWrite(Led3,LOW);
      digitalWrite(Led4,LOW);

    }
    for (int k = loc; k <= 0; k--){
      vet[k] = 0;
    }
    loc = 0;
  }
  
//this speeds up the simulation
}

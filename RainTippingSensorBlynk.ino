/*************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App dashboard setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/
#include <Arduino.h>

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID     "TMPL6qDu0KYtT"
#define BLYNK_TEMPLATE_NAME   "Rain Tipping"
#define BLYNK_AUTH_TOKEN      "i40mLgHB9NZXQ40-LnCc_mhHc3_VteYA"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "scheduler.h"

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "kaivan home";
char pass[] = "kaivan1301";

const int sen1 = D6;
const int sen2 = D7;
int count1 = 0;
int count2 = 0;
int tipping = 0;
float volume;
bool var1 = 0;
bool var2 = 0;
bool sen1now = 0;
bool sen2now = 0;


void getData() {
  sen1now = digitalRead(sen1);
  sen2now = digitalRead(sen2);
  if(sen1now && !var1){
    count1++;
    var1 = true;
    delay(10); 
  }
  else if(!sen1now){
    var1 = false;
  }

  if(sen2now && !var2){
    count2++;
    var2 = true;
    delay(10); 
  }
  else if(!sen2now){
    var2 = false;
  }
  tipping = count1+count2;
  volume=(tipping-1)*0.8952;//masih direvisi
  Blynk.virtualWrite(V0, tipping-1);      // Upload data to Blynk
  Blynk.virtualWrite(V1, volume);      // Upload data to Blynk


  Serial.println(tipping);
}

TaskScheduler uploadBLYNK(1, "upload", 100, getData);

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  uploadBLYNK.runTask();
}

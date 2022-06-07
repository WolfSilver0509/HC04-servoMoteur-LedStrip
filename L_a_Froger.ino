/* 
 *  
 *  Pour le branchement : 
 *  La bande de led est branché sur le pin 5
 *  Le servo moteur est branché sur le pin 2 
 *  Le capteur ultrason est brancher : 
 *  trig sur le pin 8
 *  echo sur le pin 9
  
*/

#include <Adafruit_NeoPixel.h>   
#include <Servo.h>
Servo servoMoteur; 
#define sortie 5                                //  Défini le pin de l'arduino sur lequel est branché la bande de led
#define nb_led 18                                //    Défini le nombre de led voulu sur la bande branché                        
#define PIN_TRIG  8                              // Défini le pin de l'arduino sur lequel est branché la broche Trig du module HC-04
#define PIN_ECHO  9                              // Défini le pin de l'arduino sur lequel est branché la broche Echo du module HC-04

Adafruit_NeoPixel module = Adafruit_NeoPixel(nb_led, sortie, NEO_GRB + NEO_KHZ800);  // création de l'objet module à utiliser pour controler la bande

long duration_hc, distance_hc;

void setup() {
  Serial.begin (9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  servoMoteur.attach(2);
  module.begin();  
 
}

void loop() {

  mesureDistance();
  Serial.print("Distance ");
  Serial.print(distance_hc);
  Serial.println(" Cm ");

  if(distance_hc > 200){
    Bleu();
    servoMoteur.write(180);
 
  }

  else{
  Rouge();
  servoMoteur.write(0);
  }

}

void Bleu(){ 
  for(int i=0;i<18;i++)  
  {
    module.setPixelColor(i,0,0,255);  
    module.setBrightness(40);
    module.show(); 
    delay (100);
  }
}
void Rouge(){ 
  for(int i=0;i<18;i++)  
  {
    module.setPixelColor(i,255,0,0);  
    module.show(); 
    delay (100);
  }
}
void mesureDistance(){
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10); 
  digitalWrite(PIN_TRIG, LOW);
  duration_hc = pulseIn(PIN_ECHO, HIGH);
  Serial.println(duration_hc);
  distance_hc = duration_hc / 58;
}

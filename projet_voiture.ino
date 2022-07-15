//www.elegoo.com


#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A4;
int Trig = A5;

//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6

#define carSpeed 150

int rightDistance = 0, leftDistance = 0, middleDistance = 0, middleDistance2 = 0;
int compteurLigne = 0;
int calibrage=0;


void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 
//Ultrasonic distance measurement Sub function
int getDistance() {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    return (int)pulseIn(Echo, HIGH) / 58;
}

void setup(){
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
  myservo.attach(3);  // attach servo on pin 3 to servo object
  
  
  myservo.write(90);
}
void loop() {


  //calibrage de la voiture pour determiner le delay qui correspond a 90 degres et la positionner droite
  if (calibrage ==0){
    forward();
    while(LT_R==false && LT_L==false);
    if (LT_M){
      
       stop();
        delay(400);
        back();
        delay(400);
        right();
        delay(900);
        stop();
        calibrage =1;
    }
      if (LT_L && LT_R==false){
        back();
        delay(400);
        right();
        delay(50);
      }else if (LT_R && LT_L ==false){
        back();
        delay(400);
        left();
        delay(50);
      }  
    
    
    }

    //rester dans les lignes 
if(calibrage==1){
    if(LT_L){
      back();
      delay(300);
      left();
      delay(400);
      
    }else if (LT_R){
      back();
      delay(300);
      right();
      delay(400);
    }else{
      forward();
    }
}
if(calibrage==1){
  //detection d'obstacle
  forward(); 
  middleDistance=getDistance();
  delay(100);
  middleDistance2=getDistance();
  //pour eviter les erreurs et les faux positifs 
  
  if(middleDistance <=30 && middleDistance>=middleDistance2){
    //si ligne de droite 
    if (compteurLigne==0){
      left();
      delay(800);

      
      //passe la premiere ligne 
      while(LT_M==false){
        forward();}
        stop();
        delay(1000);
        
        forward();
        delay(300);
      //atteint la deuxieme ligne 
      while(LT_M==false){
        forward();}
      back();
      delay(400);
      right();
      delay(800);
      forward();
      //si ligne de gauche 
      //fonctionne pareil que la ligne 0
      compteurLigne=1;
      }else if (compteurLigne==1){
        right();
      delay(800);
      
      while(LT_M==false){
        forward();}
        stop();
        delay(1000);
        
        forward();
        delay(300);
      
      while(LT_M==false){
        forward();}
      back();
      delay(400);
      left();
      delay(800);
      forward();
      compteurLigne=0;
        
      }
      
    }
      
    }
    
  

}

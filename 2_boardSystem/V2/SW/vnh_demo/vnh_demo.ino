

//Pin Map
int MINA = 5;         // Motor 1 direction input A
int MINB = 4;         // Motor 1 direction input B
int PWM = 9;         // Motor 1 PWM
int M1ENDIAG1 = 6;     // Motor 1 enable input/fault output
int M1CS = A0;         // Motor 1 current sense output
int delayTime = 200;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello world");
  pinMode(MINA, OUTPUT);
  pinMode(MINB, OUTPUT);
  pinMode(PWM, OUTPUT);
  // set timer 1 divisor to 8 for PWM frequency of  3921.16 Hz
  TCCR1B = TCCR1B & B11111000 | B00000010;  
  
  //LO REGGE MA è OLTRE I LIMITI DI DATASCHEET!!!
  //A PROPRIO RISCHIO E PERICOLO
  // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
  //TCCR1B = TCCR1B & B11111000 | B00000001;   
  
}

void loop()
{

//  for (int speedvalue = 0 ; speedvalue <= 255; speedvalue += 10) {
//    analogWrite(PWM, speedvalue);                                    //forward from zero to full speed at +10 increments
//    Serial.print("increase speed r1:");
//    Serial.println(speedvalue);
//    delay(delayTime);
//  }
//  for (int speedvalue = 255 ; speedvalue >= 0; speedvalue -= 10) {
//    analogWrite(PWM, speedvalue);                                   //forward from full to zero speed at -10 decrements
//    Serial.print("decrement speed r1:");
//    Serial.println(speedvalue);
//    delay(delayTime);
//  }

  //Counterclockwise wise sens
  digitalWrite(MINA, 0);
  digitalWrite(MINB, 1);
  for (int speedvalue = 0 ; speedvalue <= 255; speedvalue += 10) {
    analogWrite(PWM, speedvalue);                                    //forward from zero to full speed at +10 increments
    Serial.print("increase speed r2:");
    Serial.println(speedvalue);
    delay(delayTime);
  }
  for (int speedvalue = 255 ; speedvalue >= 0; speedvalue -= 10) {

    analogWrite(PWM, speedvalue);                                   //forward from full to zero speed at -10 decrements
    Serial.print("decrement speed r2:");
    Serial.println(speedvalue);
    delay(delayTime);
  }
}

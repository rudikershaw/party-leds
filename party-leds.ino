#define RED_LED 6
#define BLUE_LED 5
#define GREEN_LED 9
#define SOUND_IN 7
#define MOVEMENT_IN 4

int fadeSpeed = 1;
int pink = 1;
int baseBrightness = 200;
int movementDetected = 0;
unsigned long movementTimer = 0;


void setup() {
   pinMode(GREEN_LED, OUTPUT);
   pinMode(RED_LED, OUTPUT);
   pinMode(BLUE_LED, OUTPUT);
   
   pinMode(SOUND_IN, INPUT);
   pinMode(MOVEMENT_IN, INPUT);

   Serial.begin(9600);
}

void TurnPink() {
    for (int i = baseBrightness; i > 50; i--) {
       analogWrite(GREEN_LED, i);
       delay(fadeSpeed);
   }
}

void TurnWhite() {
    for (int i = 50; i < baseBrightness; i++) {
       analogWrite(GREEN_LED, i);
       delay(fadeSpeed);
   }
}

void printValue(String attr, int value) {
   Serial.print(attr);
   Serial.print(": ");
   Serial.println(value);
}

void soundCheck() {
  int sound = digitalRead(SOUND_IN);
//  printValue("sound", sound);
  if (sound == LOW && pink == 1) {
    TurnWhite();
    pink = 0;
  }
  
  if (sound == HIGH && pink == 0) {
    TurnPink();
    pink = 1;
    delay(25);
  }   
}

void loop() {
  int movement = digitalRead(MOVEMENT_IN);
//  printValue("movement", movement);
  if (movement == HIGH) {
     if (movementDetected == 0) {
        analogWrite(GREEN_LED, baseBrightness);
        analogWrite(RED_LED, baseBrightness);
        analogWrite(BLUE_LED, baseBrightness);
        delay(500);
     } else {
       soundCheck();
     }
     movementDetected = 1;
     movementTimer = 0;
  } else if (movementTimer > 120000) {
    movementDetected = 0;
    movementTimer = 0;
    analogWrite(GREEN_LED, 0);
    analogWrite(RED_LED, 0);
    analogWrite(BLUE_LED, 0);
    pink = 0;
    delay(500);  
  } else if (movementDetected == 1){
    soundCheck();
    movementTimer++;
    delay(1); 
  }
}

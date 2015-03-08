//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

int pirPin = 3;
int r_led = 13; 
int g_led = 12; 
int b_led = 11;

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

void setup(){
  pinMode(pirPin, INPUT);
  pinMode(r_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(b_led, OUTPUT);
  digitalWrite(pirPin, LOW);
  for(int i = 0; i < calibrationTime; i++){
    set_blue();
    delay(500);
    set_red();
    delay(500);
  }
  set_green();
  delay(50);
}

void loop(){
  if(digitalRead(pirPin) == HIGH){
    set_on();
    if(lockLow){  
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;            
      set_off();
      delay(50);
    }         
    takeLowTime = true;
  } else {       
    set_off();

    if(takeLowTime){
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause, 
    //we assume that no more motion is going to happen
    if(!lockLow && millis() - lowIn > pause){  
      //makes sure this block of code is only executed again after 
      //a new motion sequence has been detected
      lockLow = true;                        
      set_on();
      delay(50);
    }
  }
}

void set_leds(int r_bright, int g_bright, int b_bright) {
  analogWrite(r_led, r_bright);
  analogWrite(g_led, g_bright);
  analogWrite(b_led, b_bright);
}

void set_bright(int brightness) {
  set_leds(brightness, brightness, brightness);
}

void set_sodium() {
  set_leds(255, 183, 76);
}

void set_orange() {
  set_leds(255, 102, 0);
}

void set_off() {
  set_leds(0, 0, 0);
}

void set_on() {
  set_direct_sunlight();
}

void set_candle() {
  set_leds(255, 147, 41);
}

void set_40w() {
  set_leds(255, 197, 143);
}

void set_100w() {
  set_leds(255, 214, 170);
}

void set_halogen() {
  set_leds(255, 241, 224);
}

void set_carbon_arc() {
  set_leds(255, 250, 244);
}

void set_high_noon() {
  set_leds(255, 255, 251);
}

void set_direct_sunlight() {
  set_leds(255, 255, 255);
}

void set_overcast_sky() {
  set_leds(201, 226, 255);
}

void set_blue_sky() {
  set_leds(64, 156, 255);
}

void set_red() {
  set_leds(255, 0, 0);
}

void set_green() {
  set_leds(0, 255, 0);
}

void set_blue() {
  set_leds(0, 0, 255);
}

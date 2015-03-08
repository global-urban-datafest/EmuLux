#include <SPI.h>
#include <WiFi.h>
#include <String.h>
int lightSensor = 0;
int pin = 0;
int val = 0;
int ii=0;
char ssid[] = "Hackathon";          //  your network SSID (name) 
int lightval = 0;
static int led0 = 0;
static int led1 = 0;
static int led2 = 0;
static int led3 = 0;
static int led4 = 0;
static int led5 = 0;
static int led6 = 0;
static int led7 = 0;
static int led8 = 0;
static int led9 = 0;
static int led10= 0;
static int led11 = 0;
static int led12 = 0;
static int led13 = 0;


int led0P = 7;
int led9P = 0;

char c[500];
const char b = '1';
int status = WL_IDLE_STATUS;
char server[] = "streetlights.eu-gb.mybluemix.net"; 

// Initialize the client library
WiFiClient client;

void setup() {
  pinMode(lightSensor, INPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(led9P, OUTPUT);
  Serial.begin(115200);
  Serial.println("Attempting to connect to network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid);
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } 
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
  }
}

void loop() {
  char buffer[100];
  char buffer1[100];
  char buffer2[100];
  char c[500];
  char d;
  if (client.connect(server, 80)) {
    snprintf(buffer,sizeof(buffer),"{\"lightval\": %d, \"_id\": \"light\"}",lightval);
    snprintf(buffer1,sizeof(buffer1),"Content-Length: %d",strlen(buffer));
    //, \"_rev\": \"5-9286ae00bf886a2aeaf2c04b82a70ea9\"
    client.println("POST /sensorData HTTP/1.0");

    client.println("Host: streetlights.eu-gb.mybluemix.net");
    client.println(buffer1);
    client.println();

    client.println(buffer);
    client.stop();
    Serial.println("Posting");
  }
  for(int xx = 0; xx <=13;xx++){
    if (client.connect(server, 80)) {
      Serial.print(xx);
      snprintf(buffer2,sizeof(buffer),"GET /leds?key=led%d&on=%d HTTP/1.0",xx,led9);
      client.println(buffer2);
      client.println("Host: streetlights.eu-gb.mybluemix.net");
      client.println();
      ii=0;

      while (client.available()) {
        d = client.read();
        c[ii] = d;
        ii++;
      }
      client.stop();
    }
      FILE *fp;
      fp = fopen("/home/root/hack/data.txt", "w");
      fputs(c,fp);
      fclose(fp);
  }
  txtIn();
  sensorRead();
  //  ledSwitch();
  delay(100);
}
void txtIn(){

  char str[8];
  int inputnumber;
  char filename[50] = "/home/root/hack/led";
  Serial.println("d"); 
  for(int xx = 0; xx <=10;xx++){
    snprintf(filename,sizeof(filename),"/home/root/hack/led%d",xx);
      FILE *fp;
    fp = fopen(filename , "r");

    fscanf(fp,"%d",&inputnumber);
    fclose(fp);
    Serial.println(inputnumber);
    Serial.println(xx);
    digitalWrite(xx,inputnumber);
    analogWrite(xx,inputnumber);

  }

}

void serialFind(int j, char *input){
  if(j==0)return;
  while(input[j]!='"')j--;
  if(input[j-2]=='"'){
    val = 0+(input[j-1]-'0');
    j = j-8;

  }
  else if(input[j-3]=='"'){
    val = (input[j-1]-'0');
    val = val+(10*(input[j-2]-'0'));
    j = j-9;
  }
  else if(input[j-4]=='"'){
    val = input[j-1]-'0';
    val = val+(10*(input[j-2]-'0'));
    val = val+(100*(input[j-3]-'0'));
    j = j-10;
  }


  if(input[j-2]=='d'){
    pin = (input[j-1]-'0');

  }
  else if(input[j-3]=='d'){
    pin = (input[j-1]-'0');
    pin = pin+10;
  }

  switch (pin){
  case 0:
    led0 = val;
    break;
  case 7:
    led9 = val;
    break;
  }

  return;
}
void ledSwitch(){
  if(led0 ==1){
    analogWrite(0, led0);
  }
  else if(led0==0){
    digitalWrite(0, led0);
  }
  if(led9 ==1){
    digitalWrite(7, led9);
  }
  else if(led9==0){
    digitalWrite(7, led9);
  }
  return;
}
void sensorRead(){
  lightval = analogRead(lightSensor);
  return;
}
/*
void processControlData(char * data)
 {
 int pin, value;
 int count = 0;
 while ((data) && count < 20)
 {
 data = getNextControlData(data, &pin, &value);
 if ((pin >= 0 && pin <= 19) && (value >= 0 && value <= 255))
 {
 pinMode(pin, OUTPUT);
 if (value > 1)
 analogWrite(pin, value);
 else
 digitalWrite(pin, value);
 }
 else
 {
 Serial.println("error bad control data");
 Serial.print("pin = ");
 Serial.println(pin);
 Serial.print("value = ");
 Serial.println(value);
 }
 count++;
 }
 }
 char * getNextControlData(char * data, int * pin, int * value)
 {
 char *p;
 #ifdef DEBUG
 Serial.print(data);
 #endif
 p = strstr (data, "c_");
 if (!p){
 Serial.println("getNextControlData - no more records");
 return 0;
 }
 #ifdef DEBUG
 Serial.println(p);
 #endif
 p = (char *)(p+2);
 #ifdef DEBUG
 Serial.println(p);
 #endif
 *pin = atoi(p);
 p = strchr(p+1,',');
 p = strchr(p+1,',');
 p = (char *)(p+1);
 *value = atoi(p); 
 //Serial.println(p);
 Serial.println("getNextControlData - found record");
 Serial.print("pin = ");
 Serial.println(*pin);
 Serial.print("value = ");
 Serial.println(*value);
 return p;
 }
 
 if (client.connect(server, 80)) {
 client.println("GET /hi HTTP/1.0");
 client.println("Host: streetlights.mybluemix.net");
 client.println();
 client.stop();
 }
 */
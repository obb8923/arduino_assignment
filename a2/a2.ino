#define PIN_LED 13
 int count =0;
int toggle =0;
void setup() {
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ; //wait for serial port to connect
  }
Serial.println("Hello World!");
count=toggle=0;
digitalWrite(PIN_LED,toggle);  //turn off LED
}

void loop() {
  Serial.println(++count);
  toggle=toggle_state(toggle); //toggle LED value
  digitalWrite(PIN_LED,toggle); //update LEDstatus.
  delay(1000); 
}
int toggle_state(int toggle){
  return (toggle == 0) ? 1 : 0;
}

int counter = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9,INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  int switch1;
  int switch2;
  int switch3;
  int state1;
  int state2;
  int no_vid;
  
  // put your main code here, to run repeatedly:
  switch1 = digitalRead(9);
  switch2 = digitalRead(3);
  if (switch1 == 1 && switch2 == 0) {
    Serial.println("1");
    counter = 1;
  }

  else if (switch1 == 0 && switch2 == 0){
    Serial.println("0");
    counter = 0;
  }
  
  else if (switch1 == 0 && switch2 == 1){
    Serial.println("2");
    counter = 1;
  }

  else if (switch1 == 1 && switch2 == 1){
    Serial.println("3");
    counter = 1;
    
  }

  
  delay(100);
}

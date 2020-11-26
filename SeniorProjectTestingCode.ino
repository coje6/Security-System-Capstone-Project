#define PulseTrainInput 6
#define OuputPin 4

void setup() {
  
  pinMode(PulseTrainInput, INPUT);
  pinMode(OutputPin, Output);

}

void loop() {

  //waits for the pulse train, waits four microseconds, sends a signal back to imitate
  //the ultrasonic reciever pulse train returning
  while(1) {
    if(digitalRead(PulseTrainInput)==1) {
      delay(4);
      digitalWrite(OutputPin, 1);
      delay(1);
      digitalWrite(OutputPin, 0);
      delay(1);
    }
    
  }

}

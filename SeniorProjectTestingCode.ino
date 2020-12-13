#define PulseTrainInput 6
#define OutputPin 4

void setup() {
  
  pinMode(PulseTrainInput, INPUT);
  pinMode(OutputPin, OUTPUT);

}

void loop() {

  //waits for the pulse train, waits four microseconds, sends a signal back to imitate
  //the ultrasonic reciever pulse train returning

  if(digitalRead(PulseTrainInput)==1) {
    delay(2);
    digitalWrite(OutputPin, 1);
    delay(1);
    digitalWrite(OutputPin, 0);
    delay(1);
    }
    
  

}

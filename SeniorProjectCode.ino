#define RecieverInputPin 13
#define PWMOutputPin 9
#define ledPin 14

#define SpeedOfSound 1100
#define LEDon 1
#define LEDoff 0

//sets the definiton of a signal recieved to be one or zero
#define InputSignalPolarity 1
//sets the distance the the program is looking for
#define DesiredDistance 11
//sets the tolerance of the distance being looked for
#define ToleranceDistance 1

//this variable needs to be global to hold values through iterations of the main loop
float DistanceArray[10];

void setup() {
  
  pinMode(RecieverInputPin, INPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin, OUTPUT);

}

void loop() {

    //initializes non global variables
    int i;
    int NoSignal;
    long int starttime;
    long int stoptime;
    long int signaltime; 
    float seconds;
    float distance;
    float sum;
    float AverageDistance;

    //takes a starting time
    starttime=micros();
    
    //generates a PWM output at pin 9 of 40kHz for 1 milliseconds
    tone(PWMOutputPin, 40000, 1);
    delay(1); //waits for the signal to be done to make sure it isn't read

    //waits until the receiver picks up a signal, records the time
    while(digitalRead(RecieverInputPin)==InputSignalPolarity) {
      //makes sure the code doesn't sit in this loop forever
      if(starttime-micros() > 38000) { //38000 corresponds to a distance read of over 20 feet
        NoSignal=1;
        break;
      }
     }
    stoptime=micros();

    //calculates the time elapsed for the signal to be sent and returned
    signaltime = stoptime-starttime;
    seconds = float(signaltime)/float(10^6);
    distance = (SpeedOfSound * seconds)/2;

     //sets the distance to be extremely high to make the average distance
     //well out of range of the desired distance if no return singal is detected
    if(NoSignal==1) {
      distance = 1000;
    }

    //stores most recent ten distances in an array, most recent being at index 0
    for(i=0; i<9; i++) {
      DistanceArray[i+1]=DistanceArray[i];
    }
    DistanceArray[0] = distance;

    //calculates the sum of the distance array
    for(i=0;i<10; i++) {
      sum+=DistanceArray[i];
    }

    //calculates the average distance
    AverageDistance = sum/10;

    //checks if the averaged distance is outof range of the tolerance distance
    if(abs(DesiredDistance-AverageDistance)>ToleranceDistance) {
      digitalWrite(ledPin, LEDon);
    }
    else {
      digitalWrite(ledPin, LEDoff);
    }
    
    //waits 5 milliseconds between samples, allows the residual noise from the first
    //pulse to die out
    delay(5);
    

}

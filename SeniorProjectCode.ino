#define RecieverInputPin 13
#define PWMOutputPin 9
#define ledPin 14

#define SpeedOfSound 11000
#define LEDon 1
#define LEDoff 0

//sets the definiton of a signal recieved to be one or zero
#define InputSignalPolarity 1
//sets the distance the the program is looking for
#define DesiredDistance 11
//sets the tolerance of the distance being looked for
#define ToleranceDistance 1

long int starttime;
long int stoptime;
long int signaltime;
float seconds;
float distance;
float DistanceArray[10];
float sum;
float AverageDistance;
int NoSignal;
int i;

void setup() {
  
  pinMode(RecieverInputPin, INPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin, OUTPUT);

}

void loop() {

    //takes a starting time
    starttime=micros();
    
    //generates a PWM output at pin 9 of 40kHz for 2 milliseconds
    tone(PWMOutputPin, 40000, 2);
    delay(2); //waits for the signal to be done to make sure it isn't read

    //waits until the receiver pick up a signal, takes the time
    while(digitalRead(RecieverInputPin)==InputSignalPolarity) {
      //makes sure the code doesn't sit in this loop forever
      if(starttime-micros() > 4000) {
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

    //calculates an average distance over the last set of samples
    DistanceArray[0] = distance;
    sum=distance;
    for(i=1; i<=10; i++) {
      DistanceArray[i]=DistanceArray[i-1];
      sum+=DistanceArray[i];
    }
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

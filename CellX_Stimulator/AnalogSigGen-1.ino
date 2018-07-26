/* 
AnalogSigGen-1
This code targets the TeensySMB board which is basically a PJRC Teensy 3.2.
It acts like an old fashioned analog signal generator with a PWM on the side.
Written by Rick Farmer
*/

#define P1 A0             //define POT pins
#define P2 A1
#define P3 A2
#define P4 A3

#define BluLED 13         //define LED pins
#define GrnLED 5
#define YelLED 21
#define OrnLED 20
#define RedLED 6

#define S1 0              //define switche pins
#define S2 1
#define S3 2
#define S4 3

#define B1 33             //define button pin

#define Amod A14          //define DAC pin

#define Dmod 23           //define PWM pin

float val;                //timing varaibles
float phase = 0.0;
float twopi = 3.14159 * 2;
elapsedMicros usec = 0;

int Dfreq;                //Dmod frequency
int Afreq;                //Amod frequency
float Aoff;               //Amod offset
float Aamp;               //Amod amplitude


//--------------------------------------------
void setup() 
{
  analogWriteResolution(12);    //0-4095
  
  pinMode(BluLED, OUTPUT);      //DIO pins
  pinMode(GrnLED, OUTPUT);    
  pinMode(YelLED, OUTPUT);  
  pinMode(OrnLED, OUTPUT);  
  pinMode(RedLED, OUTPUT);    
  pinMode(Dmod, OUTPUT);    

  digitalWrite(Dmod, HIGH); 

  pinMode(B1, INPUT_PULLUP);     
  pinMode(S1, INPUT_PULLUP);       
  pinMode(S2, INPUT_PULLUP);     
  pinMode(S3, INPUT_PULLUP);     
  pinMode(S4, INPUT_PULLUP);     

  Serial.begin(9600);           // init USB debug terminal    
}

//--------------------------------------------
void loop() 
{
  Afreq = 4 * analogRead(P1);                       //read POTs & upscale to 12-bits
  Aoff = 4 * analogRead(P3);  
  Aamp = 4 * analogRead(P2);
  
  if(digitalRead(S1))                               //check switch
    {
      val = ((sin(phase) * (Aamp/2)) + Aoff);       //sine wave 
      digitalWrite(GrnLED, HIGH);       
      digitalWrite(RedLED, LOW);       
    }
    else                                            // - or -
    {
      if(phase <= twopi/2) val = Aoff + (Aamp/2);   //top half of square wave
        else val = Aoff - (Aamp/2);                 //bottom half of square wave  

      digitalWrite(GrnLED, LOW);       
      digitalWrite(RedLED, HIGH);             
    }
  
  analogWrite(Amod, (int)val);                      //write analog waveform to DAC
  phase = phase + (twopi/360);                      //add 1 degree
  while(usec < Afreq) {};                           //kill time
  usec = usec - Afreq;

  if(phase <= twopi/2) digitalWrite(BluLED, HIGH);  //first half of wave, blink
    else digitalWrite(BluLED, LOW);                 //second half of wave 

  if(phase >= twopi)                                //reset angle and DMOD PWM when AMOD cycle rolls over
  {
    phase = 0;  
    Dfreq = 4 * analogRead(P4);    
    analogWriteFrequency(Dmod, Dfreq-100);          //update digital freq PWM
    
    if(Dfreq >= 3995) analogWrite(Dmod,4096);       //set high if POT is at fast stop
      else if(Dfreq <= 100) analogWrite(Dmod,0);    //set low if POT is at slow stop    
             else analogWrite(Dmod,2048);           //otherwise set PWM to 50% duty cycle    
  }
}

//--------------------------------------------


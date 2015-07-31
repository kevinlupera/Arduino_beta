/*

* Super Mario Coin Bank
* Eungchan Kim
* 2013-03-05
* 
* Reference for speaker:
* https://code.google.com/p/rbots/source/browse/trunk/StarterKit/Lesson5_PiezoPlayMelody/Lesson5_PiezoPlayMelody.pde
*/

int criteria = 400; // criteria for detecting if a coin is inserted
int insert_count = 0; // count the number of inserted coins
// speaker
int speakerOut = 7;               
// period is in microsecond so P = 1/f * (1E6)
#define  g4    2551    // 392 Hz 
#define  c5    1912    // 523 Hz
#define  e5    1517
#define  g5    1276
#define  f5    1433
#define  b5    1012
#define  e6    758
#define  c6    955
#define  g6    638
#define  R     0       // Define a special note, 'R', to represent a rest
 
//super mario theme
int dollar[] = {e6, e6, R, e6, R, c6, e6, R, g6,};
//coin sound
int q_dollar[] = {b5, e6};
int q_beats[] = {8, 40};
 
int MAX_COUNT4 = sizeof(q_dollar) / 2; // Melody length, for looping.
// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1;
// Loop variable to increase Rest length
int rest_count = 50; //<-BLETCHEROUS HACK; See NOTES
// Initialize core variables
int toneM = 0;
int beat = 0;
long duration = 0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(speakerOut, OUTPUT);
}
 
void loop()
{
      sound(q_dollar,q_beats,MAX_COUNT4);
      // Set up a counter to pull from melody[] and beats[]
   delay (1000);
  }  
void sound(int* m, int* b, int max_num)
{
  for (int i=0; i<max_num; i++) {
    toneM = m[i];
    beat = b[i];
    duration = beat * tempo; // Set up timing
    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);    
  }
}
void playTone() {
  long elapsed_time = 0;
  if (toneM > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(toneM / 2);
      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(toneM / 2);
      // Keep track of how long we pulsed
      elapsed_time += (toneM);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

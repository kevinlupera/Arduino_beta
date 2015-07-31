
int criteria = 400; // criteria for detecting if a coin is inserted
int insert_count = 0; // count the number of inserted coins
// speaker
int speakerPin = 7;               
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
int beat_int = 0;
long duration = 0;

int tempo_fondo = 95;
int length = 295; // the number of notes
char notes[] = "EE E CE G  g  C  g e  a b ia gEGA FG E CDb C  g e  a b ia gEGA FG E CDb  GNFR E uaC aCD GNFR E 1 11   GNFR E uaC aCD L  D C   CC C CD EC ag  CC C CDE  CC C CD EC ag  EE E CE G  g  C  g e  a b ia gEGA FG E CDb C  g e  a b ia gEGA FG E CDb EC g u aF Fa  bAAAGFEC ag  EC g u aF Fa  bF FFEDCe ec  "; // a space represents a rest
float beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, //Page 1
                2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 4, //Page 2
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, //Page4
                1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, //Page 5
                1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1.3, 1.3, 1.3, 1, 1, 1, 1, 1, 1, 2 }; //Page 6
              
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_H   0
#define NOTE_B3  247
#define NOTE_F4  349
#define NOTE_E4  330
#define NOTE_E3  165
#define NOTE_C3  131
const int death[] = {17, NOTE_C4, 32, NOTE_CS4, 32, NOTE_D4, 16, NOTE_H, 4, NOTE_H, 2, NOTE_B3, 8, NOTE_F4, 8, NOTE_H, 8, NOTE_F4, 8, NOTE_F4, 6, 
  NOTE_E4, 6, NOTE_D4, 6, NOTE_C4, 8, NOTE_E3, 8, NOTE_H, 8, NOTE_E3, 8, NOTE_C3, 8}; // Array for Death sound effect & song                                             // Array for Death sound effect & song
                
void playTone(int ton1, int duration) {
  for (long i = 0; i < duration * 1000L; i += ton1) {
    tone(speakerPin, ton1);
    delayMicroseconds(ton1);
  }
  noTone(speakerPin);
}


void playNote(char note, int duration) {
//                        c    c#   d    d#   e    f    f#   g    g#   a    a#   b
  char names[] = { ' ',  '!', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'i', 'N', 'R', 'u',  '1', 'L', 'k'}; // [i = b flat] [N = G flat] [R = D#] [u = g#] [1 = C oct. 5] [L = E flat]
  int tones[] =  {   0, 1046, 138, 146, 155, 164, 174, 184, 195, 207, 220, 233, 246, 261, 293, 329, 349, 391, 440, 493, 523, 587, 659, 698, 783, 880, 987, 466, 740, 622, 415, 1046, 622u, 227};
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 34; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void fondo() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo_fondo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo_fondo);
    }
    
    // pause between notes
    delay(tempo_fondo / 2); 
  }
}
void loop(){
  coins();
  delay(1000);
  muerte();
  delay(1000);
  fondo();
  delay (1000);
}

void coins()
{
      sound(q_dollar,q_beats,MAX_COUNT4);
      // Set up a counter to pull from melody[] and beats_coins[]
   delay (1000);
  }  
void sound(int* m, int* b, int max_num)
{
  for (int i=0; i<max_num; i++) {
    toneM = m[i];
    beat_int = b[i];
    duration = beat_int * tempo; // Set up timing
    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);    
  }
}
void playTone() {
  long elapsed_time = 0;
  if (toneM > 0) { // if this isn't a Rest beat_int, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
      digitalWrite(speakerPin,HIGH);
      delayMicroseconds(toneM / 2);
      // DOWN
      digitalWrite(speakerPin, LOW);
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

void muerte(){
for (int thisNote = 1; thisNote < (death[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
      tone(speakerPin, death[thisNote], (1000/death[thisNote + 1]));      // Play the single note
      delay((1000/death[thisNote + 1]) * 1.30);                           // Delay for the specified time
      noTone(speakerPin);                                                 // Silence the note that was playing
    }
}


const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

char dataIn = 'S';        //Character/Data coming from the phone.
char determinant;         //Used in the check function, stores the character received from the phone.
char det;                 //Used in the loop function, stores the character received from the phone.

void setup(){
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop()
{
  det = check(); 
      while (det == 'h')   //if incoming data is a F, move forward
      {     
      
        digitalWrite(13, HIGH);  
         delay(20); 
           Serial.println("prender");
            det = check();          
      }  
      while (det == 'l')   //if incoming data is a B, move back
      {    
        digitalWrite(13, LOW);
        Serial.println("apagar"); 
        det = check();          
      }
  
}

int check()
{
  if (Serial.available() > 0)    //Check for data on the serial lines.
  {   
    dataIn = Serial.read();  //Get the character sent by the phone and store it in 'dataIn'.
        if (dataIn == 'F')
        {     
          determinant = 'F';
        }  
        else if (dataIn == 'B')
        { 
          determinant = 'B'; 
        }
     }
 }

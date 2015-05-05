/*
*/

#define RED_PIN 1
#define AMBER_PIN 3
#define GREEN_PIN 4
#define BUTTON_PIN 0

// Hello PVG - a perversion of your look-up.
#define RED 1
#define AMBER 2
#define GREEN 4
#define RED_FLASH 8
#define AMBER_FLASH 16
#define GREEN_FLASH 32
#define END_SEQUENCE 64

#define SEQUENCE_TYPES 3
#define MAX_STEPS 10
static uint8_t sequence[SEQUENCE_TYPES][MAX_STEPS][2]=
{
  { // Normal Traffic RAG
    {RED, 3},
    {RED + AMBER, 2},
    {GREEN, 4},
    {AMBER, 2},
    {RED, 3},
    {END_SEQUENCE, 1},
  },
  { // Vehicle RAG in Pelican
    {RED, 3},
    {AMBER_FLASH, 3},
    {GREEN_FLASH, 3},
    {GREEN, 4},
    {AMBER, 3},
    {RED, 3},
    {END_SEQUENCE, 1},
  },
  { // US RAG 
    {RED, 3},
    {AMBER, 2},
    {GREEN, 4},
    {AMBER, 3},
    {RED, 3},
    {END_SEQUENCE, 1},
  }

};


 
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinsToOutput();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(RED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(RED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  doSequence(0);
  delay(1000);               // wait for a second

}


void doSequence(unsigned char s)  {
  // http://playground.arduino.cc/Code/TimingRollover
  uint8_t current_step = 0;
  unsigned long start_milliseconds = 0;
  bool flash = HIGH; // Start with FLASH ON or HIGH
  while(sequence[s][current_step][0] != END_SEQUENCE )  {
      start_milliseconds = millis();
      digitalWrite(RED_PIN, sequence[s][current_step][0] & RED);
      digitalWrite(AMBER_PIN, sequence[s][current_step][0] & AMBER);
      digitalWrite(GREEN_PIN, sequence[s][current_step][0] & GREEN);
      delay(1000 * sequence[s][current_step][1]);
      current_step++;
  }

}

void pinsToOutput()  {
  pinMode(RED_PIN, OUTPUT);
  pinMode(AMBER_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}


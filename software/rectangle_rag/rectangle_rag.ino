/* 
*/

#include <avr/pgmspace.h>

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

#define FLASH_INTERVAL_MILLIS 375

#define SEQUENCE_TYPES 4
#define MAX_STEPS 30
// see http://www.arduino.cc/en/Reference/PROGMEM
// https://github.com/lilspikey/arduino_sketches/blob/master/attiny/xmas/xmas.ino
// bitrate = pgm_read_word_near ( &(bitrate_table[temp][row_num]) );
// PROGMEM const uint16_t bitrate_table[15][6] = 

const uint16_t sequence[SEQUENCE_TYPES][MAX_STEPS][2] PROGMEM =
{
  { // Normal Traffic RAG
    {RED, 3},
    {RED + AMBER, 2},
    {GREEN, 7},
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
  },
  { // Silly RAG 
    {RED, 1},
    {RED + AMBER, 1},
    {AMBER, 1},
    {AMBER + GREEN, 1},
    {GREEN, 1},
    {AMBER + GREEN, 1},
    {AMBER, 2},
    {RED + AMBER, 1},
    {RED, 2},
    {RED + AMBER, 2},
    {GREEN, 9},
    {AMBER, 2},
    {RED, 3},
    {END_SEQUENCE, 1},
  },

};

void setup() {                
  // initialize the digital pin as an output.
  pinsToOutput();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() {
//  doSequence(4);
  doSequence(3);
  doSequence(2);
  doSequence(1);
  doSequence(0);

}


void doSequence(unsigned char s)  {
  // http://playground.arduino.cc/Code/TimingRollover
  uint8_t current_step = 0;
  uint8_t leds = pgm_read_word_near( &(sequence[s][current_step][0]));
  unsigned long start_milliseconds, length_of_step, last_flash_milliseconds;
  uint8_t flash = 255; // Start with FLASH ON or HIGH
  //pgm_read_word_near ( &(bitrate_table[temp][row_num]) )
  
  last_flash_milliseconds = millis();
  while(leds != END_SEQUENCE )  {
    start_milliseconds = millis();
    length_of_step = 1000 * pgm_read_word_near( &(sequence[s][current_step][1]));
    while((millis() - start_milliseconds) < (length_of_step) )  {
      digitalWrite(RED_PIN,   (leds & RED)   | (leds & RED_FLASH   & flash));
      digitalWrite(AMBER_PIN, (leds & AMBER) | (leds & AMBER_FLASH & flash));
      digitalWrite(GREEN_PIN, (leds & GREEN) | (leds & GREEN_FLASH & flash));
      if ((millis() - last_flash_milliseconds) > FLASH_INTERVAL_MILLIS)  {
        last_flash_milliseconds = millis();
        flash = ~flash;
      }
    }
    //Restart Flash if finished a non-flashing step
    if (leds < RED_FLASH)
    {
      flash = 255;
      last_flash_milliseconds = millis();
    }
    current_step++;
    leds = pgm_read_word_near( &(sequence[s][current_step][0]));
  }
  digitalWrite(RED_PIN,   LOW);
  digitalWrite(AMBER_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void pinsToOutput()  {
  pinMode(RED_PIN,   OUTPUT);
  pinMode(AMBER_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}


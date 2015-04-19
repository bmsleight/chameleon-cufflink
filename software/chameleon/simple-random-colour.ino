#define RED_PIN 1
#define GREEN_PIN 4
#define BLUE_PIN 3


// PORTD |= 1<<2; // Set bit 2 high
// PORTD &= ~(1<<2); // Set bit 2 low

// the setup routine runs once when you press reset:
void setup() {
//  Debug.begin( 250000 );  
  // initialize the digital pin as an output.
  pinMode(RED_PIN, OUTPUT);     
  pinMode(GREEN_PIN, OUTPUT);     
  pinMode(BLUE_PIN, OUTPUT);     
}

void loop() {
  // Debug.println("Test knock-bang");

    for (byte r = 0; r<255; r++) {
      rgb_(random(0, 254),random(0, 254),random(0, 254), 250, 2000, 250);
      delay(4000);
    }
}

void rgb_(byte r_target, byte g_target, byte b_target, unsigned long fade_up_time, unsigned long on_time, unsigned long fade_off_time) {
  // Try and make the fade-up, on and fade-down do exectly the same thing in the pseudo PWM loop. 
  // Create a table with 
  //   Millseconds_for_this_part, r_value, g_value, b_value
  unsigned long totalOnTime;
  byte r_value;
  byte g_value;
  byte b_value;
  typedef struct
  {
    unsigned long milliseconds;
    byte r_value;
    byte g_value;
    byte b_value;
  }  pwmTiming_type;
  pwmTiming_type pwmTiming[17];
  for (byte l = 0; l < 7; l++) {
    pwmTiming[l].milliseconds = fade_up_time/7;
    pwmTiming[l].r_value = (r_target >> (7-l));
    pwmTiming[l].g_value = (g_target >> (7-l));
    pwmTiming[l].b_value = (b_target >> (7-l));
  }
  pwmTiming[8].milliseconds = on_time;
  pwmTiming[8].r_value = r_target;
  pwmTiming[8].g_value = g_target;
  pwmTiming[8].b_value = b_target;
  for (byte l = 9; l < 17; l++) {
    pwmTiming[l].milliseconds = fade_off_time/7;
    pwmTiming[l].r_value = (r_target >> (l-8));
    pwmTiming[l].g_value = (g_target >> (l-8));
    pwmTiming[l].b_value = (b_target >> (l-8));
  }
  for (byte l = 0; l < 17; l++) {
    r_value = pwmTiming[l].r_value;
    g_value = pwmTiming[l].g_value;
    b_value = pwmTiming[l].b_value;
    rgb(r_value, g_value, b_value, pwmTiming[l].milliseconds);
}


void rgb(byte red,byte green,byte blue,unsigned long on_time)
{
  unsigned long totalOnTime;
  totalOnTime = millis() + on_time;
  while (totalOnTime > millis())  {
    // All On
    // digitalWrite(RED_PIN, LOW);
    // digitalWrite(GREEN_PIN, LOW);
    // digitalWrite(BLUE_PIN, LOW);
    // or a quick version
    PORTB &= ~(1<<RED_PIN);
    PORTB &= ~(1<<GREEN_PIN);
    PORTB &= ~(1<<BLUE_PIN);
    for (byte p = 0; p < 255; p++) {
      if (p>red) {
        // digitalWrite(RED_PIN, HIGH); // where HIGH is off
        // or a quick version
        PORTB |= 1<<RED_PIN;
      }
      if (p>green) {
        // digitalWrite(GREEN_PIN, HIGH); // where HIGH is off
        // or a quick version
        PORTB |= 1<<GREEN_PIN;
      }
      if (p>blue) {
        // digitalWrite(BLUE_PIN, HIGH); // where HIGH is off
        // or a quick version
        PORTB |= 1<<BLUE_PIN;
      }
    }
  }
  // All off
  // digitalWrite(RED_PIN, HIGH); // where HIGH is off
  // digitalWrite(GREEN_PIN, HIGH); // where HIGH is off
  // digitalWrite(BLUE_PIN, HIGH); // where HIGH is off  
  // or a quick version
  PORTB |= 1<<RED_PIN;
  PORTB |= 1<<GREEN_PIN;
  PORTB |= 1<<BLUE_PIN;
}


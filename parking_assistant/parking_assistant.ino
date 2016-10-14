// ---------------------------------------------------------------------------
// Parking assistant
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define LED_START_PIN 8
#define LED_END_PIN 12
#define LEVEL1 B00001
#define LEVEL2 B00011
#define LEVEL3 B00111
#define LEVEL4 B01111
#define LEVEL5 B11111

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//int leds[] = {GREEN_PIN, YELLOW_PIN, RED_PIN};
int current_pin = 0;


int get_pin(int distance){
  if (distance == 0){
    return LEVEL1;
  }else if (distance <8){
    return LEVEL5;
  }else if (distance >= 10 && distance < 13){
    return LEVEL4;
  }else if (distance >= 15 && distance <=18){
    return LEVEL3;
  }else if (distance > 20 && distance <24){
    return LEVEL2;
  }else if (distance >= 26) {
    return LEVEL1;
  }else{
    return 0;
  }
}

void flash_pin(int pin_number){
  int copy_pin=pin_number;
  for (int i=LED_START_PIN; i<=LED_END_PIN; i++){
    digitalWrite(i, (copy_pin & B1));
    copy_pin = copy_pin >> 1;
  }
}

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  for (int i=LED_START_PIN; i<=LED_END_PIN; i++){
    pinMode(i, OUTPUT);
  }
  //pinMode(RED_PIN, OUTPUT);
  //pinMode(GREEN_PIN, OUTPUT);
  //pinMode(YELLOW_PIN, OUTPUT);
  
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int distance = sonar.ping_cm();
  //Serial.print("Ping: ");
  //Serial.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  //Serial.println("cm");
  int new_pin = get_pin(distance);
  if (new_pin != 0 && new_pin != current_pin){
      flash_pin(new_pin);
      current_pin = new_pin;
  }
}


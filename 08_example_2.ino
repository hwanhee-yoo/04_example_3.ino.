#define PIN_LED   9
#define PIN_TRIG  12   
#define PIN_ECHO  13   

#define SND_VEL 346.0     
#define INTERVAL 25       
#define PULSE_DURATION 10 

#define SCALE_MM_PER_US (0.5f * SND_VEL / 1000.0f)  

#define TIMEOUT 30000UL   

unsigned long last_sampling_time;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  Serial.begin(57600);
}

void loop() {
  unsigned long now = millis();
  if (now - last_sampling_time < INTERVAL) return;
  last_sampling_time = now;

  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long duration = pulseIn(PIN_ECHO, HIGH, TIMEOUT);

  if (duration == 0) {
    Serial.println("No Echo");
    analogWrite(PIN_LED, 255); 
    return;
  }

  float distance = duration * SCALE_MM_PER_US; 
  int duty = 255; 
  
  if (distance >= 100 && distance <= 200) {
    duty = map((int)distance, 100, 200, 255, 0);
  } else if (distance > 200 && distance <= 300) {
    duty = map((int)distance, 200, 300, 0, 255);
  } else {
    duty = 255;
  }

  analogWrite(PIN_LED, duty);

  Serial.print("Distance(mm): ");
  Serial.print(distance, 1);
  Serial.print(" | Duty: ");
  Serial.println(duty);
}

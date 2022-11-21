
#define A1_trig_pin 7
#define A1_echo_pin 6

#define A2_echo_pin 10
#define A2_trig_pin 11

#define A3_echo_pin 2
#define A3_trig_pin 3

#define A4_echo_pin 4
#define A4_trig_pin 5

#define A5_trig_pin 8
#define A5_echo_pin 9

//led pins
#define A1_led 22
#define A2_led 24
#define A3_led 26
#define A4_led 28
#define A5_led 30

#define MIN_DIST 4



// defines variables
long duration[5] = {0}; // variable for the duration of sound wave travel
int distance[5] = {0}; // variable for the distance measurement
int magic_number = 0;
bool next_step = false;
unsigned long previous_time = 0;



void setup() {
  pinMode(A1_echo_pin, INPUT);
  pinMode(A1_trig_pin, OUTPUT); 

  pinMode(A2_echo_pin, INPUT);
  pinMode(A2_trig_pin, OUTPUT);

  pinMode(A3_echo_pin, INPUT);
  pinMode(A3_trig_pin, OUTPUT);

  pinMode(A4_echo_pin, INPUT);
  pinMode(A4_trig_pin, OUTPUT);

  pinMode(A5_echo_pin, INPUT);
  pinMode(A5_trig_pin, OUTPUT);

  pinMode(A1_led, OUTPUT);
  pinMode(A2_led, OUTPUT);
  pinMode(A3_led, OUTPUT);
  pinMode(A4_led, OUTPUT);
  pinMode(A5_led, OUTPUT);

  randomSeed(analogRead(0));


  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

  	//play pretty pattern at startup
	digitalWrite(A1_led, HIGH);
	delay(200);
	digitalWrite(A2_led, HIGH);
	delay(200);
	digitalWrite(A3_led, HIGH);
	delay(200);
	digitalWrite(A4_led, HIGH);
	delay(200);
  digitalWrite(A5_led, HIGH);
	delay(200);
}
void loop() {


 

	//set magic number
	magic_number = random(0, 5);
	//switch off whole led
	digitalWrite(A1_led, LOW);
	digitalWrite(A2_led, LOW);
	digitalWrite(A3_led, LOW);
	digitalWrite(A4_led, LOW);
  digitalWrite(A5_led, LOW);

	//set led 
	digitalWrite(magic_number, HIGH);

	//blocking function waiting for correct signal
   previous_time = millis();

	while(!next_step){
		//updating state of sensors
  Serial.println("magic number:");
  Serial.println(magic_number);
  //lit the correct led to be awaited for
  switch (magic_number)
  {
  case 0:
       digitalWrite(A1_led, HIGH);
    break;
  case 1:
        digitalWrite(A2_led, HIGH);
    break;
  case 2:
        digitalWrite(A3_led, HIGH);
    break;
  case 3:
        digitalWrite(A4_led, HIGH);
    break;
  case 4:
        digitalWrite(A5_led, HIGH);
    break;
  }

  //reading the state of sensors 
	read_datas_from_sensors(distance, duration);


	// tests for computing distances
  if(distance[magic_number] < MIN_DIST){
        next_step = true;
     }

  }

  next_step = false;
  //To be written on SD card reader then process the average reaction time
  Serial.println("Reaction time:");
  Serial.println(millis() - previous_time);
  Serial.println("\n");

}


void read_datas_from_sensors(int distance[], long duration[]){


  // first device
  digitalWrite(A1_trig_pin, LOW);
  delayMicroseconds(2);  
  digitalWrite(A1_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1_trig_pin, LOW);

  duration[0] = pulseIn(A1_echo_pin, HIGH);
  distance[0] = duration[0] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Serial.print("\nDistance1: ");
  // Serial.print(distance[0]);

  //second device
  digitalWrite(A2_trig_pin, LOW);
   delayMicroseconds(2);  
  digitalWrite(A2_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(A2_trig_pin, LOW);

  duration[1] = pulseIn(A2_echo_pin, HIGH);
  distance[1] = duration[1] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Serial.print("\nDistance2: ");
  // Serial.print(distance[1]);
  //third device

  digitalWrite(A3_trig_pin, LOW);
  delayMicroseconds(2);  
  digitalWrite(A3_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(A3_trig_pin, LOW);

  duration[2] = pulseIn(A3_echo_pin, HIGH);
  distance[2] = duration[2] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Serial.print("\nDistance3: ");
  // Serial.print(distance[2]);
  //fourth device

  digitalWrite(A4_trig_pin, LOW);
  delayMicroseconds(2);  
  digitalWrite(A4_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(A4_trig_pin, LOW);

  duration[3] = pulseIn(A4_echo_pin, HIGH);
  distance[3] = duration[3] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Serial.print("\nDistance4: ");
  // Serial.print(distance[3]);


    //fifth device

  digitalWrite(A5_trig_pin, LOW);
  delayMicroseconds(2);  
  digitalWrite(A5_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(A5_trig_pin, LOW);

  duration[4] = pulseIn(A5_echo_pin, HIGH);
  distance[4] = duration[4] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Serial.print("\nDistance5: ");
  // Serial.print(distance[4]);


}

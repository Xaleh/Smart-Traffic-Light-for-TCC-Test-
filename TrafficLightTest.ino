//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// Traffic Light - Test
// 
// Made by Alexandre Reis
// License: CC-BY-SA 3.0
// Downloaded from: https://123d.circuits.io/circuits/2048846-traffic-light-test

// Declaration of inputs and outputs
int Red = 3; 				// Red lantern (Stop)
int Yellow = 2; 			// Yellow lantern (Attention)
int Green_F = 1; 			// Green lantern for go AHEAD (Forward)
int Green_R = 5; 			// Green lantern to go to the RIGHT (Turn right)
int Green_L = 4; 			// Green lantern to go to the LEFT (Turn Left)
int Status_RX = 13; 		// Switch to inform if the Status that was sent to Central was received
int Status_GoLeft = 12; 	// Switch to inform if the Traffic Light will open forward
int Status_GoRight = 11; 	// Switch to inform if the Traffic Light will open to right
int Status_Rain = 10; 		// Switch to inform if it is raining
int Status_Night = 9; 		// Switch to inform if it is night

// Declaration of the variables
int SW_RX = 0;
int SW_GL = 0;
int SW_GR = 0;
int SW_R = 0;
int SW_N = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green_F, OUTPUT);
  pinMode(Green_R, OUTPUT);
  pinMode(Green_L, OUTPUT);
  pinMode(Status_RX, INPUT);
  pinMode(Status_GoLeft, INPUT);
  pinMode(Status_GoRight, INPUT);
  pinMode(Status_Rain, INPUT);
  pinMode(Status_Night, INPUT);
}

// the Main program:
void loop() {
  Red_ON();							// Traffic Light in red light
  while (SW_RX == LOW){				// Status received?
  	Receipt();
  }
  SW_RX = 0;						//Cleaning the receive status of the central
  delay(10000);						// Wait for 10 seconds  
  
  Directions();						//Reading the directions to open the traffic light
  if (SW_GL == HIGH){
    //Changing state of the traffic light to Green Light (Foward)
    Green_Left_ON();				// Traffic Light in green light to go ahead (Left)
    while (SW_RX == LOW){			// Status received?
      Receipt();
    }
    SW_RX = 0;						//Cleaning the receive status of the central
    delay(10000);					// Wait for 10 seconds
  }
  else if (SW_GR == HIGH){
    //Changing state of the traffic light to Green Light (Right)  
    Green_Right_ON();				// Traffic Light in green light to go ahead (Right)
    while (SW_RX == LOW){			// Status received?
      Receipt();
    }
    SW_RX = 0;						//Cleaning the receive status of the central
    delay(10000);					// Wait for 10 seconds
  }
  else{
    //Changing state of the traffic light to Green Light (Left)  
    Green_ON();						// Traffic Light in green light to go ahead (Forward)
    while (SW_RX == LOW){			// Status received?
      Receipt();
    }
    SW_RX = 0;						//Cleaning the receive status of the central
    delay(10000);					// Wait for 10 seconds
  }

  //Changing state of the traffic light to Yellow Light
  Yellow_ON();						// Traffic Light in yellow light
  while (SW_RX == LOW){				// Status received?
    Receipt();
  }
  SW_RX = 0;						//Cleaning the receive status of the central
  delay(3000);						// Wait for 3 seconds
  Weather_Darkness();				//Getting data of the weather and darkness to raise the time of Yellow Light on.
  if (SW_R == HIGH){
    delay(1000);					//Wait for 1 second
  }
  if (SW_N == HIGH){
    delay(1000);					//Wait for 1 second
  }  
}

// the change lights routine for each light:
void Red_ON() {
  digitalWrite(Red, HIGH); 			// turn the LED RED on (HIGH is the voltage level)
  digitalWrite(Yellow, LOW); 		// turn the LED YELLOW off (LOW is the voltage level)
  digitalWrite(Green_F, LOW); 		// turn the LED GREEN off (LOW is the voltage level)
  digitalWrite(Green_R, LOW); 		// turn the LED GREEN RIGHT off (LOW is the voltage level)
  digitalWrite(Green_L, LOW); 		// turn the LED GREEN LEFT off (LOW is the voltage level)
}

void Yellow_ON() {
  digitalWrite(Red, LOW); 			// turn the LED RED off (LOW is the voltage level)
  digitalWrite(Yellow, HIGH); 		// turn the LED YELLOW on (HIGH is the voltage level)
  digitalWrite(Green_F, LOW); 		// turn the LED GREEN off (LOW is the voltage level)
  digitalWrite(Green_R, LOW); 		// turn the LED GREEN RIGHT off (LOW is the voltage level)
  digitalWrite(Green_L, LOW); 		// turn the LED GREEN LEFT off (LOW is the voltage level)
}

void Green_ON() {
  digitalWrite(Red, LOW); 			// turn the LED RED off (LOW is the voltage level)
  digitalWrite(Yellow, LOW); 		// turn the LED YELLOW off (LOW is the voltage level)
  digitalWrite(Green_F, HIGH); 		// turn the LED GREEN on (HIGH is the voltage level)
  digitalWrite(Green_R, LOW); 		// turn the LED GREEN RIGHT off (LOW is the voltage level)
  digitalWrite(Green_L, LOW); 		// turn the LED GREEN LEFT off (LOW is the voltage level)
}

void Green_Right_ON() {
  digitalWrite(Red, LOW); 			// turn the LED RED off (LOW is the voltage level)
  digitalWrite(Yellow, LOW); 		// turn the LED YELLOW off (LOW is the voltage level)
  digitalWrite(Green_F, LOW); 		// turn the LED GREEN off (LOW is the voltage level)
  digitalWrite(Green_R, HIGH); 		// turn the LED GREEN RIGHT on (HIGH is the voltage level)
  digitalWrite(Green_L, LOW); 		// turn the LED GREEN LEFT off (LOW is the voltage level)
}

void Green_Left_ON() {
  digitalWrite(Red, LOW); 			// turn the LED RED off (LOW is the voltage level)
  digitalWrite(Yellow, LOW); 		// turn the LED YELLOW off (LOW is the voltage level)
  digitalWrite(Green_F, LOW); 		// turn the LED GREEN off (LOW is the voltage level)
  digitalWrite(Green_R, LOW); 		// turn the LED GREEN RIGHT off (LOW is the voltage level)
  digitalWrite(Green_L, HIGH); 		// turn the LED GREEN LEFT on (HIGH is the voltage level)
}

  //Getting the signals to decide which direction the traffic light will open (forward, right or left)
  void Directions() {
    SW_GL = digitalRead(Status_GoLeft);
    SW_GR = digitalRead(Status_GoRight);
  }

  //Getting the status of the weather and darkness in the local to decide if it will raise the time in Yellow Light
  void Weather_Darkness() {
    SW_R = digitalRead(Status_Rain);
    SW_N = digitalRead(Status_Night);
  }
  
  //Getting the status of receipt the data sent to Central
  void Receipt(){
  	SW_RX = digitalRead(Status_RX);
  }
    

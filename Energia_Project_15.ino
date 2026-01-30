  //Build in libraries
  //Build in Library for 16x2 LCD for using Build in Functions and for Pin Configuration
  #include <LiquidCrystal.h>
  //Build in Library for Servo Motors to attach servos
  #include <Servo.h> 

  // Define pin mappings for your specific Tiva C series board
  #define LCD_RS   PE_3
  #define LCD_EN   PE_2
  #define LCD_D4   PE_1
  #define LCD_D5   PD_3
  #define LCD_D6   PD_2
  #define LCD_D7   PD_1
  
  // Declare color based variables globally
  int redFrequency = 0;
  int greenFrequency = 0;
  int blueFrequency = 0;
  int i = 0;

  //Pin attachement of LCD with Tiva as above shown such as LCD_rs represent PE_3
  LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

  //Functions Decleration 
  void Sensor_init();
  void Sensor_Setup();  
  void Pickup_pos();
  void Detect_Color();
 

  //Use servo function from servo.h to declare base , Shoulder, etc variables as servos
  Servo Base;
  Servo Shoulder;
  Servo Elbow;
  Servo Wrist_roll;
  Servo Claw;

  //Variables to store initial position of the servos
  int Pos_Base = 5;
  int Pos_Shoulder = 120; 
  int Pos_Elbow = 180;
  int Pos_Wrist =90;
  int Pos_Claw = 90;
  int pos = 0;

//Start of setup function---------------------------------------------------------
void setup() 
{
  //Calling of sensor setup function to set sensors pins as input, output
  Sensor_Setup();
  
  // Initialize the 16x2 LCD
  lcd.begin(16, 2);
  
  //Initialize the SERVO motors to attach servo with pins
  Base.attach(PB_2);
  Shoulder.attach(PE_0);
  Elbow.attach(PF_0);
  Wrist_roll.attach(PB_6);
  Claw.attach(PA_4);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

//Start of loop function---------------------------------------------------------
void loop() 
{
  // Reset all positions to set motors at initial position 
  Shoulder.write(Pos_Shoulder);
  Elbow.write(Pos_Elbow);
  Wrist_roll.write(Pos_Wrist);
  delay(150);
  Base.write(Pos_Base);

  //Calling of delay function to set delay of 1.5 sec
  delay(1500);

  //to Clear LCD 
  lcd.clear();
  
  // Turn off all On board LEDs first
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  //Calling of delay function to set delay of 1.5 sec
  delay(1500);
  
  //Set position of Motors for pickup
  Pickup_pos();

  //Calling of Colour detection function that detect colour and set motors position accordingly.
  Detect_Color(); 
}

//Start of user functions------------------------------------------------------------------------
//Function 1: to set pins of sensors 
void Sensor_init()
{
  #define S0 PB_0        // Assuming pin S0 corresponds to PB 0
  #define S1 PB_1        // Assuming pin S1 corresponds to PB 1
  #define S2 PE_4        // Assuming pin S2 corresponds to PE 4
  #define S3 PE_5        // Assuming pin S3 corresponds to PE 5
  #define OUT PB_4       // Assuming pin OUT corresponds to PB 4
  
  #define LED1 RED_LED   // Assuming RED_LED is the macro for the red LED pin
  #define LED2 GREEN_LED // Assuming GREEN_LED is the macro for the green LED pin
  #define LED3 BLUE_LED  // Assuming BLUE_LED is the macro for the blue LED pin
  
}

//Function 2: Set pins that configure in sensor_init as input or output
void Sensor_Setup()
{
  pinMode(S0, OUTPUT);     //Set S0 as output
  pinMode(S1, OUTPUT);     //Set S1 as output
  pinMode(S2, OUTPUT);     //Set S2 as output
  pinMode(S3, OUTPUT);     //Set S3 as output
  pinMode(OUT, INPUT);     //Set output pin of sensor  as Input for tiva

  pinMode(LED1, OUTPUT);     //Set On-board Red LED as output
  pinMode(LED2, OUTPUT);     //Set On-board Green LED as output
  pinMode(LED3, OUTPUT);     //Set On-board Blue LED as output

  // Start with 20% frequency scaling
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600); // Initialize serial communication for debugging
}

void Detect_Color()
{
  
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  redFrequency = pulseIn(OUT, LOW);
  delay(100); // Adjust delay as needed for stability and LED display time

  // Setting green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  greenFrequency = pulseIn(OUT, LOW);
  delay(100); // Adjust delay as needed for stability and LED display time

  // Setting blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(OUT, LOW);
  delay(100); // Adjust delay as needed for stability and LED display time

  // Turn off all LEDs first
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  // Determine which color is dominant and turn on the corresponding LED
  if (greenFrequency < redFrequency && greenFrequency < blueFrequency)
  {
    digitalWrite(LED2, HIGH); // Turn GREEN LED ON
    //Print Green ON LCD
     lcd.clear();
    // Set cursor to the first column of the first row
    lcd.setCursor(1, 0);
    // Print "Color_Detected" on the LCD
    lcd.print("Color_Detected");  
    // Set cursor to the third column of the second row
    lcd.setCursor(5, 1);
    // Print "Green" on the LCD
    lcd.print("GREEN");
    //Call if green color detects motors move towards red basket
    // Start of placement toward green------------------------------------------

      for(pos = 82; pos < 90; pos+=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                      //delay function to create a delay of 50 milli sec
   }
   //delay function to create a delay of 150 milli sec
   delay(150);
  
   
    for(pos = 5; pos < 83; pos+=1)
   {                           
        Base.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
   for(pos = 180; pos > 160; pos-=1)
   {                           
        Elbow.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
   //delay function to create a delay of 150 milli sec
   delay(150);
   
   for(pos = 90; pos > 55; pos-=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
   for(pos = 90; pos < 110; pos+=1)
   {                           
        Claw.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  }
  else if (redFrequency < blueFrequency && redFrequency < greenFrequency)
  {
    digitalWrite(LED1, HIGH); // Turn RED LED ON
    //Print Red ON LCD
    lcd.clear();
    // Set cursor to the first column of the first row
    lcd.setCursor(1, 0);
    // Print "Color_Detected" on the LCD
    lcd.print("Color_Detected");
  
    // Set cursor to the third column of the second row
    lcd.setCursor(6, 1);
    // Print "RED" on the LCD
    lcd.print("RED");

    //Call if red color detects motors move towards red basket
    // Start of placement toward red------------------------------------------
     for(pos = 80; pos < 90; pos+=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
   
    for(pos = 5; pos < 58; pos+=1)
   {                           
        Base.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
   for(pos = 180; pos > 160; pos-=1)
   {                           
        Elbow.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
   
   for(pos = 90; pos > 55; pos-=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
   for(pos = 90; pos < 110; pos+=1)
   {                           
        Claw.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  }
  
  else if (blueFrequency < redFrequency && blueFrequency < greenFrequency)
  {
    digitalWrite(LED3, HIGH); // Turn BLUE LED ON
    //Print Blue ON LCD
    lcd.clear();
    // Set cursor to the first column of the first row
    lcd.setCursor(1, 0);
    // Print "Color_Detected" on the LCD
    lcd.print("Color_Detected");
  
    // Set cursor to the third column of the second row
    lcd.setCursor(6, 1);
    // Print "Blue" on the LCD
    lcd.print("BLUE");

    //Call if Blue color detects motors move towards red basket
    // Start of placement toward Blue------------------------------------------
    for(pos = 82; pos < 90; pos+=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);  
   
    for(pos = 5; pos < 102; pos+=1)
   {                           
        Base.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
   for(pos = 180; pos > 160; pos-=1)
   {                           
        Elbow.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
   
   for(pos = 90; pos > 55; pos-=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
   for(pos = 90; pos < 110; pos+=1)
   {                           
        Claw.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  }
  
  delay(500); // Adjust delay as needed to control LED display time and loop timing before reset 
  
}

//Functions For Motors----------------------------------------------------------
void Pickup_pos()
{
     for(pos = 90; pos < 150; pos+=1)
   {                           
        Claw.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
    for(pos = 120; pos > 74; pos-=1)
   {                           
        Shoulder.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
  
    for(pos = 120; pos > 50; pos-=1)
   {                           
        Wrist_roll.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
     delay(150);
     
   for(pos = 150; pos > 90; pos-=1)
   {                           
        Claw.write(pos);            // tell servo to go to position in variable 'pos' 
        delay(50);                 //delay function to create a delay of 50 milli sec
   }
    //delay function to create a delay of 150 milli sec
   delay(150);
}

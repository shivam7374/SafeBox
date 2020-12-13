// SAFEBOX USING KNOCK PATTERN
// HARSH-2019UCO1504  SHIVAM-2019UCO1526  YASH-2019UCO1530  HEMANT-2019UCO1534

#include <Servo.h> // Importing the servo library
Servo servo_motor; // Creating a servo instance

// Variables defining pin no. for LEDs' , piezo and switch
const int switch_push = 2;
const int led_yellow = 3;
const int led_green = 4;
const int led_red = 5;
const int piezo_sensor = A0;

int knock_read;                 // Variable to read piezo value
int switch_read;                // Variable to read switch value
const int threshold_knock = 50; // Variable declaring lower limit of knock value i.e threshold value
bool safebox_lock = false;      // Status of safebox lock

void setup()
{
      servo_motor.attach(9); // Attaching servo motor to 9th pin
      // Configuring the LED pins to behave as output pins
      pinMode(led_red, OUTPUT);
      pinMode(led_yellow, OUTPUT);
      pinMode(led_green, OUTPUT);
      pinMode(switch_push, INPUT);   // Configuring the switch pin as input pin
      Serial.begin(9600);            // Setting data rate for serial transmission, 9600 being the baud rate
      digitalWrite(led_green, HIGH); // Turning green LED on , i.e setting its voltage to 5V
      servo_motor.write(0);          // Setting the angle of servo shaft to 0 degree i.e safebox is unlocked
      Serial.println("!! Safebox is unlocked");
}

void loop()
{
      if (safebox_lock == false) // Checking if safebox is unlocked or not
      {
            switch_read = digitalRead(switch_push);
            if (switch_read == HIGH) // Locking the box if button is pressed
            {
                  safebox_lock = true;
                  // Changing the status of LEDs
                  digitalWrite(led_green, LOW);
                  digitalWrite(led_red, HIGH);
                  servo_motor.write(90); // Setting the servo angle to 90 degrees i.e safebox is locked
                  Serial.println("!! Safeboxbox is locked");
                  delay(1000);
            }
      }
      if (safebox_lock == true) // Checking if safebox is locked or not
      {
            int count_knocks = 0; // Variable for counting no of valid knocks
            knock_read = analogRead(piezo_sensor);
            while (knock_read > 0) // If piezo is knocked
            {
                  if (is_knock_valid(knock_read) == 1)
                  {
                        count_knocks += 1;
                  }
                  knock_read = analogRead(piezo_sensor);
            }
            if (count_knocks == 5) // Knock pattern is correct
            {
                  safebox_lock = false;
                  servo_motor.write(0); // Setting the servo to unlocked position of safebox
                  delay(20);
                  // Changing the status of LEDs
                  digitalWrite(led_green, HIGH);
                  digitalWrite(led_red, LOW);
                  Serial.println("!! Safebox is unlocked");
            }
            else if (count_knocks > 0 && count_knocks != 5)
            {
                  Serial.println("!! Invalid knock pattern");
            }
      }
}

int is_knock_valid(int kvalue) // Checking if knock is valid or not
{
      if (kvalue > threshold_knock)
      {
            // Yellow LED blinks on valid knock
            digitalWrite(led_yellow, HIGH);
            delay(50);
            digitalWrite(led_yellow, LOW);
            Serial.print("The knock was valid with value : ");
            Serial.println(kvalue);
            return 1;
      }
      else
      {
            Serial.print("The knock was invalid with value : ");
            Serial.println(kvalue);
            return 0;
      }
}
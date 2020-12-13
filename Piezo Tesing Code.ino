int piezo_Pin= 0;
int LED_Pin= 13;

//Set the threshold levels
int threshold= 500;

//Wakeup the Serial Monitor 
void setup()
{
Serial.begin(9600);
pinMode(LED_Pin, OUTPUT);
}

//if the reading is higher than the threshold value, then the LED is turned ON for a Second You can edit to your sepecification
void loop()
{
int reading= analogRead(piezo_Pin);
Serial.println(reading);
if (reading > threshold)
{
digitalWrite(LED_Pin, HIGH);
delay(1000);
digitalWrite(LED_Pin, LOW);
}
}

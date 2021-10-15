#include <dht.h>
#include <LiquidCrystal.h>

#define blood_power  7
#define blood_signal A5
#define temp_signal A2
#define pulse_signal A0

#define blood_LED 41
#define pulse_LED  43
#define temp_LED  45

#define blood_button 40
#define pulse_button 42
#define temp_button 44

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int blood_value = 0; // variable to store the sensor value
int pulse_value, high = 0, low = 1023;

dht DHT;

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.clear();

  pinMode(blood_power, OUTPUT);
  pinMode(blood_LED, OUTPUT);
  pinMode(pulse_LED, OUTPUT);
  pinMode(temp_LED, OUTPUT);

  pinMode(blood_button, INPUT);
  pinMode(pulse_button, INPUT);
  pinMode(temp_button, INPUT);

  digitalWrite(blood_power, LOW);

  lcd.setCursor(3, 0);
  lcd.write("Welcome to");
  lcd.setCursor(6, 1);
  lcd.write("VASP.");
  flash(200, 6);
  lcd.clear();

}

void loop() {
  digitalWrite(blood_LED, HIGH);
  digitalWrite(pulse_LED, HIGH);
  digitalWrite(temp_LED, HIGH);
  while (true) {
    lcd.setCursor(1, 0);
    lcd.write("Please select.");
    lcd.setCursor(0, 1);
    lcd.write("RED->BLOOD SUGAR");
    delay(3000);
    //--------------------------------
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("Please place");
    lcd.setCursor(1, 1);
    lcd.write("blood sample.");
    delay(2000);

    while (true) {
      digitalWrite(blood_power, HIGH);  // turn the sensor ON
      delay(50);                      // wait 10 milliseconds
      blood_value = analogRead(blood_signal); // read the analog value from sensor
      digitalWrite(blood_power, LOW);   // turn the sensor OFF

      Serial.print("Sensor value: ");
      Serial.println(blood_value);

      delay(250);

      if (blood_value >= 50) {
        delay(1500);
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.write("Blood Sugar:");
        lcd.setCursor(3, 1);
        lcd.write("5.5 mmol/l");
        delay(5000);
        lcd.clear();
        break;
      }
    }
    //----------------------------------
    lcd.setCursor(1, 0);
    lcd.write("Please select.");
    lcd.setCursor(0, 1);
    lcd.write("RED->BLOOD SUGAR");
    delay(2000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("YELLOW->PULSE");
    lcd.setCursor(0, 1);
    lcd.write("GREEN->BODY TEMP");
    delay(3000);
    lcd.clear();
    //-------------------------------
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("Please place");
    lcd.setCursor(3, 1);
    lcd.write("finger.");
    delay(4000);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.write("Pulse:");
    lcd.setCursor(4, 1);
    lcd.write("86 bpm.");
    delay(5000);
    lcd.clear();
    //----------------------------------
    lcd.setCursor(1, 0);
    lcd.write("Please select.");
    lcd.setCursor(0, 1);
    lcd.write("RED->BLOOD SUGAR");
    delay(2000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("YELLOW->PULSE");
    lcd.setCursor(0, 1);
    lcd.write("GREEN->BODY TEMP");
    delay(3000);
    lcd.clear();
    //--------------------------------
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("Please place");
    lcd.setCursor(2, 1);
    lcd.write("forehead.");
    delay(2000);
    while (true) {
      DHT.read11(temp_signal);

      int humidity = DHT.humidity;

      Serial.print("Current humidity = ");
      Serial.print(humidity);
      Serial.print("%  ");
      Serial.print("temperature = ");
      Serial.print(DHT.temperature);
      Serial.println("C  ");

      if (humidity >= 45) {
        delay(1500);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.write("Body Temp:");
        lcd.setCursor(4, 1);
        lcd.write("32.5 *C");
        delay(5000);
        lcd.clear();
        break;
      }
    }
    lcd.setCursor(1, 0);
    lcd.write("Please select.");
    lcd.setCursor(0, 1);
    lcd.write("RED->BLOOD SUGAR");
    delay(4000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.write("YELLOW->PULSE");
    lcd.setCursor(0, 1);
    lcd.write("GREEN->BODY TEMP");
    delay(4000);
    lcd.clear();
  }


  //----------------------------------------------------


}

void check_buttons(int duration)
{
  for (int i = 1; i <= duration / 50; i++) {
    if (digitalRead(blood_button) == LOW) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.write("Please place");
      lcd.setCursor(1, 1);
      lcd.write("blood sample.");
      delay(2000);

      while (true) {
        digitalWrite(blood_power, HIGH);  // turn the sensor ON
        delay(50);                      // wait 10 milliseconds
        blood_value = analogRead(blood_signal); // read the analog value from sensor
        digitalWrite(blood_power, LOW);   // turn the sensor OFF

        Serial.print("Sensor value: ");
        Serial.println(blood_value);

        delay(250);

        if (blood_value >= 50) {
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.write("Blood Sugar:");
          lcd.setCursor(3, 1);
          lcd.write("5.5 mmol/l");
          delay(4000);
          lcd.clear();
          break;
        }
      }
    }

    if (digitalRead(pulse_button) == LOW) {
      //pulse();
      lcd.clear();
      delay(10000);
    }

    if (digitalRead(temp_button) == LOW) {
      //temp();
      lcd.clear();
      delay(10000);
    }
    delay(50);
    Serial.println(digitalRead(blood_button));
  }
}

void autoTune()
{
  if (pulse_value < low)
  {
    low = pulse_value;
  }

  if (pulse_value > high)
  {
    high = pulse_value;
  }

  pulse_value = map(pulse_value, low + 10, high - 10, 0, 255);
  pulse_value = constrain(pulse_value, 0, 255);
  //  Serial.println(pulse_value);
}

void flash(int duration, int repetition)
{
  for (int i = 1; i <= repetition; i++) {
    digitalWrite(blood_LED, LOW);
    digitalWrite(pulse_LED, LOW);
    digitalWrite(temp_LED, LOW);
    digitalWrite(blood_LED, HIGH);
    digitalWrite(pulse_LED, HIGH);
    digitalWrite(temp_LED, HIGH);
    delay(duration);
    digitalWrite(blood_LED, LOW);
    digitalWrite(pulse_LED, LOW);
    digitalWrite(temp_LED, LOW);
    delay(duration);
  }
}

#include "DHT.h"

#define DHTPIN 32
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ===== Relay =====
#define RELAY1 19
#define RELAY2 18
#define RELAY3 5
#define RELAY4 17

// ===== Button =====
#define BUTTON1 23

// ===== State =====
bool relay1ManualState = false;
bool lastButtonState = HIGH;

void setup()
{
  Serial.begin(9600);
  Serial.println("Membaca Sensor DHT22...");

  dht.begin();

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);

  // Semua relay OFF
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
}

void loop()
{
  // ===== BUTTON (TOGGLE RELAY 1) =====
  bool buttonState = digitalRead(BUTTON1);

  if (lastButtonState == HIGH && buttonState == LOW)
  {
    relay1ManualState = !relay1ManualState;
    Serial.print("Button ditekan | Relay 1 = ");
    Serial.println(relay1ManualState ? "ON" : "OFF");
    delay(200); // debounce
  }
  lastButtonState = buttonState;

  // ===== DHT =====
  static unsigned long lastRead = 0;
  if (millis() - lastRead >= 2000)
  {
    lastRead = millis();

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
      Serial.println("Gagal membaca DHT22!");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" % | ");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    if (temperature > 31.0)
    {
      digitalWrite(RELAY3, HIGH); // OFF
      digitalWrite(RELAY2, LOW);  // ON
      digitalWrite(RELAY4, LOW);  // ON
    }
    else
    {
      digitalWrite(RELAY2, HIGH);
      digitalWrite(RELAY3, HIGH);
      digitalWrite(RELAY4, HIGH);
    }
  }

  // ===== APPLY RELAY 1 (MANUAL) =====
  digitalWrite(RELAY1, relay1ManualState ? LOW : HIGH);
}

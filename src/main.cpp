#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================= DHT22 =================
#define DHTPIN 32
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED gagal terdeteksi");
    while (true)
      ;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); 

  // Cek jika sensor gagal baca
  if (isnan(humidity) || isnan(temperature))
  {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println("DHT22 ERROR");
    display.display();
    delay(2000);
    return;
  }

  // Logika mode sederhana
  String mode = "IDLE";
  if (humidity > 65)
    mode = "DEHUMID";
  else if (humidity < 45)
    mode = "HUMID";

  // ===== TAMPILAN OLED =====
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("HUMIDITY CONTROL");

  display.setCursor(0, 14);
  display.print("Temp : ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 26);
  display.print("RH   : ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 40);
  display.print("Mode : ");
  display.println(mode);

  display.display();
  delay(2000);
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Lebar OLED
#define SCREEN_HEIGHT 64 // Tinggi OLED
#define OLED_RESET -1    // Reset pin (gunakan -1 jika tidak ada)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Masukkan array PROGMEM dari langkah 1 di sini
const unsigned char logo_unova[] PROGMEM = {/* data HEX tadi */};

void setup()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Alamat I2C umum 0x3C
    for (;;)
      ;
  }

  display.clearDisplay();

  // Menampilkan Bitmap
  // drawBitmap(x, y, data, lebar, tinggi, warna)
  display.drawBitmap(0, 16, logo_unova, 128, 32, WHITE);

  display.display();
}

void loop()
{
  // Tidak ada proses berulang
}
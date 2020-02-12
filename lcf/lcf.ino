#include <LiquidCrystal_I2C.h>
#include <OneWire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
OneWire ds(0);

void setup() 
{
  lcd.init();
  lcd.clear();
// Turn on the backlight.
  lcd.backlight();
}

void loop() 
{
  byte i; // counter
  byte present = 0; // 
  byte data[12]; 
  byte addr[8];
  float celsius, fahrenheit;
  delay(100);
  
  if ( !ds.search(addr)) 
  {
    ds.reset_search();
    delay(100);
    return;
  }
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        
  delay(1000); 
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         
 
  for ( i = 0; i < 9; i++) {     
    data[i] = ds.read();
  }
  
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);

  if (cfg == 0x00) raw = raw & ~7;  
  else if (cfg == 0x20) raw = raw & ~3; 
  else if (cfg == 0x40) raw = raw & ~1; 
    
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  lcd.print(celsius);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print(fahrenheit);
  lcd.print(" F");
  lcd.setCursor(0,0);
}

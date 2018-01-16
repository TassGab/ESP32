#include <EEPROM.h>
int addr = 0;
#define EEPROM_SIZE 64
struct my_data {
  unsigned int count;
  unsigned int channel;
  char title[10];
};
my_data datas;
unsigned int sl = 0;
void setup()
{

  sl = sizeof(datas);
  Serial.begin(115200);
  Serial.println("start...");
  Serial.print("Structure size="); Serial.println(sl);
  if (!EEPROM.begin(sl))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  
  Serial.println(" bytes read from Flash . Values are:");
  for (int i = 0; i < sl; i++)
  {
    Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
  }
  Serial.println();
  Serial.println("writing struct in memory");
  datas.count = 15;
  datas.channel = 1;
  datas.title[0] = 'H';
  datas.title[1] = 'e';
  datas.title[2] = 'l'; datas.title[3] = 'l'; datas.title[4] = 'o'; datas.title[5] = '\0';
  EEPROM.put(addr, datas);
  EEPROM.commit();
    Serial.println("\nRead flash after put");
  for (int i = 0; i < sl; i++)
  {
    Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
  }
  my_data test;
  EEPROM.get(addr, test);
  Serial.println("\nRead structure after get");

  Serial.println(); Serial.println("----------------------------------");
  Serial.print("title="); Serial.println(test.title);
  Serial.print("count="); Serial.println(test.count);
  Serial.print("ch="); Serial.println(test.channel);
  while (1);
}

void loop()
{
  // need to divide by 4 because analog inputs range from
  // 0 to 1023 and each byte of the EEPROM can only hold a
  // value from 0 to 255.
  // int val = analogRead(10) / 4;



}

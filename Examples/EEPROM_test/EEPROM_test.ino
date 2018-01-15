#include <EEPROM.h>
int addr = 0;
#define EEPROM_SIZE 64
struct my_data{
  unsigned int count;
  unsigned int channel;
  char title[10];
};
my_data datas;
unsigned int sl=0;
void setup()
{
  
  sl=sizeof(datas);
  Serial.begin(115200);
  Serial.println("start...");
  Serial.print("Structure size=");Serial.println(sl);
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
  datas.count=10;
  datas.channel=1;
  datas.title[0]='H';
  datas.title[1]='e';
  datas.title[2]='l';datas.title[3]='l';datas.title[4]='o';datas.title[5]='\0';
}

void loop()
{
  // need to divide by 4 because analog inputs range from
  // 0 to 1023 and each byte of the EEPROM can only hold a
  // value from 0 to 255.
  // int val = analogRead(10) / 4;
  
  byte val = byte(*((byte *)&datas+addr));
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.
  EEPROM.write(addr, val);
  Serial.print(val); Serial.print(" ");
  // advance to the next address.  there are 512 bytes in
  // the EEPROM, so go back to 0 when we hit 512.
  // save all changes to the flash.
  addr = addr + 1;
  if (addr == sl)
  {
    Serial.println();
    addr = 0;
    EEPROM.commit();
    Serial.print(sl);
    Serial.println(" bytes written on Flash . Values are:");
    my_data test;
    for (int i = 0; i < sl; i++)
    {
      byte val=byte(EEPROM.read(i));
      Serial.print(val); Serial.print(" ");
      *((byte *)&test+i)=val;
    }
    Serial.println("\nRead structure");
    
    Serial.println(); Serial.println("----------------------------------");
    Serial.print("title=");Serial.println(test.title);
    Serial.print("count=");Serial.println(test.count);
    Serial.print("ch=");Serial.println(test.channel);
      while(1);
  }


}

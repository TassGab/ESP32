Porting of ProgTherm for arduino chibi to ESP32

#implemented:
-check on EEPROM_FLASH_PARTITION_NAME to distinguish between AVR and ESP32
-explicit casting of types

#To be implemented:
-EEPROM.commit() on each function write: DONE
-EEPROM.begin(): DONE
-Use of EEPROM in two libraries: works but to understand
-Error in getting next event time but the allarm is triggered

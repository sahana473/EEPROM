/* Interfacing I2C 24LC512 EEPROM to Arduino Uno
 *  
 * Hardware Component:
 *  Arduino Uno
 *  24LC512 EEPROM
 *  
 * Hardware Connection:
 *  SDA of Arduino Uno is connected to SDA of EEPROM
 *  SCK of Arduino Uno is connected to SCK of EEPROM
 *  
 *  Author - Sahana B G
 *  Date - 11 May 2021
 */

 // Header file
 #include<Wire.h>

 // Device address for EEPROM when A0,A1,A2 are grounded
 const uint8_t DEVICE_ADDRESS = 0x50;

 // Memory address to store data
 const uint16_t MEMORY_ADDRESS = 0XABEF;

 // Data to store in the above address
 const uint8_t DATA = 0x35;
 
 void setup()
 {
  // Initialize I2C
  Wire.begin();

  // Initialize Serial Monitor
  Serial.begin(9600);
 } 

void loop()
{
  Serial.println("Writing data to EEPROM");
  Serial.print("Address = ");
  Serial.println(MEMORY_ADDRESS,HEX);
  Serial.print("Data =");
  Serial.println(DATA,HEX);
 
  
  // Write data to EEPROM first 
  write_data_eeprom();

  delay(500);

  // Read back the data
  byte data = read_data_eeprom();
  Serial.println("Reading data from EEPROM");
  Serial.print("Address = ");
  Serial.println(MEMORY_ADDRESS,HEX);
  Serial.print("Data =");
  Serial.println(data,HEX);

}

void write_data_eeprom()
{
  //Send a request to begin communication with the device at the specified DEVICE_ADDRESS
  Wire.beginTransmission(DEVICE_ADDRESS);

  // Send higher byte of memory address
  Wire.write((byte)(MEMORY_ADDRESS>>8));

  // Send lower byte of memory address
  Wire.write((byte)(MEMORY_ADDRESS & 0x00FF));

  // Send data to be stored
 // Wire.write((byte)DATA);
   Wire.write(DATA);

  // End the transmission
  Wire.endTransmission(); 
 }

byte read_data_eeprom()
{
 // Send a request to begin communication with the device at the specified DEVICE_ADDRESS
  Wire.beginTransmission(DEVICE_ADDRESS);

  // Send higher byte of memory address
  Wire.write((byte)(MEMORY_ADDRESS>>8));

  // Send lower byte of memory address
  Wire.write((byte)(MEMORY_ADDRESS & 0x00FF));

  // End the transmission
  Wire.endTransmission(); 

  // Request 1 byte
  Wire.requestFrom((byte)DEVICE_ADDRESS,(byte)1);

  // Read the data 
  byte recive_data = Wire.read();
  
  // End the transmission
  Wire.endTransmission();

  return recive_data;
}

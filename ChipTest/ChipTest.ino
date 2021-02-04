#include <xCore.h>
#include <xSI01.h>
#include <xSN01.h>
#include <xSL01.h>
#include <xSW01.h>

xSI01 SI01;
xSN01 SN01;
xSL01 SL01;
xSW01 SW01;
const int DELAY_TIME = 5000;
void setup() {
  // Start the Serial Monitor at 115200 BAUD
  Serial.begin(115200);
  // Set the I2C Pins for CW01
  #ifdef ESP8266
    Wire.pins(2, 14);
    Wire.setClockStretchLimit(15000);
  #endif
  Wire.begin();
  SI01.begin();
  SN01.begin();
  SL01.begin();
  SW01.begin();
  if (!SI01.begin()) {
    Serial.println("Cannot connect SI01");
  } else {
    Serial.println("start successful");
  }
}

void loop(){
  delay(DELAY_TIME);
  SI01.poll();
  printGyro();
  printAccel(); 
  printMag(); 
  printAttitude(); 

  String time;
  int latitude = 0;
  int longitude = 0;
  String date;
  float lux = 0;
  float uv = 0;
  
  SN01.poll();
  date = SN01.getDate();
  
  // Get the time from the GPS 
  time = SN01.getTime();

  // Get the latitude from GPS
  latitude = SN01.getLatitude();

  // Get the longitude from GPS
  longitude = SN01.getLongitude();

  Serial.print("GPS Time: ");
  Serial.println(time);
  Serial.print("GPS Date: ");
  Serial.println(date);
  Serial.print("GPS Latitude: ");
  Serial.println(latitude);
  Serial.print("GPS longitude: ");
  Serial.println(longitude);

  SL01.poll();
  lux = SL01.getLUX();
  Serial.print("Ambient Light Level: ");
  Serial.print(lux);
  Serial.println(" LUX");
  uv = SL01.getUVA();
  Serial.print("UVA Intersity: ");
  Serial.print(uv);
  Serial.println(" uW/m^2");
  
  // Request SL01 to return calculated UVB intensity
  uv = SL01.getUVB();
  Serial.print("UVB Intensity: ");
  Serial.print(uv);
  Serial.println(" uW/m^2");

  uv = SL01.getUVIndex();
  // Display Data on the Serial monitor
  Serial.print("UVB Index: ");
  Serial.println(uv);

  // Create a variable to store the data read from SW01  
  float tempC;
  float tempF;
  tempC = tempF = 0;
  
  // Read and calculate data from SW01 sensor
  SW01.poll();
  
  // Request SW01 to get the temperature measurement and store in
  // the temperature variable   
  tempC = SW01.getTempC(); // Temperature in Celcuis
  tempF = SW01.getTempF(); // Temperature in Farenheit
  
  // Display the recoreded data over the Serial Monitor   
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");
  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.println(" F"); 
  
  // Create a variable to store the data read from SW01
  float alt;
  alt = 0;
  float humidity;
  humidity = 0;
  humidity = SW01.getHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

void printGyro(void) {
  Serial.print("Gx: ");
  Serial.print(SI01.getGX(), 2);
  Serial.print("Gy: ");
  Serial.print(SI01.getGY(), 2);
  Serial.print("Gz: ");
  Serial.println(SI01.getGZ(), 2);

}

void printAccel(void) {
  Serial.print("Ax: ");
  Serial.print(SI01.getAX(), 2);
  Serial.print("Ay ");
  Serial.print(SI01.getAY(), 2);
  Serial.print("Az ");
  Serial.println(SI01.getAZ(), 2);
}

void printMag(void) {
  Serial.print("Mx: ");
  Serial.print(SI01.getMX(), 2);
  Serial.print("My: ");
  Serial.print(SI01.getMY(), 2);
  Serial.print("Mz: ");
  Serial.println(SI01.getMZ(), 2);

}

void printAttitude(void) {
  Serial.print("Roll is: ");
  Serial.println(SI01.getRoll(), 2);
  Serial.print("Pitch is:");
  Serial.println(SI01.getPitch(), 2);
  Serial.print("GForce is:");
  Serial.println(SI01.getGForce(), 2);
}

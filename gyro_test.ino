#include <L3G.h>
#include <Wire.h>

L3G gyro;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  if (!gyro.init()) {
    Serial.println("failed to autodetect gyro type");
    while (1);
  }
  gyro.enableDefault();

}

void loop() {
  // put your main code here, to run repeatedly:
  gyro.read();
  Serial.print("G ");
  Serial.print("X: ");
  Serial.print((int)gyro.g.x);
  Serial.print(" Y: ");
  Serial.print((int)gyro.g.y);
  Serial.print(" Z: ");
  Serial.println((int)gyro.g.z);

  delay(100);
}

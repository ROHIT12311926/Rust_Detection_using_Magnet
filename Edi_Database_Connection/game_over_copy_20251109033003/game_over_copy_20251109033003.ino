#include <Wire.h>
#include "Adafruit_MLX90393.h"

Adafruit_MLX90393 mlx;
float offsetX = 0, offsetY = 0, offsetZ = 0;

void setup() {
  Serial.begin(115200);
  if (!mlx.begin_I2C()) {
    Serial.println("MLX90393 not detected!");
    while (1);
  }

  Serial.println("Calibrating... Keep sensor away from magnets!");
  delay(2000);

  float sumX = 0, sumY = 0, sumZ = 0;
  sensors_event_t event;
  for (int i = 0; i < 100; i++) {
    mlx.getEvent(&event);
    sumX += event.magnetic.x;
    sumY += event.magnetic.y;
    sumZ += event.magnetic.z;
    delay(10);
  }

  offsetX = sumX / 100.0;
  offsetY = sumY / 100.0;
  offsetZ = sumZ / 100.0;

  Serial.println("Calibration Done!");
  Serial.println("X,Y,Z,Magnitude,Label");  // header for Python
}

void loop() {
  sensors_event_t event;
  mlx.getEvent(&event);

  float X = event.magnetic.x - offsetX;
  float Y = event.magnetic.y - offsetY;
  float Z = event.magnetic.z - offsetZ;
  float magnitude = sqrt((X * X) + (Y * Y) + (Z * Z));

  String label;
  if (magnitude < 5) {
    label = "Be ready";
  } else if (magnitude > 350) {
    label = "Keep the panels";
  } else if (magnitude > 185) {
    label = "RUSTED";
  } else {
    label = "NON-RUSTED";
  }

  // Print in CSV format
  Serial.print(X); Serial.print(",");
  Serial.print(Y); Serial.print(",");
  Serial.print(Z); Serial.print(",");
  Serial.print(magnitude); Serial.print(",");
  Serial.println(label);

  delay(200);
}

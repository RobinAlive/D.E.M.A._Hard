#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
    Serial.begin(9600);
    mlx.begin();
}

void loop() {
    float objectTemp = mlx.readObjectTempC();
    float ambientTemp = mlx.readAmbientTempC();
    
    Serial.print("Object Temperature: ");
    Serial.print(objectTemp);
    Serial.print(" °C\tAmbient Temperature: ");
    Serial.print(ambientTemp);
    Serial.println(" °C");
    
    delay(1000); // Wait for a second
}

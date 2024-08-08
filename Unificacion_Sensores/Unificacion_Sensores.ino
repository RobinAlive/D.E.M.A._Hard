#include <DHT.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define DHTTYPE DHT11
#define DHTPIN 9

#define REPORTING_PERIOD_MS 1000

// Crear objetos para los sensores
DHT dht(DHTPIN, DHTTYPE);
PulseOximeter pox;

// Variable para registrar el último reporte de tiempo
uint32_t tsLastReport = 0;

// Callback que se ejecuta cuando se detecta un latido
void onBeatDetected() {
    // Esto es opcional, se puede eliminar si no se requiere el mensaje en serie
    Serial.println("♥ Beat!");
}

void setup() {
    Serial.begin(9600);

    // Inicializar el sensor de temperatura
    dht.begin();

    // Inicializar el oxímetro de pulso
    Serial.print("Inicializando el oxímetro de pulso...");
    if (!pox.begin()) {
        Serial.println("FALLÓ");
        for (;;);
    } else {
        Serial.println("ÉXITO");
    }

    // Configurar el sensor de ritmo cardiaco y oxígeno en sangre
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
    // Leer temperatura
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("ERROR EN EL SENSOR DE TEMPERATURA");
        return;
    }

    // Actualizar datos del oxímetro
    pox.update();

    // Obtener y enviar datos cada segundo
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        float heartRate = pox.getHeartRate();
        float SpO2 = pox.getSpO2();

        // Crear la cadena JSON
        String jsonData = "{";
        jsonData += "\"temperatura\":" + String(temperature) + ",";
        jsonData += "\"ritmo_cardiaco\":" + String(heartRate) + ",";
        jsonData += "\"oxigeno_en_sangre\":" + String(SpO2);
        jsonData += "}";

        // Enviar la cadena JSON a través del puerto serial
        Serial.println(jsonData);

        tsLastReport = millis();
    }
}

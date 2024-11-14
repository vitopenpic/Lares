// Blynk Template Configuration

#define BLYNK_TEMPLATE_ID "TMPL2ZXgCCAXN"
#define BLYNK_TEMPLATE_NAME "Lares"
#define BLYNK_AUTH_TOKEN "bMLrv7UdN1rYHND9VuoRNnqVYN0QNd4X"

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BlynkSimpleEsp8266.h> 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "No name's Galaxy S22";
char pass[] = "mnnn6473";

// MPU6050 object
Adafruit_MPU6050 mpu;
// Accelerometer values
float ax, ay, az; 
const float fallThreshold = 14*14; // Magic number

// Blynk Virtual Pins
#define VP_ACCEL_X V0
#define VP_ACCEL_Y V1
#define VP_ACCEL_Z V2

void setup() {
    Serial.begin(9600); // Baud rate
    
    // Initialize Blynk
    Blynk.begin(auth, ssid, pass);

    // Initialize MPU6050
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 found!");
}

void loop() {
    // Read accelerometer and gyroscope data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Save sensor readings
    ax = a.acceleration.x; ay = a.acceleration.y; az=a.acceleration.z;
    float magnitude_of_acc = ax*ax + ay*ay + az*az;

    // Print acceleration and gyroscope readings
    Serial.print("Acceleration X: "); Serial.print(a.acceleration.x);
    Serial.print(" Y: "); Serial.print(a.acceleration.y);
    Serial.print(" Z: "); Serial.println(a.acceleration.z);

    // Send readings to Blynk
    Blynk.virtualWrite(VP_ACCEL_X, a.acceleration.x);
    Blynk.virtualWrite(VP_ACCEL_Y, a.acceleration.y);
    Blynk.virtualWrite(VP_ACCEL_Z, a.acceleration.z);

    Blynk.run(); // Run Blynk
    // // Wait until Blynk is connected
    // while (Blynk.connected() == false) {
    //     Serial.println("Connecting to Blynk...");
    //     delay(1000);
    // }
    // Serial.println("Blynk connected!");
    delay(1000); // Delay to make the output readable (in ms)

    if (magnitude_of_acc > fallThreshold){
        Blynk.logEvent("caida", "Se cayo!!!");
    }
}

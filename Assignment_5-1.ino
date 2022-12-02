// Include the Math library for calculations
#include <math.h>

// Variable Definitions
int count = 0; // Counter for trial #
int n = 20; // Number of readings taken per trial
// Digital I/O Pins connected to each light on the RGB LED
int redPin = 6;
int greenPin = 5;
int bluePin = 3;
float threshold = 25.0; // Compare temp readings to this number to
// determine what color to flash. You may need to use a different value
// depending on your environment

// Function to obtain temperature readings in Celsius from
// the thermistor
float Thermistor(int RawADC) {
float Temp;
float x = log(((10240000 / RawADC) - 10000));
Temp = 1 /(0.001129148 + (0.000234125 +(0.0000000876741 * square(x))) * x);
 Temp = Temp - 273.15; // Convert Kelvin to Celsius
 return Temp;
}
// Function to obtain the mean of a set of temperature readings
float getMean(float * val, int arrayCount) {
float total = 0;
 for (int i = 0; i < arrayCount; i++) {
 total = total + val[i];
 }
float avg = total/(float)arrayCount;
return avg;
}
// Function to obtain the standard deviation of a set of temperature
// readings
float getStdDev(float * val, int arrayCount) {
 float avg = getMean(val, arrayCount);
 float total = 0;
 for (int i = 0; i < arrayCount; i++) {
 total = total + square(val[i] - avg);
 }
 float variance = total/(float)arrayCount;
 float stdDev = sqrt(variance);
 return stdDev;
}
void setup() {
  // put your setup code here, to run once:
  // Specify the baud rate
 Serial.begin(9600);
 // Set up the pin modes
 // Pins for reading analog signal from the thermistor
 pinMode(A0, INPUT);

 // Pins for writing digital signal to the RGB LED
 pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT);
 pinMode(bluePin, OUTPUT);
 // Output a message to the user
 Serial.println("Begin collecting data...");
}

void loop() {
  // Create an array to store temperature readings
 float data[n];
 // Create a variable for the current reading
 float entry;
 // Update and display the trial #
 count++;
 Serial.print("Trial #");
 Serial.println(count);
 // Take temperature readings while flashing the green LED
 Serial.println("#\tTemp (C)");
 // Loop containing instructions for each entry in the trial
 for (int j = 0; j<n; j++){
 entry = Thermistor(analogRead(0)); // Read the temperature

 Serial.print(j+1); // Print the measurement number within the trial
 Serial.print("\t");
 Serial.println(entry); // Print the temperature

 // Add the temperature reading to the array for the trial
 data[j] = entry;
 // Flash the GREEN LED
 analogWrite(greenPin, 100);
 delay(500);
 analogWrite(greenPin, 0);
 delay(500);
 }
 Serial.print("End of Trial #");
 Serial.println(count);

 // Perform the mean and standard deviation calculations
 float mean = getMean(data, n);
 float std = getStdDev(data, n);

 // Display the results to the user
 Serial.print("Mean: ");
 Serial.println(mean);
 Serial.print("Standard deviation: ");
 Serial.print(std);
 Serial.println("\n");
 if (mean >= threshold){
 // Flash the Yellow LED when the average temperature is above the
 // threshold
 analogWrite(redPin, 225);
 analogWrite(greenPin, 225);
 delay(1000);
 analogWrite(redPin, 0);
 analogWrite(greenPin, 0);
 delay(50);
 }
 else{
 // Flash the BLUE LED when the average temperature is below the
 // threshold
 analogWrite(bluePin, 100);
 delay(1000);
 analogWrite(bluePin, 0);
 delay(50);
 }
 
}

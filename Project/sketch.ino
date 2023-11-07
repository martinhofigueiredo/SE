#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void dump(decode_results *results) {
 int count = results->rawlen;
 if (results->decode_type == UNKNOWN) {
 Serial.println("Could not decode message");
 } 
 else {
 Serial.println("Signal received.");
 if (results->decode_type == NEC) {
 Serial.print("Decoded NEC, ");
 } 
 else if (results->decode_type == SONY) {
 Serial.print("Decoded SONY, ");
 } 
 else if (results->decode_type == RC5) {
 Serial.print("Decoded RC5, ");
 } 
 else if (results->decode_type == RC6) {
 Serial.print("Decoded RC6, ");
 }
 Serial.print("Value= ");
 Serial.print(results->value, DEC);
 Serial.print(" (");
 Serial.print(results->bits, DEC);
 Serial.println(" bits)");
 }
 
}

void setup()
{
 Serial.begin(9600);
 Serial.println("IR decoder");
 irrecv.enableIRIn(); // Start the receiver
}

int on = 0;
unsigned long last = millis();

void loop() {
 if (irrecv.decode(&results)) {
 // Wait for 0.5sec before decoding another code
 if (millis() - last > 500) {
 
 dump(&results);
 }
 last = millis(); 
 irrecv.resume(); // Receive the next value
 }
}
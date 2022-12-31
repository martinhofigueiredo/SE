// Sketch to draw an analogue clock on the screen
// This uses anti-aliased drawing functions that are built into TFT_eSPI

// Anti-aliased lines can be drawn with sub-pixel resolution and permit lines to be
// drawn with less jaggedness.

// Based on a sketch by DavyLandman:
// https://github.com/Bodmer/TFT_eSPI/issues/905

#include "WiFiManager.h"

#include <Arduino.h>
// #include <TFT_eSPI.h> // Master copy here: https://github.com/Bodmer/TFT_eSPI
// #include <SPI.h>
#include "common.hpp"
#include "NotoSansBold15.h"

//TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
TFT_eSprite face = TFT_eSprite(&tft);

#define CLOCK_X_POS 10
#define CLOCK_Y_POS 10

#define CLOCK_FG   TFT_NAVY
#define CLOCK_BG   TFT_GOLD 
#define SECCOND_FG TFT_RED
#define LABEL_FG   TFT_SKYBLUE

#define CLOCK_R       127.0f / 2.0f // Clock face radius (float type)
#define H_HAND_LENGTH CLOCK_R/2.0f
#define M_HAND_LENGTH CLOCK_R/1.4f
#define S_HAND_LENGTH CLOCK_R/1.3f

#define FACE_W CLOCK_R * 2 + 1
#define FACE_H CLOCK_R * 2 + 1

// Calculate 1 second increment angles. Hours and minute hand angles
// change every second so we see smooth sub-pixel movement
#define SECOND_ANGLE 360.0 / 60.0
#define MINUTE_ANGLE SECOND_ANGLE / 60.0
#define HOUR_ANGLE   MINUTE_ANGLE / 12.0

// Sprite width and height
#define FACE_W CLOCK_R * 2 + 1
#define FACE_H CLOCK_R * 2 + 1

// Time h:m:s
uint8_t h = 0, m = 0, s = 0;

float time_secs = h * 3600 + m * 60 + s;

// Load header after time_secs global variable has been created so it is in scope
#include "NTP_Time.h" // Attached to this sketch, see that tab for library needs

// =========================================================================
// Get coordinates of end of a line, pivot at x,y, length r, angle a
// =========================================================================
// Coordinates are returned to caller via the xp and yp pointers
#define DEG2RAD 0.0174532925
void getCoord(int16_t x, int16_t y, float *xp, float *yp, int16_t r, float a)
{
  float sx1 = cos( (a - 90) * DEG2RAD);
  float sy1 = sin( (a - 90) * DEG2RAD);
  *xp =  sx1 * r + x;
  *yp =  sy1 * r + y;
}

class clockApp{
public:
  // Time for next tick
  uint32_t targetTime = 0;

  static void clockLocalTime()
  {
      // Combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      //unsigned long secsSince1900 = highWord << 16 | lowWord;
      setTime(utc);      // Set system clock to utc time (not time zone compensated)
      time_t utc_local = 0;
      time_t unix_time = now();
      float time_secs_local = 0.0;
      // Now convert NTP Unix time (Seconds since Jan 1 1900) into everyday time:
      // UTC time starts on Jan 1 1970. In seconds the difference is 2208988800:
      utc_local = unix_time; //- 2208988800UL;

      timeValid = true;

      // Print the hour, minute and second:
      Serial.print("Received time : ");

      uint8_t hh = hour(utc_local);
      Serial.print(hh); // print the hour (86400 equals secs per day)

      Serial.print(':');
      uint8_t mm = minute(utc_local);
      if (mm < 10 ) Serial.print('0');
      Serial.print(mm); // print the minute (3600 equals secs per minute)

      Serial.print(':');
      uint8_t ss = second(utc_local);
      if ( ss < 10 ) Serial.print('0');
      Serial.println(ss); // print the second

      time_secs_local = hh * 3600 + mm * 60 + ss; // Update the clock time
  }

  // =========================================================================
  // Draw the clock face in the sprite
  // =========================================================================
  static void renderDigitalClock(float t)
  {
    String dig_num = "00:00:00";
    
    face.createSprite(FACE_W, FACE_H);
    // The face is completely redrawn - this can be done quickly
    face.fillSprite(TFT_BLACK);

    dig_num = timeString(t);
    //Add text (could be digital time...)
    face.setTextColor(LABEL_FG, CLOCK_BG);
    face.drawString(dig_num, CLOCK_R, CLOCK_R * 0.75);

    face.pushSprite(5, 150, TFT_TRANSPARENT);
  }

  // =========================================================================
  // Draw the clock face in the sprite
  // =========================================================================
  static void renderFace(float t) {
    float h_angle = t * HOUR_ANGLE;
    float m_angle = t * MINUTE_ANGLE;
    float s_angle = t * SECOND_ANGLE;

    // The face is completely redrawn - this can be done quickly
    face.fillSprite(TFT_BLACK);

    // Draw the face circle
    face.fillSmoothCircle( CLOCK_R, CLOCK_R, CLOCK_R, CLOCK_BG );

    // Set text datum to middle centre and the colour
    face.setTextDatum(MC_DATUM);

    // The background colour will be read during the character rendering
    face.setTextColor(CLOCK_FG, CLOCK_BG);

    // Text offset adjustment
    constexpr uint32_t dialOffset = CLOCK_R - 10;

    float xp = 0.0, yp = 0.0; // Use float pixel position for smooth AA motion

    // Draw digits around clock perimeter
    for (uint32_t h = 1; h <= 12; h++) {
      getCoord(CLOCK_R, CLOCK_R, &xp, &yp, dialOffset, h * 360.0 / 12);
      face.drawNumber(h, xp, 2 + yp);
    }

    // Add text (could be digital time...)
    // face.setTextColor(LABEL_FG, CLOCK_BG);
    // face.drawString("SMART CLOCK", CLOCK_R, CLOCK_R * 0.75);

    // Draw minute hand
    getCoord(CLOCK_R, CLOCK_R, &xp, &yp, M_HAND_LENGTH, m_angle);
    face.drawWideLine(CLOCK_R, CLOCK_R, xp, yp, 6.0f, CLOCK_FG);
    face.drawWideLine(CLOCK_R, CLOCK_R, xp, yp, 2.0f, CLOCK_BG);

    // Draw hour hand
    getCoord(CLOCK_R, CLOCK_R, &xp, &yp, H_HAND_LENGTH, h_angle);
    face.drawWideLine(CLOCK_R, CLOCK_R, xp, yp, 6.0f, CLOCK_FG);
    face.drawWideLine(CLOCK_R, CLOCK_R, xp, yp, 2.0f, CLOCK_BG);

    // Draw the central pivot circle
    face.fillSmoothCircle(CLOCK_R, CLOCK_R, 4, CLOCK_FG);

    // Draw cecond hand
    getCoord(CLOCK_R, CLOCK_R, &xp, &yp, S_HAND_LENGTH, s_angle);
    face.drawWedgeLine(CLOCK_R, CLOCK_R, xp, yp, 2.5, 1.0, SECCOND_FG);
    face.pushSprite(5, 10, TFT_TRANSPARENT);
  }

  // =========================================================================
  // Setup
  // =========================================================================
  void clock_setup() {
    Serial.begin(9600);
    while (!Serial)
    ;
    Serial.println("Booting...");

    // Initialise the screen
    tft.init();

    // Ideally set orientation for good viewing angle range because
    // the anti-aliasing effectiveness varies with screen viewing angle
    // Usually this is when screen ribbon connector is at the bottom
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    // Create the clock face sprite
    //face.setColorDepth(8); // 8 bit will work, but reduces effectiveness of anti-aliasing
    face.createSprite(FACE_W, FACE_H);

    // Only 1 font used in the sprite, so can remain loaded
    face.loadFont(NotoSansBold15);

    // The face is completely redrawn - this can be done quickly
    face.fillSprite(TFT_BLACK);
    
    // Set text datum to middle centre and the colour
    face.setTextDatum(MC_DATUM);

    // Add text (could be digital time...)
    face.setTextColor(LABEL_FG, CLOCK_BG);
    face.drawString("SMART CLOCK", CLOCK_R, CLOCK_R * 0.75);

    face.pushSprite(5,80, TFT_TRANSPARENT);

    //tft.drawCentreString("Connecting to WIFI",0,8,NotoSansBold15)

    WiFi.mode(WIFI_STA);

    WiFiManager wm;
    // wm.resetSettings(); // Comment for production
    
    bool auto_connect_res;
    auto_connect_res = wm.autoConnect("SmartClockWIFI");
    
    if(!auto_connect_res)
    {
      Serial.println("Failed to connect");
      WiFi.setAutoReconnect(true);
      // ESP.restart();
    }
    else
      Serial.println("Connected");
      
    // Initialise the screen
    tft.init();
    // Ideally set orientation for good viewing angle range because
    // the anti-aliasing effectiveness varies with screen viewing angle
    // Usually this is when screen ribbon connector is at the bottom
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    // Create the clock face sprite
    //face.setColorDepth(8); // 8 bit will work, but reduces effectiveness of anti-aliasing
    face.createSprite(FACE_W, FACE_H);

    // Only 1 font used in the sprite, so can remain loaded
    face.loadFont(NotoSansBold15);

    // Draw the whole clock - NTP time not available yet
    renderFace(time_secs);

    targetTime = millis() + 100;
  }
  timeStatus_t status;
  // =========================================================================
  // Loop
  // =========================================================================
  void clock_routine() {

    // Update time periodical
    if (targetTime < millis()) {
      // Update next tick time in 100 milliseconds for smooth movement
      targetTime = millis() + 100;
      // Increment time by 100 milliseconds
      time_secs += 0.100;
      // Midnight roll-over
      if (time_secs >= (60 * 60 * 24)) time_secs = 0;

      // All graphics are drawn in sprite to stop flicker
      renderFace(time_secs);
      renderDigitalClock(time_secs);

      // Request time from NTP server and synchronise the local clock
      // (clock may pause since this may take >100ms)
      syncTime();
    }
  }

};
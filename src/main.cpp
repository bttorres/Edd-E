#include <functions.h>

// Initialize servos and motors with corresponding GPIOs
#define pan 26
#define tilt 33
#define roll 32
#define left_forward 27
#define left_backward 14
#define right_forward 21
#define right_backward 22
#define SD_CS 16
#define TFT_CS 5
#define TFT_DC 17
#define TFT_RST 4
// Initialize servos
Servo pan_servo;
Servo tilt_servo;
Servo roll_servo;
ESP32PWM pwm;
SdFat SD;                        // SD card filesystem
Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
// ESP32 creates it's own WiFi and acts as an Access Point
// ESP32 provides IP address to go to for web app control
// IP address: 192.168.4.1
const char *ssid1 = "Eddies WiFi";
const char *password1 = "1234567890";
// Initialize needed variables
int pan_val = 90;
int tilt_val = 90;
int roll_val = 90;
int servo_speed = 6;

void setup()
{
  // Initialize servo motors using ESP32Servo library
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  // Set frequency to 50 Hz for standard SG90
  pan_servo.setPeriodHertz(50);
  tilt_servo.setPeriodHertz(50);
  roll_servo.setPeriodHertz(50);
  // Initialize servos with corresponding GPIOs
  pan_servo.attach(pan, 500, 2500);
  tilt_servo.attach(tilt, 500, 2500);
  roll_servo.attach(roll, 500, 2500);
  // Initialize motors with corresponding GPIOs
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
  // Initialize screen
  tft.init(240, 320);
  tft.setRotation(1);
  SD.begin(SD_CS, SD_SCK_MHZ(25));
  tft.fillScreen(ST77XX_BLACK);
  delay(1000);
  // Silences brown outs
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  // Set up serial for testing
  Serial.begin(115200);
  // Starting WiFi Access Point
  WiFi.softAP(ssid1, password1);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  startServer();
}

void loop()
{
  // Set servo positions from inputs of webapp
  pan_val = map(sendVal[0], 0, 309, 180, 0);
  pan_servo.write(pan_val);
  tilt_val = map(abs(sendVal[1]), 0, 309, 45, 135);
  tilt_servo.write(tilt_val);
  roll_servo.write(sendVal[2]);
  // Set wheel velocity from inputs of webapp
  if (sendVal[3] >= 0) // Move left wheel forward
  {
    analogWrite(left_forward, sendVal[3]);
    analogWrite(left_backward, 0);
  }
  else // Move left wheel backward
  {
    analogWrite(left_forward, 0);
    analogWrite(left_backward, abs(sendVal[3]));
  }
  if (sendVal[4] >= 0) // Move right wheel forward
  {
    analogWrite(right_forward, sendVal[4]);
    analogWrite(right_backward, 0);
  }
  else // Move right wheel backward
  {
    analogWrite(right_forward, 0);
    analogWrite(right_backward, abs(sendVal[4]));
  }
  // Perform selected actions from webapp
  switch (sendVal[5])
  {
  case 1: // Happy
    reader.drawBMP("/happy.bmp", tft, 40, 0);
    delay(500);
    pan_servo.write(100);
    tilt_servo.write(100);
    for (int i = 0; i < 5; i++)
    {
      for (int j = 60; j < 121; j++)
      {
        roll_servo.write(j);
        delay(servo_speed);
      }
      for (int j = 120; j > 59; j--)
      {
        roll_servo.write(j);
        delay(servo_speed);
      }
    }
    for (int i = 60; i < 86; i++)
    {
      roll_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 2: // Sleep
    reader.drawBMP("/sleep.bmp", tft, 40, 0);
    delay(500);
    pan_servo.write(100);
    roll_servo.write(85);
    for (int i = 100; i > 49; i--)
    {
      tilt_servo.write(i);
      delay(servo_speed);
    }
    delay(5000);
    for (int i = 50; i < 101; i++)
    {
      tilt_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 3: // Sad
    reader.drawBMP("/sad.bmp", tft, 40, 0);
    delay(500);
    pan_servo.write(100);
    for (int i = 100; i > 64; i--)
    {
      tilt_servo.write(i);
      delay(servo_speed);
    }
    for (int i = 0; i < 5; i++)
    {
      for (int j = 60; j < 121; j++)
      {
        roll_servo.write(j);
        delay(servo_speed);
      }
      for (int j = 120; j > 59; j--)
      {
        roll_servo.write(j);
        delay(servo_speed);
      }
    }
    for (int i = 60; i < 86; i++)
    {
      roll_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 4: // Yes
    reader.drawBMP("/yes.bmp", tft, 40, 0);
    delay(500);
    pan_servo.write(100);
    roll_servo.write(85);
    for (int i = 0; i < 5; i++)
    {
      for (int j = 60; j < 121; j++)
      {
        tilt_servo.write(j);
        delay(servo_speed);
      }
      for (int j = 120; j > 59; j--)
      {
        tilt_servo.write(j);
        delay(servo_speed);
      }
    }
    for (int i = 60; i < 101; i++)
    {
      tilt_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 5: // Mad
    reader.drawBMP("/mad.bmp", tft, 40, 0);
    delay(500);
    roll_servo.write(85);
    for (int i = 100; i > 64; i--)
    {
      tilt_servo.write(i);
      delay(servo_speed);
    }
    for (int i = 0; i < 5; i++)
    {
      for (int j = 60; j < 121; j++)
      {
        pan_servo.write(j);
        delay(servo_speed);
      }
      for (int j = 120; j > 59; j--)
      {
        pan_servo.write(j);
        delay(servo_speed);
      }
    }
    for (int i = 60; i < 101; i++)
    {
      pan_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 6: // No
    reader.drawBMP("/no.bmp", tft, 40, 0);
    delay(500);
    tilt_servo.write(100);
    roll_servo.write(85);
    for (int i = 0; i < 5; i++)
    {
      for (int j = 60; j < 121; j++)
      {
        pan_servo.write(j);
        delay(servo_speed);
      }
      for (int j = 120; j > 59; j--)
      {
        pan_servo.write(j);
        delay(servo_speed);
      }
    }
    for (int i = 60; i < 101; i++)
    {
      pan_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 7: // Confused
    reader.drawBMP("/confused.bmp", tft, 40, 0);
    delay(500);
    pan_servo.write(100);
    tilt_servo.write(100);
    for (int i = 85; i < 136; i++)
    {
      roll_servo.write(i);
      delay(servo_speed);
    }
    delay(5000);
    for (int i = 135; i > 84; i--)
    {
      roll_servo.write(i);
      delay(servo_speed);
    }
    sendVal[5] = 0;
    break;
  case 8: // Custom
    /* code */
    break;
  default: // default to blank, black screen
    tft.fillScreen(ST77XX_BLACK);
    break;
  }
  delay(15);
}

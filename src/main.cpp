#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <Servo.h>

// PIN DEFINITIONS
#define RSL_LED 23
#define R1 21
#define R1C 0
#define R2 19
#define R2C 1
#define L1 18
#define L1C 2
#define L2 13
#define L2C 3
#define B1 17
#define B1C 4
#define B2 16
#define B2C 5
#define A1 4
#define A1C 6
#define A2 2
#define A2C 7

static const int S1 = 12;
static const int S2 = 27;
// static const int S3 = 26;
// static const int S4 = 25;

Servo Ser1;
bool ser1WaitingForOff = false;
int ser1PressTime = 0;
Servo Ser2;
bool ser2WaitingForOff = false;
int ser2PressTime = 0;
// Servo Ser3;
// bool ser3WaitingForOff = false;
// bool ser3PressTime = 0;
// Servo Ser4;
// bool ser4WaitingForOff = false;
// bool ser4PressTime = 0;


// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create a WebSocket object

AsyncWebSocket ws("/ws");

int watchdogRemaining = 0; // when this times out, stop all motors, change the rsl mode, and hold servos still.
bool robotEnabled = false;
bool RSLOn = false;

String incomingMsg = "";

// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else{
   Serial.println("LittleFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

void updateRSL() {
  if (robotEnabled) {
    if ((millis() / 10) % 100 == 0) { // full-second blinks when robot on
      RSLOn = !RSLOn;
    }
  }else{
    if ((millis() / 10) % 30 == 0) { // 0.3-second fast blinks when robot off
      RSLOn = !RSLOn;
    }
  }
  digitalWrite(RSL_LED, RSLOn);
}

void resetWatchdog() {
  watchdogRemaining = millis() + 5000;
}

void disableAllMotors() {
  driveMotor(R1C, R2C, 0);
  driveMotor(L1C, L2C, 0);
  driveMotor(A1C, A2C, 0);
  driveMotor(B1C, B2C, 0);
}

void watchdogAwoken() {
  robotEnabled = false;
  disableAllMotors();
}

void watchdogAsleep() {
  robotEnabled = true;
}

void checkWatchdog() {
  if (watchdogRemaining - millis() < 0) {
    watchdogAwoken();
  }else{
    watchdogAsleep();
  }
}

void handlePWMMessage(int ch, int pwr) {
  switch (ch) {
    case 1: //A
      driveMotor(A1C, A2C, pwr);
      break;
    case 2: //B
      driveMotor(B1C, B2C, pwr);
      break;
    case 3: //L
      driveMotor(L1C, L2C, pwr);
      break;
    case 4: //R
      driveMotor(R1C, R2C, pwr);
      break;
    default:
  }
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    incomingMsg = (char*)data;
    Serial.println(incomingMsg);
    char msgType = incomingMsg.charAt(0);

    if (msgType == 'W') {
      resetWatchdog();
      return;
    }
    // ex: 
    int parameter1 = incomingMsg.substring(1,3).toInt();
    int parameter2 = incomingMsg.substring(5,8).toInt();

    switch (msgType) {
      case 'W': // watchdog!
        resetWatchdog();
        break;
      case 'P': // PWM!
        handlePWMMessage(parameter1, parameter2 - 255);
        break;

      case 'S': // servo control!

        break;
      case 'N': // play a note!

        break;
      default:
        break;
    }
  }
}


void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setupPinModes() {
  pinMode(RSL_LED, OUTPUT);
  
  for (int i = 0; i < 8; i++) {
    ledcSetup(i, 1000, 8);
  }

  ledcAttachPin(R1, R1C);
  ledcAttachPin(R2, R2C);
  ledcAttachPin(L1, L1C);
  ledcAttachPin(L2, L2C);
  ledcAttachPin(A1, A1C);
  ledcAttachPin(A2, A2C);
  ledcAttachPin(B1, B1C);
  ledcAttachPin(B2, B2C);

  Ser1.attach(S1,8);
  Ser2.attach(S2,9);
  // Ser3.attach(S3,10);
  // Ser4.attach(S4,11);

  // Ser1.write(0);
  // Ser2.write(0);
  // Ser3.write(0);
  // Ser4.write(0);
}

// note that these are PWM CHANNEL pins
void driveMotor(int pin1, int pin2, int pwm) {
  if (pwm > 255)
    pwm = 255;
  if (pwm < -255)
    pwm = -255;
  if (pwm == 0) {
     ledcWrite(pin1, 0);
     ledcWrite(pin2, 0);
  }
  if (pwm > 0) {
     ledcWrite(pin2, 0);
     ledcWrite(pin1, pwm);
  }
  if (pwm < 0) {
     ledcWrite(pin1, 0);
     ledcWrite(pin2, -pwm);
  }
}

void setup() {
  Serial.begin(115200);
  
  initFS();
  initWiFi();
  initWebSocket();
  
  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });
  
  server.serveStatic("/", LittleFS, "/");

  // Start server
  server.begin();
}

void loop() {
  checkWatchdog();
  ws.cleanupClients();
}
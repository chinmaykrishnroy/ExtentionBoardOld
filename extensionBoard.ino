#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <EEPROM.h>

const int s3 = 12;
const int s4 = 14;
const int s5 = 4;
const int s6 = 5;
// const int LED_BUILTIN = 2;
WiFiServer server(80);

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(70);
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(4);
  Serial.println("\n\nWelcome!\n");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);
  pinMode(s6, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("EEPROM");
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  Serial.println("EEPROM DONE");
  digitalWrite(s3, EEPROM.read(2));
  digitalWrite(s4, EEPROM.read(3));
  digitalWrite(s5, EEPROM.read(0));
  digitalWrite(s6, EEPROM.read(1));
  delay(1000);

  Serial.println();
  WiFiManager wm;
  //wm.resetSettings();
  bool res;
  res = wm.autoConnect("PrefectESP", "password");  // password protected ap
  if (!res) {
    Serial.println("Failed to connect");
    ESP.restart();
  }
  Serial.println(WiFi.localIP());
  for (int j = 0; j < 5; j++) blink();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\" /><style> .skin1 button { border: 3px solid #fe53bb; color: #fe53bb; background-color: #840151; } .skin1 button:hover { border-color: #fe86cf; color: #fe86cf; background-color: #b70170; } .skin1 button:focus { border-color: #fe86cf; color: #fe86cf; background-color: #b70170; padding: 16px 16px; outline: 0; border-radius: 12px; } .skin1 button:focus:first-of-type { border-radius: 30px 12px 12px 30px; } .skin1 button:focus:last-of-type { border-radius: 12px 30px 30px 12px; } .skin2 button { border: 3px solid #f5d300; color: #f5d300; background-color: #292300; } .skin2 button:hover { border-color: #ffe129; color: #ffe129; background-color: #5c4f00; } skin2 button:focus { border-color: #ffe129; color: #ffe129; background-color: #5c4f00; padding: 16px 16px; outline: 0; border-radius: 12px; } .skin2 button:focus:first-of-type { border-radius: 30px 12px 12px 30px; } .skin2 button:focus:last-of-type { border-radius: 12px 30px 30px 12px; } .skin3 button { border: 3px solid #00d4ff; color: #00d4ff; background-color: #002a33; } .skin3 button:hover { border-color: #33ddff; color: #33ddff; background-color: #005566; } .skin3 button:focus { border-color: #33ddff; color: #33ddff; background-color: #005566; padding: 16px 16px; outline: 0; border-radius: 12px; } .skin3 button:focus:first-of-type { border-radius: 30px 12px 12px 30px; } .skin3 button:focus:last-of-type { border-radius: 12px 30px 30px 12px; } .skin4 button { border: 3px solid #72ff00; color: #72ff00; background-color: #173300; } .skin4 button:hover { border-color: #8eff33; color: #8eff33; background-color: #2e6600; } .skin4 button:focus { border-color: #8eff33; color: #8eff33; background-color: #2e6600; padding: 16px 16px; outline: 0; border-radius: 12px; } .skin4 button:focus:first-of-type { border-radius: 30px 12px 12px 30px; } .skin4 button:focus:last-of-type { border-radius: 12px 30px 30px 12px; } * { font-family: \"Muli\", sans-serif; } button::-moz-focus-inner { border: 0; } button { outline: 0; } body { background: #001519; height: 100vh; margin: 0; display: grid; place-items: center; justify-items: center; } .group-container { height: 100px; display: grid; place-items: center; justify-items: center; } .multi-button { font-size: 0; } button { font-weight: 800; background: transparent; min-width: 100px; text-transform: uppercase; border-radius: 8px; font-size: 15px; display: inline-block; padding: 10px 16px; margin: 0 3px 0 0; cursor: pointer; transition-duration: 0.1s; transition-timing-function: ease-in-out; } button:first-of-type { border-radius: 20px 8px 8px 20px; } button:last-of-type { border-radius: 8px 20px 20px 8px; } @media only screen and (max-width: 767px) { button { min-width: 80px; } } .nohigh { user-select: none; -webkit-user-select: none; -moz-user-select: none; -ms-user-select: none; } .nohigh::selection { background: transparent; }</style><script> window.addEventListener(\"load\", () => {var all = document.getElementsByClassName(\"nohigh\");for (let a of all) { a.onselectstart = () => false; }});</script><div class=\"container nohigh\"> <div class=\"group-container\"> <div class=\"multi-button skin1\"> <button onclick=\"window.location.href=\'/M\';\">S1 ON</button> <button onclick=\"window.location.href=\'/N\';\">S1 OFF</button></div> </div> <div class=\"group-container\"> <div class=\"multi-button skin2\"> <button onclick=\"window.location.href=\'/O\';\">S2 ON</button> <button onclick=\"window.location.href=\'/P\';\">S2 OFF</button> </div> </div> <div class=\"group-container\"> <div class=\"multi-button skin3\"> <button onclick=\"window.location.href=\'/Q\';\">S3 ON</button> <button onclick=\"window.location.href=\'/R\';\">S3 OFF</button> </div> </div> <div class=\"group-container\"> <div class=\"multi-button skin1\"> <button onclick=\"window.location.href=\'/S\';\">S4 ON</button> <button onclick=\"window.location.href=\'/T\';\">S4 OFF</button></div> </div> </div> </div></div><!--<footer style=\"color:#FAF6ED; text-align: right; vertical-align: bottom; font-size: xx-small;\" ><i>Chinmay Krishn Roy</i></footer>-->");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /M")) {
          digitalWrite(s5, LOW);
          EEPROM.write(0, 0);
          blink();
        }
        if (currentLine.endsWith("GET /N")) {
          digitalWrite(s5, HIGH);
          EEPROM.write(0, 1);
          blink();
        }
        if (currentLine.endsWith("GET /O")) {
          digitalWrite(s6, LOW);
          EEPROM.write(1, 0);
          blink();
        }
        if (currentLine.endsWith("GET /P")) {
          digitalWrite(s6, HIGH);
          EEPROM.write(1, 1);
          blink();
        }
        if (currentLine.endsWith("GET /Q")) {
          digitalWrite(s3, LOW);
          EEPROM.write(2, 0);
          blink();
        }
        if (currentLine.endsWith("GET /R")) {
          digitalWrite(s3, HIGH);
          EEPROM.write(2, 1);
          blink();
        }
        if (currentLine.endsWith("GET /S")) {
          digitalWrite(s4, LOW);
          EEPROM.write(3, 0);
          blink();
        }
        if (currentLine.endsWith("GET /T")) {
          digitalWrite(s4, HIGH);
          EEPROM.write(3, 1);
          blink();
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
  EEPROM.commit();
}

/**
 * This example shows how to turn on and off the ESP8266's on board LED over WiFi.
 *
 * @author https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html
 * @editor F.S. Koulen
 * @date 2023-10-18
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include "main/Constants.h"

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int led = 2;

void handleRoot();              // function prototypes for HTTP handlers
void handleLED();

void handleNotFound();

void setup(void) {
    Serial.begin(115200);         // Start the Serial communication to send messages to the computer
    delay(10);
    Serial.println('\n');

    pinMode(led, OUTPUT);

    WiFiManager wifiManager;
    wifiManager.setDebugOutput(true);
    wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD);

    Serial.println('\n');
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

    if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
        Serial.println("mDNS responder started");
    } else {
        Serial.println("Error setting up MDNS responder!");
    }

    server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
    server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
    server.onNotFound(
            handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

    server.begin();                           // Actually start the server
    Serial.println("HTTP server started");
}

void loop(void) {
    server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
    server.send(200, "text/html",
                R"(<form action="/LED" method="POST"><input type="submit" value="Toggle LED"></form>)");
}

void handleLED() {                          // If a POST request is made to URI /LED
    digitalWrite(led, !digitalRead(led));      // Change the state of the LED
    server.sendHeader("Location",
                      "/");        // Add a header to respond with a new location for the browser to go to the home page again
    server.send(
            303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound() {
    server.send(404, "text/plain",
                "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
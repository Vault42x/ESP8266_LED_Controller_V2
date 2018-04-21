#include <ESP8266WiFi.h>

// Configure static network information
// If using DHCP, comment out all IPAddress
// lines below.
//
IPAddress ip(192, 160, 1, 10);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(192, 168, 1, 1);

// Configure Wifi Connection Security
//
const char* ssid     = "Put your SSID Here";
const char* password = "Put your WPA2 Key Here";

// Define Pins for RGB LEDs
// NodeMCU Pins
//   RED_LED   - 8266 PIN D6 - 12
//   BLUE_LED  - 8266 PIN D5 - 14
//   GREEN_LED - 8266 PIN D4 - Pin 2
//
#define RED_LED 12
#define BLUE_LED 14
#define GREEN_LED 2

// Define HTTP Server Port
//
WiFiServer server(80);

void setup(){
  Serial.begin(115200);
  WiFi.config(ip, gateway, subnet, DNS);
  delay(100);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print("#");
      delay(500);
  }
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println();
    Serial.println("Connection Failed");
    delay(5000);
    ESP.restart();
  }
  Serial.print("   OK  ");
  Serial.print("Device IP: ");
  Serial.println(WiFi.localIP());

  // Define LED Output Pins
  //
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Start the HTTP Server
  //
  server.begin();
  Serial.println("HTTP Server Started...");
 
  // Display Connection Address
  //
  Serial.print("Connection Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  
  // Wait for Connection
  //
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait for HTTP Request
  //
  Serial.println("New Socket Open");
  while(!client.available()){
    delay(1);
  }
 
  // Read HTTP Request
  //
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Perform Requested LED Function
  // 
  int value = LOW;
  if (request.indexOf("/LED=OFF") != -1)  {
    analogWrite(RED_LED, 0);
    analogWrite(BLUE_LED, 0);
    analogWrite(GREEN_LED, 0);
  }
  if (request.indexOf("/COLOR=RED") != -1) {
    analogWrite(RED_LED, 255);
    analogWrite(BLUE_LED, 0);
    analogWrite(GREEN_LED, 0);
  }
  if (request.indexOf("/COLOR=BLUE") != -1) {
    analogWrite(RED_LED, 0);
    analogWrite(BLUE_LED, 255);
    analogWrite(GREEN_LED, 0);
  }
  if (request.indexOf("/COLOR=GREEN") != -1) {
    analogWrite(RED_LED, 0);
    analogWrite(BLUE_LED, 0);
    analogWrite(GREEN_LED, 255);
  }
  if (request.indexOf("/COLOR=WHITE") != -1) {
    analogWrite(RED_LED, 255);
    analogWrite(BLUE_LED, 255);
    analogWrite(GREEN_LED, 255);
  }
   if (request.indexOf("/COLOR=VIOLET") != -1) {
    analogWrite(RED_LED, 255);
    analogWrite(BLUE_LED, 255);
    analogWrite(GREEN_LED, 0);
  }

  // Return HTTP Response
  //
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  
  client.println("<html>");
  client.println("<br>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a> ");  
  client.println("<a href=\"/COLOR=RED\"\"><button>Red </button></a> ");
  client.println("<a href=\"/COLOR=GREEN\"\"><button>Green </button></a> ");
  client.println("<a href=\"/COLOR=BLUE\"\"><button>Blue </button></a> ");
  client.println("<a href=\"/COLOR=WHITE\"\"><button>White </button></a> ");
  client.println("<a href=\"/COLOR=VIOLET\"\"><button>Violet </button></a> ");
  client.println("</html>");
 
  delay(1);
  Serial.println("Socket Closed");
  Serial.println("");

}

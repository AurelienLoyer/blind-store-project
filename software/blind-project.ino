#include <ESP8266WiFi.h>
#include "FS.h"
#include "DHT.h"
#include "config.h"

#define DHTPIN 3     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22 // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);

#define SENSOR_PIN A0 // select the input pin for the potentiometer
#define MIN_VALUE 25 // 
#define MAX_VALUE 800 //

const char* ssid = CONFIG_SSID;
const char* password = CONFIG_PASSWORD;

int Pin1 = 1; // GPIO5
int Pin2 = 2; // GPIO4

const char* state = "STOP";

String html_home; // 
int blind_position = 0; // 
int sensorValue = 0; //
int timeToUp = 10; // 10 secondes pour monter complétement le volet
int timeToDown = 6; // 6 secondes pour descendre complétement le volet 

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
    Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  prepareFiles();
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  sensorValue = analogRead(SENSOR_PIN);
  float level = 100 - ((sensorValue - MIN_VALUE) * 100 / (MAX_VALUE - MIN_VALUE));
  sensorValue = level;

  // Move position
  if(state == "UP") {
    // ici il faut soustraire le calcul qui donne un pourcentage d'avancement à la position initialle
    blind_position = blind_position - ((0.1 * 100) / timeToUp);
  }else if (state == "DOWN") {
    blind_position = blind_position + ((0.1 * 100) / timeToDown);
  }

  Serial.println(blind_position);
  
  if(blind_position <= 0){
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    state = "STOP";
    Serial.println("STOP LIMITE 0 !!!");
  }

  if(blind_position >= 100){
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    state = "STOP";
    Serial.println("STOP LIMITE 100 !!!");
  }
  
  // Match the request 
  if (request.indexOf("/action?value=up") != -1)  {
    Serial.println("UP Request !!!");
    state = "UP";
    client.println('{"resp":"ok","action":"up"}');
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, HIGH);    
  }
  else if (request.indexOf("/action?value=down") != -1)  {
    Serial.println("DOWN Request !!!");
    state = "DOWN";
    client.println('{"resp":"ok","action":"down"}');
    digitalWrite(Pin1, HIGH);
    digitalWrite(Pin2, LOW);
  }
  else if (request.indexOf("/action?value=stop") != -1)  {
    Serial.println("STOP Request !!!");
    state = "STOP";
    client.println('{"resp":"ok","action":"stop"}');
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
  }
  else if (request.indexOf("/position") != -1)  {
    client.println(blind_position);
  }
  else if (request.indexOf("/luminosity") != -1)  {
    client.println(sensorValue);
  }
  else if (request.indexOf("/temperature") != -1)  {
    client.println(t);
  }
  else if (request.indexOf("/humidity") != -1)  {
    client.println(h);
  }
  else if (request.indexOf("/move?to=") != -1)  {
    /*char delims[] = "/move?to=";
    char *part = strtok(request, delims);
    while (part != NULL) {
      Serial.println(part); 
    }*/
    Serial.println(request);
  }
  else {
    client.println(html_home);
  }

  delay(100);
 
}

void prepareFiles(){
  
  Serial.println("Prepare file system");
  SPIFFS.begin();
  
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    Serial.println("File open index failed");  
  } else{
    Serial.println("File open index success");
    html_home = "";
    while (file.available()) {
      String line = file.readStringUntil('\n');
      html_home += line + "\n";
    }
    file.close();
  }
  
  file = SPIFFS.open("/position.txt", "r");
  if (!file) {
    Serial.println("File open position failed");  
  } else{
    Serial.println("File open position success");
    while (file.available()) {
      //Serial.write(file.read());
      String line = file.readStringUntil('\n');
      blind_position = line.toInt();
      Serial.println("Blind position saved : " + line);
    }
    file.close();
  }
}

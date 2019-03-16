#include <SoftwareSerial.h>
#include "WiFiEsp.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>

  const char serverJson[] = "api.openweathermap.org";
const String email = "eri_byd@hotmail.com";
const String xid = "dicegame24";
String data = "P1,4,2,1";
const String hostname = "primat.se";
String countryCode = "se";
const String APIKey = "0c6c77820236b1a47e8ac996c35c21c8";
//const String uri = "/services/data/" + email + "-" + xid + ".csv";
const String senduri = "/services/sendform.aspx?xdata=" + email + "|" + xid;
const int port = 80;
String line;
// Create module object on GPIO pin

// wifi 6 (RX) and 7 (TX)
SoftwareSerial mySerial1(10, 11);

// Declare and initialise global arrays for WiFi settings
const char ssid[] = "AndroidAP";
const char pass[] = "nevc6096";


  WiFiEspClient clientJson;
int testVar = 0;
int switchNumber=0;


// Declare and initialise variable for radio status
int status = WL_IDLE_STATUS;
WiFiEspServer server(80);
RingBuffer buf(8);
WiFiEspClient client;
void setup()
{
    // Initialize serial for debugging
    Serial.begin(115200);
    // Initialize serial
   mySerial1.begin(9600);
    wifiInit();
}

void loop()
{
    //jSon();
    //delay(1000); 
    //printWifiStatus();
   // delay(5000);

client = server.available();
if(client) {
buf.init(); 
    Serial.println("New client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        buf.push(c);
if(testVar == 1){Serial.print("JAAAAA");}


        if (buf.endsWith("GET /H")) 
        {
            
             Serial.println("TESTING");
            jSon();
 
          }
          else if (buf.endsWith("GET /L")) 
          {
            digitalWrite(11, LOW);
          }

        
        if (c == '\n' && currentLineIsBlank) 
        {
          Serial.println("Sending response");

          // Send a standard HTTP response header
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n");

String html ="<!DOCTYPE html> <html> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <link rel= \"stylesheet\" href=\"https://zztorp.github.io/WeatherDataHtmlCss/main.css\"> </head> <body> <h1 align=\"center\">Mathilda & Eriks IoT-Projekt</h1> <h1 align=\"center\">Weather Data</h1> <div class=\"row\"> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Stockholm.jpg\"  style=\"width:100%\"> <button class=\"btn\" onclick=\"window.location.href='/H'\"> Stockholm</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Tokyo.jpg\" style=\"width:100%\" alt=\"centered image\"/> <button class=\"btn\">Tokyo</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Paris.jpg\" alt=\"Paris\" style=\"width:100%\"> <button class=\"btn\">Paris</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Amsterdam.jpg\" alt=\"Amsterdam\" style=\"width:100%\"> <button class=\"btn\">Amsterdam</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/London.jpg\" alt=\"London\" style=\"width:100%\"> <button class=\"btn\">London</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/Barcelona.jpg\" alt=\"Barcelona\" style=\"width:100%\"> <button class=\"btn\">Barcelona</button> </div> <div class=\"column\"> <div class=\"container\"> <img src=\"https://zztorp.github.io/WeatherDataHtmlCss/SanFrancisco.jpg\" alt=\"SanFrancisco\" style=\"width:100%\"> <button class=\"btn\">San Francisco</button> </div> </div> </body> </html>";
client.print(html);
            
         
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    delay(3000);

    client.stop();

    Serial.println("Client disconnected");
  }
  

}

void TEST()
{
  Serial.print("IT WORKS!!!!");
  }


void jSon()
{
  String city;
 switchNumber = 2;

switch(switchNumber)
{
  case 1:
  city = "tokyo";
  break;
  case 2:
  city = "Stockholm";
  break;
  case 3:
  city = "Amsterdam";
  break;
  case 4:
  city = "Barcelona";
  break;
  case 5:
  city = "Paris";
  break;
  case 6:
  city = "London";
  break;
  case 7:
  city = "SanFrancisco";
  break;
 
  }

  String uri = "/data/2.5/weather?q=" + city + "&APPID=" + APIKey;//"/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + APIKey;
Serial.print(uri);
delay(1000);
   // Serial.println();
   // Serial.println(F("Reading from server..."));
    // if you get a connection, report back via serial
    if (clientJson.connect(serverJson, port))
    {
        Serial.println("Connected to server");
        // Make a HTTP request
        clientJson.println("GET " + uri + " HTTP/1.1");
        clientJson.println("Host: " + hostname);
        clientJson.println("Connection: close");
        clientJson.println();
    }

    /* if there are incoming bytes available
     * from the server, read them and print them */
    while (clientJson.available() == 0)
    {
        delay(5);
        Serial.print("newhurrdirr");
    }
if (client.available()) {
        char c = clientJson.read();
        Serial.write(c);
        Serial.print("ö");
        }
Serial.print("sistatest");
  char endOfHeaders[] = "\r\n\r\n";

 if (!clientJson.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    Serial.print("innan buff");

   return;
  }
Serial.print("innan parce");


 // const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2)
//+ JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12)+ 368;
//const size_t bufferSize = 500;
//DynamicJsonBuffer jsonBuffer(bufferSize);

      

      
StaticJsonBuffer <1000> jsonBuffer;

JsonObject& root = jsonBuffer.parseObject(clientJson);
Serial.print("efter parce");

if(!root.success()) {
  Serial.println("parseObject() failed");
}

JsonObject& weather_0 = root["weather"][0];

//double longitude = root ["weather"][0];
const char* weather = weather_0 ["main"];
//Serial.print(longitude);
Serial.print(weather);


  clientJson.stop();
  }

  
void wifiInit()
{
    // Initialize ESP module
    WiFi.init(&mySerial1);
    // Check for the presence of the shield
    if (WiFi.status() == WL_NO_SHIELD)
    {
        Serial.println("WiFi shield not present");
        // Don't continue
        while (true)
        {
        
        }       
    }

    // Attempt to connect to WiFi network
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network
        status = WiFi.begin(ssid, pass);
    }

    server.begin();
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    Serial.println("You're connected to the network");
    printWifiStatus();
    Serial.println();

}





void printWifiStatus()
{
    // print the SSID of the network you're attached to
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address
    //IPAddress ip = WiFi.localIP();
    //Serial.print("IP Address: ");
    //Serial.println(ip);

    // print the received signal strength
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");

}

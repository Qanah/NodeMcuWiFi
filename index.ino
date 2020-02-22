#include <ESP8266WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiServer server(80);

int led_0 = 13;
int led_1 = 12;
int led_2 = 4;
int led_3 = 5;

void setup() {
  Serial.begin(115200);
  delay(10); 
  
  // put your setup code here, to run once:
  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);

  digitalWrite(led_0, LOW);
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);
  digitalWrite(led_3, LOW);

  Serial.print("Connecting to");
  Serial.println();
  Serial.print(ssid);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi Connected");

  server.begin();

  Serial.println();
  Serial.print("Server started");

  Serial.println();
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println();
}

void loop() {

  WiFiClient client = server.available(); 
  if(!client) {
    return;
  }

  Serial.println("New Client");
  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value_0 = digitalRead(led_0);
  int value_1 = digitalRead(led_1);
  int value_2 = digitalRead(led_2);
  int value_3 = digitalRead(led_3);
  
  if(request.indexOf("/LED_0=ON") != -1) {
    value_0 = HIGH;
  }
  if(request.indexOf("/LED_0=OFF") != -1) {
    value_0 = LOW;
  }

  if(request.indexOf("/LED_1=ON") != -1) {
    value_1 = HIGH;
  }
  if(request.indexOf("/LED_1=OFF") != -1) {
    value_1 = LOW;
  }

  if(request.indexOf("/LED_2=ON") != -1) {
    value_2 = HIGH;
  }
  if(request.indexOf("/LED_2=OFF") != -1) {
    value_2 = LOW;
  }

  if(request.indexOf("/LED_3=ON") != -1) {
    value_3 = HIGH;
  }
  if(request.indexOf("/LED_3=OFF") != -1) {
    value_3 = LOW;
  }

  if(request.indexOf("/All=ON") != -1) {
    value_0 = HIGH;
    value_1 = HIGH;
    value_2 = HIGH;
    value_3 = HIGH;
  }
  if(request.indexOf("/All=OFF") != -1) {
    value_0 = LOW;
    value_1 = LOW;
    value_2 = LOW;
    value_3 = LOW;
  }
  
  digitalWrite(led_0, value_0);
  digitalWrite(led_1, value_1);
  digitalWrite(led_2, value_2);
  digitalWrite(led_3, value_3);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>NodeMcu V3 Client</title>");
  client.println("</head>");
  client.println("<body>");
  
  client.println("<a href='/All=ON'>Turn All ON</a>");
  client.println("<a href='/All=OFF'>Turn All OFF</a>");

  client.println("<table border='1'>");

  client.println("<tr>");
  client.println("<th>Led Nomber</th>");
  client.println("<th>Led Status</th>");
  client.println("<th>Actions</th>");
  client.println("</tr>");
  
  client.println("<tr>");
  client.println("<td>1</td>");
  client.println("<td>");
  client.println((value_0 == HIGH) ? "On" : "Off"); 
  client.println("</td>");
  client.println("<td>");
  client.println((value_0 == HIGH) ? "<a href='/LED_0=OFF'>Turn Off</a>" : "<a href='/LED_0=ON'>Turn On</a>"); 
  client.println("</td>");
  client.println("</tr>");

  client.println("<tr>");
  client.println("<td>2</td>");
  client.println("<td>");
  client.println((value_1 == HIGH) ? "On" : "Off"); 
  client.println("</td>");
  client.println("<td>");
  client.println((value_1 == HIGH) ? "<a href='/LED_1=OFF'>Turn Off</a>" : "<a href='/LED_1=ON'>Turn On</a>"); 
  client.println("</td>");
  client.println("</tr>");

  client.println("<tr>");
  client.println("<td>3</td>");
  client.println("<td>");
  client.println((value_2 == HIGH) ? "On" : "Off"); 
  client.println("</td>");
  client.println("<td>");
  client.println((value_2 == HIGH) ? "<a href='/LED_2=OFF'>Turn Off</a>" : "<a href='/LED_2=ON'>Turn On</a>"); 
  client.println("</td>");
  client.println("</tr>");

  client.println("<tr>");
  client.println("<td>4</td>");
  client.println("<td>");
  client.println((value_3 == HIGH) ? "On" : "Off"); 
  client.println("</td>");
  client.println("<td>");
  client.println((value_3 == HIGH) ? "<a href='/LED_3=OFF'>Turn Off</a>" : "<a href='/LED_3=ON'>Turn On</a>"); 
  client.println("</td>");
  client.println("</tr>");
  
  client.println("</table>");
  client.println("</body>");
  client.println("</html>");
  
  delay(1);

  Serial.println("Client disconnected");
}

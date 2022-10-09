#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "AFTERMATH";
const char* password = "YLLEQGQG72F";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output3State = "off";
String output2State = "off";
String output1State = "off";

//Servo variables as above
String output6State = "off";
String output7State = "off";
String output8State = "off";
String output9State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;//d1forward
const int output4 = 4;//d2right
const int output3 = 0;//d3alt
const int output2 = 2;//d4back
const int output1 = 16;//d0left

const int output6 = 14;//d5Servo++
const int output7 = 12;//d6Servo--
const int output8 = 13;//d7Servo++
const int output9 = 15;//d8Servo--
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  Serial.println("Setting Up");
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output1, OUTPUT);
  //Servo control outputs
  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output8, OUTPUT);
  pinMode(output9, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output1, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ....");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println(WiFi.localIP());
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
           
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output2State = "off";
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output5State = "off";
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } 
            else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 6 on");
              output6State = "on";
              digitalWrite(output6, HIGH);
            }else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 6 off");
              output6State = "off";
              digitalWrite(output6, LOW);
            }else if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("GPIO 7 on");
              output7State = "on";
              digitalWrite(output7, HIGH);
            }else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("GPIO 7 off");
              output7State = "off";
              digitalWrite(output7, LOW);
            }else if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("GPIO 8 on");
              output8State = "on";
              digitalWrite(output8, HIGH);
            }else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("GPIO 8 off");
              output8State = "off";
              digitalWrite(output8, LOW);
            }

            else if (header.indexOf("GET /9/on") >= 0) {
              Serial.println("GPIO 9 on");
              output9State = "on";
              digitalWrite(output9, HIGH);
            }else if (header.indexOf("GET /9/off") >= 0) {
              Serial.println("GPIO 9 off");
              output9State = "off";
              digitalWrite(output9, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<title>Robot Net Control</title>");

            client.println("<style>*{margin: 0;padding: 0;}");
            client.println("body{background-color: rgba(188, 241, 228, 0.267);}");
            client.println("h1{width: 100%;display: flex;justify-content: center;margin: auto;}");
            client.println(".center{width: 100%;height: 50vh;display: flex;justify-content: center;align-items: center;}");
            client.println(".container{width: 100%;display: grid;grid-template-columns: 1fr 1fr 1fr;grid-template-rows: 1fr 1fr 1fr;grid-template-areas:\"topl forward topr\"\"lefty alt righty\"\"botl backward botr\";}");
            client.println(".item-5{grid-area: forward;}");
            client.println(".item-4{grid-area: righty;}");
            client.println(".item-3{grid-area: alt;}");
            client.println(".item-2{grid-area: backward;}");
            client.println(".item-6{grid-area: topl;}");
            client.println(".item-7{grid-area: botl;}");
            client.println(".item-8{grid-area: topr;}");
            client.println(".item-9{grid-area: botr;}");
            
            client.println(".button{margin: 1em;padding: 1em;width: 5em;border-radius: 10px;border: 1px transparent solid;box-shadow:1px 2px 4px grey;}");
            client.println(".button1{background-color: rgb(167, 166, 166); margin: 1em;padding: 1em;width: 5em;border-radius: 10px;border: 1px transparent solid;box-shadow:1px 2px 4px grey;}");
            client.println(".buttonS{margin: 1em;padding: 1em;width: 5em;border-radius: 40px;border: 1px transparent solid;box-shadow:1px 2px 4px grey;}");
            client.println(".buttonS1{background-color: rgb(184, 178, 251); margin: 1em;padding: 1em;width: 5em;border-radius: 40px;border: 1px transparent solid;box-shadow:1px 2px 4px grey;}</style></head>");

            client.println("<body><h1>AMeCaR Control</h1><div class=\"center\"><div class=\"container\">");


            if (output5State == "off") {
              client.println("<div class = \"item item-5\"><a class=\"signals\" href=\"/5/on\"><button class=\"button\">▲</button></a></div>");
            } else {
              client.println("<div class = \"item item-5\"><a class=\"signals\" href=\"/5/off\"><button class=\"button1\">▲</button></a></div>");
            }


            if (output4State == "off") {
              client.println("<div class = \"item item-4\"><a  class=\"signals\" href=\"/4/on\"><button class=\"button\">►</button></a></div>");
            } else {
              client.println("<div class = \"item item-4\"><a  class=\"signals\" href=\"/4/off\"><button class=\"button1\">►</button></a></div>");
            }

            if (output3State == "off") {
              client.println("<div class = \"item item-3\"><a  class=\"signals\" href=\"/3/on\"><button class=\"button\">ALT</button></a></div>");
            } else {
              client.println("<div class = \"item item-3\"><a  class=\"signals\" href=\"/3/off\"><button class=\"button1\">ALT</button></a></div>");
            }

            if (output2State == "off") {
              client.println("<div class = \"item item-2\"><a  class=\"signals\" href=\"/2/on\"><button class=\"button\">▼</button></a></div>");
            } else {
              client.println("<div class = \"item item-2\"><a  class=\"signals\" href=\"/2/off\"><button class=\"button1\">▼</button></a></div>");
            }

            if (output1State == "off") {
              client.println("<div class = \"item item-1\"><a  class=\"signals\" href=\"/1/on\"><button class=\"button\">◄</button></a></div>");
            } else {
              client.println("<div class = \"item item-1\"><a  class=\"signals\" href=\"/1/off\"><button class=\"button1\">◄</button></a></div>");
            }
            
            if (output6State == "off") {
              client.println("<div class = \"item item-6\"><a class = \"servo\" href=\"/6/on\"><button class=\"buttonS\">+</button></a></div>");
            } else {
              client.println("<div class = \"item item-6\"><a href=\"/6/off\"><button class=\"buttonS1\">+</button></a></div>");
            }
            if (output7State == "off") {
              client.println("<div class = \"item item-7\"><a href=\"/7/on\"><button class=\"buttonS\">-</button></a></div>");
            } else {
              client.println("<div class = \"item item-7\"><a href=\"/7/off\"><button class=\"buttonS1\">-</button></a></div>");
            }
            if (output8State == "off") {
              client.println("<div class = \"item item-8\"><a href=\"/8/on\"><button class=\"buttonS\">+</button></a></div>");
            } else {
              client.println("<div class = \"item item-8\"><a href=\"/8/off\"><button class=\"buttonS1\">+</button></a></div>");
            }
            if (output9State == "off") {
              client.println("<div class = \"item item-9\"><a href=\"/9/on\"><button class=\"buttonS\">-</button></a></div>");
            } else {
              client.println("<div class = \"item item-9\"><a href=\"/9/off\"><button class=\"buttonS1\">-</button></a></div>");
            }
            client.println("</div></div>");
            client.println("<script>window.addEventListener(\"load\", () => {");
            client.println("console.log(\"loaded\");");
            client.println("let link = document.querySelectorAll(\".signals\");");
            client.println("link.forEach((item, index) => {item.addEventListener(\"click\", (e) => {e.preventDefault();");
            client.println("link.forEach((lin, i) => {if(i!== index){lin.lastChild.classList.remove(\"button1\");");
            client.println("console.log(i, index);}");
            client.println("})");
            client.println("item.lastChild.classList.add(\"button1\");");
            client.println("location.href = item.href;");
            client.println("console.log(item.href);console.log(\"You clicked \" + index);}) })");
            client.println("console.log(link);});</script>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

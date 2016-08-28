/*Description : API for accessing TV remote */

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <ESP8266mDNS.h>

const char* ssid = "HANUMAN FOURTH FLOOR";
const char* password = "pongal@15";
MDNSResponder mdns;

IRsend irsend(4); //an IR led is connected to GPIO pin 0

int khz = 38; 

unsigned int KEY_POWER[] = {9012,4431,586,543,585,1654,584,545,586,545,588,543,586,542,587,547,585,554,583,1654,585,546,583,1653,586,1653,584,1653,585,1654,584,1651,588,1664,582,545,586,1653,584,546,583,548,585,1652,585,548,585,544,585,556,585,1651,588,546,586,1660,577,1657,583,545,636,1608,585,1655,578,1657,584};
unsigned int KEY_MUTE[] = {9006,4441,587,545,585,1653,585,545,585,546,585,544,586,546,585,545,586,552,586,1652,584,546,585,1651,586,1663,575,1651,585,1653,582,1655,584,1674,572,547,585,545,585,545,583,549,559,1678,585,546,585,544,585,556,580,1656,585,1653,585,1652,584,1653,602,527,586,1653,584,1654,584,1654,585};
unsigned int KEY_1[] = {9001,4447,582,544,585,1651,587,546,584,547,586,545,592,545,581,555,577,574,562,1657,583,544,585,1659,580,1658,582,1651,585,1658,580,1658,581,1663,554,1686,581,544,583,547,588,545,562,565,583,545,583,549,588,552,584,545,585,1651,585,1653,601,1636,585,1653,584,1652,560,1676,586,1655,583};
unsigned int KEY_2[] = {8972,4444,583,546,584,1654,584,548,583,547,584,547,583,548,584,547,584,554,584,1651,589,543,585,1653,584,1654,585,1653,561,1677,586,1653,584,1662,582,548,585,1654,584,546,585,545,597,535,585,546,581,549,584,557,585,1655,583,548,583,1654,583,1656,584,1653,585,1653,585,1650,587,1663,576};
unsigned int KEY_3[] = {8984,4457,570,545,584,1654,584,546,585,546,585,557,572,546,584,548,597,542,584,1653,585,546,584,1654,585,1650,589,1652,584,1654,582,1653,585,1672,576,1653,584,1654,585,546,584,544,586,547,584,548,558,584,571,556,585,546,585,574,564,1642,586,1654,583,1672,567,1652,583,1656,584,1655,584};
unsigned int KEY_4[] = {8984,4454,573,545,584,1653,584,548,583,547,583,545,586,546,584,559,572,554,585,1653,585,545,585,1651,587,1654,584,1666,571,1649,588,1654,584,1661,585,546,584,546,586,1651,586,547,583,547,586,545,584,546,585,557,585,1661,576,1652,585,545,585,1653,586,1650,587,1653,592,1648,582,1656,584};
unsigned int KEY_5[] = {9008,4441,584,547,584,1651,587,545,585,546,584,546,585,546,584,548,583,555,584,1656,583,546,585,1654,584,1653,598,1642,596,1641,584,1652,585,1659,588,1653,584,546,587,1653,585,546,584,544,586,547,584,546,585,556,585,546,585,1665,572,543,587,1653,584,1654,585,1654,584,1655,584,1653,585};
unsigned int KEY_6[] = {9015,4431,585,545,585,1654,583,547,585,557,571,549,584,546,584,546,585,554,585,1652,585,546,584,1663,576,1660,577,1653,584,1650,587,1653,585,1676,570,545,586,1649,588,1652,585,546,584,546,585,549,583,544,585,554,587,1652,584,546,585,546,584,1653,598,1637,586,1653,585,1653,585,1654,584};
unsigned int KEY_7[] = {9019,4424,587,547,583,1652,585,546,584,560,571,547,582,547,586,544,585,554,584,1653,585,546,584,1663,577,1652,584,1653,585,1653,582,1656,585,1672,574,1652,585,1650,587,1654,585,544,587,556,573,546,585,545,606,534,586,546,584,546,585,547,583,1654,585,1650,586,1654,584,1653,585,1654,585};
unsigned int KEY_8[] = {9011,4433,587,546,584,1668,569,545,583,548,584,547,584,546,584,547,584,554,585,1654,587,545,583,1655,583,1654,585,1652,582,1655,597,1641,584,1662,584,545,588,543,585,546,584,1653,596,536,584,545,586,545,583,558,585,1654,583,1654,583,1666,572,544,587,1654,583,1654,585,1653,585,1663,576};
unsigned int KEY_9[] = {9005,4459,571,544,585,1650,588,549,590,540,586,546,581,549,585,548,581,604,536,1659,580,543,585,1661,576,1650,587,1668,570,1657,581,1659,578,1662,583,1659,588,537,593,539,586,1654,579,549,585,546,582,547,587,554,584,543,584,1660,577,1662,577,546,587,1704,533,1655,614,1625,582,1659,576};
unsigned int KEY_0[] = {8983,4467,583,546,583,1667,573,546,584,546,585,546,584,547,584,547,581,556,583,1666,573,546,583,1654,585,1651,588,1652,585,1663,574,1653,583,1673,577,548,586,544,586,543,587,546,584,545,586,547,582,549,584,558,582,1660,578,1655,582,1653,582,1660,579,1658,579,1652,585,1659,587,1649,580};
unsigned int KEY_CHANNELUP[] = {8986,4446,578,546,585,1667,568,548,584,545,586,545,586,545,585,545,585,554,585,1650,601,532,585,1653,585,1652,585,1650,588,1653,595,1644,583,1662,584,1651,587,1651,585,545,597,1642,584,1650,587,546,585,545,585,556,584,546,584,546,584,1650,587,546,584,547,584,1653,560,1675,587,1663,575};
unsigned int KEY_CHANNELDOWN[] = {8987,4460,600,533,585,1653,585,544,586,545,583,548,585,546,584,548,583,554,596,1643,583,546,582,1656,585,1652,585,1653,586,1650,587,1654,586,1660,584,1653,618,1631,575,1651,585,1653,585,1651,587,545,585,557,574,555,584,545,585,546,586,546,585,542,587,546,585,1653,586,1664,573,1667,571};
unsigned int KEY_VOLUMEUP[] = {9017,4440,579,544,586,1656,582,544,582,550,583,543,587,546,597,533,590,549,589,1654,582,541,591,1654,581,1657,576,1662,580,1659,554,1681,578,1670,577,548,589,1654,578,544,585,1655,584,1659,577,549,584,550,575,559,587,1659,576,544,584,1661,575,550,578,551,586,1657,580,1657,583,1655,632};
unsigned int KEY_VOLUMEDOWN[] = {9004,4456,571,545,581,1657,584,545,585,546,585,548,582,545,560,572,580,557,585,1652,584,545,586,1652,585,1657,584,1651,586,1652,584,1652,585,1674,574,547,583,1665,573,1653,585,1649,588,1670,566,545,585,547,584,555,586,1650,587,546,586,544,586,545,585,547,583,1658,579,1653,585,1654,585};

WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);

  irsend.begin();
  
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
  Serial.println("WiFi Connected");

  // Start the server
  server.begin();
  Serial.println("HTTP Server Started");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("IRBlasterLR", WiFi.localIP())) {
    Serial.println("MDNS Responder Started");
  }

  Serial.println();
  Serial.println();
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
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  if (req.indexOf("/KEY_POWER") != -1){
      irsend.sendRaw(KEY_POWER, sizeof(KEY_POWER) / sizeof(KEY_POWER[0]), khz);   
      Serial.println("IRreq KEY_POWER sent");
  }
  else if (req.indexOf("/KEY_MUTE") != -1){
      irsend.sendRaw(KEY_MUTE, sizeof(KEY_MUTE) / sizeof(KEY_MUTE[0]), khz);   
      Serial.println("IRreq KEY_MUTE sent");
  }
  else if (req.indexOf("/KEY_1") != -1){
      irsend.sendRaw(KEY_1, sizeof(KEY_1) / sizeof(KEY_1[0]), khz);   
      Serial.println("IRreq KEY_1 sent");
  }
  else if (req.indexOf("/KEY_2") != -1){
      irsend.sendRaw(KEY_2, sizeof(KEY_2) / sizeof(KEY_2[0]), khz);   
      Serial.println("IRreq KEY_2 sent");
  }
  else if (req.indexOf("/KEY_3") != -1){
      irsend.sendRaw(KEY_3, sizeof(KEY_3) / sizeof(KEY_3[0]), khz);   
      Serial.println("IRreq KEY_3 sent");
  }
  else if (req.indexOf("/KEY_4") != -1){
      irsend.sendRaw(KEY_4, sizeof(KEY_4) / sizeof(KEY_4[0]), khz);   
      Serial.println("IRreq KEY_4 sent");
  }
  else if (req.indexOf("/KEY_5") != -1){
      irsend.sendRaw(KEY_5, sizeof(KEY_5) / sizeof(KEY_5[0]), khz);   
      Serial.println("IRreq KEY_5 sent");
  }
  else if (req.indexOf("/KEY_6") != -1){
      irsend.sendRaw(KEY_6, sizeof(KEY_6) / sizeof(KEY_6[0]), khz);   
      Serial.println("IRreq KEY_6 sent");
  }
  else if (req.indexOf("/KEY_7") != -1){
      irsend.sendRaw(KEY_7, sizeof(KEY_7) / sizeof(KEY_7[0]), khz);   
      Serial.println("IRreq KEY_7 sent");
  }
  else if (req.indexOf("/KEY_8") != -1){
      irsend.sendRaw(KEY_8, sizeof(KEY_8) / sizeof(KEY_8[0]), khz);   
      Serial.println("IRreq KEY_8 sent");
  }
  else if (req.indexOf("/KEY_9") != -1){
      irsend.sendRaw(KEY_9, sizeof(KEY_9) / sizeof(KEY_9[0]), khz);   
      Serial.println("IRreq KEY_9 sent");
  }  
  else if (req.indexOf("/KEY_0") != -1){
      irsend.sendRaw(KEY_0, sizeof(KEY_0) / sizeof(KEY_0[0]), khz);   
      Serial.println("IRreq KEY_0 sent");
  }
  else if (req.indexOf("/KEY_CHANNELUP") != -1){
      irsend.sendRaw(KEY_CHANNELUP, sizeof(KEY_CHANNELUP) / sizeof(KEY_CHANNELUP[0]), khz);   
      Serial.println("IRreq KEY_CHANNELUP sent");
  }
  else if (req.indexOf("/KEY_CHANNELDOWN") != -1){
      irsend.sendRaw(KEY_CHANNELDOWN, sizeof(KEY_CHANNELDOWN) / sizeof(KEY_CHANNELDOWN[0]), khz);   
      Serial.println("IRreq KEY_CHANNELDOWN sent");
  }
  else if (req.indexOf("/KEY_VOLUMEDOWN") != -1){
      irsend.sendRaw(KEY_VOLUMEDOWN, sizeof(KEY_VOLUMEDOWN) / sizeof(KEY_VOLUMEDOWN[0]), khz);   
      Serial.println("IRreq KEY_VOLUMEDOWN sent");
  }
  else if (req.indexOf("/KEY_VOLUMEUP") != -1){
      irsend.sendRaw(KEY_VOLUMEUP, sizeof(KEY_VOLUMEUP) / sizeof(KEY_VOLUMEUP[0]), khz);   
      Serial.println("IRreq KEY_VOLUMEUP sent");
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  
  client.flush();
   
  // Send the response to the client
  //client.print(s);
  client.print("HTTP/1.1 200 OK\r\n");
  delay(1);
  Serial.println("Client Disconnected");
  Serial.println();
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

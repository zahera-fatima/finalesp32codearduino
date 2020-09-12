#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <WiFi.h>
#include "BluetoothSerial.h"
#include <WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>





const char* ssid = "A30";
const char* password = "15121472";

WebServer server(80);
const char* device="esp";

// Set your Static IP address
IPAddress local_IP(192, 168, 43, 109);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const uint16_t kIrLed = 21;
IRsend irsend(kIrLed); 

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title>ESP8266 Demo</title></head>" \
                "<body>" \
                  "<h1>Hello from ESP8266, you can send NEC encoded IR" \
                      "signals from here!</h1>" \                                     
                      "<p><a href=\"ir?code=CD364887\">Send left hand up</a></p>" \           
                  "<p><a href=\"ir?code=DE3AD379\">Send right hand up</a></p>" \
                  "<p><a href=\"ir?code=744F598C\">Send Left Hand Down</a></p>" \
                  "<p><a href=\"ir?code=FC055B44\">Send Right Hand Down</a></p>" \
                  "<p><a href=\"ir?code=714F54D5\">Send Left Hand In</a></p>" \
                  "<p><a href=\"ir?code=F905568D\">Send Right Hand In</a></p>" \
                  "<p><a href=\"ir?code=5A872050\">Send Left Hand Out</a></p>" \
                  "<p><a href=\"ir?code=6B267EBA\">Send Right Hand Out</a></p>" \
                  "<p><a href=\"ir?code=59871EBF\">Send Tilt Left</a></p>" \
                  "<p><a href=\"ir?code=6A267D29\">Send Tilt Right</a></p>" \
                  "<p><a href=\"ir?code=806D9980\">Send Move Forward</a></p>" \
                  "<p><a href=\"ir?code=7F6D97EF\">Move Backward</a></p>" \
                  "<p><a href=\"ir?code=E13AD830\">Send turn right</a></p>" \
                  "<p><a href=\"ir?code=CC3646F2\">Send turn left</a></p>" \
                  "<p><a href=\"ir?code=8239B38\">Send stop</a></p>" \
                  "<p><a href=\"ir?code=FDD80FB6\">Send R>> </a></p>" \
                  "<p><a href=\"ir?code=FCD80E25\">Send L>> </a></p>" \
                  "<p><a href=\"ir?code=1685CBA\">Send S>> </a></p>" \
                  "<p><a href=\"ir?code=73EC692C\">Send P </a></p>" \
                  "<p><a href=\"ir?code=70EC6475\">Send <<P>> </a></p>" \
                  "<p><a href=\"ir?code=8F4434CF\">Send Right thumbs up </a></p>" \
                  "<p><a href=\"ir?code=A4EA2959\">Send left thumbs up </a></p>" \        
                  "<p><a href=\"ir?code=A90EB64E\">Send Right pick up</a></p>" \
                  "<p><a href=\"ir?code=3566219E\">Send Left pick up </a></p>" \
                  "<p><a href=\"ir?code=AA0EB7E3\">Send Right lean forward</a></p>" \
                  "<p><a href=\"ir?code=36662333\">Send Left lean forward</a></p>" \
                  "<p><a href=\"ir?code=1C950C98\">Send Right throw </a></p>" \
                  "<p><a href=\"ir?code=31D5D49A\">Send left throw </a></p>" \
                  "<p><a href=\"ir?code=1B950B07\">Send Listen </a></p>" \
                  "<p><a href=\"ir?code=30D5D309\">Send Sleep </a></p>" \
                  "<p><a href=\"ir?code=41846192\">Send Step </a></p>" \
                  "<p><a href=\"ir?code=8E44333A\">Send Right turn step </a></p>" \
                  "<p><a href=\"ir?code=A7EA2E10\">Send Left turn step </a></p>" \
                  "<p><a href=\"ir?code=40846001\">Send back step </a></p>" \
                  "<p><a href=\"ir?code=B52CF642\">Send Reset </a></p>" \
                  "<p><a href=\"ir?code=95FA735D\">Send left </a></p>" \
                  "<p><a href=\"ir?code=96FA74EE\">Send Right </a></p>" \
                  "<p><a href=\"ir?code=9A8AC1F2\">Send Sonic </a></p>" \
                  "<p><a href=\"ir?code=D0ECE64\">Send Execute </a></p>" \
                  "<p><a href=\"ir?code=A0EC9AD\">Send Wakeup </a></p>" \
                  "<p><a href=\"ir?code=678E250D\">Send Right sweep </a></p>" \                
                  "<p><a href=\"ir?code=56899A1B\">Send left sweep</a></p>" \
                  "<p><a href=\"ir?code=8558ACD8\">Send Talk back </a></p>" \
                  "<p><a href=\"ir?code=FDA2AB20\">Send High five</a></p>" \
                  "<p><a href=\"ir?code=8258A821\">Send Right strike 1 </a></p>" \
                  "<p><a href=\"ir?code=FAA2A669\">Send left strike 1 </a></p>" \
                  "<p><a href=\"ir?code=F479D04E\">Send whistle</a></p>" \
                  "<p><a href=\"ir?code=E3DA71E4\">Send Burp </a></p>" \
                  "<p><a href=\"ir?code=F379CEBD\">Send right strike 2 </a></p>" \
                  "<p><a href=\"ir?code=E2DA7053\">Send left strike 2 </a></p>" \
                  "<p><a href=\"ir?code=9C0EB14\">Send bulldozer </a></p>" \
                  "<p><a href=\"ir?code=8C0E983\">Send OOps </a></p>" \
                  "<p><a href=\"ir?code=6A8E29C4\">Send right strike 3 </a></p>" \
                  "<p><a href=\"ir?code=55899886\">Send left strike 3 </a></p>" \
                  "<p><a href=\"ir?code=9176ECCC\">Send roar </a></p>" \
                  "<p><a href=\"ir?code=872B614A\">Send demo 1 </a></p>" \
                  "<p><a href=\"ir?code=862B5FB9\">Send demo 2 </a></p>" \
                  "<p><a href=\"ir?code=8ABBAE4E\">Send dance </a></p>" \
                  "<p><a href=\"ir?code=FD3FBAC0\">Send all demo </a></p>" \
                  "<p><a href=\"ir?code=FA3FB609\">Send power off </a></p>" \
                  "<p><a href=\"ir?code=CD364889\">Send EXERCISE1 </a></p>" \
                  "<p><a href=\"ir?code=DE3AD37E\">Send EXERCISE2 </a></p>" \
                  "<p><a href=\"ir?code=CE0BF79A\">Send EXERCISE3 </a></p>" \
                  "<p><a href=\"ir?code=D3C1B2C9\">Send EXERCISE4 </a></p>" \
                  "<p><a href=\"ir?code=499602D2\">Send EXERCISE5 </a></p>" \



          
                                   
                "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 16);
       Serial.println(code);
      
     
           if(code==3442886791){
      uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(rawData, 17, 38);
       Serial.println("CD364887 Left Hand Up"); break;}
       if(code==3728397177){
     uint16_t  rawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up"); break;}
      if(code==1951357324){
      uint16_t  rawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("744F598C Left Hand Down"); break;}
       if(code==4228209476){
       uint16_t    rawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down"); break;}
      
       if(code==1901024469 ){
      uint16_t rawData[17] = {7250,3350, 950,850, 900,900, 950,850, 950,850, 950,3400, 900,900, 900,3400, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("714F54D5 Left Hand In"); break;}
      if(code==4177876621 ){
      uint16_t  rawData[17] = {7150,3400, 950,850, 950,850, 950,850, 950,3400, 900,3400, 900,900, 900,3400, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("F905568D Right Hand In"); break;}
      if(code== 1518805072 ){
       uint16_t  rawData[17] = {7250,3400, 900,850, 1000,850, 950,850, 950,900, 900,900, 950,3350, 950,850, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("5A872050 Left Hand Out"); break;}
      if(code==1797684922 ){
        uint16_t  rawData[17] = {7200,3400, 900,900, 900,900, 950,900, 900,3350, 950,850, 900,3450, 900,900, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("6B267EBA Right Hand Out"); break;}
      if(code==1502027455 ){
      uint16_t rawData[17] = {7200,3400, 900,950, 850,950, 900,900, 900,900, 950,850, 950,3400, 900,3400, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("59871EBF Tilt Left"); break;}
      if(code==1780907305 ){
      uint16_t  rawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 950,3350, 1000,850, 950,3350, 950,3350, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("6A267D29 Tilt Right"); break;}
      if(code==2154666368 ){
      uint16_t  rawData[17] = {7250,3300, 1000,850, 950,850, 950,850, 950,850, 950,3350, 1000,3300, 1000,800, 1000};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("806D9980 Move Forward"); break;}
      
      if(code==2137888751){
      uint16_t  rawData[17] = {7200,3400, 950,850, 950,850, 950,900, 900,900, 900,3400, 950,3350, 950,3400, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("7F6D97EF Move Backward"); break;}
      if(code==3778730032){
 
      uint16_t  rawData[17] = {7250,3350, 1000,850, 950,850, 950,850, 950,3350, 950,850, 1000,850, 950,850, 950};     
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("E13AD830 Turn Right"); break;}
      if(code==3426109170 ){
       uint16_t rawData[17] = {7250,3350, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,800, 1000}; 
       irsend.sendRaw(rawData, 17, 38);
       Serial.println("CC3646F2 Turn Left"); break;}
      if(code==136551224){
      uint16_t  rawData[17] = {7250,3350, 900,900, 950,850, 950,850, 950,3400, 950,3350, 950,3350, 950,850, 1000};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("8239B38   Stop"); break;}
      if(code==4258795446){
        uint16_t rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,3350, 950,850, 950,850, 1000,3300, 1000,800, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FDD80FB6 R >>"); break;
        }
      if(code==4242017829){
        uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,3350, 950,850, 950,850, 1000,3300, 1000,3300, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FCD80E25 L >>"); break;}
       if(code==23616698){
        uint16_t rawData[17] = {7250,3300, 1000,800, 1000,850, 950,3350, 950,850, 950,3350, 1000,800, 1000,800, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1685CBA     S >>"); break;}
       if(code==1944873260){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,900, 950,3300, 1000,850, 950,850, 1000,850, 950,850, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("73EC692C P"); break;}
      if(code==1894540405){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,800, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("70EC6475 <<P>> "); break;}
      if(code==2403611855){
        uint16_t rawData[17] = {7300,3350, 950,850, 950,3400, 950,850, 1000,3300, 1000,850, 950,850, 950,3400, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8F4434CF Right Thumbs Up"); break;}
      if(code==2766809433){
        uint16_t rawData[17] = {7250,3300, 1000,850, 950,3350, 1000,800, 1000,800, 1000,850, 950,850, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A4EA2959 Left Thumbs Up"); break;}
      if(code==2836313678){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,3300, 1000,850, 950,3350, 1000,3300, 1000,850, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A90EB64E Right Pick Up"); break;}
      if(code==895885726){
        uint16_t rawData[17] = {7250,3400, 900,900, 950,3350, 1000,850, 900,900, 950,3350, 1000,850, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("3566219E   Left Pick Up"); break;}
      if(code==2853091299){
        uint16_t rawData[17] = {7300,3350, 950,850, 950,3350, 1000,850, 950,3350, 1000,3300, 1000,850, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("AA0EB7E3 Righ Lean Forward"); break;}
      if(code==912663347){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,3400, 900,900, 950,850, 950,3400, 900,900, 900,3400, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("36662333   Left Lean Forward"); break;}
      if(code==479530136){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3350, 1000,800, 1000,3350, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1C950C98   Right Throw"); break;}
      if(code==836097178){
        uint16_t rawData[17] = {7200,3400, 950,850, 950,3400, 950,850, 950,850, 950,900, 900,3400, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("31D5D49A   Left Throw"); break;}
      if(code==462752519){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,3350, 950,850, 950,3400, 950,850, 950,3350, 1000,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1B950B07   Listen"); break;}
      if(code==819319561){
        uint16_t  rawData[17] = {7250,3350, 1000,850, 950,3350, 950,850, 1000,850, 950,850, 950,3350, 1000,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("30D5D309   Sleep"); break;}
      if(code==1099194770){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step"); break;}
      if(code==2386834234){
        uint16_t rawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8E44333A Right Turn Step"); break;}
      if(code==2817142288){
        uint16_t rawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step"); break;}
      if(code==1082417153){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("40846001 Back Step"); break;}
      if(code==3039622722){
        uint16_t rawData[17] = {7250,3300, 1000,800, 1000,3350, 950,850, 950,3350, 950,3350, 1000,3300, 1000,800, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("B52CF642 Reset"); break;}
      if(code==2516218717){
        uint16_t  rawData[17] = {7250,3350, 950,850, 1000,3300, 1000,3300, 1000,800, 1000,850, 1000,3300, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("95FA735D Left"); break;} 
      if(code==2532996334){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3300, 1000,3300, 1050,800, 1000,800, 1000,3300, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("96FA74EE Right"); break;   }                  
      if(code==2592784882){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,3300, 1000,850, 950,3350, 950,850, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9A8AC1F2 Sonic"); break;     }                  
     if(code==219074148){
        uint16_t rawData[17] = {7250,3300, 1000,850, 950,3350, 950,3350, 1000,800, 1000,850, 950,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("D0ECE64   Execute"); break;}                  
     if(code==168741293){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3300, 1000,3300, 1000,850, 1000,800, 950,850, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A0EC9AD   Wake Up"); break; }                  
     if(code==1737368845){
        uint16_t rawData[17] = {7200,3400, 950,3350, 1000,800, 1000,850, 950,3350, 1000,800, 1000,850, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("678E250 Right Sweep"); break;       }                  
    if(code==1451858459){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,850, 950,850, 950,850, 950,850, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("56899A1B Left Sweep"); break; }                  
    if(code==2237181144){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 950,850, 1000,3350, 950,3350, 950,900, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8558ACD8 Talk Back"); break; }                  
    if(code==4255296288){
        uint16_t rawData[17] = {7300,3300, 1000,3350, 950,850, 950,850, 1000,850, 1000,3300, 1000,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FDA2AB20 High Five"); break; }                  
    if(code==2186848289){
        uint16_t rawData[17] = {7250,3400, 950,3350, 950,850, 1000,850, 950,3350, 950,3400, 900,900, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8258A821 Right Strike 1 "); break;}                  
    if(code==4204963433){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 900,900, 950,850, 1000,3350, 950,900, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FAA2A669 Left Strike 1"); break; }                  
    if(code==4101623886){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 1000,850, 950,3300, 1000,850, 950,3350, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("F479D04E Whistle"); break; }                  
    if(code==3822744036){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,850, 950,850, 950,3350, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("E3DA71E4 Burp"); break; }                  
    if(code==4084846269){
        uint16_t rawData[17] = {7300,3350, 950,3350, 950,900, 950,850, 950,3350, 1000,850, 950,3350, 950,3400, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("F379CEBD Right Strike 2"); break; }                  
    if(code==3805966419){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 1000,800, 950,900, 950,850, 950,3350, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("E2DA7053 Left strike 2"); break;}                  
    if(code==163638036){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,900, 950,850, 950,3350, 1000,3300, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9C0EB14   Bulldozer"); break; }                  
    if(code==146860419){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000,3300, 1000,3350, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8C0E983   Oops"); break; }                  
   if(code==1787701700){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000,3300, 1000,3350, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("6A8E29C4 Right Strike 3"); break; }                  
   if(code==1435080838){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 950,850, 1000,850, 950,850, 1000,800, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("55899886 Left strike 3"); break; }   
   if(code==2440490188){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,800, 950,3400, 950,3350, 950,3400, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9176ECCC Roar"); break; }   
   if(code==2267767114){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 950,3400, 900,900, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("872B614A Demo 1"); break; }  
   if(code==2250989497){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 1000,3300, 1000,850, 950,850, 950,3350, 1000,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("862B5FB9 Demo 2"); break; }
   if(code==2327555662){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,3350, 950,850, 1000,3300, 1050,800, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8ABBAE4E Dance"); break;}            
   if(code==4248812224){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,800, 1000,3350, 1000,800, 1000,850, 950,850, 1000,800, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FD3FBAC0 All Demo"); break; }   
   if(code==4198479369){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FA3FB609 Power OFF"); break;   } 

        if(code==3442886793){
      uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(rawData, 17, 38);
   
       Serial.println("CD364887 Left Hand Up");
     
       delay(2000);
       uint16_t  vawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(vawData, 17, 38);
   
       Serial.println("CD364887 Left Hand Up");
     
       delay(2000);
       uint16_t  lawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(lawData, 17, 38);
   
      Serial.println("CD364887 Left Hand Up");
      delay(3000);
      uint16_t  RawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(RawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");
      delay(500);
      uint16_t  sawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(sawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");
      delay(500);
      uint16_t  qawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(qawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");
      delay(3000);
      uint16_t  tawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(tawData, 17, 38);
      Serial.println("744F598C Left Hand Down");
      delay(2000);
      uint16_t    uawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(uawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down");
      delay(2000);
      uint16_t  iawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(iawData, 17, 38);
      Serial.println("744F598C Left Hand Down");
      delay(2000);
      uint16_t  nawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(nawData, 17, 38);
      Serial.println("744F598C Left Hand Down");
      delay(2000);
      uint16_t    oawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(oawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down");
      break;}

        if(code==3728397182){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t RawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(RawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t wawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(wawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t qawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(qawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t eawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(eawData, 17, 38);
        Serial.println("8E44333A Right Turn Step");
        delay(3000);
        uint16_t tawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(tawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step");
        delay(3000);
        uint16_t yawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(yawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step");
        delay(3000);
        uint16_t uawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(uawData, 17, 38);
        Serial.println("8E44333A Right Turn Step");
        delay(3000);
        
        break;}

        if(code==3456890778){
        uint16_t  zawData[17] = {7250,3400, 900,850, 1000,850, 950,850, 950,900, 900,900, 950,3350, 950,850, 950};
        irsend.sendRaw(zawData, 17, 38);
        Serial.println("5A872050 Left Hand Out");
        delay(2000);
        uint16_t bawData[17] = {7250,3350, 950,850, 900,900, 950,850, 950,850, 950,3400, 900,900, 900,3400, 950};
        irsend.sendRaw(bawData, 17, 38);
        Serial.println("714F54D5 Left Hand In");
        delay(2000);
        uint16_t  tawData[17] = {7200,3400, 900,900, 900,900, 950,900, 900,3350, 950,850, 900,3450, 900,900, 900};
        irsend.sendRaw(tawData, 17, 38);
        Serial.println("6B267EBA Right Hand Out");
        delay(2000);
        uint16_t  pawData[17] = {7150,3400, 950,850, 950,850, 950,850, 950,3400, 900,3400, 900,900, 900,3400, 900};
        irsend.sendRaw(pawData, 17, 38);
        Serial.println("F905568D Right Hand In");
        
        
        break;}
        
        if(code==3552686793){
        uint16_t RawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(RawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t aawData[17] = {7250,3350, 950,850, 1000,3300, 1000,850, 950,3350, 1000,3300, 1000,850, 950,850, 1000};  
        irsend.sendRaw(aawData, 17, 38);
        Serial.println("A90EB64E Right Pick Up");
        delay(3000);
        uint16_t wawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(wawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t nawData[17] = {7250,3350, 1000,850, 950,3350, 1000,800, 1000,3350, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(nawData, 17, 38);
        Serial.println("1C950C98  Right Throw");
        delay(3000);
        
        break;}
        
        if(code==1234567890){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t QawData[17] = {7250,3400, 900,900, 950,3350, 1000,850, 900,900, 950,3350, 1000,850, 900,900, 950};  
        irsend.sendRaw(QawData, 17, 38);
        Serial.println("3566219E   Left Pick Up");
        delay(3000);
        uint16_t wawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(wawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t aawData[17] = {7200,3400, 950,850, 950,3400, 950,850, 950,850, 950,900, 900,3400, 950,850, 1000};  
        irsend.sendRaw(aawData, 17, 38);
        Serial.println("31D5D49A   Left Throw");
        delay(3000);
        break;
        }


        }
        }

  }

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}
 
void setup(void) {
  
  irsend.begin();
  Serial.begin(115200);
  
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration
   // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(local_IP,gateway,subnet);
  WiFi.begin(ssid, password);
 
  WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
  

  // Wait for connection
 // if (WiFi.status() == WL_CONNECTED){
      Serial.println("");
      Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/ir", handleIr);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });
  

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  if (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(500);
   
  }
}

void loop() {
  server.handleClient();
  if (SerialBT.available()) {
    int code=SerialBT.read();
   
    Serial.println(code);
     if(code==48){
      uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(rawData, 17, 38);
       Serial.println("CD364887 Left Hand Up");}
       if(code==49){
     uint16_t  rawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");}
      if(code==50){
      uint16_t  rawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("744F598C Left Hand Down"); }
       if(code==51){
       uint16_t    rawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down"); }
      
       if(code==52){
      uint16_t rawData[17] = {7250,3350, 950,850, 900,900, 950,850, 950,850, 950,3400, 900,900, 900,3400, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("714F54D5 Left Hand In");}
      if(code==53 ){
      uint16_t  rawData[17] = {7150,3400, 950,850, 950,850, 950,850, 950,3400, 900,3400, 900,900, 900,3400, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("F905568D Right Hand In"); }
      if(code== 54 ){
       uint16_t  rawData[17] = {7250,3400, 900,850, 1000,850, 950,850, 950,900, 900,900, 950,3350, 950,850, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("5A872050 Left Hand Out"); }
      if(code==55 ){
        uint16_t  rawData[17] = {7200,3400, 900,900, 900,900, 950,900, 900,3350, 950,850, 900,3450, 900,900, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("6B267EBA Right Hand Out"); }
      if(code==56){
      uint16_t rawData[17] = {7200,3400, 900,950, 850,950, 900,900, 900,900, 950,850, 950,3400, 900,3400, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("59871EBF Tilt Left");}
      if(code==57){
      uint16_t  rawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 950,3350, 1000,850, 950,3350, 950,3350, 950};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("6A267D29 Tilt Right"); }
      if(code==65){
      uint16_t  rawData[17] = {7250,3300, 1000,850, 950,850, 950,850, 950,850, 950,3350, 1000,3300, 1000,800, 1000};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("806D9980 Move Forward"); }
      
      if(code==66){
      uint16_t  rawData[17] = {7200,3400, 950,850, 950,850, 950,900, 900,900, 900,3400, 950,3350, 950,3400, 900};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("7F6D97EF Move Backward"); }
      if(code==67){
 
      uint16_t  rawData[17] = {7250,3350, 1000,850, 950,850, 950,850, 950,3350, 950,850, 1000,850, 950,850, 950};     
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("E13AD830 Turn Right");}
      if(code==68 ){
       uint16_t rawData[17] = {7250,3350, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,800, 1000}; 
       irsend.sendRaw(rawData, 17, 38);
       Serial.println("CC3646F2 Turn Left"); }
      if(code==69){
      uint16_t  rawData[17] = {7250,3350, 900,900, 950,850, 950,850, 950,3400, 950,3350, 950,3350, 950,850, 1000};
      irsend.sendRaw(rawData, 17, 38);
      Serial.println("8239B38   Stop"); }
      if(code==70){
        uint16_t rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,3350, 950,850, 950,850, 1000,3300, 1000,800, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FDD80FB6 R >>");
        }
      if(code==71){
        uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,3350, 950,850, 950,850, 1000,3300, 1000,3300, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FCD80E25 L >>"); }
       if(code==72){
        uint16_t rawData[17] = {7250,3300, 1000,800, 1000,850, 950,3350, 950,850, 950,3350, 1000,800, 1000,800, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1685CBA     S >>"); }
       if(code==73){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,900, 950,3300, 1000,850, 950,850, 1000,850, 950,850, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("73EC692C P"); }
      if(code==74){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,800, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("70EC6475 <<P>> ");}
      if(code==75){
        uint16_t rawData[17] = {7300,3350, 950,850, 950,3400, 950,850, 1000,3300, 1000,850, 950,850, 950,3400, 950};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8F4434CF Right Thumbs Up"); }
      if(code==76){
        uint16_t rawData[17] = {7250,3300, 1000,850, 950,3350, 1000,800, 1000,800, 1000,850, 950,850, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A4EA2959 Left Thumbs Up"); }
      if(code==77){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,3300, 1000,850, 950,3350, 1000,3300, 1000,850, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A90EB64E Right Pick Up");}
      if(code==78){
        uint16_t rawData[17] = {7250,3400, 900,900, 950,3350, 1000,850, 900,900, 950,3350, 1000,850, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("3566219E   Left Pick Up"); }
      if(code==79){
        uint16_t rawData[17] = {7300,3350, 950,850, 950,3350, 1000,850, 950,3350, 1000,3300, 1000,850, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("AA0EB7E3 Righ Lean Forward"); }
      if(code==80){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,3400, 900,900, 950,850, 950,3400, 900,900, 900,3400, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("36662333   Left Lean Forward"); }
      if(code==81){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3350, 1000,800, 1000,3350, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1C950C98   Right Throw"); }
      if(code==82){
        uint16_t rawData[17] = {7200,3400, 950,850, 950,3400, 950,850, 950,850, 950,900, 900,3400, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("31D5D49A   Left Throw"); }
      if(code==83){
        uint16_t rawData[17] = {7250,3350, 950,850, 1000,3350, 950,850, 950,3400, 950,850, 950,3350, 1000,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("1B950B07   Listen"); }
      if(code==84){
        uint16_t  rawData[17] = {7250,3350, 1000,850, 950,3350, 950,850, 1000,850, 950,850, 950,3350, 1000,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("30D5D309   Sleep"); }
      if(code==85){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step"); }
      if(code==86){
        uint16_t rawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8E44333A Right Turn Step"); }
      if(code==87){
        uint16_t rawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step"); }
      if(code==88){
        uint16_t rawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("40846001 Back Step"); }
      if(code==89){
        uint16_t rawData[17] = {7250,3300, 1000,800, 1000,3350, 950,850, 950,3350, 950,3350, 1000,3300, 1000,800, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("B52CF642 Reset"); }
      if(code==90){
        uint16_t  rawData[17] = {7250,3350, 950,850, 1000,3300, 1000,3300, 1000,800, 1000,850, 1000,3300, 950,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("95FA735D Left"); } 
      if(code==97){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3300, 1000,3300, 1050,800, 1000,800, 1000,3300, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("96FA74EE Right");    }                  
      if(code==98){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,3300, 1000,850, 950,3350, 950,850, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9A8AC1F2 Sonic");      }                  
     if(code==99){
        uint16_t rawData[17] = {7250,3300, 1000,850, 950,3350, 950,3350, 1000,800, 1000,850, 950,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("D0ECE64   Execute"); }                  
     if(code==100){
        uint16_t rawData[17] = {7250,3350, 1000,850, 950,3300, 1000,3300, 1000,850, 1000,800, 950,850, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("A0EC9AD   Wake Up");  }                  
     if(code==101){
        uint16_t rawData[17] = {7200,3400, 950,3350, 1000,800, 1000,850, 950,3350, 1000,800, 1000,850, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("678E250 Right Sweep");        }                  
    if(code==102){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,850, 950,850, 950,850, 950,850, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("56899A1B Left Sweep");  }                  
    if(code==103){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 950,850, 1000,3350, 950,3350, 950,900, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8558ACD8 Talk Back");  }                  
    if(code==104){
        uint16_t rawData[17] = {7300,3300, 1000,3350, 950,850, 950,850, 1000,850, 1000,3300, 1000,850, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FDA2AB20 High Five");  }                  
    if(code==105){
        uint16_t rawData[17] = {7250,3400, 950,3350, 950,850, 1000,850, 950,3350, 950,3400, 900,900, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8258A821 Right Strike 1 "); }                  
    if(code==106){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 900,900, 950,850, 1000,3350, 950,900, 950,3350, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FAA2A669 Left Strike 1");  }                  
    if(code==107){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 1000,850, 950,3300, 1000,850, 950,3350, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("F479D04E Whistle");  }                  
    if(code==108){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,850, 950,850, 950,3350, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("E3DA71E4 Burp");  }                  
    if(code==109){
        uint16_t rawData[17] = {7300,3350, 950,3350, 950,900, 950,850, 950,3350, 1000,850, 950,3350, 950,3400, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("F379CEBD Right Strike 2");  }                  
    if(code==110){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 1000,800, 950,900, 950,850, 950,3350, 1000,3300, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("E2DA7053 Left strike 2"); }                  
    if(code==111){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,900, 950,850, 950,3350, 1000,3300, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9C0EB14   Bulldozer");  }                  
    if(code==112){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000,3300, 1000,3350, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8C0E983   Oops"); }                  
   if(code==113){
        uint16_t rawData[17] = {7250,3350, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000,3300, 1000,3350, 1000};
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("6A8E29C4 Right Strike 3");  }                  
   if(code==114){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 950,850, 1000,850, 950,850, 1000,800, 1000,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("55899886 Left strike 3"); }   
   if(code==115){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,800, 950,3400, 950,3350, 950,3400, 900,900, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("9176ECCC Roar"); }   
  if(code==116){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 950,3400, 900,900, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("872B614A Demo 1");  }  
   if(code==117){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,850, 1000,3300, 1000,850, 950,850, 950,3350, 1000,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("862B5FB9 Demo 2"); }
   if(code==118){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,3350, 950,850, 1000,3300, 1050,800, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("8ABBAE4E Dance");}            
   if(code==119){
        uint16_t rawData[17] = {7300,3350, 950,3350, 1000,800, 1000,3350, 1000,800, 1000,850, 950,850, 1000,800, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FD3FBAC0 All Demo"); }   
   if(code==120){
        uint16_t rawData[17] = {7250,3350, 1000,3350, 950,850, 1000,3300, 1000,850, 950,850, 1000,800, 1000,3350, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("FA3FB609 Power OFF"); } 
   if(code==121){
      uint16_t  rawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(rawData, 17, 38);
   
       Serial.println("CD364887 Left Hand Up");
     
       delay(2000);
       uint16_t  vawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(vawData, 17, 38);
   
       Serial.println("CD364887 Left Hand Up");
     
       delay(2000);
       uint16_t  lawData[17] = {7300,3300, 1000,800, 1000,800, 1000,850, 950,850, 950,850, 1000,800, 1000,3300, 1000};
       irsend.sendRaw(lawData, 17, 38);
   
      Serial.println("CD364887 Left Hand Up");
      delay(3000);
      uint16_t  RawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(RawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");
      delay(500);
      uint16_t  sawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(sawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");
      delay(500);
      uint16_t  qawData[17] = {7250,3350, 950,850, 950,850, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950};
      irsend.sendRaw(qawData, 17, 38);
      Serial.println("DE3AD379 Right Hand Up");
      delay(3000);
      uint16_t  tawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(tawData, 17, 38);
      Serial.println("744F598C Left Hand Down");
      delay(2000);
      uint16_t    uawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(uawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down");
      delay(2000);
      uint16_t  iawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(iawData, 17, 38);
      Serial.println("744F598C Left Hand Down");
      delay(2000);
      uint16_t  nawData[17] = {7200,3350, 950,850, 1000,850, 950,850, 950,850, 950,3350, 950,850, 950,900, 900};
      irsend.sendRaw(nawData, 17, 38);
      Serial.println("744F598C Left Hand Down");
      delay(2000);
      uint16_t    oawData[17] = {7250,3350, 950,850, 950,900, 900,900, 900,3400, 900,3400, 900,900, 950,850, 950};
      irsend.sendRaw(oawData, 17, 38);
      Serial.println("FC055B44 Right Hand Down");
      }

  if(code==122){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t RawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(RawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t wawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(wawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t qawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(qawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t eawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(eawData, 17, 38);
        Serial.println("8E44333A Right Turn Step");
        delay(3000);
        uint16_t tawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(tawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step");
        delay(3000);
        uint16_t yawData[17] = {7250,3350, 1000,800, 950,3350, 950,850, 950,850, 1000,800, 1050,800, 950,850, 950};  
        irsend.sendRaw(yawData, 17, 38);
        Serial.println("A7EA2E10 Left Turn Step");
        delay(3000);
        uint16_t uawData[17] = {7200,3350, 950,850, 900,3400, 950,850, 950,3350, 950,850, 950,850, 950,850, 950};  
        irsend.sendRaw(uawData, 17, 38);
        Serial.println("8E44333A Right Turn Step");
        delay(3000);
        
        }

   if(code==60){
        uint16_t  zawData[17] = {7250,3400, 900,850, 1000,850, 950,850, 950,900, 900,900, 950,3350, 950,850, 950};
        irsend.sendRaw(zawData, 17, 38);
        Serial.println("5A872050 Left Hand Out");
        delay(2000);
        uint16_t bawData[17] = {7250,3350, 950,850, 900,900, 950,850, 950,850, 950,3400, 900,900, 900,3400, 950};
        irsend.sendRaw(bawData, 17, 38);
        Serial.println("714F54D5 Left Hand In");
        delay(2000);
        uint16_t  tawData[17] = {7200,3400, 900,900, 900,900, 950,900, 900,3350, 950,850, 900,3450, 900,900, 900};
        irsend.sendRaw(tawData, 17, 38);
        Serial.println("6B267EBA Right Hand Out");
        delay(2000);
        uint16_t  pawData[17] = {7150,3400, 950,850, 950,850, 950,850, 950,3400, 900,3400, 900,900, 900,3400, 900};
        irsend.sendRaw(pawData, 17, 38);
        Serial.println("F905568D Right Hand In");
        
        
        }
        
    if(code==63){
        uint16_t RawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(RawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t aawData[17] = {7250,3350, 950,850, 1000,3300, 1000,850, 950,3350, 1000,3300, 1000,850, 950,850, 1000};  
        irsend.sendRaw(aawData, 17, 38);
        Serial.println("A90EB64E Right Pick Up");
        delay(3000);
        uint16_t wawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(wawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t nawData[17] = {7250,3350, 1000,850, 950,3350, 1000,800, 1000,3350, 950,850, 950,3400, 950,850, 950};  
        irsend.sendRaw(nawData, 17, 38);
        Serial.println("1C950C98  Right Throw");
        delay(3000);
        }
        
     if(code==62){
        uint16_t rawData[17] = {7250,3350, 1000,800, 1000,3300, 1000,800, 1000,850, 950,3350, 950,3350, 950,850, 1000};  
        irsend.sendRaw(rawData, 17, 38);
        Serial.println("41846192 Step");
        delay(3000);
        uint16_t QawData[17] = {7250,3400, 900,900, 950,3350, 1000,850, 900,900, 950,3350, 1000,850, 900,900, 950};  
        irsend.sendRaw(QawData, 17, 38);
        Serial.println("3566219E   Left Pick Up");
        delay(3000);
        uint16_t wawData[17] = {7250,3350, 950,850, 950,3350, 1000,850, 950,850, 950,3300, 1000,3300, 1050,3300, 1000};  
        irsend.sendRaw(wawData, 17, 38);
        Serial.println("40846001 Back Step");
        delay(3000);
        uint16_t aawData[17] = {7200,3400, 950,850, 950,3400, 950,850, 950,850, 950,900, 900,3400, 950,850, 1000};  
        irsend.sendRaw(aawData, 17, 38);
        Serial.println("31D5D49A   Left Throw");
        delay(3000);
        }
  }
  delay(20);
  
  }

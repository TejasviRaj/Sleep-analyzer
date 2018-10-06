#include <ESP8266WiFi.h>

#include<string.h>

void send_data();


char a;

const char* ssid     = "harkabahadur";

const char* password = "bodhinamaskar";

const char* host = "192.168.43.4";

int sensor_value;

int on_value;

void uart0_gets(char s[])

  {

    char return_char[100];

    int index=0;

      do

      {

        while (!Serial.available()) {}

        return_char[index]=Serial.read();

        index++;

      }

          while(return_char[index-1] != ' ');

      return_char[index-1]='\0';

      strcpy(s,return_char);

  }



  int uart0_getint()

  {

    char d[5];

    uart0_gets(d);



    int ans=0;

    for (unsigned int i=0;i<strlen(d);i++)

    {

      ans=ans*10+(d[i]-'0');

    }

    return ans;

  }



void setup() {

  Serial.begin(9600);

  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

 // Serial.println("");

  Serial.println("WiFi connected");

 Serial.println("IP address: ");

 Serial.println(WiFi.localIP());

 Serial.print("Netmask: ");

 Serial.println(WiFi.subnetMask());

  Serial.print("Gateway: ");

  Serial.println(WiFi.gatewayIP());
  Serial.flush();

  Serial.print('}');

}

void waitandsendchar(char waiting_char, char sending_char)
{
  Serial.flush();
    a='1';
         do
         {
                  Serial.print(waiting_char);
                  if (Serial.available())
                  a=Serial.read();
         }
            while(a!=sending_char);
   Serial.flush();
}


void waitandsendstring(char start,int waiting_char, char sending_char)
{
  Serial.flush();
    a='1';
         do
         {
                  Serial.print(start);
                  Serial.print(waiting_char);
                  Serial.print(" ");
                  if (Serial.available())         
                  a=Serial.read();
         }
            while(a!=sending_char);
   Serial.flush();
}

 void loop() {

     a='1';
      do
      {
          if (Serial.available())
            a=Serial.read();   
      }
      while (a!='[');

    waitandsendchar('[','$');
    sensor_value= uart0_getint();
      for (int i=1;i<=100;i++)
             Serial.print("$");   
        send_data();
    waitandsendchar('=','=');
    waitandsendstring('$',on_value,'$');
    }


void send_data()
{

  WiFiClient client;

  const int httpPort = 8000;

  if (!client.connect(host, httpPort)) {

    Serial.print('!');

    return;

  }
 String url = "/reply/?sensor_value=" + String(sensor_value);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +

               "Host: " + host + "\r\n" +

               "Connection: close\r\n\r\n");
  delay(100);

  int flag=0;
  
  while(!client.available()) {}

  while(client.available()){

           char x;
               do
               {
                 x= client.read();
               }

               while (x!='$');
         String on_value = client.readStringUntil('#');
     }
  }

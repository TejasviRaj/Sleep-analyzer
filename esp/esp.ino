#include <ESP8266WiFi.h>

#include<string.h>

void send_data();



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

 void loop() {

  

  if(Serial.available())

    {

      char b;
      b =Serial.read();

      Serial.print(b);

      Serial.print(" ");


      if (b=='[')

      {
              sensor_value=uart0_getint();

                Serial.print(sensor_value);
                 Serial.print(" ");
              send_data();
      }



    }



}



void send_data()

{

  WiFiClient client;

  const int httpPort = 8000;

  if (!client.connect(host, httpPort)) {

    Serial.print('!');

    return;

  }

    Serial.print('=');



  // We now create a URI for the request

 String url = "/reply/?sensor_value=" + String(sensor_value);

 //String url =  "/127.0.0.1/new.php?x=22";

 //localhost/send_data.php?id=1&num=10

//  Serial.print("Requesting URL: ");

//  Serial.println(url);

   // This will send the request to the server

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +

               "Host: " + host + "\r\n" +

               "Connection: close\r\n\r\n");



  delay(100);

  int flag=0;

  // Read all the lines of the reply from server and print them to Serial

  while(!client.available()) {}

  while(client.available()){

  //  if (flag==0)

   // {

    //  Serial.println("Flag still 0");

   //   String line = client.readStringUntil('\r');

      //Serial.println(line);

    //  if(line=="The data is ")

     // {

            //    Serial.print("Now flag is 1");

       //             flag=1;



    //  }

   // }

   // if(flag==1)

     // {

           char x;
               do
               {
                 x= client.read();
               }

               while (x!='$');
         String on_value = client.readStringUntil('#');
              // Serial.println(on_value);


       //  Serial.println("The total number of data are ");

         Serial.print(on_value);

         Serial.print(' ');



                  //       Serial.print("Now flag is 2");





     // }







     }

     Serial.println();

     Serial.println("closing connection");

  }

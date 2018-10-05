int vibration_sensor = A0;
int sensor_value;
int on_value;
char a;


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
 // pinMode(vibration_sensor, INPUT);
    pinMode(13, OUTPUT);


  while (!Serial.available());
  do
  {
    a= Serial.read();
  }
     while (a!='}');
           //wifi connected

}

void loop() {
    int return_value;

        Serial.flush();

          sensor_value = analogRead(vibration_sensor);


        Serial.write("[ ");
         a=Serial.read();

      if (a=='[')
    {
          Serial.print(sensor_value);
          Serial.print(" ");
          digitalWrite(13,sensor_value);
          
          return_value=uart0_getint();
          if (return_value==sensor_value)
              {
                 while (!Serial.available());

                 do
                 {
                   a=Serial.read();
                 }
                   while (a!='=');

                   on_value=uart0_getint();


              }

 }

  delay(100);        // delay in between reads for stability



}

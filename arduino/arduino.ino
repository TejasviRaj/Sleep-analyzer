int vibration_sensor = 2;
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

 
void communicate()

{

    char a;
 while (!Serial.available());
 
 Serial.flush();

  Serial.write("[ ");

      a=Serial.read();

 if (a=='[')
 {
          Serial.print(sensor_value);
          Serial.print(" ");
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



  

for (int i=0;i<num_of_food;i++)

{

      food[i].id=uart0_getint();

      uart0_gets(c);

      food[i].name= String(c);

      

      food[i].price=uart0_getint();;

      food[i].num=uart0_getint();;

      food[i].p=uart0_getint();




  }



}




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

 
void get_info()

{


}
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(vibration_sensor, INPUT);

  while (!Serial.available())!
  do
  {
    a= Serial.read();    
  }
     while (a!='}');
           //wifi connected
           
}

void loop() {

        Serial.flush();

        Serial.write("[ ");
         a=Serial.read();

      if (a=='[')
    {
          Serial.print(sensor_value);
          Serial.print(" ");
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




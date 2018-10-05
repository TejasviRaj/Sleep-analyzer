int vibration_sensor = 2;
int sensor_value=0;
int on_value;
char a;
char temp[100]="";


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

void setup() {
  Serial.begin(9600);
  pinMode(vibration_sensor, INPUT);
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
         //sensor_value= digitalRead()
       // sensor_value =Serial.digitalRead(vibration_sensor);
 
            waitandsendchar('[','[');
            waitandsendstring('$',sensor_value,'$');
            a='1';
            do
            {
              if (Serial.available())         
                  a=Serial.read();
            }
            while(a!='=');

             waitandsendchar('=','$');
             on_value=uart0_getint();

             for (int i=1;i<=100;i++)
             Serial.print("$");
             
              delay(100);        // delay in between reads for stability
}

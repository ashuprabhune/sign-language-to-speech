void setup()
{
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
  //(ledpin,OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
}

void loop()
{
    int a= analogRead(A0);
    float voltage= 3.3*a/1023.0;
    int val= map(5*a, 180, 400, 0, 10);
    Serial.println(val);
    delay(500);
    //delay 50ms
}


const int sen1 = D6;
const int sen2 = D7;
int count1 = 0;
int count2 = 0;
long tipping = 0.000;
long volume;
bool var1 = 0;
bool var2 = 0;
bool sen1now = 0;
bool sen2now = 0;

void setup() {
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  Serial.begin(9600);
}

void loop() {
  sen1now = digitalRead(sen1);
  sen2now = digitalRead(sen2);
  if(sen1now && !var1){
    count1++;
    var1 = true;
    delay(10); 
  }
  else if(!sen1now){
    var1 = false;
  }

  if(sen2now && !var2){
    count2++;
    var2 = true;
    delay(10); 
  }
  else if(!sen2now){
    var2 = false;
  }
  tipping = count1+count2;
  volume=tipping*0.8952;//masih direvisi

  Serial.print("Jumlah Tipping : ");
  Serial.print(tipping-1);
  Serial.print("  Jumlah Volume : ");
  Serial.print(volume);
  Serial.print("\n");
  delay(100);
}

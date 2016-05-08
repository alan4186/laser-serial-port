char h = char(HIGH);
char l = char(LOW);
char msg[64*8];
char inStr[64];
int laserPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT); 
  nullMsg1(msg);
  nullMsg2(inStr);
  //handshake();  
  //sendBits(msg, );
}

void loop() {
  while(Serial.available() == 0);
  //delay(10);
  Serial.readBytes(inStr, 64);
  Serial.println(inStr);
  
  for(int i = 0; i < 64; i++){
    for(int j = 0; j < 8; j++){   
    msg[i*8+j] = !((inStr[i] >> 7-j) & 0x01);
    }
    //Serial.println(' ');
  }
  //Serial.print();
  handshake();
  //sendSize();
  sendBits(msg);
  nullMsg1(msg);
  nullMsg2(inStr);
  return;
}

void sendBits(char* msg){
    for(int i = 0; i < (64*8); i++){
       digitalWrite(laserPin, (int)msg[i]);
       delay(10);  
    }
    digitalWrite(laserPin, LOW);
} 

void nullMsg1(char * msg){
  for(int i = 0; i < (64*8); i++){
     msg[i] = '\0'; 
  }
}

void nullMsg2(char * msg){
  for(int i = 0; i < 64; i++){
     msg[i] = '\0'; 
  }
}

void handshake(){
  digitalWrite(laserPin, HIGH);
  delay(1000); 
  digitalWrite(laserPin, LOW);
  delay(10);
}

#include <Servo.h> 
#include <SoftwareSerial.h>
#include <MP3.h>

MP3 mp3;
Servo myservo;  // servo for head
Servo myservo_2; // servo for legs
Servo myservo_3; // servo for hands
int pos = 0; // initialization of position.
boolean flag_head = false; // initialization of flags.
boolean flag_hands = false;
boolean flag_legs = false;
boolean flag_sound = false;
int sound_select = 0;
String val = "";//定义变量val，用于暂存上位机发送来的字符
char inByte;         // incoming serial byte
// code to run once.
void setup() 
{
  Serial.begin(9600);  // 启动串行通讯，波特率为9600b/s
  myservo.attach(9); // attaches the servo on pin 9 to the servo object 
  myservo_2.attach(10); // attaches the servo_2 on pin 10 to the servo object2 
  myservo_3.attach(11); // attaches the servo_3 on pin 11 to the servo object3 
  //mp3
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  mp3.volume(0x1F);
  mp3.set_mode(MP3::SINGLE);
  Serial.println("Panda Cub Start...ab");

}

// code to run repeatly.
void loop() 
{ 
  while(Serial.available() > 0)//如果上位机发送来了字符
  {
    char Byte = Serial.read();
    SelectButton(Byte);
  }
  Serial.print("head = ");
  Serial.println(flag_head);
  Serial.print("hands = ");   
  Serial.println(flag_hands);
  Serial.print("legs = ");
  Serial.println(flag_legs);
  Serial.print("sound = ");
  switch(sound_select){
    case 0:
      Serial.println("No Sound");
    break;
  case 1:
    Serial.println("Hungry");
    break;    
  case 2:
    Serial.println("Full");
    break;
  case 3:
    Serial.println("Sleep");
    break;
  case 4:
    Serial.println("Wake up");
    break;
  }
  move_panda(flag_head,flag_hands,flag_legs);
}
void SelectButton(char inByte)
{
  switch(inByte)
  {
  case 'a':
    if(flag_head)
      flag_head = false;
    else
      flag_head = true;
    break;
  case 'b':
    if(flag_hands)
      flag_hands = false;
    else
      flag_hands = true;
    break;
  case 'c':
    if(flag_legs)
      flag_legs = false;
    else
      flag_legs = true;
    break;
  case 'd':      
    mp3.stop();  
    sound_select = 0;
    break;
  case 'h':      
    mp3.play_spi_flash(0x0001);
    sound_select = 1;
    break;
  case 'f':      
    mp3.play_spi_flash(0x0002);
    sound_select = 2;
    break;

  case 's':      
    mp3.play_spi_flash(0x0003);
    sound_select = 3;
    break;
  case 'w':      
    mp3.play_spi_flash(0x0004);
    sound_select = 4;
    break;
  }
}



void move_panda(boolean flag_head, boolean flag_legs, boolean flag_hands)
{

  for(pos = 30;pos >= 0;pos -= 1)
  {
    if(flag_hands == true){
      myservo_2.write(pos + 60);
    }
    if(flag_legs == true){
      myservo_3.write(pos + 90); 
    }
    if(flag_head == true){
      myservo.write(120 - abs(30 - 2 * pos));
    }
    delay(30);
  }
  for(pos = 0; pos <= 30;pos += 1)
  {
    if(flag_hands == true){
      myservo_2.write(pos + 60);
    }
    if(flag_legs == true){
      myservo_3.write(pos + 90); 
    }
    if(flag_head == true){
      myservo.write(60 + abs(30 - 2 * pos));
    }
    delay(30);
  }
}















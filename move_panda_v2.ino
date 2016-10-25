#include <Servo.h> 
#include <SoftwareSerial.h>
#include <MP3.h>

MP3 mp3;
// create three servo objects to control servos. 
Servo myservo;  // servo for head
Servo myservo_2; // servo for legs
Servo myservo_3; // servo for hands
// determine the postions of servo needed to control servos.
int pos = 0; // initialization of position.
boolean flag_head2 = false; // initialization of flags.
boolean flag_legs2 = false;
boolean flag_hands2 = false;
boolean flag_sound2 = false;
String val = "";//定义变量val，用于暂存上位机发送来的字符

// code to run once.
void setup() 
{
  Serial.begin(9600);  // 启动串行通讯，波特率为9600b/s
  pinMode(9,OUTPUT);  // 申明数字端口9为输出端口
  pinMode(10,OUTPUT); // 申明数字端口10为输出端口
  pinMode(11,OUTPUT); // 申明数字端口11为输出端口
  myservo.attach(9); // attaches the servo on pin 9 to the servo object 
  myservo_2.attach(10); // attaches the servo_2 on pin 10 to the servo object2 
  myservo_3.attach(11); // attaches the servo_3 on pin 11 to the servo object3 
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  mp3.volume(0x1F);
  mp3.set_mode(MP3::RANDOM);
  mp3.play_spi_flash(0x0001);
}

// code to run repeatly.
void loop() 
{ 
  while(Serial.available() == 0);
  while(Serial.available() > 0)//如果上位机发送来了字符
  {
    val += char(Serial.read());
    delay(2);
  }
  Serial.println(val);
  define_flags(val);
  move_panda(flag_head2,flag_hands2,flag_legs2);
  play_mp3(flag_sound2);
  val = String("");
  flag_head2 = false ;
  flag_hands2 = false ;
  flag_legs2 = false ;
  flag_sound2 = false;
}

void move_panda(boolean flag_head, boolean flag_hands, boolean flag_legs)
{

  for(pos = 30;pos >= 0;pos -= 1)
  {
    if(flag_legs == true)
    {
      myservo_2.write(pos + 60);
    }
    if(flag_hands == true)
    {
      myservo_3.write(pos + 90); 
    }
    if(flag_head == true)
    {
      myservo.write(120 - abs(30 - 2 * pos));
    }
    delay(30);
  }
  for(pos = 0; pos <= 30;pos += 1)
  {
    if(flag_legs == true)
    {
      myservo_2.write(pos + 60);
    }
    if(flag_hands == true)
    {
      myservo_3.write(pos + 90); 
    }
    if(flag_head == true)
    {
      myservo.write(60 + abs(30 - 2 * pos));
    }
    delay(30);
  }
}
void define_flags(String val)
{
  if(val == "a")
  {
    flag_head2 = true;
    flag_hands2 = false;
    flag_legs2 = false;
    flag_sound2 = false;
  }
  if(val == "b")
  {
    flag_head2 = false;
    flag_hands2 = true;
    flag_legs2 = false;
    flag_sound2 = false;
  }
  if(val == "c")
  {
    flag_head2 = false;
    flag_hands2 = false;
    flag_legs2 = true;
    flag_sound2 = false;
  }
  if(val == "d")
  {
    flag_head2 = false;
    flag_hands2 = false;
    flag_legs2 = false;
    flag_sound2 = true;
  }
  if(val == "ab" || val == "ba")
  {
    flag_head2 = true;
    flag_hands2 = true;
    flag_legs2 = false;
    flag_sound2 = false;
  }
  if(val == "ac" || val == "ca")
  {
    flag_head2 = true;
    flag_hands2 = false;
    flag_legs2 = true;
    flag_sound2 = false;
  }
  if(val == "ad" || val == "da")
  {
    flag_head2 = true;
    flag_hands2 = false;
    flag_legs2 = false;
    flag_sound2 = true;
  }
  if(val == "bc" || val == "cb")
  {
    flag_head2 = false;
    flag_hands2 = true;
    flag_legs2 = true;
    flag_sound2 = false;
  }
  if(val == "bd" || val == "db")
  {
    flag_head2 = false;
    flag_hands2 = true;
    flag_legs2 = false;
    flag_sound2 = true;
  }
  if(val == "cd" || val == "dc")
  {
    flag_head2 = false;
    flag_hands2 = false;
    flag_legs2 = true;
    flag_sound2 = true;
  }
  if(val == "abc" || val == "acb" || val == "bac" || val == "bca" || val == "cab" || val == "cba")
  {
    flag_head2 = true;
    flag_hands2 = true;
    flag_legs2 = true;
    flag_sound2 = false;
  }
  if(val == "acd" || val == "adc" || val == "cad" || val == "cda" || val == "dac" || val == "dca")
  {
    flag_head2 = true;
    flag_hands2 = false;
    flag_legs2 = true;
    flag_sound2 = true; 
  }
  if(val == "abd" || val == "adb" || val == "bad" || val == "bda" || val == "dab" || val == "dba")
  {
    flag_head2 = true;
    flag_hands2 = true;
    flag_legs2 = false;
    flag_sound2 = true; 
  }
  if(val == "bcd" || val == "bdc" || val == "cbd" || 
    val == "cdb" || val == "dbc" || val == "dcb")
  {
    flag_head2 = false;
    flag_hands2 = true;
    flag_legs2 = true;
    flag_sound2 = true; 
  }
  if(val == "abcd" || val == "abdc" || val == "acbd" || 
    val == "acdb" || val == "adbc" || val == "adcb" || 
    val == "bacd" || val == "badc" || val == "bcad" || 
    val == "bcda" || val == "bdac" || val == "bdca" || 
    val == "cabd" || val == "cadb" || val == "cbad" || 
    val == "cbda" || val == "cdab" || val == "cdba" || 
    val == "dabc" || val == "dacb" || val == "dbac" || 
    val == "dbca" || val == "dcab" || val == "dcba")
  {
    flag_head2 = true;
    flag_hands2 = true;
    flag_legs2 = true;
    flag_sound2 = true;
  }
}
void play_mp3(boolean flag_sound)
{
  if(flag_sound == true)
  {
    mp3.pause();
  }
}

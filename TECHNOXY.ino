
// RemoteXY select connection mode and include library  
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h> 

#include <RemoteXY.h> 

// RemoteXY connection settings  
#define REMOTEXY_WIFI_SSID "TECHNO MADE" 
#define REMOTEXY_WIFI_PASSWORD "" 
#define REMOTEXY_SERVER_PORT 6377 
#define REMOTEXY_ACCESS_PASSWORD "TM" 


// RemoteXY configurate   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,3,0,0,0,49,0,8,2,0,
  5,37,65,28,30,30,6,164,165,2,
  1,4,2,22,11,6,164,31,31,111,
  110,32,0,111,102,102,0,129,0,6,
  15,74,10,6,84,69,67,72,78,79,
  32,77,65,68,69,0 }; 
   
// this structure defines all the variables of your control interface  
struct { 

    // input variable
  int8_t joystick_1_x; // =-100..100 x-coordinate joystick position 
  int8_t joystick_1_y; // =-100..100 y-coordinate joystick position 
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

#define PIN_SWITCH_1 D0
#define PIN_MOTOR_LEFT_SPEED   14          // Enable/speed motors Right        GPIO14(D5)
#define PIN_MOTOR_RIGHT_SPEED   12          // Enable/speed motors Left         GPIO12(D6)
#define PIN_MOTOR_LEFT_UP  15          // L298N in1 motors Right           GPIO15(D8)
#define PIN_MOTOR_LEFT_DN  13          // L298N in2 motors Right           GPIO13(D7)
#define PIN_MOTOR_RIGHT_UP  2           // L298N in3 motors Left            GPIO2(D4)
#define PIN_MOTOR_RIGHT_DN  0           // L298N in4 motors Left            GPIO0(D3)


unsigned char RightMotor[3] =  
  {PIN_MOTOR_RIGHT_UP, PIN_MOTOR_RIGHT_DN, PIN_MOTOR_RIGHT_SPEED}; 
unsigned char LeftMotor[3] =  
  {PIN_MOTOR_LEFT_UP, PIN_MOTOR_LEFT_DN, PIN_MOTOR_LEFT_SPEED}; 


void Wheel (unsigned char * motor, int v) 
{ 
  if (v>100) v=100; 
  if (v<-100) v=-100; 
  if (v>0) { 
    digitalWrite(motor[0], HIGH); 
    digitalWrite(motor[1], LOW); 
    analogWrite(motor[2], v*10.23); 
  } 
  else if (v<0) { 
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], HIGH); 
    analogWrite(motor[2], (-v)*10.23); 
  } 
  else { 
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], LOW); 
    analogWrite(motor[2], 0); 
  } 
} 

void setup()  
{ 
  RemoteXY_Init ();  
   
  pinMode (PIN_SWITCH_1, OUTPUT);
   
   pinMode(PIN_MOTOR_LEFT_SPEED, OUTPUT);
 pinMode(PIN_MOTOR_RIGHT_SPEED, OUTPUT);  
 pinMode (PIN_MOTOR_RIGHT_UP, OUTPUT); 
  pinMode (PIN_MOTOR_RIGHT_DN, OUTPUT); 
  pinMode (PIN_MOTOR_LEFT_UP, OUTPUT); 
  pinMode (PIN_MOTOR_LEFT_DN, OUTPUT); 
   
   
} 

void loop()  
{  
  RemoteXY_Handler (); 
   
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
  /* manage the right motor */ 
  Wheel (RightMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x); 
  /* manage the left motor */ 
  Wheel (LeftMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x); 

}

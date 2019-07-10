//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include <ESP32Servo.h>

#define pin_1_A0   25 
#define pin_2_A0   26 
#define pin_PWM_A0 27
//right front

#define pin_1_B0   19
#define pin_2_B0   18
#define pin_PWM_B0 5
//right rear

#define pin_1_A1   17
#define pin_2_A1   16
#define pin_PWM_A1 4
//left front

#define pin_1_B1   0
#define pin_2_B1   2
#define pin_PWM_B1 15
//left rear

int motor_freq = 2500;
int Serial_Baud = 115200;

ESP32PWM pwmA0;
ESP32PWM pwmB0;
ESP32PWM pwmA1;
ESP32PWM pwmB1;

float adjust_right_control;
float adjust_left_control;


BluetoothSerial SerialBT;

int buttons = 0;
boolean button_start = false;
boolean button_option = false;
boolean button_L1 = false;
boolean button_R1 = false;
boolean button_cross = false;
boolean button_circle = false;
boolean button_square = false;
boolean button_triangle = false;
int Xaxis = 15;
int Yaxis = 15;

boolean manual_control = false;
void parse_BT();
void parse_buttons();

float right_control = 0.0;
float left_control = 0.0;

void setup() {
  Serial.begin(Serial_Baud);
  SerialBT.begin("ECE 597 Autonomous Robot Override"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  // put your setup code here, to run once:
  pwm_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    parse_BT();
  }
  if(manual_control == true){
    manual_control_routine();
  }
}


void pwm_setup() {
  pinMode(pin_1_A0  , OUTPUT);
  pinMode(pin_2_A0  , OUTPUT);
  digitalWrite(pin_1_A0  , LOW);
  digitalWrite(pin_2_A0  , LOW);
  pwmA0.attachPin(pin_PWM_A0, motor_freq, 10);
  
  pinMode(pin_1_B0  , OUTPUT);
  pinMode(pin_2_B0  , OUTPUT);
  digitalWrite(pin_1_B0  , LOW);
  digitalWrite(pin_2_B0  , LOW);
  pwmB0.attachPin(pin_PWM_B0, motor_freq, 10);
  
  pinMode(pin_1_A1  , OUTPUT);
  pinMode(pin_2_A1  , OUTPUT);
  digitalWrite(pin_1_A1  , LOW);
  digitalWrite(pin_2_A1  , LOW);
  pwmA1.attachPin(pin_PWM_A1, motor_freq, 10);
  
  pinMode(pin_1_B1  , OUTPUT);
  pinMode(pin_2_B1  , OUTPUT);
  digitalWrite(pin_1_B1  , LOW);
  digitalWrite(pin_2_B1  , LOW);
  pwmB1.attachPin(pin_PWM_B1, motor_freq, 10);
}

void parse_buttons(){
  button_start = false;
  button_option = false;
  button_L1 = false;
  button_R1 = false;
  button_cross = false;
  button_circle = false;
  button_square = false;
  button_triangle = false;
  if(buttons % 2 == 1){
    button_start = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_option = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_R1 = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_L1 = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_triangle = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_square = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_circle = true;
  }
  buttons = buttons / 2;
  if(buttons % 2 == 1){
    button_cross = true;
  }
}

void parse_BT()
{
  String inString_buttons = "";
  String inString_Xaxis = ""; 
  String inString_Yaxis = "";

  while(SerialBT.available() > 0){ //if there is new data from the control station, interpret it
    manual_control = true;
    inString_buttons = SerialBT.readStringUntil('\t');  //get the value
    inString_Xaxis = SerialBT.readStringUntil('\t');  //get the value
    inString_Yaxis = SerialBT.readStringUntil('\n');  //get the value
    //Serial.println(inString);
  }
  //when value is most recent, parse it into useable data
  buttons = inString_buttons.toInt();
  Xaxis = inString_Xaxis.toInt();
  Yaxis = inString_Yaxis.toInt();
}
void manual_control_routine(){
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    delay(5);
    parse_buttons();
    Serial.print("Buttons Pressed:[ ");
    if(button_cross == true)
      Serial.print("X  ");
    if(button_circle == true)
      Serial.print("O  ");
    if(button_triangle == true)
      Serial.print("^  ");
    if(button_square == true)
      Serial.print("[]  ");
    if(button_L1 == true)
      Serial.print("L1  ");
    if(button_R1 == true)
      Serial.print("R1  ");
    if(button_start == true)
      Serial.print("START  ");
    if(button_option == true)
      Serial.print("OPTIONS  ");
    Serial.println("]");
    Serial.println(Xaxis);
    Serial.println(Yaxis);
    
    wheel_control(Xaxis, Yaxis, button_L1, button_R1);
    manual_control = false;
}

void wheel_control(int Xaxis, int Yaxis, boolean turbo, boolean precision){
  int adjusted_X = 15 - Xaxis;
  int adjusted_Y = Yaxis - 15;
  float R_plus_L = (float)(15-abs(adjusted_X))*(((float)adjusted_Y)/15) + adjusted_Y;
  float R_minus_L = (float)(15-abs(adjusted_Y))*(((float)adjusted_X)/15) + adjusted_X;
  right_control = (R_plus_L + R_minus_L)/2;
  left_control = (R_plus_L - R_minus_L)/2;
  //formulas sourced from http://home.kendra.com/mauser/joystick.html
  
  Serial.println(right_control);
  Serial.println(left_control);
  adjust_right_control = abs(right_control)/15.0;
  if(button_L1 == true)
    adjust_right_control = adjust_right_control / 2;
  Serial.println(adjust_right_control);
  pwmA0.writeScaled(adjust_right_control);
  pwmB0.writeScaled(adjust_right_control);
  adjust_left_control = abs(left_control)/15.0;
  if(button_L1 == true)
    adjust_left_control = adjust_left_control / 2;
  Serial.println(adjust_left_control);
  pwmA1.writeScaled(adjust_left_control);
  pwmB1.writeScaled(adjust_left_control);
  //make left_control scale from 0.0 to 1.0 instead of from -15.0 to +15.0
  if(right_control > 0){
    digitalWrite(pin_1_A0  , LOW);
    delay(5);
    digitalWrite(pin_2_A0  , HIGH);
    digitalWrite(pin_1_B0  , LOW);
    delay(5);
    digitalWrite(pin_2_B0  , HIGH);
  }
  else if(right_control < 0){
    digitalWrite(pin_2_A0  , LOW);
    delay(5);
    digitalWrite(pin_1_A0  , HIGH);
    digitalWrite(pin_2_B0  , LOW);
    delay(5);
    digitalWrite(pin_1_B0  , HIGH);
  }
  else{
    digitalWrite(pin_1_A0  , LOW);
    digitalWrite(pin_2_A0  , LOW);
    digitalWrite(pin_1_B0  , LOW);
    digitalWrite(pin_2_B0  , LOW);
  }
  if(left_control > 0){
    digitalWrite(pin_1_A1  , LOW);
    delay(5);
    digitalWrite(pin_2_A1  , HIGH);
    digitalWrite(pin_1_B1  , LOW);
    delay(5);
    digitalWrite(pin_2_B1  , HIGH);
  }
  else if(left_control < 0){
    digitalWrite(pin_2_A1  , LOW);
    delay(5);
    digitalWrite(pin_1_A1  , HIGH);
    digitalWrite(pin_2_B1  , LOW);
    delay(5);
    digitalWrite(pin_1_B1  , HIGH);
  }
  else{
    digitalWrite(pin_1_A1  , LOW);
    digitalWrite(pin_2_A1  , LOW);
    digitalWrite(pin_1_B1  , LOW);
    digitalWrite(pin_2_B1  , LOW);
  }
}

//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial


#include <Arduino.h>

#include <ros.h>
#include <geometry_msgs/Twist.h>

#include <U8g2lib.h>
#include "BluetoothSerial.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 15, /* data=*/ 4);   // ESP32 Thing, HW I2C with pin remapping

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#include <ESP32Servo.h>

#define pin_1_A0   39 
#define pin_2_A0   38 
#define pin_PWM_A0 34
//right front

#define pin_1_B0   32
#define pin_2_B0   35
#define pin_PWM_B0 33
//right rear

#define pin_1_A1   26
#define pin_2_A1   25
#define pin_PWM_A1 27
//left front

#define pin_1_B1   12
#define pin_2_B1   14
#define pin_PWM_B1 13
//left rear

int motor_freq = 2500;
int Serial_Baud = 115200;

ESP32PWM pwmA0;
ESP32PWM pwmB0;
ESP32PWM pwmA1;
ESP32PWM pwmB1;

float adjust_right_control;
float adjust_left_control;

boolean lf_front_direction = true;
boolean lr_front_direction = true;
boolean rf_front_direction = true;
boolean rr_front_direction = true;

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
void u8g2_setup();
void ros_setup();

void ros_routine();
void auto_control();

float right_control = 0.0;
float left_control = 0.0;

int mode_change_count = 0;

ros::NodeHandle esp32control;
void auto_control(const geometry_msgs::Twist &jetson_input);
ros::Subscriber<geometry_msgs::Twist> control_sub("esp_control", &auto_control);



void setup() {
  Serial.begin(Serial_Baud);
  SerialBT.begin("ECE 597 Autonomous Robot Override"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  // put your setup code here, to run once:
  
  u8g2_setup();
  pwm_setup();
  ros_setup();
}

char charBuffer[128];

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    parse_BT();
  }
  
  u8g2.clearBuffer();
  if(manual_control == true){
    mode_change_count = 0;
    manual_control_routine();
    u8g2.drawStr(0,0, "Mode: MANUAL");
  }
  else{
    if(mode_change_count > 10)
    {
      u8g2.drawStr(0,0, "Mode: Auto");
      manual_control = false;
      esp32control.spinOnce();
    }
    else
    {
      u8g2.drawStr(0,0, "Mode: MANUAL");
      mode_change_count += 1;
    }
  }
  u8g2_printData();
}

void u8g2_setup(){
  u8g2.begin();
  u8g2.setFont(u8g2_font_sirclivethebold_tr);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void ros_setup(){
  esp32control.initNode();
  esp32control.subscribe(control_sub);
}

void auto_control(const geometry_msgs::Twist &jetson_input){
  Xaxis = jetson_input.linear.x;
  Yaxis = jetson_input.angular.z;
  
  wheel_control(Xaxis, Yaxis, false, false);
}

void u8g2_printData(){
  if(lf_front_direction == true)
    sprintf(charBuffer, "L. Front: +%1.2f", adjust_left_control);
  else
    sprintf(charBuffer, "L. Front: -%1.2f", adjust_left_control);  
  u8g2.drawStr(0, 16, charBuffer);
  
  if(lr_front_direction == true)
    sprintf(charBuffer, "L. Rear:   +%1.2f", adjust_left_control);
  else
    sprintf(charBuffer, "L. Rear:   -%1.2f", adjust_left_control);
  u8g2.drawStr(0, 24, charBuffer);
  
  if(rf_front_direction == true)
    sprintf(charBuffer, "R. Front: +%1.2f", adjust_left_control);
  else
    sprintf(charBuffer, "R. Front: -%1.2f", adjust_left_control);
  u8g2.drawStr(0, 32, charBuffer);
  
  if(rr_front_direction == true)
    sprintf(charBuffer, "R. Rear:   +%1.2f", adjust_left_control);
  else
    sprintf(charBuffer, "R. Rear:   -%1.2f", adjust_left_control);
  u8g2.drawStr(0, 40, charBuffer);
  
  u8g2.sendBuffer();
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
    {
      manual_control = false;
      Serial.print("OPTIONS  ");
    }
    Serial.println("]");
    Serial.println(Xaxis);
    Serial.println(Yaxis);
    
    wheel_control(Xaxis, Yaxis, button_L1, button_R1);
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
  lf_front_direction = true;
  lr_front_direction = true;
  rf_front_direction = true;
  rr_front_direction = true;
  if(right_control > 0){
    digitalWrite(pin_1_A0  , LOW);
    delay(5);
    digitalWrite(pin_2_A0  , HIGH);
    digitalWrite(pin_1_B0  , LOW);
    delay(5);
    digitalWrite(pin_2_B0  , HIGH);
  }
  else if(right_control < 0){
    rf_front_direction = false;
    rr_front_direction = false;
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
    lf_front_direction = false;
    lr_front_direction = false;
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

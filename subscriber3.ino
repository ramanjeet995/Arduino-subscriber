#include <ros.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
//I2C pins declaration - white5v,black-gnd,red A5, brown A4
LiquidCrystal_I2C lcd(0x27, 16,2);

Stepper left(200, 8, 9, 10, 11);
Stepper right(200, 4, 5, 6, 7);

void motion(const geometry_msgs::Twist &msg);
ros::NodeHandle node;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &motion);

int mode=0;
int change=0;

void motion(const geometry_msgs::Twist &msg)
{ 
  
  lcd.println("Messaged");
  
   if (msg.linear.x>0)
    mode=1;
      
   else if (msg.linear.x<0)
    mode=2;

   else if (msg.angular.z>0)
    mode=3;

   else if (msg.angular.z<0)
    mode=4;
  
   else if(msg.linear.x<0.5 || msg.linear.x>-0.5 || msg.angular.z<0.5 || msg.angular.z>-0.5)
     mode=0;



   
  
}


void setup() {
  left.setSpeed(60);
  right.setSpeed(60);
  Serial.begin(57600);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  node.initNode();
  node.subscribe(sub);
}


void loop()
{
  lcd.println("yo");
  node.spinOnce();
  lcd.println(mode);
  while (mode==1)
        { 
          left.step(-1);
          right.step(-1);
          break;        // without break it gets stuck in the loop
        }
  while (mode==2)
        { 
          left.step(1);
          right.step(1);
          break;
        }
  while (mode==3)
        { 
          left.step(-1);
          right.step(1);
          break;
        }
  while (mode==4)
        { 
          left.step(1);
          right.step(-1);
          break;
        }
   //mode=0;   , this is the main differenc ebetween subscriber 2 and subscriber 3
  lcd.clear();
}

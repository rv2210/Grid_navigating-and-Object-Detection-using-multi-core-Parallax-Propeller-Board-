
/*
Blank Simple Project.c
http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h" // Include simple tools
#include "servo.h"
#include "ping.h" // Include ping tools


#define true 1
#define false 0
#define I2_STATE 2
#define I3_STATE 3
#define I5_STATE 4
#define FORWARD 6
#define LEFT 7
#define RIGHT 8






// Forward declaration
void Stop(); 
void LEDblink();
void LEDON();
void joint_check();
void redbox_check();
void turnright();
void turnleft();
void i5_state();
void i2_state();
void i3_state();

void forward();
void followline();
void readdata();
int location_check();
void IRsense();
void BohemianRhapsody();


// predesign path array for each condition

// statks for different cogs

// For storing process ID
int *cog1;
int *cog2;
int *cog3;
int *cog4;
int *cog5;
int *cog6;
int *cog7;

//static volatile int count ; // Global vars for cogs to share

int redbox_flag2 = 1;
int count3;
int count2;

//int intcheckflag = 0;
int joint_flag;
int count_flag;

//count1 is intersection count
//count4 is object count
static volatile int time1, time2, time3, time4, time5, time6, time7, time8, count1=0, count4;

//ultrasonic sensor values
int cmDist1;
int cmDist2;
int cmDist3;


void IRsense(){
while(1)
{
//read values from all the 8 sensors
high(8);
high(9);
high(10);
high(11);
high(12);
high(13);
high(14);
high(15);
pause(100);
time1=rc_time(8,1);
time2=rc_time(9,1);
time3=rc_time(10,1);
time4=rc_time(11,1);
time5=rc_time(12,1);
time6=rc_time(13,1);
time7=rc_time(14,1);
time8=rc_time(15,1);

}
} 



void turnright()
{
//tunrright90 deg
servo_speed(16,0);
servo_speed(17,100);
pause(1200);
} 
void turnleft()
{
//tunrleft90 deg
servo_speed(16,-100);
servo_speed(17,-10);
pause(1250);
} 

void joint_check(){//check if the interseciton point found
while(1)
{
//print("%csensor2 = %d, sensor3 = %d%, sensor6 = %d%, sensor7 = %d%c", HOME, sensor2, sensor3,sensor6,sensor7, CLREOL);
pause(100); 
//intersection point found condition
if ( time2 > 900 && time3 > 900 && time4 > 900&& time5 > 900&& time6 > 900 && time7 > 900 && time8>900 ) 
{ 
//count1 ++;
//count3 = count1 - 3;
//servo_speed(16, -40);
//servo_speed(17, 20);
if (count1>=0)
{
count1 ++;
joint_flag = 1;
pause(500);
high(5);
pause(500);
low(5);
}
//avoid first interscetion which is the curve one 
else if (count1 == 0 )
{ 
pause(100);
count1 ++;
joint_flag = 1;
} 
if(count1 == 3 && cmDist3 < 32 ) //i2 condition
{

redbox_flag2 = I2_STATE; 
}
else if(count1 == 4 && cmDist3 < 32) //i3 condition
{
redbox_flag2 = I3_STATE; 
}
else if(count1 == 6 && cmDist3 < 32) //i5 condition
{
redbox_flag2 = I5_STATE; 
}
else{
redbox_flag2 = 1; //meets no conditions
}
}
else
{ joint_flag = 0;
low(6);
}
} 
}
void followline(){


if ((time4 > 400 && time5 > 400) && (time3 < 400 || time6 < 400) ) 
{ // sees no line on either side, goes straight until a line is seen
servo_speed(16, -40);
servo_speed(17, 20);
} 
else if ((time3 > 400 && time4 > 400) && (time2 < 400 || time7 < 400) )
{ // sees line on right side, is making a right turn
servo_speed(16, -20);
servo_speed(17, 20);
} 
else if (((time6 > 400 && time7 > 400)||(time7>400 && time8> 400)) && ( time2 < 400|| time1<400) ) 
{ // sees line on left side, is making a left turn
servo_speed(16, -40);
servo_speed(17, 0); 
} 

else 
{ // both are seeing line, goes straight until light is seen
servo_speed(16, -40);
servo_speed(17, 20);
}
}

void readdata()//
{
while(1)
// Repeat indefinitely
{ 
//rightsensor =cmDist1, leftsensor= cmDist2, middlesensor = cmDist3

pause(100);
cmDist1 = ping_cm(0);
pause(200); 
cmDist2 = ping_cm(2);
pause(200);
cmDist3 = ping_cm(4); // Get cm distance from Ping)))
pause(200); 
while(cmDist3 < 30 )
{
//object at the front detected
count4++;
high(3);
pause(500);
low(3);
pause(500);
break;
} 
while(cmDist2 < 20 )
{
//location object detected
high(3);
pause(500);
low(3);
pause(500);
count4++;
break;
} 
// Wait 1/5 second
}

}




void i2_state(){ //
//int count4;
while(1){
//count4 = count1 - 3;

if ( count1 == 3 && joint_flag == 1)
{ 
turnleft();
followline();
continue;

}

else if (count1 == 4 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 7 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 9 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 12 && joint_flag == 1)
{// turn left
turnright();
followline();
continue;
} 

else if (count1 == 14 && joint_flag == 1 )
{//turn right
turnright();
followline();
continue;

}

else if (count1 == 18 )
{ 
servo_disable(16);
servo_disable(17);
pause(10000);

}
else
{followline();
} 
}
}

void i3_state(){ //
//int count4;
while(1){
//count4 = count1 - 3;

if ( count1 == 4 && joint_flag == 1)
{ 
turnright();
followline();
continue;

}

else if (count1 == 5 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 6 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 8 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 11 && joint_flag == 1)
{// turn left
turnright();
followline();
continue;
} 

else if (count1 == 13 && joint_flag == 1 )
{//turn right
turnright();
followline();
continue;

}

else if (count1 == 16 && joint_flag == 1 )
{//turn right
turnright();
followline();
continue;

}

else if (count1 == 18 && joint_flag == 1 )
{//turn right
turnright();
followline();
continue;

}

else if (count1 == 22 )
{ 
servo_disable(16);
servo_disable(17);
pause(10000);

}
else
{followline();
} 
}
}

void i5_state() { //
//int count4;
while(1){
//count4 = count1 - 3;

if ( count1 == 6 && joint_flag == 1)
{ 
turnright();
followline();
continue;

}

else if (count1 == 4 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 7 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 10 && joint_flag == 1)
{//turn right
turnright();
followline();
continue;
}

else if (count1 == 12 && joint_flag == 1)
{// turn left
turnright();
followline();
continue;
} 


else if (count1 == 16 )
{ 
servo_disable(16);
servo_disable(17);
pause(10000);

}
else
{followline();
} 
}
}




int main() // Main function
{
//int cog1 = cogstart(&IRsense, NULL, stack1, sizeof(stack1));
//int cog2 = cogstart(&followline, NULL, stack2, sizeof(stack2)); 
cog_run(IRsense, 128);
//cog1 = cogstart((void*)IRsense, NULL, stack1, sizeof(stack1));
cog_run(joint_check, 128);
//cog3 = cogstart((void*)joint_check, NULL, stack2, sizeof(stack2));
cog_run(readdata, 128);
//cog4 = cogstart((void*)readdata, NULL, stack4, sizeof(stack4));
//cog_run(BohemianRhapsody, 128);
//cog6 = cogstart((void*)redbox_check, NULL, stack6, sizeof(stack6)); 
pause(50);

while(1){
if ((time4 > 400 && time5 > 400) && (time3 < 400 || time6 < 400) ) 
{ // sees no line on either side, goes straight until a line is seen
servo_speed(16, -40);
servo_speed(17, 20);
} 
else if ((time3 > 400 && time4 > 400) && (time2 < 400 || time7 < 400) )
{ // sees line on right side, is making a right turn
servo_speed(16, -20);
servo_speed(17, 20);
} 
else if (((time6 > 400 && time7 > 400)||(time7>400 && time8> 400)) && ( time2 < 400|| time1<400) ) 
{ // sees line on left side, is making a left turn
servo_speed(16, -40);
servo_speed(17, 0); 
} 

else 
{ // both are seeing line, goes straight until light is seen
servo_speed(16, -40);
servo_speed(17, 20);
}
if(redbox_flag2 != 1)
{//redbox detected at certain intersection , robot go to predesign path
switch(redbox_flag2){
//(one core)do design path for i + (one core)joint_check()+(one core)location_check()+(one core)play cool music
case I2_STATE: i2_state(); break; 
//cogstart(&joint_check, NULL, stack, sizeof(stack)); cogstart(&location_check, NULL, stack, sizeof(stack));break;
case I3_STATE: i3_state(); break; 
//cogstart(&joint_check, NULL, stack, sizeof(stack)); cogstart(&location_check, NULL, stack, sizeof(stack));break;
case I5_STATE: i5_state(); break; 
//cogstart(&joint_check, NULL, stack, sizeof(stack)); cogstart(&location_check, NULL, stack, sizeof(stack));break;
} 
//printf("rc_time = %d ,%d ,%d ,%d ,%d ,%d ,%d , %d \n", time1,time2,time3,time4,time5,time6,time7,time8);
//printf("count1 = %d \n",count1);
}
//printf("count1 = %d \n",count1);
print("right =%d, left= %d, middle = %d, redflag2 =%d, count = %d \n", cmDist1, cmDist2,cmDist3,redbox_flag2,count1 ); // Display result
pause(100); // Wait 1/10 of a second
} 
}




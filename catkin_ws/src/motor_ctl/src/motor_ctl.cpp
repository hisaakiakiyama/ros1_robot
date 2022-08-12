#include <ros/ros.h>
#include <std_msgs/Int32MultiArray.h>

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define right_1 22
#define right_2 27
#define left_1  24
#define left_2  23

std_msgs::Int32MultiArray command;//ros-pwm-pca9685
std_msgs::Int32MultiArray motor_log; //motor log

int main (int argc, char **argv) {
    command.data.resize(16);
    motor_log.data = {0,0,0,0};
    ros::init(argc, argv, "motor_ctl_talker");
    ros::NodeHandle n;
    ros::Publisher motor_ctl = n.advertise<std_msgs::Int32MultiArray>("command", 10);
    if(wiringPiSetupGpio() == -1) return 1;
    pinMode(right_1,OUTPUT);
    pinMode(right_2,OUTPUT);
    pinMode(left_1,OUTPUT);
    pinMode(left_2,OUTPUT);

    int right_speed = 0;
    int left_speed  = 0;

    ros::Rate loop_rate(10);
    while (ros::ok()){
        //joy情報の受信，整理
        // if(){//右モータ正転，逆転，ブレーキ
            motor_log.data[0] = 1;
        // }else if(){
        //     motor_log.data[0] = 0;
        // }else(){
        //     motor_log.data[0] = 2;
        // }
        
        // if(){//左モータ正転，逆転，ブレーキ
            motor_log.data[1] = 0;
        // }else if(){
        //     motor_log.data[1] = 0;
        // }else(){
        //     motor_log.data[1] = 2;
        // }

        //right speed, left speedの更新
        int hoge = 65535/2;
        int piyo = 65535/2;
        right_speed = hoge;
        left_speed  = piyo;

        //gpio(回転方向)の更新
        if(motor_log.data[0] == 1){//右正転
            digitalWrite(right_1,HIGH);
            digitalWrite(right_2,LOW);
        }else if(motor_log.data[0] == 0){//右逆転
            digitalWrite(right_1,LOW);
            digitalWrite(right_2,HIGH);
        }else{//右ブレーキ
            digitalWrite(right_1,HIGH);
            digitalWrite(right_2,HIGH);
        }

        if(motor_log.data[2] == 1){//左正転
            digitalWrite(left_1,HIGH);
            digitalWrite(left_2,LOW);
        }else if(motor_log.data[2] == 0){//左逆転
            digitalWrite(left_1,LOW);
            digitalWrite(left_2,HIGH);
        }else{//左ブレーキ
            digitalWrite(left_1,HIGH);
            digitalWrite(left_2,HIGH);
        }
        

        //command arrayの更新
        command.data[0] = left_speed;
        command.data[1] = right_speed;
        command.data[2] = -1;
        command.data[3] = -1;
        command.data[4] = -1;
        command.data[5] = -1;
        command.data[6] = -1;
        command.data[7] = -1;
        command.data[8] = -1;
        command.data[9] = -1;
        command.data[10] = -1;
        command.data[11] = -1;
        command.data[12] = -1;
        command.data[13] = -1;
        command.data[14] = -1;
        command.data[15] = -1;
        
        //command array publish
        motor_ctl.publish(command);//motor_ctl publish
        ros::spinOnce();
        loop_rate.sleep();
        ROS_INFO("published array\n");
    }
    return 0;
}
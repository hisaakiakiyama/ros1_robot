#include <ros/ros.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Joy.h>

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define right_1 22
#define right_2 27
#define left_1  24
#define left_2  23

std_msgs::Int32MultiArray command;//ros-pwm-pca9685
std_msgs::Float32MultiArray motor_log; //motor log

ros::Publisher motor_ctl;
ros::Publisher motor_logger;

void joy_callback(const sensor_msgs::Joy& joy_msg){
    if(joy_msg.buttons[5] == 1){//R1が押されている間は左スティックのみで操作
        if(abs(joy_msg.axes[0]) < 0.1){//直進
            if(joy_msg.axes[1] > 0){//前進
                motor_log.data[0] = motor_log.data[2] = 1;
                motor_log.data[1] = motor_log.data[3] = abs(joy_msg.axes[1]);
            }else{//後退
                motor_log.data[0] = motor_log.data[2] = 0;
                motor_log.data[1] = motor_log.data[3] = abs(joy_msg.axes[1]);
            }
        }else if(abs(joy_msg.axes[1]) < 0.15){//信地旋回
            if(joy_msg.axes[0] > 0){//左
                motor_log.data[0] = motor_log.data[2] = 1;
                motor_log.data[3] = abs(joy_msg.axes[0]);
                motor_log.data[1] = 0;
            }else{//右
                motor_log.data[0] = motor_log.data[2] = 1;
                motor_log.data[1] = abs(joy_msg.axes[0]);
                motor_log.data[3] = 0;
            }
        }else{
            ROS_INFO("doing...\n");
        }
    }else{
        if(joy_msg.axes[1] > 0){//左スティック上下
            motor_log.data[0] = 1;
            motor_log.data[1] = abs(joy_msg.axes[1]);
        }else{
            motor_log.data[0] = 0;
            motor_log.data[1] = abs(joy_msg.axes[1]);
        }

        if(joy_msg.axes[4] > 0){//右スティック上下
            motor_log.data[2] = 1;
            motor_log.data[3] = abs(joy_msg.axes[4]);
        }else{
            motor_log.data[2] = 0;
            motor_log.data[3] = abs(joy_msg.axes[4]);
        }
    }
}

int main (int argc, char **argv) {
    command.data.resize(16);
    motor_log.data.resize(4);
    motor_log.data = {0,0,0,0};//左正逆,左回転速度,右正逆,右回転速度
    //nodeの起動
    ros::init(argc, argv, "motor_ctl_talker");
    ros::NodeHandle n;
    //pubの定義
    motor_ctl = n.advertise<std_msgs::Int32MultiArray>("command", 10);
    motor_logger = n.advertise<std_msgs::Float32MultiArray>("motor_log", 10);
    //subの定義
    ros::Subscriber joy_sub = n.subscribe("joy",10,joy_callback);
    if(wiringPiSetupGpio() == -1) return 1;
    pinMode(right_1,OUTPUT);
    pinMode(right_2,OUTPUT);
    pinMode(left_1,OUTPUT);
    pinMode(left_2,OUTPUT);

    int right_speed = 0;
    int left_speed  = 0;

    ros::Rate loop_rate(10);
    while (ros::ok()){
        //right speed, left speedの更新
        int left_speed = 65535*motor_log.data[1];
        int right_speed = 65535*motor_log.data[3];

        //gpio(回転方向)の更新
        if(motor_log.data[0] == 1){//左正転
            digitalWrite(left_1,HIGH);
            digitalWrite(left_2,LOW);
        }else if(motor_log.data[0] == 0){//左逆転
            digitalWrite(left_1,LOW);
            digitalWrite(left_2,HIGH);
        }else{//左ブレーキ
            digitalWrite(left_1,HIGH);
            digitalWrite(left_2,HIGH);
        }
        
        if(motor_log.data[2] == 1){//右正転
            digitalWrite(right_1,HIGH);
            digitalWrite(right_2,LOW);
        }else if(motor_log.data[2] == 0){//右逆転
            digitalWrite(right_1,LOW);
            digitalWrite(right_2,HIGH);
        }else{//右ブレーキ
            digitalWrite(right_1,HIGH);
            digitalWrite(right_2,HIGH);
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
        motor_logger.publish(motor_log);//motor_log publish
        ros::spinOnce();
        loop_rate.sleep();
        ROS_INFO("published array\n");
    }
    return 0;
}
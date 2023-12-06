#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>

void lidarCallback(){
  ;
}

void velocityCallback(){
  ;
}

int main(int argc, char **argv)
{

  ros::Publisher *p_pub;
  ros::init(argc, argv, "robot_no_crash");

  ros::NodeHandle n;
  
  

  ros::Publisher no_crash_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  p_pub = &no_crash_pub;

  ros::Subscriber lidar_sub = n.subscribe("laser_1", 1000, lidarCallback);
  ros::Subscriber des_vel_sub = n.subscribe("des_vel", 1000, velocityCallback);

  ros::Rate loop_rate(10);

    geometry_msgs::Twist msg;
    
    no_crash_pub.publish(msg);

  
  return 0;
}
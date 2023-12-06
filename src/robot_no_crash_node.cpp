#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>

ros::Publisher *p_cmd_pub;
sensor_msgs::LaserScan laser_read;
double wall_dist = 0.0;
bool isWall = false;

void laserCallback(const sensor_msgs::LaserScan laser_read) {
  isWall = false;
  for (int indx = 45; indx < 225; indx++) {
    if (laser_read.ranges[indx] < wall_dist) {
      isWall = true;
      break;
    }
  }
}

void desCallback(const geometry_msgs::Twist::ConstPtr& des_msg) {
  geometry_msgs::Twist vel_msg;
  vel_msg = *des_msg;

  if (isWall && (vel_msg.linear.x > 0.0)) {
    vel_msg.linear.x = 0.0;
    ROS_INFO_THROTTLE(0.5,"HALT");
  }
  else if (vel_msg.linear.x < 0.0) {
    isWall = false;
  }

  p_cmd_pub->publish(vel_msg);
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "robot_no_crash_node");

  ros::NodeHandle n;

  ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  p_cmd_pub = &cmd_pub;

  ros::Subscriber des_sub = n.subscribe("des_vel", 10, desCallback);
  ros::Subscriber laser_sub = n.subscribe("laser_0", 10, laserCallback);

  ros::Rate loop_rate(10);

n.param("wall_dist", wall_dist, 1.0);
  int count = 0;
  while (ros::ok()) {
    geometry_msgs::Twist des_msg;
    cmd_pub.publish(des_msg);
  }
  return 0;
}
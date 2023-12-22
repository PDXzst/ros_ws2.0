#include<stdio.h>
#include<ros/ros.h>
#include<nav_msgs/Path.h>
#include<nav_msgs/Odometry.h>

ros::Publisher path_pub;    //发布path的节点
ros::Subscriber odom_sub;   //接收odometry的节点

nav_msgs::Path path;        //发布的路径
bool init_flag=1;             //path初始化标记位

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom){
    if(init_flag){
        path.header=odom->header;
        init_flag=0;
    }

    geometry_msgs::PoseStamped pose_stamped_this;
    pose_stamped_this.header=odom->header;
    pose_stamped_this.pose=odom->pose.pose;

    path.poses.push_back(pose_stamped_this);
    path_pub.publish(path);
}


int main (int argc, char **argv)
{
    ros::init (argc, argv, "odometry2path_normal");
    ros::NodeHandle nh;
    
 //       记得在此处更改odometry消息topic名称     //
    odom_sub  = nh.subscribe<nav_msgs::Odometry>("/imu_normal_odometry", 10, odomCallback);
    path_pub = nh.advertise<nav_msgs::Path>("/path_normal",10, true);
 

    
    ros::spin();
    // ros::Rate loop_rate(50);
    // loop_rate.sleep();
    return 0;
}

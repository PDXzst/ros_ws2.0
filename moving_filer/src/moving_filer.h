#ifndef MOVING_FILER_H
#define MOVING_FILER_H
#include <Eigen/Dense>

#include <yaml-cpp/yaml.h>
#include <mutex>
#include <glog/logging.h>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <GeographicLib/LocalCartesian.hpp>
#include "nlink_parser/LinktrackNodeframe2.h"
#include <string>
#include <deque>
#include <ros/ros.h>
#include <mutex>

namespace moving_filer{
class Moving_Filer{
public:
    struct UWB_data{
        double stamp;
        float range;
    };
    Moving_Filer(ros::NodeHandle &_nh);
private:
    std::deque<nlink_parser::LinktrackNodeframe2> uwb_data;
    void uwb_cb(const nlink_parser::LinktrackNodeframe2ConstPtr& uwb_in);
    void check_data_number();
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_uwb_dis;
    ros::Publisher pub_uwb_dis;
    std::mutex mtx;
    nlink_parser::LinktrackNodeframe2 uwb_data_pub;
    float uwb_dis_pub = 0;
    const float NUM = 10;
}; 

}


#endif
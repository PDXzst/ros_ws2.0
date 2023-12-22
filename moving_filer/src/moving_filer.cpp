#include "moving_filer.h"

namespace moving_filer{
Moving_Filer::Moving_Filer(ros::NodeHandle &_nh){
    nh = _nh;
    std::string uwb_topic = "/nlink_linktrack_nodeframe2";
    std::string pub_uwb_topic = "/uwb_msgs_filed";
    sub_uwb_dis = nh.subscribe<nlink_parser::LinktrackNodeframe2>(uwb_topic,100,&Moving_Filer::uwb_cb,this);
    pub_uwb_dis = nh.advertise<nlink_parser::LinktrackNodeframe2>(pub_uwb_topic,50);
}
void Moving_Filer::uwb_cb(const nlink_parser::LinktrackNodeframe2ConstPtr& uwb_in){
    nlink_parser::LinktrackNodeframe2 uwb_in_ros(*uwb_in);
    if(!uwb_in_ros.nodes.empty()){
        mtx.lock();
        uwb_data.push_back(uwb_in_ros);
        mtx.unlock();
        check_data_number();
    }
}

void Moving_Filer::check_data_number(){
    if(uwb_data.size() == NUM){
        nlink_parser::LinktrackNodeframe2 uwb_data_pub = uwb_data.back();
        for(int i=0;i<NUM;i++){
            uwb_dis_pub += uwb_data[i].nodes[0].dis/NUM;
        }
        uwb_data_pub.nodes[0].dis = uwb_dis_pub;
        pub_uwb_dis.publish(uwb_data_pub);

        uwb_data.pop_front();        
        uwb_dis_pub = 0;
    }
}
}; 

#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "std_msgs/Float32.h"

    const double degree = M_PI/180;

    // robot state
    float tilt = 0, tinc = degree;


    /// messageCb
    /*!
           Detailierte beschreibung der Funktionalität
      \sa messageCb()
      \param pa1 toggle_msg
      \param pa2 Parameter 2
     */

    void messageCb( const std_msgs::Float32& toggle_msg){
	 tilt = toggle_msg.data;
     ROS_ERROR("Tilt angle: %f: ",tilt);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;

    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    ros::Subscriber joint_sub = n.subscribe ("axservo",1, messageCb);
    tf::TransformBroadcaster broadcaster;
    ros::Rate loop_rate(30);





    // message declarations
    geometry_msgs::TransformStamped odom_trans;
    sensor_msgs::JointState joint_state;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    while (ros::ok()) {
        //update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(1);
        joint_state.position.resize(1);
        joint_state.name[0] ="tilt";
        joint_state.position[0] = tilt;
        //ROS_ERROR("Tilt angle: %f: ",tilt);

        // update transform
        // (moving in a circle with radius=2)
//        odom_trans.header.stamp = ros::Time::now();
//        odom_trans.transform.translation.x = cos(angle)*2;
//        odom_trans.transform.translation.y = sin(angle)*2;
//        odom_trans.transform.translation.z = .7;
//        odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(angle+M_PI/2);

        //send the joint state and transform
        joint_pub.publish(joint_state);
//        broadcaster.sendTransform(odom_trans);

        // Create new robot state
//        tilt += tinc;
//        if (tilt<-.5 || tilt>0) tinc *= -1;
//        angle += degree/4;
        ros::spinOnce();
        // This will adjust as needed per iteration
        loop_rate.sleep();
    }


    return 0;
}

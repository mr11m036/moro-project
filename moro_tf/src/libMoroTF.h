
/*!*********************************************************************\
* Dateiname: libMoroTF.h
* Autor : Mario Grotschar
* Projekt : Moro
* Copyright (C) <<COPYRIGHT>>
*
* !\brief  Beinhaltet Funktionen für das Moro Projekt.
*
* Datum: Autor: Grund der Aenderung:
* 1.07.2013 Mario Grotschar Neuerstellung
* <<DATUM>> <<AUTOR>> <<AENDERUNGSGRUND>>
*
\**********************************************************************/

#ifndef LIBMORO_H_
#define LIBMORO_H_

/*--- #includes der Form <...> ---------------------------------------*/
#include <ros/ros.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

#include "std_msgs/Float32.h"

/* ---Constants -------------------------------------------------------*/
const std::string sBaseParentFrame = "odom";
const std::string sBaseChileFrame  = "base_link";
const std::string sDynamixelTopic = "/dynamixel/pose";
const double degree = M_PI/180;

class CMoro {
public:
	CMoro(float setTilt = 0, float setTinc = M_PI/180): tilt (setTilt), tinc (setTinc)
	{
		 odom_trans.header.frame_id  = sBaseParentFrame;
		 odom_trans.child_frame_id	 = sBaseChileFrame;
		 joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
		 joint_sub = n.subscribe(sDynamixelTopic, 10, &CMoro::joint_callback, this);
	};
	void setParentHeaderID(std::string setParentID);
	void setChildHeaderID(std::string setChildID);
	void joint_callback(const std_msgs::Float32 &toggle_msg);
	void setTilt(float setTilt);
	float getTilt();
	void resizeMessage(int setSize);
	void updateJointState();
	void run();
	sensor_msgs::JointState getJointState();
	virtual ~CMoro();

protected:
	    ros::NodeHandle n;
	    ros::Publisher	 joint_pub;
	    ros::Subscriber  joint_sub;
private:

    float tilt;
    float tinc;

    geometry_msgs::TransformStamped odom_trans;
    sensor_msgs::JointState 		joint_state;
};

#endif /* LIBMORO_H_ */


/*!*********************************************************************\
* Dateiname: libMoroTF.cpp
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

/*--- #includes der Form "..." ---------------------------------------*/
#include "libMoroTF.h"
#include "std_msgs/Float32.h"

/*--- #includes der Form <...> ---------------------------------------*/
#include <ros/ros.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "std_msgs/Float32.h"


CMoro::~CMoro() {
	// TODO Auto-generated destructor stub
}

/// setChildHeaderID
/*!
       Setzt die header Frame ID. Nötig damit TF funktioniert.
 */

void CMoro::setParentHeaderID(std::string setParentID) {
    odom_trans.header.frame_id = setParentID;

}

/// setChildHeaderID
/*!
       Setzt die header Frame ID. Nötig damit TF funktioniert.
 */

void CMoro::setChildHeaderID(std::string setChildID) {
    odom_trans.child_frame_id = setChildID;
}

/// updateJointState
/*!
       Aktualisiert die Statusmeldung bzgl. der Gelenkspositionen der Schwenkvorrichtung.
 */

void CMoro::updateJointState() {
    joint_state.header.stamp = ros::Time::now();
    joint_state.name.resize(1);
    joint_state.position.resize(1);
    joint_state.name[0] =	"tilt";
    joint_state.position[0] = tilt;
}

/// setTilt
/*!
      Setzt den Tilt Winkel.
 */

void CMoro::setTilt(float setTilt) {
	tilt = setTilt;
}

/// setTilt
/*!
      Setzt den Tilt Winkel.
 */

float CMoro::getTilt() {
	return tilt;
}

/// JointState
/*!
      Gibt die Joint_State Nachricht zurück.
 */
sensor_msgs::JointState CMoro::getJointState() {
	return joint_state;
}

/// joint_callback
/*!
      Die Callbackmethode für die Winkeldaten.
 */
void CMoro::joint_callback(const std_msgs::Float32 &toggle_msg) {
	 this->setTilt(toggle_msg.data);
	 ROS_INFO("Tilt angle: %f: ", this->getTilt());
}

/// run
/*!
      Lässt die ROS Schleife laufen und published die Joint States.
 */
void CMoro::run() {

	ros::Rate loop_rate(30);

while (ros::ok()) {
	        // Den Joint State updaten.
	    	updateJointState();

	        // Die Joint State Nachricht schicken.
	        joint_pub.publish(getJointState());

	        // SpinOnce sonst sendet er nicht.
	        ros::spinOnce();

	        // This will adjust as needed per iteration
	        loop_rate.sleep();
	    }
}

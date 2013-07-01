/*!*********************************************************************\
* Dateiname: publish_state.cpp
* Autor : Mario Grotschar
* Projekt : Moro
* Copyright (C) <<COPYRIGHT>>
*
* !\brief  Schickt die Pose meldungen des Kippsgelenks auf eine ROS Topic.
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


int main(int argc, char** argv) {

	ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;

    CMoro *statePublisher = new CMoro();

    statePublisher->run();

    return 0;
}

#include <ros/ros.h>
#include "/opt/ros/fuerte/stacks/laser_pipeline/laser_assembler/srv_gen/cpp/include/laser_assembler/AssembleScans.h"

using namespace laser_assembler;

const std::string default_frame_id ="laser";

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_client");
  ros::NodeHandle n;
  ros::service::waitForService("assemble_scans");
  ros::ServiceClient client = n.serviceClient<AssembleScans>("assemble_scans");
  std::string topic = n.resolveName("point_cloud");
  ros::Rate loop_rate(30);
  uint32_t queue_size = 1;
  // assume you get a point cloud message somewhere
  sensor_msgs::PointCloud cloud_msg;

  // advertise
  ros::Publisher pub = n.advertise<sensor_msgs::PointCloud>(topic, queue_size);
  AssembleScans srv;


  while (ros::ok()) {

	  srv.request.begin = ros::Time(0,0);
	  srv.request.end   = ros::Time::now();
	  if (client.call(srv)) {
		  cloud_msg.points = srv.response.cloud.points;
		  cloud_msg.header.stamp = srv.request.end;
		  cloud_msg.header.frame_id = default_frame_id;
	  }

         ros::spinOnce();





  // and publish
  pub.publish(cloud_msg);
  loop_rate.sleep();
  }
}

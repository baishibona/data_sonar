#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

#include <iostream>
#include <fstream>

using namespace std;
typedef pcl::PointCloud<pcl::PointXYZI> PointCloud;
ofstream logfile("sonar.txt");


void sonar_callback( const sensor_msgs::PointCloud2ConstPtr& cloud2_msg )
{
  pcl::PCLPointCloud2 cloud2;
  pcl_conversions::toPCL(*cloud2_msg, cloud2);
  PointCloud* cloud_local (new PointCloud);
  pcl::fromPCLPointCloud2(cloud2,*cloud_local);

  cout << "Got a point cloud msg : " << cloud2_msg->height << " by " << cloud2_msg->width << endl;

  for(int i = 1; i < cloud2_msg->width; i++)
  {
      logfile << cloud_local->at(i).x << "\t" << cloud_local->at(i).y << "\t" << cloud_local->at(i).z << "\t" 
              << cloud_local->at(i).intensity << "\t" 
                                      << endl;
  }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sonar_bagfile_reader");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe<sensor_msgs::PointCloud2>("/tritech_micron_node/sonarscan", 1, sonar_callback);


  ros::spin();
  return 0;
}
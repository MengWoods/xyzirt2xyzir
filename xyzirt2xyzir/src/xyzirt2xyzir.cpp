#include <pcl_conversions/pcl_conversions.h>
#include <xyzirt2xyzir/xyzirt2xyzir.h>

xyzirt2xyzir::xyzirt2xyzir(ros::NodeHandle& node)
{
    node.param<std::string>("sub_pointcloud_topic", sub_pointcloud_topic_, "sub_pointcloud_topic_not_set");
    node.param<std::string>("pub_pointcloud_topic", pub_pointcloud_topic_, "pub_pointcloud_topic_not_set");
    node.param<bool>("verbose", verbose_, false);
    pointcloud_sub_ = node.subscribe(sub_pointcloud_topic_, 10, &xyzirt2xyzir::converterCallback, this);
    pointcloud_pub_ = node.advertise<sensor_msgs::PointCloud2>(pub_pointcloud_topic_, 10);
    ROS_INFO("xyzirt2xyzir node is inited!");
}

void xyzirt2xyzir::converterCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud_msg_ptr)
{
    ros::Time start_time = ros::Time::now();
    PointPointIRTCloudPtr cloud_pcl_ptr(new PointPointIRTCloud);
    pcl::fromROSMsg(*cloud_msg_ptr, *cloud_pcl_ptr);

    PointPointIRCloudPtr cloud_xyzir_ptr(new PointPointIRCloud);
    for (size_t i = 0; i < cloud_pcl_ptr->points.size(); ++i) {
        PointIR point;
        point.x = cloud_pcl_ptr->points[i].x;
        point.y = cloud_pcl_ptr->points[i].y;
        point.z = cloud_pcl_ptr->points[i].z;
        point.intensity = cloud_pcl_ptr->points[i].intensity;
        point.ring = cloud_pcl_ptr->points[i].ring;
        // Push the new point to the output point cloud
        cloud_xyzir_ptr->points.push_back(point);
    }

    // Convert the PCL point cloud to ROS message
    sensor_msgs::PointCloud2 output_msg;
    pcl::toROSMsg(*cloud_xyzir_ptr, output_msg);
    output_msg.header = cloud_msg_ptr->header;
    // Publish the converted point cloud
    pointcloud_pub_.publish(output_msg);
    
    // Log processing time
    if (verbose_) 
    {
        ros::Time end_time = ros::Time::now();
        double processing_time = (end_time - start_time).toSec();
        ROS_INFO_STREAM("Point cloud conversion took " << processing_time * 1000 << " ms.");
    }
}
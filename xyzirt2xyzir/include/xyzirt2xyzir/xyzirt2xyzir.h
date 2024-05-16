
#pragma once

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <xyzirt2xyzir/constants.h>

class xyzirt2xyzir
{
public:
    /**
     * @brief Constructor
     * @param [in] node : ROS node handle
     */ 
    xyzirt2xyzir(ros::NodeHandle& node);

    /**
     * @brief Destructor
     */
    ~xyzirt2xyzir() = default;

private:
    /**
     * @brief Callback for point cloud data conversion
     *
     * @param[in] cloud_msg_ptr Pointcloud sensor msg pointer to be converted
     */
    void converterCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud_msg_ptr);

    ros::Subscriber pointcloud_sub_;            ///< Point cloud subscriber
    ros::Publisher pointcloud_pub_;             ///< Point cloud publisher
    std::string sub_pointcloud_topic_;          ///< Topic for subscribing to point cloud
    std::string pub_pointcloud_topic_;          ///< Topic for publishing point cloud
    bool verbose_{false};                       ///< Verbose flag for debug
};

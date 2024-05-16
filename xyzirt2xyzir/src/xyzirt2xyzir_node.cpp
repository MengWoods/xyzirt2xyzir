
#include <ros/ros.h>
#include <xyzirt2xyzir/xyzirt2xyzir.h>

int main(int argc, char** argv)
{
    try
    {
        ros::init(argc, argv, "xyzirt2xyzir_node");
        ros::NodeHandle node_handle("~");
        ros::Rate update_rate(20);
        xyzirt2xyzir xyzirt2xyzir_ros(node_handle);
        ROS_INFO("xyzirt2xyzir node is ready...");

        while (ros::ok())
        {
            ros::spinOnce();
            update_rate.sleep();
        }
    }
    catch (const std::exception& exc)
    {
        ROS_ERROR("Terminated with error: %s", exc.what());
        return 1;
    }
    return 0;
}


#pragma once
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <cstdint>

// Define and register custom point type, typical Velodyne point type
struct PointXYZIR {
    PCL_ADD_POINT4D
    PCL_ADD_INTENSITY;
    std::uint16_t ring;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

POINT_CLOUD_REGISTER_POINT_STRUCT (PointXYZIR,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (float, intensity, intensity)
    (std::uint16_t, ring, ring))

// Define a register custom point type, Robosense point type
struct PointXYZIRT {
  PCL_ADD_POINT4D;
  float intensity;
  std::uint16_t ring;
  double time_stamp;
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIRT,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (float, intensity, intensity)
    (std::uint16_t, ring, ring)
    (double, time_stamp, time_stamp)
)


using PointIR = PointXYZIR;
using PointPointIRCloud = pcl::PointCloud<PointIR>;
using PointPointIRCloudPtr = pcl::PointCloud<PointIR>::Ptr;

using PointIRT = PointXYZIRT;
using PointPointIRTCloud = pcl::PointCloud<PointIRT>;
using PointPointIRTCloudPtr = pcl::PointCloud<PointIRT>::Ptr;
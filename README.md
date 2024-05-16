# xyzirt2xyzir

`xyzirt2xyzir` is a tool to convert point cloud data from XYZIRT (Robosense) to XYZIR (Velodyne) format.

## Dependencies

Dependencies for this tool are listed in the [package.xml](./xyzirt2xyzir/package.xml) file.

## Usage

clone the project to your `catkin_ws/src` path.

```bash
catkin build xyzirt2xyzir
source devel/setup.bash
roslaunch xyzirt2xyzir xyzirt2xyzir.launch
```

The input and output topic can be modified in [launchfile](./xyzirt2xyzir/launch/xyzirt2xyzir.launch).

## Other

If you encounter any errors, please raise an issue.

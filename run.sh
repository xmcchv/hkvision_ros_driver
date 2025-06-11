#!/bin/bash

# 获取脚本的目录
SCRIPT_DIR="$(cd "$(dirname "$0")"; pwd)"
echo $SCRIPT_DIR
cd $SCRIPT_DIR/../../

if catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3;then
    echo "编译success"
    source devel/setup.bash

    roslaunch hikrobot_camera multicam.launch

else
    echo "编译失败"
fi

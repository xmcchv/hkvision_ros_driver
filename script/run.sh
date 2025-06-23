#!/bin/bash

# 获取脚本的目录
SCRIPT_DIR="$(cd "$(dirname "$0")"; pwd)"
echo $SCRIPT_DIR
cd $SCRIPT_DIR/../../../

if catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3;then
    echo "编译success"
    source devel/setup.bash
    # 获取第一个参数
    PARAM=$1
    # 根据参数的值执行不同的操作
    if [ "$PARAM" = "-n" ]; then
        echo "不启动程序..."
    else
        echo "直接运行..."
        roslaunch hikrobot_camera multicam.launch
    fi
else
    echo "编译失败"
fi

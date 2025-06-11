# CMake 最小版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(hikrobot_camera)

set(USE_TIMER ON)  # ON OFF
set(USE_COMPRESS OFF)

if(USE_TIMER)
    add_definitions(-DUSE_TIMER)
endif()
if(USE_COMPRESS)
    add_definitions(-DUSE_COMPRESS)
endif()

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  camera_info_manager
)

catkin_package(
 
)

# 寻找 OpenCV
find_package(OpenCV REQUIRED)
# set(OpenCV_DIR /usr/local/include/opencv4)
# set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/3rdparty/opencv-4.5.4/install)

find_package(OpenCV PATHS ${OpenCV_DIR} REQUIRED)
# find_package(OpenCV 4 REQUIRED opencv_core opencv_imgproc opencv_highgui opencv_calib3d opencv_videoio opencv_xfeatures2d opencv_features2d opencv_imgcodecs opencv_dnn opencv_video)
message(STATUS "==========================================")
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "==========================================")

# 包含头文件目录
include_directories(
    ${catkin_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include/
    ${OPENCV_INCLUDE_DIRS}
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib/
)

# set(MVS_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib/)
# file(GLOB MVS_LIBRARIES "${MVS_LIBRARY_DIR}/*.so")
# file(GLOB MVS_LIBRARIES "${MVS_LIBRARY_DIR}/*.1")

# 添加源文件
add_executable(hkvision src/main.cpp)

# 链接库
# 库文件位于 linux64/lib 和 lib/HCNetSDKCom
target_link_libraries(hkvision 
    ${catkin_LIBRARIES}
    # OpenCV 库
    ${OpenCV_LIBS}
    # ${MVS_LIBRARIES}
    hcnetsdk
   HCCore
   AudioRender
   crypto
   hpr
   NPQos
   PlayCtrl
   ssl
   SuperRender

   analyzedata
   HCAlarm
   HCCoreDevCfg
   HCDisplay
   HCGeneralCfgMgr
   HCIndustry
   HCPlayBack
   HCPreview
   HCVoiceTalk
   iconv2
   StreamTransClient
   SystemTransform
)


add_executable(listener src/listener.cpp)
target_link_libraries(listener 
    ${catkin_LIBRARIES}
    ${OpenCV_LIBS}
    hcnetsdk HCCore AudioRender crypto hpr NPQos PlayCtrl ssl SuperRender
 analyzedata HCAlarm HCCoreDevCfg HCDisplay HCGeneralCfgMgr HCIndustry 
 HCPlayBack HCPreview HCVoiceTalk iconv2 StreamTransClient SystemTransform
)

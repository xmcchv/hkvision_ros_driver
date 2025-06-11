#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from collections import deque

class TimeSyncChecker:
    def __init__(self):
        self.left_buffer = deque(maxlen=10)
        self.right_buffer = deque(maxlen=10)
        
        rospy.Subscriber("/hikcam_left", Image, self.left_cb)
        rospy.Subscriber("/hikcam_right", Image, self.right_cb)
        
        self.timer = rospy.Timer(rospy.Duration(0.1), self.check_sync)

    def left_cb(self, msg):
        self.left_buffer.append(msg.header.stamp)
    
    def right_cb(self, msg):
        self.right_buffer.append(msg.header.stamp)
    
    def check_sync(self, event):
        if len(self.left_buffer) > 0 and len(self.right_buffer) > 0:
            avg_diff = sum(
                (l - r).to_sec() 
                for l, r in zip(self.left_buffer, self.right_buffer)
            ) / len(self.left_buffer)
            
            if abs(avg_diff) > 0.001:  # 1ms阈值
                rospy.logwarn(f"Camera time misalignment: {avg_diff*1000:.3f}ms")
            else:
                rospy.loginfo("Cameras are well synchronized")

if __name__ == "__main__":
    rospy.init_node("time_sync_checker")
    TimeSyncChecker()
    rospy.spin()
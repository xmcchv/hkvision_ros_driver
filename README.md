

### 时间戳对齐算法

```c++

---|--------------|--------- lidar
 lidar_pub_time1 lidar_pub_time2 
    process_time     
     {      }
-----|------|-----------------|-------|---- camera
    callback_time        callback_time1
        image_pub_time            image_pub_time1


```

Residual_time = lidar_pub_time1 - image_pub_time
image_pub_time = callback_time + process_time

Residual_time = lidar_pub_time1 - callback_time - process_time

callback_time1 = callback_time + frame_interval

delay_time = callback_time1 - callback_time - Residual_time
           = callback_time1 - lidar_pub_time1 + process_time
           = callback_time - lidar_pub_time1 + frame_interval + process_time

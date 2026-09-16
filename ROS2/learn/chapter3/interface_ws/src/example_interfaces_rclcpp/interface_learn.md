```Mermaid
sequenceDiagram
    participant Control as Control节点
    participant Executor as ROS2执行器(线程池)
    participant Robot as Robot节点
    participant Timer as 定时器线程
    participant ClientCB as 客户端回调线程
    participant SubCB as 订阅回调线程

    Note over Control,Robot: 初始化阶段
    Control->>Control: 1. 创建客户端和订阅者
    Robot->>Robot: 1. 创建服务、发布者、定时器
    
    Note over Control,Robot: 主程序执行
    Control->>Control: 2. 调用 move_robot(5.0)
    
    rect rgb(200, 200, 255)
    Note over Control: move_robot服务调用流程
    Control->>Control: 2.1 等待服务上线
    Control->>Robot: 2.2 发送异步请求(async_send_request)
    Note over Executor: ROS2执行器管理回调
    Executor->>Robot: 分配服务处理线程
    Robot->>Robot: 3.1 handle_move_robot被调用
    Robot->>Robot: 3.2 调用 robot.move_distance(5.0)
    Note over Robot: 阻塞移动过程(每步500ms)
    loop 直到到达目标位置
        Robot->>Robot: 3.3 计算移动步长
        Robot->>Robot: 3.4 更新当前位置
        Robot->>Robot: 3.5 休眠500ms
    end
    Robot->>Control: 3.6 返回响应结果
    Executor->>ClientCB: 分配客户端回调线程
    ClientCB->>Control: 4. 执行 result_callback_
    end
    
    rect rgb(200, 255, 200)
    Note over Timer: 定时发布流程(独立线程)
    loop 每500ms执行一次
        Executor->>Timer: 分配定时器回调线程
        Timer->>Robot: 执行 timer_callback
        Robot->>Robot: 获取当前状态和位置
        Robot->>Control: 发布 RobotStatus 消息
        Executor->>SubCB: 分配订阅回调线程
        SubCB->>Control: 执行 robot_status_callback_
    end
    end
    
    Note over Control: 5. 主线程继续执行 rclcpp::spin()
```
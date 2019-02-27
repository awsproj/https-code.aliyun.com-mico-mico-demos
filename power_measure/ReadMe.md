# 模块功耗测试方法

---

## 准备工作

### 硬件

 1. MXKit-Base v1.3开发板
 2. Wi-Fi模块
 3. 测试仪器（万用表等）

### 软件
> 本文默认用户已经具备编译和下载mico的环境。
如有疑问，请查看 http://developer.mxchip.com/handbooks

> 以下示例以EMW3080模块为例，其他模块需修改相应的board信息

1.打开`power_measure/main.c`
2.功耗测试代码中包含了多种测试模式的设置，用户可以根据需要，配置不同的测试模式。以下示例配置为测试打开MCU和WiFi低功耗后保持WiFi连接的场景

```C
//设置当前的测试模式
#define POWER_MEASURE_PROGRAM RTOS_WLAN_CONNECT
//MCU低功耗开关
#define MCU_POWERSAVE_ENABLED 1
//WiFi低功耗开关
#define IEEE_POWERSAVE_ENABLED 1

#define RTOS_INITIALIZED          1
#define RTOS_FULL_CPU_THREAD      2
#define RTOS_FLASH_READ           3
#define RTOS_FLASH_ERASE          4
#define RTOS_FLASH_WRITE          5
#define RTOS_WLAN_INITIALIZED     6
#define RTOS_WLAN_SOFT_AP         7
#define RTOS_WLAN_EASYLINK        8
#define RTOS_WLAN_CONNECT         9
#define RTOS_WLAN_UDP_SEND       10
#define STANDBY_MODE             11
```

3.修改代码中的路由器SSID和密码，以便模块上电后能够自动连接测试路由器

```C
strncpy((char*) wNetConfig.ap_info.ssid, "ssid", 32);
wNetConfig.ap_info.security = SECURITY_TYPE_AUTO;
strncpy((char*) wNetConfig.key, "password", 64);
wNetConfig.key_len = 8;
```

4.打开`mico-os/board/MX1290/platform.c`，屏蔽`init_platform()`函数中led的初始化代码，避免板上的led影响测试结果
5.使用`mico make power_measure@MX1290@moc download`命令编译并下载固件到开发板上
6.模块启动后会自动连接代码中设置的路由器，并打开mcu低功耗和WiFi低功耗

## 测试

> 以下测试基于MXKit-Base v1.3和CORE-3080 V2.0展开

1.去掉开发板上J1处的跳线帽，并将电流表的正负极接线接到对应的针脚上
![IMG_1501.jpg-413.7kB][1]
2.使用microUSB为开发板供电，并调整电流表的设置
3.稍等几分钟，待测试数据相对平稳后，记录电流表上的平均电流、最大最小电流等数值
![IMG_1499.jpg-547.5kB][2]

  [1]: http://static.zybuluo.com/1113240207/yew03g4xkx4qh1ak6ly2uhmt/IMG_1501.jpg
  [2]: http://static.zybuluo.com/1113240207/llqubp1guv1vs5mjq38okuua/IMG_1499.jpg
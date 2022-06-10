# ESP-NOW控制的Soundbar
## Sender

- 使用esp-now通信，数据包格式包括发送端mac地址、按键对应io口（gpio12和gpio14）分别对应int值12和14、电池电压
- 代码中电池电压采样：使用的esp-12模组，adc输入引脚测量范围为0-1V，对应采样值为0-1023，本版硬件采用47k+10k的分压比例，则测量得到的值换算回实际电压公式为analogRead(A0)*5.7/1023，其中分压比例5.7=(47+10)/10

## Receiver
- 接收端可以使用nodemcu开发板或其他esp系列开发板
- 本例中使用的接收端不是专门为音响设计，但是因其包含两路mos，供电电压12v，因此可以拿来使用，diy时可更换为双路继电器模块

## 程序烧录
- 先烧录Receiver程序，烧录成功后打开串口调试助手，波特率115200，按reset键重启模块，串口会输出接收端的mac地址，记下
- 在Sender程序中修改broadcastAddress[]数组，内部为16进制，将上一步的mac地址填入
- 烧录Sender程序
- 串口接入Receiver模块，波特率115200，点按Sender按键，串口会输出当然sender的mac地址、按键编号和供电电压值

## 视频教程
- B站：https://www.bilibili.com/video/BV1nW4y1k7vH/
- 油管：https://youtu.be/zsieRLuU3Sw

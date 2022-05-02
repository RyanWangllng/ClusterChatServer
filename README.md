### 设计技术：
- C++11、多线程、CMake
- JSON、muduo
- MySQL、Redis、Nginx
### 服务器结构：
- 网络模块  
    > 采用muduo网络库实现。
- 业务模块  
    > 实现新用户注册、用户登录、添加好友、添加群组、好友聊天、群组聊天以及离线消息功能，并采用JSON格式进行消息传送。
- 数据存储模块  
    > 使用MySQL存储信息，一共设计有五个表，分别是用户基础信息、用户好友信息、用户群组信息、群组详细信息以及离线消息。
- 负载均衡模块  
    > 采用Nginx的TCP负载均衡模块实现服务器集群配置，并用Redis发布-订阅功能实现跨服务器通信。
### 相关组件安装
```bash
# muduo网络库安装
sudo apt install g++ cmake make libboost-dev
git clone git@github.com:chenshuo/muduo.git
cd muduo
./build.sh # 构建
./build.sh install # 将库文件和头文件安装到默认搜索路径下
mv muduo/ /usr/include # muduo文件夹在build/release-install-cpp11/include路径下
mv * /usr/local/lib # 将build/release-install-cpp11/lib下的文件全部移动到系统目录下

# MySQL安装
sudo apt install mysql-server
sudo apt-get install libmysqlclient-dev

# Nginx安装
sudo apt-get install nginx

# Redis安装
sudo apt-get install redis-server
```
### 安装编译
```bash
git clone git@github.com:RyanWangllng/ClusterChatServer.git
cd ClusterChatServer/build/
cmake ..
make # 编译好的文件在bin目录底下
```
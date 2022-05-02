### 涉及技术：
- C++11、多线程、CMake
- JSON、muduo
- MySQL、Redis、Nginx
### 服务器架构：
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
sudo ./build.sh install # 将库文件和头文件安装到默认搜索路径下
mv muduo/ /usr/include # muduo文件夹在build/release-install-cpp11/include路径下
mv * /usr/local/lib # 将build/release-install-cpp11/lib下的文件全部移动到系统目录下

# MySQL安装
sudo apt install mysql-server
sudo apt-get install libmysqlclient-dev

# Nginx安装
sudo apt-get install nginx

# Redis安装
sudo apt-get install redis-server

# hiredis安装
wget https://github.com/redis/hiredis/archive/v0.14.0.tar.gz
tar -xzf v0.14.0.tar.gz
cd hiredis-0.14.0/
make
sudo make install
sudo cp /usr/local/lib/libhiredis.so.0.14 /usr/lib/ # 将动态库移动到系统目录下
```
### 数据库表
##### User
字段 |类型 |约束
---|---|---
id | int | primary key/auto_increment
name | varchar(50) | not null/unique
password | varchar(50) | not null
state | enum('online','offline') | default 'offline'
##### Friend
字段 |类型 |约束
---|---|---
userid | int | not null/union primary key
friendid | int | not null/union primary key
##### AllGroup
字段 |类型 |约束
---|---|---
id | int | primary key/auto_increment
groupname | varchar(50) | not null/unique
groupdesc | varchar(200) | default ''
##### GroupUser
字段 |类型 |约束
---|---|---
groupid | int | not null/union primary key
userid | int | not null/union primary key
grouprole | enum('creator','normal') | default 'normal'
##### OfflineMessage
字段 |类型 |约束
---|---|---
userid | int | not null
message | varchar(500) | not null

### Nginx均衡负载（TCP）配置
```bash
cd /etc/nginx/
vim nginx.conf
#在events和http中间添加
stream {
        upstream MyServer {
                server 127.0.0.1:6000 weight=1 max_fails=3 fail_timeout=30s;
                server 127.0.0.1:6002 weight=1 max_fails=3 fail_timeout=30s;
        }

        server {
                proxy_connect_timeout 1s;
                proxy_timeout 3s;
                listen 8000;
                proxy_pass MyServer;
                tcp_nodelay on;
        }
}
cd /usr/sbin/
./nginx -s reload # 平滑重启
```
### 安装编译
```bash
git clone git@github.com:RyanWangllng/ClusterChatServer.git
cd ClusterChatServer/build/
cmake ..
make # 编译好的文件在bin目录底下
```
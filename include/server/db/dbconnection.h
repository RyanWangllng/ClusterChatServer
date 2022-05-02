#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <mysql/mysql.h>
#include <ctime>
#include "string"
using namespace std;

/*
    MySQL数据库连接操作模块
*/
class Connection {
public:
    // 初始化数据库连接 MySQL()
    Connection();
    // 释放数据库连接资源 ~MySQL()
    ~Connection();

    // 连接数据库
    bool connect(string ip, 
                unsigned short port, 
                string user, 
                string password,
                string dbname);
    // 更新操作 insert、delete、update bool update(string sql)
    bool update(string sql);
    // 查询操作 select
    MYSQL_RES* query(string sql);
    // 获取连接
    MYSQL* getConnection() {
        return _conn;
    }
    
    // 更新连接的起始空闲时间点
    void updateAliveTime() {
        _alivetime = clock();
    }
    // 返回存活的时间
    clock_t getAliveTime() const {
        return clock() - _alivetime;
    }

private:
    MYSQL *_conn; // MySQL的一条连接
    clock_t _alivetime; // 记录进入空闲状态后的起始存活时间
};

#endif// DBCONNECTION_H
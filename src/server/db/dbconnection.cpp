#include "dbconnection.h"
#include <muduo/base/Logging.h>

Connection::Connection() {
	//初始化数据库连接
	_conn = mysql_init(nullptr);
	if (nullptr == _conn) {
		LOG_INFO << "Init mysql fail!";
	}
}

Connection::~Connection() {
	//释放数据库连接资源
	if (_conn != nullptr) mysql_close(_conn);
}

bool Connection::connect(string ip, unsigned short port,
						 string username, string password, string dbname) {
	//连接数据库
	MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
								  password.c_str(), dbname.c_str(), port, nullptr, 0);
	if (p != nullptr) {
		mysql_query(_conn, "set names gbk");
		LOG_INFO << "Connect mysql-server success!";
	} else {
		LOG_INFO << "Connect mysql-server fail!";
	}

	return p;
}

bool Connection::update(string sql) {
	if (mysql_query(_conn, sql.c_str())) {
		LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
				 << sql << "更新失败!";
		return false;
	}

	return true;
}

MYSQL_RES *Connection::query(string sql) {
	if (mysql_query(_conn, sql.c_str())) {
		LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
				 << sql << "查询失败!";
		return nullptr;
	}

	return mysql_use_result(_conn);
}
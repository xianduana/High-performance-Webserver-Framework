/*
 * @Author       : xianduana
 * @Date         : 2024-02
 */
#ifndef SQLCONNPOOL_H
#define SQLCONNPOOL_H

#include <mysql/mysql.h>
#include <string>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <thread>
#include "../log/log.h"

class SqlConnPool {
public:
    static SqlConnPool *Instance();//静态实例

    MYSQL *GetConn();//获取连接
    void FreeConn(MYSQL * conn);//释放连接
    int GetFreeConnCount();//获取空闲的数量

    void Init(const char* host, int port,//主机名  端口
              const char* user,const char* pwd, //用户名  密码
              const char* dbName, int connSize);//数据库名  连接大小
    void ClosePool();

private:
    SqlConnPool();
    ~SqlConnPool();

    int MAX_CONN_;//最大连接数
    int useCount_;//当前用户数
    int freeCount_;//空闲的用户

    std::queue<MYSQL *> connQue_;
    std::mutex mtx_;//互斥锁
    sem_t semId_;//信号量
};


#endif // SQLCONNPOOL_H
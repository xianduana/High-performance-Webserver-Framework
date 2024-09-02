# High-performance-Webserver-Framework
用C++实现的高性能WEB服务器框架，经过webbench压力测试可以实现2000+的QPS

## 功能
* 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型；
* 利用正则与状态机解析HTTP请求报文，实现处理静态资源的请求；
* 利用标准库容器封装char，实现自动增长的缓冲区；
* 基于小根堆实现的定时器，关闭超时的非活动连接；
* 利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；
* 利用RAII机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。

## 环境要求
* Linux
* C++14
* MySql

## 目录树
```
.
├── code           源代码
│   ├── buffer
│   ├── http
│   ├── log
│   ├── timer
│   ├── pool
│   ├── server
│   └── main.cpp
├── resources      静态资源
│   ├── index.html
│   ├── image
│   ├── video
│   ├── js
│   └── css
├── bin            可执行文件(编译后生成)
│   └── server
├── log            日志文件
├── build          
│   └── Makefile
├── Makefile
└── readme.md
```

## 项目启动
需要先配置好对应的数据库(这里已我的配置为例)
```bash
// Mysql账号密码使用默认的root 和 ""
// 建立"webserver"库
create database webserver;

// 创建user表
USE webserver;
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;

// 添加数据
INSERT INTO user(username, password) VALUES('name', 'password');
```

```bash
make
./bin/server
```

## 压力测试

1.WebBench安装

```
wget http://home.tiscali.cz/~cz210552/distfiles/webbench-1.5.tar.gz
tar zxvf webbench-1.5.tar.gz
cd webbench-1.5
//	安装一些依赖包以及做一下软链接

sudo apt-get install -y libtirpc-dev
sudo ln -s /usr/include/tirpc/rpc/types.h /usr/include/rpc
sudo ln -s /usr/include/tirpc/netconfig.h /usr/include
sudo apt-get install universal-ctags

make
make install
```

2.压测

![performance](D:\githubproject\High-performance-Webserver-Framework\readme.assest\压力测试.png)
```bash
./webbench-1.5/webbench -c 100 -t 10 http://ip:port/
```
* 测试环境: VM虚拟机：Ubuntu:22.04.4 4核cpu 内存:4G 
* QPS 2000+


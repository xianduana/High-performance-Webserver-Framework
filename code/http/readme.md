<!--
 * @Author       : xianduana
 * @Date         : 2024-02
--> 
1. 初始化请求request_.Init();

2. 解析请求request_.parse(readBuff_)

3. 解析成功之后初始化响应报文

4. 创建响应报文

5. 分散写（状态行、头部）和正文
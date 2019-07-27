///////////////////////////////////////////////////////
// gflags 是一个配置管理库
// 让我们更优雅的方式使用 命令行参数 作为配置项
///////////////////////////////////////////////////////

#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(ip, "127.0.0.1", "服务器依赖的ip地址");
DEFINE_int32(port, 80, "服务器依赖的端口号");

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::cout << FLAGS_ip << std::endl;
  std::cout << FLAGS_port << std::endl;
  return 0;
}


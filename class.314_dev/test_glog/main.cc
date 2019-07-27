#include <glog/logging.h>

int main(int argc, char* argv[]) {
  (void) argc;
  google::InitGoogleLogging(argv[0]);
  FLAGS_log_dir = "./log";

  // 不算错误. 
  LOG(INFO) << "log info";
  // 处理方式, 一旦日志积累到一定程度, 也要发送报警短信
  LOG(WARNING) << "log warning";
  // 处理方式, 出现错误日志, 给开发人员发送报警短信
  LOG(ERROR) << "log error";
  // 处理方式, 进程异常终止, 吐出 core dump 文件.
  // 也要发报警短信, 自动的把进程重新启动.
  // LOG(FATAL) << "log fatal";
  return 0;
}


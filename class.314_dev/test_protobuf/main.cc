#include "hello.pb.h"

int main() {
  // 序列化
  Hello hello;
  hello.set_name("汤老湿");
  hello.set_score(100);
  std::string str;
  hello.SerializeToString(&str);
  // std::cout << str << std::endl;

  Hello hello_result;
  hello_result.ParseFromString(str);
  std::cout << hello_result.name() << ", "
            << hello_result.score() << std::endl;
  return 0;
}

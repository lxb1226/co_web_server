//
// Created by heyjude on 2022/7/21.
//

#include "HttpServer.h"
#include "conet/base/Log.h"
#include <iostream>

using namespace std;

// const char *srcDir =
// "\\\\wsl$\\Ubuntu-20.04\\home\\heyjude\\workspace\\repos\\Burger\\examples\\http_server\\resources";

const char *srcDir = "../http_server/resources";

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    cout << "Usage: " << argv[0] << " port" << endl;
    return 0;
  }
  LOGGER();
  LOG_LEVEL_TRACE;
  Scheduler sched;
  uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
  InetAddress serverAddr(port);
  HttpServer httpServer(&sched, serverAddr, srcDir);
  DEBUG("server start at port : {}", port);
  httpServer.start();
  sched.wait();
}
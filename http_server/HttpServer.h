//
// Created by heyjude on 2022/7/21.
//

#ifndef co_net_HTTPSERVER_H
#define co_net_HTTPSERVER_H

#include "conet/base/Log.h"
#include "conet/net/Buffer.h"
#include "conet/net/CoTcpServer.h"
#include "conet/net/Scheduler.h"
#include <boost/noncopyable.hpp>
#include <functional>
#include <set>
#include <string>

using namespace conet;
using namespace conet::net;
using namespace std::placeholders;

class HttpServer : boost::noncopyable {
public:
  HttpServer(Scheduler *sched, const InetAddress listenAddr, const char *srcDir)
      : sched_(sched), server_(sched, listenAddr, "HttpServer"),
        srcDir_(srcDir) {
    server_.setConnectionHandler(std::bind(&HttpServer::connHandler, this, _1));
  };

  void start() { server_.start(); }

  void connHandler(const CoTcpConnection::ptr &conn);

  //    void onStringMsg(const std::string &msg) {
  //        for (auto it = connections_.begin(); it != connections_.end(); ++it)
  //        {
  //            codec_.wrapAndSend(*it, msg);
  //        }
  //    }

private:
  using ConnectionList = std::set<CoTcpConnection::ptr>;
  Scheduler *sched_;
  CoTcpServer server_;
  const char *srcDir_;
  ConnectionList connections_;
};

#endif // co_net_HTTPSERVER_H

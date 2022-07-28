//
// Created by heyjude on 2022/7/21.
//

#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"


void HttpServer::connHandler(const CoTcpConnection::ptr &conn) {
    connections_.insert(conn);
    Buffer::ptr readBuff = std::make_shared<Buffer>();
    Buffer::ptr writeBuff = std::make_shared<Buffer>();

    HttpRequest request;
    HttpResponse response;
    //    struct iovec iov[2];
    //    int iovCnt = 1;
    DEBUG("start to process connect");
    // TODO:这边逻辑是错误的
    // 进一步修改这里逻辑
    while (conn->recv(readBuff) > 0) {
        // TODO:这里逻辑是错误的
        request.Init();
        if (request.parse(*readBuff)) {
            DEBUG("request parse success!")
            DEBUG("request.path : {}", request.path())
            response.Init(srcDir_, request.path(), request.IsKeepAlive(), 200);
        } else {
            response.Init(srcDir_, request.path(), false, 400);
        }

        response.MakeResponse(*writeBuff);
        //        int saveError = 0;
        if (response.FileLen() > 0 && response.File()) {
            writeBuff->append(response.File(), response.FileLen());
        }

        conn->send(writeBuff);
        writeBuff->retrieveAll();
    }
    connections_.erase(conn);
}
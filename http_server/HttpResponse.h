//
// Created by heyjude on 2022/7/21.
//

#ifndef co_net_HTTPRESPONSE_H
#define co_net_HTTPRESPONSE_H

#include <conet/net/Buffer.h>
#include <fcntl.h>// open
#include <iostream>
#include <sys/mman.h>// mmap, munmap
#include <sys/stat.h>// stat
#include <unistd.h>  // close
#include <unordered_map>

using namespace conet::net;

class HttpResponse {
public:
    HttpResponse();
    ~HttpResponse();

    void Init(const std::string &srcDir, std::string &path, bool isKeepAlive = false, int code = -1);
    void MakeResponse(Buffer &buff);
    void UnmapFile();
    char *File();
    size_t FileLen() const;
    void ErrorContent(Buffer &buff, std::string message);
    int Code() const { return code_; }

private:
    void AddStateLine_(Buffer &buff);
    void AddHeader_(Buffer &buff);
    void AddContent_(Buffer &buff);

    void ErrorHtml_();
    std::string GetFileType_();

    int code_;
    bool isKeepAlive_;

    std::string path_;
    std::string srcDir_;

    char *mmFile_;
    struct stat mmFileStat_;

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
    static const std::unordered_map<int, std::string> CODE_STATUS;
    static const std::unordered_map<int, std::string> CODE_PATH;
};


#endif//co_net_HTTPRESPONSE_H

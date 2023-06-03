#include "syscall.h"

int main() {
    char buf[20];
    Write("--", 2, 1);
    Read(&buf, 20, 0);
    
    Socket_t sockId = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
    if (sockId < 0) {
        return -1;
    }
    int st = Connect(sockId, "127.0.0.1", 7777);
    if (st < 0) {
        return -1;
    }
    char request[46] = {"GET /lego/                    HTTP/1.1\r\n\r\n"};
    for (int i = 10; i < 31; ++i) {
        request[i] = buf[i - 10];
    }
    char response[1024];
    Write(sockId, request, 46);
    Read(sockId, response, 1024);
    Write(response, 1024, 1);
    Close(sockId);
    return 0;
}
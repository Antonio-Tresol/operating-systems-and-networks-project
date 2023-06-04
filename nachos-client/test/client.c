#include "syscall.h"

int main() {
    char request[43];
    int i;
    for (i = 0; i < 43; ++i) {
        request[i] = ' ';
    }

    request[0] = 'G';
    request[1] = 'E';
    request[2] = 'T';
    request[3] = ' ';
    request[4] = '/';
    request[5] = 'l';
    request[6] = 'e';
    request[7] = 'g';
    request[8] = 'o';
    request[9] = '/';

    char buf[20];
    for (i = 0; i < 20; ++i) {
        buf[i] = ' ';
    }

    Write("--", 2, 1);
    Read(buf, 20, 0);

    for (i = 10; i < 30; ++i) {
        request[i] = buf[i - 10];
    }

    request[30] = 'H';
    request[31] = 'T';
    request[32] = 'T';
    request[33] = 'P';
    request[34] = '/';
    request[35] = '1';
    request[36] = '.';
    request[37] = '1';
    request[38] = '\r';
    request[39] = '\n';
    request[40] = '\r';
    request[41] = '\n';
    request[42] = '\0';

    char ipAddr[15];
    ipAddr[0] = '1';
    ipAddr[1] = '2';
    ipAddr[2] = '7';
    ipAddr[3] = '.';
    ipAddr[4] = '0';
    ipAddr[5] = '.';
    ipAddr[6] = '0';
    ipAddr[7] = '.';
    ipAddr[8] = '1';
    ipAddr[9] = 0;
    ipAddr[10] = 0;
    ipAddr[11] = 0;
    ipAddr[12] = 0;
    ipAddr[13] = 0;
    ipAddr[14] = 0;

    char response[512];
    for (i = 0; i < 512; ++i) {
        response[i] = '\0';
    }

    Socket_t sockId = Socket(AF_INET_NachOS, SOCK_STREAM_NachOS);
    if (sockId < 0) {
        return -1;
    }

    int st = Connect(sockId, ipAddr, 7777);
    if (st < 0) {
        return -1;
    }

    Write(request, 43, sockId);

    int num = 512;
    while(num == 512) {
        num = Read(response, num, sockId);
        Write(response, num, 1);
    }

    Close(sockId);
    return 0;
}


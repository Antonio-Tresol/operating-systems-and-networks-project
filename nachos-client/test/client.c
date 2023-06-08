#include "syscall.h"

int main() {
  char request[16];  // N-xxxxxxxxxxxxx
  int i;
  for (i = 0; i < 25; ++i) {
    request[i] = ' ';
  }
  request[0] = 'N';
  request[1] = '-';
  char buf[12];
  for (i = 0; i < 12; ++i) {
    buf[i] = ' ';
  }
  Write("--", 2, 1);
  Read(buf, 20, 0);
  for (i = 2; i < 16; ++i) {
    request[i] = buf[i - 2];
  }
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
  while (num == 512) {
    num = Read(response, num, sockId);
    Write(response, num, 1);
  }
  Close(sockId);
  return 0;
}

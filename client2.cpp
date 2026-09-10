#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string_view>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "COULDNT INITIALIZE SOCKEt\n";
    return 1;
  }
  sockaddr_in systemadd{};
  systemadd.sin_family = AF_INET;
  systemadd.sin_port = htons(8080);

  if (inet_pton(AF_INET, "127.0.0.1", &systemadd.sin_addr) < 0) {
    std::cerr << "INVALID ADDRESS\n";
    return 1;
  }
  if (connect(sock, (struct sockaddr *)&systemadd, sizeof(systemadd)) < 0) {
    std::cerr << "NOHUAIODN\n";
    return 1;
  }
  std::string_view message = "GLORY TO NETANYAHU";
  send(sock, message.data(), message.length(), 0);
  std::cout << "Payload transmitted.\n";
  close(sock);
}
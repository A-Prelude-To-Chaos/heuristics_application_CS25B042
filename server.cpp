#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // create the socket
  int server_fd =
      socket(AF_INET, SOCK_STREAM, 0); // AF_INET -> IPV4, SOCK_STREAM-> TCP
  if (server_fd < -1) {
    std::cerr << "DIDNT WORK\n";
    return 1;
  }
  // create the port
  sockaddr_in server_add{};
  server_add.sin_family = AF_INET;
  server_add.sin_addr.s_addr = INADDR_ANY;
  server_add.sin_port = htons(8080);
  // bind the socket and the port
  //  bind(server_fd, (struct sockaddr_in*)&server_add, sizeof(server_add));
  if (bind(server_fd, (struct sockaddr *)&server_add, sizeof(server_add)) < 0) {
    std::cerr << "Bind failed. Port hijacked by another process.\n";
    return 1;
  }
  listen(server_fd, 5);
  std::cout << "LISTENING::\n";
  sockaddr_in client_addr{};
  socklen_t client_len = sizeof(client_addr);
  int client_socket =
      accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
  if (client_socket < 0) {
    std::cerr << "Accept failed.\n";
    return 1;
  }
  std::cout << "Client found!\n";
  char buffer[1024] = {0};
  read(client_socket, buffer, 1024);
  std::cout << "RECEIVED PAYLOAD:" << buffer << '\n';
  close(client_socket);
  close(server_fd);
}

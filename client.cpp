#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <string_view>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address.\n";
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection Failed. Target server is offline.\n";
        return 1;
    }

    std::string_view message = "HELLLLLLLLLOOOOOOOOO SEERVER";
    send(sock, message.data(), message.length(), 0);
    std::cout << "Payload transmitted.\n";

    close(sock);
    return 0;
}

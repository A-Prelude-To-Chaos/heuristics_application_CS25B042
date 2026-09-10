#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <string_view>

int main() {
    // 1. FORGE SOCKET
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    // 2. CONFIGURE TARGET SERVER ADDRESS
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // Convert string IP to binary network format
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address.\n";
        return 1;
    }

    // 3. CONNECT TO SERVER
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection Failed. Target server is offline.\n";
        return 1;
    }

    // 4. SEND PAYLOAD (Using string_view to avoid copying overhead)
    std::string_view message = "CHEEEEEEEESECAKE SALONIIIIIIIIIIIJDSBAKJSAKLJBAJKNB LKJNbkj:jnb";
    send(sock, message.data(), message.length(), 0);
    std::cout << "Payload transmitted.\n";

    // 5. TEARDOWN
    close(sock);
    return 0;
}

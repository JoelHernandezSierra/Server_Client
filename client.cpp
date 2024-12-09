#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    const char* message = "Hola servidor!";
    char buffer[1024] = { 0 };

    // Inicialitzar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicialitzar Winsock" << std::endl;
        return 1;
    }

    // Crear el socket del client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar l'adreça del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Direcció no vàlida o no suportada" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Connectar al servidor
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connexió fallida: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connexió establerta amb el servidor." << std::endl;

    // Enviar missatge al servidor
    send(clientSocket, message, strlen(message), 0);
    std::cout << "Enviant missatge: " << message << std::endl;

    // Rebre resposta del servidor
    int valread = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (valread > 0) {
        std::cout << "Resposta del servidor: " << buffer << std::endl;
    }

    // Tancar el socket
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    char buffer[1024];

    // Inicialitzar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configurar l'adreça del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    // Enllaçar el socket
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Escoltar connexions
    listen(serverSocket, 5);
    std::cout << "Esperant connexions..." << std::endl;

    // Acceptar connexió del client
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    std::cout << "Connexió acceptada!" << std::endl;

    // Rebre missatge del client
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Missatge rebut del client: " << buffer << std::endl;

    // Enviar resposta al client
    const char* response = "Hola des del servidor!";
    send(clientSocket, response, strlen(response), 0);
    std::cout << "Resposta enviada al client." << std::endl;

    // Tancar sockets
    closesocket(clientSocket);
    closesocket(serverSocket);

    // Finalitzar Winsock
    WSACleanup();

    return 0;
}

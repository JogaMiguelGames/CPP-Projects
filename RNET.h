#ifndef RNET_H
#define RNET_H

#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")

class RNET {
public:
    RNET();
    ~RNET();

    std::string GetIPAddress(const std::string& hostname);
    SOCKET CreateSocket(int family = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
    void Connect(SOCKET sock, const std::string& ip, int port);
    void Bind(SOCKET sock, const std::string& ip, int port);
    void Listen(SOCKET sock, int backlog = SOMAXCONN);
    SOCKET Accept(SOCKET sock);
    void CloseSocket(SOCKET sock);
    int SendData(SOCKET sock, const std::string& data);
    std::string ReceiveData(SOCKET sock, int bufferSize = 1024);
    
    std::vector<std::string> GetAvailableIPs();
    bool SetSocketOption(SOCKET sock, int level, int optname, int optval);
    
    std::string IPv4ToString(const struct in_addr& addr);
    std::string IPv6ToString(const struct in6_addr& addr);
    struct in_addr StringToIPv4(const std::string& ip);
    struct in6_addr StringToIPv6(const std::string& ip);

private:
    void InitializeWinsock();
    void CleanupWinsock();
    void CheckError(int result, const std::string& errorMessage);

    WSADATA wsaData;
};

RNET::RNET() {
    InitializeWinsock();
}

RNET::~RNET() {
    CleanupWinsock();
}

void RNET::InitializeWinsock() {
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    CheckError(result, "Failed to initialize Winsock");
}

void RNET::CleanupWinsock() {
    WSACleanup();
}

void RNET::CheckError(int result, const std::string& errorMessage) {
    if (result != 0) {
        throw std::runtime_error(errorMessage + ": " + std::to_string(WSAGetLastError()));
    }
}

std::string RNET::GetIPAddress(const std::string& hostname) {
    struct addrinfo hints = {};
    struct addrinfo* result;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int res = getaddrinfo(hostname.c_str(), nullptr, &hints, &result);
    CheckError(res, "getaddrinfo failed");

    char ipstr[INET6_ADDRSTRLEN];
    std::string ipAddress;

    for (struct addrinfo* p = result; p != nullptr; p = p->ai_next) {
        if (p->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = reinterpret_cast<struct sockaddr_in*>(p->ai_addr);
            inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
        } else {
            struct sockaddr_in6* ipv6 = reinterpret_cast<struct sockaddr_in6*>(p->ai_addr);
            inet_ntop(AF_INET6, &(ipv6->sin6_addr), ipstr, sizeof(ipstr));
        }
        ipAddress = ipstr;
    }

    freeaddrinfo(result);
    return ipAddress;
}

#endif
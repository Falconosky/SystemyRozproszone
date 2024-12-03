// client_connection.h
#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

extern std::queue<std::string> messageQueue;
extern std::mutex queueMutex;
extern std::condition_variable queueCondVar;
extern bool running;

int initialize_connection(const std::string& ip_address, int port);
void receive_thread_function(int sockfd);
void send_thread_function(int sockfd);

#endif // CLIENT_CONNECTION_H

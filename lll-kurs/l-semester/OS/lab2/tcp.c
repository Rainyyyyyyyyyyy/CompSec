#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>
#include <errno.h>
/*
    1.Принимать соединения на некоторый порт, сообщать о новых соединениях на терминал,
     одно соединение оставлять принятым, остальные закрывать сразу после подключения.
    2. При появлении любых данных в соединении выводить сообщение на терминал
     (для простоты достаточно вывести только количество полученных данных).
    3. При получении сигнала выводить сообщение на терминал.
*/
volatile sig_atomic_t wassighup = 0;
void handle_signal(int signo) {
// вызывается при регистрации SIGHUP 
    wassighup = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {    // Если при запуске не был указан порт
        fprintf(stderr, "Server needs port: %s <port>\n", argv[0]);
        return 1;
    }
    // порт указан, создаём сокет сервера
    printf("Starting\n");
    int server_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int port = atoi(argv[1]);   // сохранение порта в специальную переменную port

    // Создание сокета
    printf("Creating socket\n");
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Creating of socket has been failed");
        return 1;
    }

    // Инициализация структуры адреса сервера
    printf("Initializing server address structure\n");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;   // прослушка по любому адресу
    server_addr.sin_port = htons(port);

    // Прикрепление сокета к полученному порту
    printf("Binding socket to the specified port\n");
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding has been failed");
        close(server_sock);
        return 1;
    }

    // Прослушивание входный соединений
    printf("Listening for incoming connections\n");
    if (listen(server_sock, 1) == -1) {
        perror("Listening has been failed");
        close(server_sock);
        return 1;
    }
   
    printf("Registration signal handler for SIGHUP\n");
    struct sigaction sa;
    sigaction(SIGHUP, NULL, &sa);
    sa.sa_handler = handle_signal;
    sa.sa_flags |= SA_RESTART;
    sigaction(SIGHUP, &sa, NULL);

    printf("Server is running on port %d\n", port);
	// Блокировка сигнала SIGHUP
    
    sigset_t origMask;
    sigset_t blockedMask;
    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, SIGHUP);
    sigprocmask(SIG_BLOCK, &blockedMask, &origMask);

    // Заблокирован сигнал SIGHUP
    printf("Block signal SIGHUP\n");

    fd_set readfds;
    int max_fd;
    printf("While(process_running):\n");

    int number_of_clients = 0;
    int client_fd;
    struct sockaddr_in client_address;
    struct sockaddr_in excess_address;  
    int excess_fd;          
     while (1) {
	    FD_ZERO(&readfds);
	    FD_SET(server_sock, &readfds);	
	    max_fd = server_sock;
        int ready_fds;
        if(number_of_clients == 1){
		    FD_SET(client_fd, &readfds);
            if(client_fd > max_fd)max_fd = client_fd;
        }
        while(pselect(max_fd + 1, &readfds, NULL, NULL, NULL, &origMask) == -1){
            if(errno == EINTR){
                if(wassighup == 1){
                    wassighup = 0;
                    printf("Wassighup has caught\n");
                }
            }
        }
        
        if (FD_ISSET(server_sock, &readfds)){ 
            if(number_of_clients == 0) { // при отсутствии подключений - подключаем
                int len = sizeof(client_address);
                client_fd = accept(server_sock, &client_address, &len);
                if (client_fd >= 0) {
                    printf("Connected!\n");
                    number_of_clients++;
                }
                else {
                    printf("Accept error.\n");
                }
            }
            else { // иначе - закрываем новое соединение
                int len = sizeof(excess_address);
                excess_fd = accept(server_sock, &excess_address, &len);
                if (excess_fd >= 0) {
                    printf("New connection was denied.\n");
                    close(excess_fd);
                }
            }
        }
            // Проверка данных на сокетах клиентов
            if (FD_ISSET(client_fd, &readfds)) {
                char buffer[1024];
                ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
                printf("Server recieved data\n");
                if (bytes_read == -1) {
                    perror("Recieving has been failed");
                } else if (bytes_read == 0) {
                        // Соединение закрыто клиентом
                    printf("Connection closed by client\n");
                    number_of_clients = 0;
                    close(client_fd);
                    FD_CLR(client_fd, &readfds);
                } else {
                    printf("Received %zd bytes from client\n", bytes_read);
                }
            }
        }
    return 0;
}

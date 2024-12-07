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
        сообщение о новых подключениях: строка 161 и 176
        охранение одного соединения: блок else {} на строке 154
        отключение "лишних" соединений: блок if() на строке 155
    2. При появлении любых данных в соединении выводить сообщение на терминал
     (для простоты достаточно вывести только количество полученных данных).
        Вывод данных от клиента: блок на строке 124
    3. При получении сигнала выводить сообщение на терминал.
        Вывод получения сигнала: строка 76 
*/

volatile sig_atomic_t process_running = 1;

void handle_signal(int signo) {
    // Обработчик сигналов не делает ничего, кроме завершения цикла pselect
    printf("process_running set to 0\n");
    process_running = 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {    // Если при запуске не был указан порт
        fprintf(stderr, "Server needs port: %s <port>\n", argv[0]);
        return 1;
    }
    // порт указан, создаём сокет сервера
    printf("Starting\n");
    int server_sock, client_sock;
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
   
    

    // Register signal handler for SIGHUP
    printf("Registration signal handler for SIGHUP\n");
    signal(SIGHUP, handle_signal);

    printf(" = = = = Server is running on port %d = = = =\n", port);

    struct timespec timeout = {5, 0}; // тайм-аут ожидания = 5 секунд для pselect()
    sigset_t blockedMask, origMask;

    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, SIGHUP);

    // Заблокировать сигнал SIGHUP
    printf("Block signal SIGHUP\n");
    if (sigprocmask(SIG_BLOCK, &blockedMask, &origMask) == -1) {
        perror("Block_signal_SIGHUP error");
        return 1;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(server_sock, &readfds);
    int max_fd = server_sock;   // пока что 0 соединений, поэтому max_fd показывает на сокет сервера
    printf("While(process_running):\n");

    int number_of_clients = 0;

     while (process_running) {
        // Копируем набор дескрипторов, так как pselect изменяет его
        fd_set temp_fds = readfds;

        // Ожидание изменений дескрипторов на сокетах клиентов
        int ready_fds;
        do {
            ready_fds = pselect(max_fd + 1, &temp_fds, NULL, NULL, &timeout, &origMask);
        } while (ready_fds == -1 && errno == EINTR);

        if (ready_fds == -1) {
            perror("pselect error");
            break;
        }
         else if (ready_fds == 0) {
            // после pselect() ни один дескриптор не обновился
            // значит нет активности на клиентских сокетах 
            printf("No activity on sockets\n");
        } 
        else {
            // Проверка данных на сокетах клиентов
            for (int i = server_sock + 1; i <= max_fd; i++) {
                if (FD_ISSET(i, &temp_fds)) {
                    // FD_ISSET проверяет сокет на то, в наборе ли подключённых соединений он сейчас
                    char buffer[1024];
                    // дескрипторы обновились, клиент действительно в списке подключений
                    // начинаем принимать от него данные в buffer
                    ssize_t bytes_read = recv(i, buffer, sizeof(buffer), 0);
                    printf("Server recvieved data\n");
                    if (bytes_read == -1) {
                        perror("Recieving has been failed");
                    } else if (bytes_read == 0) {
                        // Соединение закрыто клиентом
                        printf("Connection closed by client\n");
                        number_of_clients = 0;
                        close(i);
                        FD_CLR(i, &readfds);
                        // Клиент отключился самостоятельно
                        // FD_CLR удаляет из набора дескрипторы, которые относились к этому соединению
                    } else {
                        printf("Received %zd bytes from client\n", bytes_read);
                        send(i, buffer, bytes_read, 0);
                        // выводим на консоль сервера полученные данные (размер в байтах)
                        // и отправляем их обратно имитируя эхо-сервер
                    }
                }
            }

            // Проверка входящих соединений
            if (FD_ISSET(server_sock, &temp_fds)) {
                if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
                    perror("Accepting has been failed");
                } else {
                    if(number_of_clients == 1){
                        // пришло новое ("лишнее") соединение
                        // сервер его принимает, выводит на консоль, что клиент подключился
                        // и сразу закрывает его
                        char client_ip[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
                    printf("Accepted connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));
                    FD_SET(client_sock, &readfds);
                    printf("Connection closed by server\n");
                        //number_of_clients = 0;

                        close(client_sock);
                        FD_CLR(client_sock, &readfds);

                    }       // иначе новое соединение - первое, принимаем его
                    else{
                    // Пришло новое соединение
                    // Логгирование нового соединения
                        number_of_clients = 1;
                        char client_ip[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
                        printf("Accepted connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));

                    // Добавление сокета клиента в множество
                        FD_SET(client_sock, &readfds);

                    // Обновление max_fd при необходимости
                        if (client_sock > max_fd) {
                            max_fd = client_sock;
                        }
                    }
                }
            }
        }
    }

    // Закрытие всех сокетов клиентов
    printf("Closing all sockets\n");
    for (int i = server_sock + 1; i <= max_fd; i++) {
        if (FD_ISSET(i, &readfds)) {
            close(i);
        }
    }

    // Закрытие сокета сервера
    close(server_sock);
    printf("Server is shutting down\n");
    return 0;

}

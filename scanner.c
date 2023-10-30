#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Użycie: %s <adres_początkowy> <adres_końcowy> <port>\n", argv[0]);
        return 1;
    }

    char *start_ip = argv[1];
    char *end_ip = argv[2];
    int port = atoi(argv[3]);

    struct sockaddr_in sa;
    int sockfd;

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;

    // Konwersja adresów IP początkowego i końcowego na wartości numeryczne
    if (inet_pton(AF_INET, start_ip, &sa.sin_addr) == 0 || inet_pton(AF_INET, end_ip, &sa.sin_addr) == 0) {
        perror("Błąd konwersji adresów IP");
        return 1;
    }

    // Skanowanie zakresu adresów IP
    for (uint32_t ip = ntohl(sa.sin_addr.s_addr); ip <= ntohl(sa.sin_addr.s_addr); ip++) {
        sa.sin_addr.s_addr = htonl(ip);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Błąd przy tworzeniu gniazda");
            return 1;
        }

        sa.sin_port = htons(port);
        if (connect(sockfd, (struct sockaddr *)&sa, sizeof(sa)) == 0) {
            printf("Host %s:%d jest dostępny.\n", inet_ntoa(sa.sin_addr), port);
        }

        close(sockfd);
    }

    return 0;
}

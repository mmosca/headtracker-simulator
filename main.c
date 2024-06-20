#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "msp-headtracker.h"

int main(int argc, char **argv)
{
    int port = 5761;
    char host[] = "localhost";

    struct addrinfo *info = NULL;;

    int ret = getaddrinfo(host, NULL, NULL, &info);

    if(ret != 0) {
        fprintf(stderr, "getad:drinfo: %s\n", gai_strerror(ret));
        return 1;
    }

    info->ai_addr->sa_family = AF_INET;
    ((struct sockaddr_in *)info->ai_addr)->sin_port = htons(port);

    do
    {

        int s = socket(AF_INET, SOCK_STREAM, 0);

        if (s < 0)
        {
            perror("socket");
            return 1;
        }

        ret = connect(s, info->ai_addr, info->ai_addrlen);

        freeaddrinfo(info);
        info = NULL;

        if (ret < 0)
        {
            perror("connect");
            goto done;
        }

        simulateHeadTracker(s);

done:
        close(s);
        sleep(1);

    } while (1);

    return 0;
}


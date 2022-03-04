# sockets_library_in_c
This a sockets helper lib
## Server side code(ex)
```c
#include "sockets_library_in_c/sockets.h" // if server is not in the repo folder
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void){
    SERVER server;
    int soc, opt = 1;
    char string[BUFFSIZE], old_string[BUFFSIZE];
    old_string[0] = '{';

    __server_init__(&server);
    server.create(&server, AF_INET, SOCK_STREAM, 0);
    server.set(&server, SOL_SOCKET, BOTH, opt, AF_INET, INADDR_ANY, 8080);
    server.bin(&server);
    server.lis(&server, 1);
    soc = server.acc(&server);

    while(1){
        server.r(&server, soc, string, BUFFSIZE);
        if(strcmp(string, "Disconnect") == 0){
            close(soc);
            return 0;
        }
        printf("%s\n", string);
    }
}
```
## Client side code
```c
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdint.h>
#include <unistd.h>
#include "sockets_library_in_c/sockets.h" // if client is not in the repo folder
#include <string.h>
#include <stdio.h>

int main(void){
    CLIENT client;
    char string[BUFFSIZE];

    __client_init__(&client);
    client.create(&client, AF_INET, SOCK_STREAM, 0);
    client.connect(&client, AF_INET, 8080, "127.0.0.1");

    while(1){
        printf("Message: ");
        scanf("%s", string);
        client.s(&client, client.fd, string, BUFFSIZE, 0);
        if(strcmp(string, "Disconnect") == 0){
            break;
        }
    }
}
```

## LICENSE
  
[apache 2.0](https://www.apache.org/licenses/LICENSE-2.0)
 
😃
 

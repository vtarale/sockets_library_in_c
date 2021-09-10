#ifndef COOLSTUFF
#define COOLSTUFF

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdint.h>
#include <unistd.h>

#define BUFFSIZE 1024

#define BOTH SO_REUSEADDR | SO_REUSEPORT
#define READDR SO_REUSEADDR
#define RERORT SO_REUSEPORT



typedef struct socklen_t SOCK_T;


struct server{
    int serverfd;
    struct sockaddr_in address;
    unsigned int address_length;
    int operation;
    int operation_length;

    int (*create)(struct server *self, int domain, int type, int protocal);
    int (*set)(struct server *self, int level, int opration_name, int operation_val,
               int family, uint32_t add, int port);
    int (*bin)(struct server *self);
    int (*lis)(struct server *self, int max_lis);
    int (*acc)(struct server *self);
    int (*r)(struct server *self, int fd, char *string, int nbytes);
    int (*s)(struct server *self, int fd, char *string, int nbytes, int flags);
};

struct client{
    int fd;
    struct sockaddr_in server_address;
    unsigned int server_address_length;

    int (*create)(struct client *self, int domain, int type, int protocal);
    int (*connect)(struct client *self, int family, int port, char address[BUFFSIZE]);
    int (*r)(struct client *self, int fd, char *string, int nbytes);
    int (*s)(struct client *self, int fd, char *string, int nbytes, int flags);
};


typedef struct server SERVER;
typedef struct client CLIENT;

 
int __server_init__(SERVER *self);
int __client_init__(CLIENT *self);

#endif
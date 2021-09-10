#include "sockets.h"


static int __server_create__(SERVER *self, int domain, int type, int protocal);
static int __server_set__(SERVER *self, int level, int opration_name, int operation_val,
                          int family, uint32_t add, int port);
static int __server_bin__(SERVER *self);
static int __server_lis__(SERVER *self, int max_lis);
static int __server_acc__(SERVER *self);
static int __client_create__(CLIENT *self, int domain, int type, int protocal);
static int __client_connect__(CLIENT *self, int family, int port,
                              char address[BUFFSIZE]);
static int __universal_read__(SERVER *self,int fd, char *string, int nbytes);
static int __universal_send__(SERVER *self, int fd, char *string, int nbytes, int flags);


int __server_init__(SERVER *self){
    self->create = (void *)&__server_create__;
    self->set = (void *)&__server_set__;
    self->bin = (void *)&__server_bin__;
    self->lis = (void *)&__server_lis__;
    self->acc = (void *)&__server_acc__;
    self->r = (void *)&__universal_read__;
    self->s = (void *)&__universal_send__;
}

int __client_init__(CLIENT *self){
    self->create = (void *)&__client_create__;
    self->connect = (void *)&__client_connect__;
    self->r = (void *)&__universal_read__;
    self->s = (void *)&__universal_send__;
}

static int __server_create__(SERVER *self, int domain, int type, int protocal){
    self->serverfd = socket(domain, type, protocal);
    self->address_length = sizeof(self->address);
}

static int __server_set__(SERVER *self, int level, int opration_name, int operation_val,
                   int family, uint32_t add, int port){
    setsockopt(self->serverfd, level, opration_name, &operation_val, sizeof(operation_val));
    self->address.sin_family = family;
    self->address.sin_addr.s_addr = add;
    self->address.sin_port = htons(port);
}

static int __server_bin__(SERVER *self){
    bind(self->serverfd, (struct sockaddr *)&self->address, self->address_length);
}

static int __server_lis__(SERVER *self, int max_lis){
    listen(self->serverfd, max_lis);
}

static int __server_acc__(SERVER *self){
    int new_socket = accept(self->serverfd, (struct sockaddr *)&self->address,
                            &self->address_length);
    return new_socket;
}

static int __client_create__(CLIENT *self, int domain, int type, int protocal){
    self->fd = socket(domain, type, protocal);
    self->server_address_length = sizeof(self->server_address);
}

static int __client_connect__(CLIENT *self, int family, int port,
                              char address[BUFFSIZE]){
    self->server_address.sin_family = family;
    self->server_address.sin_port = htons(port);
    inet_pton(family, address, &self->server_address.sin_addr);
    connect(self->fd, (struct sockaddr *)&self->server_address, self->server_address_length);
}

static int __universal_read__(SERVER *self,int fd, char *string, int nbytes){
    read(fd, string, nbytes);
}

static int __universal_send__(SERVER *self, int fd, char *string, int nbytes, int flags){
    send(fd, string, nbytes, flags);
}
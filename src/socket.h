#ifndef MCLIENT_CLI_SOCKET_H
#define MCLIENT_CLI_SOCKET_H

extern int sock;
extern int client_fd;

void sock_init(char *server_address);
void sock_send(char *message);
char *sock_recv();
void sock_close();

#endif

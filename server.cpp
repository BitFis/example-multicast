#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

int server() {
  // OPEN
  int fd = socket(AF_INET6, SOCK_DGRAM, 0);

  // BIND
  struct sockaddr_in6 address = {AF_INET6, htons(4321)};
  bind(fd, (struct sockaddr *)&address, sizeof(address));

  // JOIN MEMBERSHIP
  struct ipv6_mreq group;
  group.ipv6mr_interface = 0;
  inet_pton(AF_INET6, "ff12::1234", &group.ipv6mr_multiaddr);
  setsockopt(fd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, &group, sizeof group);

  printf(" server init %d\n", fd);

  return fd;
}

int client() {
  int fd = socket(AF_INET6, SOCK_DGRAM, 0);
  printf(" client init %d\n", fd);
  return fd;
}

ssize_t send(int fd, const char *msg) {
  if (fd < 0) {
    return 0;
  }

  // ADDRESS
  struct sockaddr_in6 address = {AF_INET6, htons(4321)};
  inet_pton(AF_INET6, "ff12::1234", &address.sin6_addr);

  // SEND TO
  char buffer[128];
  size_t len = strlen(msg);
  strcpy(buffer, msg);
  return sendto(fd, buffer, len, 0, (struct sockaddr *)&address,
                sizeof(address));
}

ssize_t read(int fd) {
  if (fd < 0) {
    return 0;
  }

  // READ
  char buffer[128] = {};
  auto readlen = read(fd, buffer, sizeof(buffer));

  printf("READ: %zu\n", readlen);
  for (int i = 0; i < readlen; i++) {
    printf(" %02X ", buffer[i]);
  }
  printf("\n");

  return readlen;
}

// 0 = disabled
// 1 = enabled
// 2 = default / skip
void setloopbackenabled(int fd, int opt) {
  if (fd < 0) {
    return;
  }
  if (opt > 1) {
    printf(" default loopback value %d\n", fd);
    return;
  }
  if (setsockopt(fd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &opt, sizeof(opt)) <
      0) {
    printf("setsockopt(IPV6_MULTICAST_LOOP) for %d failed, %s", fd,
           strerror(errno));
    printf(" set loopback value of %d to %d\n", fd, opt);
  }
}

int main(int argc, char *argv[]) {
  bool runserver = false;
  bool runclient = false;

  int serverloval = 0;
  int clientloval = 3;
  
  ssize_t serverFid = -1;
  int clientfd = -1;
  
  if (argc > 1) {
    printf("arg: %s\n", argv[1]);
    const char *arg1 = argv[1];

    if (strcmp(arg1, "server") == 0) {
      serverFid = server();
    }
    if (strcmp(arg1, "client") == 0) {
      clientfd = client();
    }
    if (strcmp(arg1, "both") == 0) {
      clientfd = serverFid = server();
    }
  }

  if (argc > 2) {
    if (strcmp(argv[2], "enabled") == 0) {
      serverloval = 1;
      clientloval = 1;
    }
    if (strcmp(argv[2], "disabled") == 0) {
      serverloval = 0;
      clientloval = 0;
    }
  }

  bool sent = false;

  setloopbackenabled(serverFid, serverloval);
  setloopbackenabled(clientfd, clientloval);

  send(clientfd, "hello");

  read(serverFid);

  return 0;
}

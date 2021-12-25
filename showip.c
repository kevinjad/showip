/* showip.c
 *
 * Copyright 2021 kevinjad
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written
 * authorization.
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void error_n_exit(char* msg){
  fprintf(stderr, "[FATAL] %s\n", msg);
  exit(-1);
}

int main(int argc, char* args[]){

  struct addrinfo hint, *res, *p; //p is for traversing the result
  int status;
  char ip[INET6_ADDRSTRLEN];

  memset (&hint, 0, sizeof (hint));
  hint.ai_family = AF_UNSPEC;
  hint.ai_socktype = SOCK_STREAM;

  if(argc < 2){
    error_n_exit ("Invalid Usage: Please provide a host address.");
  }

  if( (status = getaddrinfo ( args[1], NULL, &hint, &res)) != 0){
    error_n_exit ("getaddrinfo failed :(");
  }

  printf ("IP address for %s:\n", args[1]);
  for(p = res; p != NULL; p = p->ai_next){
    void* address;
    char* ip_version;
    if(p->ai_family == AF_INET){ //IPV4
      struct sockaddr_in* ipv4 = (struct sockaddr_in*) p->ai_addr;
      address = &(ipv4->sin_addr);
      ip_version = "IPv4";
    } else{ //IPv6
      struct sockaddr_in6* ipv6 = (struct sockaddr_in6*) p->ai_addr;
      address = &(ipv6->sin6_addr);
      ip_version = "IPv6";
    }

    inet_ntop (p->ai_family, address, ip, sizeof (ip));
    printf("%s: %s\n", ip_version, ip);
  }

  freeaddrinfo (res);
  return 0;
}

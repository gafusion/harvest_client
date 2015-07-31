#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
char harvest_table[50];
char harvest_host[100];
int  harvest_port=3200;
int  harvest_verbose=1;
int  harvest_sendline_n=65507;
char harvest_tag[255];
clock_t harvest_tic;
clock_t harvest_toc;

//Get ip from domain name
int hostname_to_ip(char * hostname , char* ip){
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL){
        // get the host info
        strcpy(ip , "127.0.0.1" );
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++){
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 1;
}

int print_storage(char *harvest_sendline){
  printf("[%3.3f%%] ",(float)100*strlen(harvest_sendline)/harvest_sendline_n);
  return 0;
}

//verbosity
int set_harvest_verbose(int verbose){
  harvest_verbose=verbose;
  return 0;
}

int set_harvest_verbose_(int *verbose){
  int verbose_ = *verbose;
  set_harvest_verbose(verbose_);
  return 0;
}

//payload string
int set_harvest_payload_str_base(char *harvest_sendline, char *what, char *data, char *prepend){
  sprintf(harvest_sendline,"%s|%s@%s=%s",harvest_sendline,prepend,what,data);
  if (harvest_verbose){
    print_storage(harvest_sendline);
    printf("s@%s=%s\n",what,data);
  }
  return 0;
}

int set_harvest_payload_str(char *harvest_sendline, char *what, char *data){
  set_harvest_payload_str_base(harvest_sendline,what,data,"s");
  return 0;
}

int set_harvest_payload_str_(char *harvest_sendline, char *what, char *data){
  set_harvest_payload_str_base(harvest_sendline,what,data,"s");
  return 0;
}

//payload namelist
int set_harvest_payload_nam(char *harvest_sendline, char *what, char *data){
  set_harvest_payload_str_base(harvest_sendline,what,data,"n");
  return 0;
}

int set_harvest_payload_nam_(char *harvest_sendline, char *what, char *data){
  set_harvest_payload_str_base(harvest_sendline,what,data,"n");
  return 0;
}

//payload int
int set_harvest_payload_int(char *harvest_sendline, char *what, int data){
  sprintf(harvest_sendline,"%s|i@%s=%d",harvest_sendline,what,data);
  if (harvest_verbose){
    print_storage(harvest_sendline);
    printf("i@%s=%d\n",what,data);
  }
  return 0;
}

int set_harvest_payload_int_(char *harvest_sendline, char *what, int *data){
  int data_ = *data;
  set_harvest_payload_int(harvest_sendline,what,data_);
  return 0;
}

//payload switch (0-255)
int set_harvest_payload_swt(char *harvest_sendline, char *what, int data){
  sprintf(harvest_sendline,"%s|t@%s=%d",harvest_sendline,what,data);
  if (harvest_verbose){
    print_storage(harvest_sendline);
    printf("i@%s=%d\n",what,data);
  }
  return 0;
}

int set_harvest_payload_swt_(char *harvest_sendline, char *what, int *data){
  int data_ = *data;
  set_harvest_payload_swt(harvest_sendline,what,data_);
  return 0;
}

////payload float
int set_harvest_payload_flt(char *harvest_sendline, char *what, double data){
  sprintf(harvest_sendline,"%s|f@%s=%g",harvest_sendline,what,(float) data);
  if (harvest_verbose){
    print_storage(harvest_sendline);
    printf("f@%s=%g\n",what,(float) data);
  }
  return 0;
}

int set_harvest_payload_flt_(char *harvest_sendline, char *what, float *data){
  float data_ = *data;
  set_harvest_payload_flt(harvest_sendline,what,data_);
  return 0;
}

////payload double
int set_harvest_payload_dbl(char *harvest_sendline, char *what, double data){
  sprintf(harvest_sendline,"%s|f@%s=%g",harvest_sendline,what,data);
  if (harvest_verbose){
    print_storage(harvest_sendline);
    printf("f@%s=%g\n",what,data);
  }
  return 0;
}

int set_harvest_payload_dbl_(char *harvest_sendline, char *what, double *data){
  double data_ = *data;
  set_harvest_payload_dbl(harvest_sendline,what,data_);
  return 0;
}

////payload boolean
int set_harvest_payload_bol(char *harvest_sendline, char *what, int data){
  sprintf(harvest_sendline,"%s|b@%s=%d",harvest_sendline,what,data);
  if (harvest_verbose){
    print_storage(harvest_sendline);
    printf("b@%s=%d\n",what,data!=0);
  }
  return 0;
}

int set_harvest_payload_bol_(char *harvest_sendline, char *what, int *data){
  int data_ = *data;
  set_harvest_payload_bol(harvest_sendline,what,data_);
  return 0;
}

//host
int set_harvest_host(char *host){
  sprintf(harvest_host,"%s",host);
  return 0;
}

int set_harvest_host_(char *host){
  set_harvest_host(host);
  return 0;
}

//tag
int set_harvest_tag(char *tag){
  sprintf(harvest_tag,"%s",tag);
  return 0;
}

int set_harvest_tag_(char *tag){
  set_harvest_tag(tag);
  return 0;
}

//port
int set_harvest_port(int port){
  harvest_port=port;
  return 0;
}

int set_harvest_port_(int *port){
  int port_ = *port;
  set_harvest_port(port_);
  return 0;
}

//table
int set_harvest_table(char *table){
  sprintf(harvest_table,"%s",table);
  return 0;
}

int set_harvest_table_(char *table){
  set_harvest_table(table);
  return 0;
}

//init
int init_harvest(char *table, char *harvest_sendline, int n){
  harvest_tic=clock();

  set_harvest_host("gadb-harvest.ddns.net");
  if (getenv("HARVEST_HOST")!=NULL)
    set_harvest_host(getenv("HARVEST_HOST"));

  set_harvest_port(32000);
  if (getenv("HARVEST_PORT")!=NULL)
    set_harvest_port(atoi(getenv("HARVEST_PORT")));

  set_harvest_verbose(0);
  if (getenv("HARVEST_VERBOSE")!=NULL)
    set_harvest_verbose(atoi(getenv("HARVEST_VERBOSE")));

  set_harvest_tag("");
  if (getenv("HARVEST_TAG")!=NULL)
    set_harvest_tag(getenv("HARVEST_TAG"));

  set_harvest_table(table);

  harvest_sendline_n=n;
  memset(harvest_sendline, 0, harvest_sendline_n);

  if (harvest_verbose)
    printf("===HARVEST starts===\n");
  return 0;
}

int init_harvest_(char *table, char *harvest_sendline, int *n){
  int n_ = *n;
  init_harvest(table,harvest_sendline,n_);
  return 0;
}

//send
int harvest_send(char* harvest_sendline){
  int sockfd;
  int version;
  struct sockaddr_in servaddr,cliaddr;
  char sendline[harvest_sendline_n]; //max UDP message size
  char harvest_ip[15];
  char hostname[128];

  version=3;

  hostname_to_ip(harvest_host, harvest_ip);
  gethostname(hostname, sizeof hostname);

  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=inet_addr(harvest_ip);
  servaddr.sin_port=htons(harvest_port);

  sprintf(sendline,"%d",version);
  sprintf(sendline,"%s:%s",sendline,harvest_table);
  sprintf(sendline,"%s:s@_user=%s",sendline,getenv("USER"));
  sprintf(sendline,"%s|s@_hostname=%s",sendline,hostname);
  sprintf(sendline,"%s|s@_workdir=%s",sendline,getenv("PWD"));
  sprintf(sendline,"%s|s@_tag=%s",sendline,getenv(harvest_tag));
  sprintf(sendline,"%s|s@_tag=%s",sendline,harvest_sendline);
  memset(harvest_sendline, 0, harvest_sendline_n);
  sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));

  harvest_toc=clock();
  if (harvest_verbose){
    printf("%s:%d --> %s\n",harvest_ip,harvest_port,sendline);
    printf("===HARVEST ends=== (%3.3f ms)\n",(double)(harvest_toc - harvest_tic) / CLOCKS_PER_SEC * 1E3);
  }
  return 0;
}

int harvest_send_(char* harvest_sendline){
  harvest_send(harvest_sendline);
  return 0;
}

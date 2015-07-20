#include <stdio.h>
#include "send2DB.h"

int main(int argc, char**argv){

  set_harvest_verbose(1);

  char harvest_sendline[65507]; //max UDP message size

  init_harvest("test_omfit?10",harvest_sendline,sizeof(harvest_sendline));
  set_harvest_verbose(1);

  set_harvest_payload_str(harvest_sendline,"str","C");
  set_harvest_payload_int(harvest_sendline,"int",5);
  set_harvest_payload_swt(harvest_sendline,"swt",5);
  set_harvest_payload_bol(harvest_sendline,"bol",1);
  set_harvest_payload_flt(harvest_sendline,"flt",(float) 5.4);
  set_harvest_payload_dbl(harvest_sendline,"dbl",(double) 5.5);
  set_harvest_payload_bol(harvest_sendline,"+ctrl",1);

  harvest_send(harvest_sendline);
}


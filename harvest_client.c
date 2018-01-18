#include <stdio.h>
#include "harvest_lib.h"

int main(int argc, char**argv){

  set_harvest_verbose(1);

  char harvest_sendline[65507];
  double array[9]={10., 23., 42., 1., 654., 0., 40652., 22., 0.};

  init_harvest("",harvest_sendline,sizeof(harvest_sendline));
  set_harvest_verbose(1);
  set_harvest_protocol("UDP");

  set_harvest_payload_str(harvest_sendline,"str","C");
  set_harvest_payload_int(harvest_sendline,"int",5);
  set_harvest_payload_swt(harvest_sendline,"swt",5);
  set_harvest_payload_bol(harvest_sendline,"bol",1);
  set_harvest_payload_flt(harvest_sendline,"flt",(float) 5.4);
  set_harvest_payload_dbl(harvest_sendline,"dbl",(double) 5.5);
  set_harvest_payload_bol(harvest_sendline,"+ctrl",1);
  set_harvest_payload_dbl_array(harvest_sendline,"arr",array,9);

  harvest_send(harvest_sendline);
}


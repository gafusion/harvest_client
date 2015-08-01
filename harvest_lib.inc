  INTERFACE
   FUNCTION set_harvest_verbose(verbose)
     INTEGER set_harvest_verbose
     INTEGER :: verbose
   END FUNCTION set_harvest_verbose
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_str(harvest_sendline, what, data)
     INTEGER set_harvest_payload_str
     CHARACTER :: harvest_sendline, what
     CHARACTER :: data
   END FUNCTION set_harvest_payload_str
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_nam(harvest_sendline, what, data)
     INTEGER set_harvest_payload_nam
     CHARACTER :: harvest_sendline, what
     CHARACTER :: data
   END FUNCTION set_harvest_payload_nam
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_int(harvest_sendline, what, data)
     INTEGER set_harvest_payload_int
     CHARACTER :: harvest_sendline, what
     INTEGER data
   END FUNCTION set_harvest_payload_int
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_swt(harvest_sendline, what, data)
     INTEGER set_harvest_payload_swt
     CHARACTER :: harvest_sendline, what
     INTEGER data
   END FUNCTION set_harvest_payload_swt
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_flt(harvest_sendline, what, data)
     INTEGER set_harvest_payload_flt
     CHARACTER :: harvest_sendline, what
     REAL*4 data
   END FUNCTION set_harvest_payload_flt
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_flt_array(harvest_sendline, what, data, len)
     INTEGER set_harvest_payload_flt_array
     CHARACTER :: harvest_sendline, what
     REAL*4 data(:)
     INTEGER len
   END FUNCTION set_harvest_payload_flt_array
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_dbl(harvest_sendline, what, data)
     INTEGER set_harvest_payload_dbl
     CHARACTER :: harvest_sendline, what
     REAL*8 data
   END FUNCTION set_harvest_payload_dbl
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_dbl_array(harvest_sendline, what, data, len)
     INTEGER set_harvest_payload_dbl_array
     CHARACTER :: harvest_sendline, what
     REAL*8 data(:)
     INTEGER len
   END FUNCTION set_harvest_payload_dbl_array
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_payload_bol(harvest_sendline, what, data)
     INTEGER set_harvest_payload_bol
     CHARACTER :: harvest_sendline, what
     LOGICAL data
   END FUNCTION set_harvest_payload_bol
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_host(harvest_host)
     INTEGER set_harvest_host
     CHARACTER :: harvest_host
   END FUNCTION set_harvest_host
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_port(harvest_port)
     INTEGER set_harvest_port
     INTEGER :: harvest_port
   END FUNCTION set_harvest_port
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_tag(tag)
     INTEGER set_harvest_tag
     CHARACTER :: tag
   END FUNCTION set_harvest_tag
  END INTERFACE

  INTERFACE
   FUNCTION set_harvest_table(table)
     INTEGER set_harvest_table
     CHARACTER :: table
   END FUNCTION set_harvest_table
  END INTERFACE

  INTERFACE
   FUNCTION init_harvest(table, harvest_sendline, n)
     INTEGER init_harvest
     CHARACTER :: table, harvest_sendline
     INTEGER n
   END FUNCTION init_harvest
  END INTERFACE

  INTERFACE
  FUNCTION harvest_send(harvest_sendline)
     INTEGER harvest_send
     CHARACTER :: harvest_sendline
   END FUNCTION harvest_send
  END INTERFACE
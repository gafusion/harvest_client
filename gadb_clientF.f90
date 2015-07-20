program f_call_c

  CHARACTER(LEN=65507) :: harvest_sendline
  CHARACTER  NUL
  PARAMETER (NUL = CHAR(0))

  ierr=init_harvest('test_omfit?'//NUL,harvest_sendline,LEN(harvest_sendline))
  ierr=set_harvest_verbose(1)

  ierr=set_harvest_payload_str(harvest_sendline,'str'//NUL,'F'//NUL)
  ierr=set_harvest_payload_int(harvest_sendline,'int'//NUL,5)
  ierr=set_harvest_payload_swt(harvest_sendline,'swt'//NUL,5)
  ierr=set_harvest_payload_flt(harvest_sendline,'flt'//NUL,5.5)
  ierr=set_harvest_payload_dbl(harvest_sendline,'dbl'//NUL,5.5D+0)
  ierr=set_harvest_payload_bol(harvest_sendline,'bol'//NUL,.True.)
  ierr=set_harvest_payload_bol(harvest_sendline,'+ctrl'//NUL,.True.)

  ierr=harvest_send(harvest_sendline)

end program f_call_c

program f_call_c

  CHARACTER(LEN=65507) :: harvest_sendline
  CHARACTER  NUL
  PARAMETER (NUL = CHAR(0))

  CHARACTER(LEN=50000) :: namelist_str
  INTEGER :: i1, i2, i3, ierr
  REAL :: r1, r2, r3, arr1(2,4)
  NAMELIST/inputs/i1, i2, i3, r1, r2, r3, arr1
  i1 = 1
  i2 = 2
  i3 = 3
  r1 = 1.
  r2 = 2.
  r3 = 3.
  arr1(1,1) = 1
  arr1(2,1) = 2
  arr1(1,2) = 3
  arr1(2,2) = 4
  write(namelist_str,nml=inputs)
  write(namelist_str,*) TRIM(namelist_str),NUL

  ierr=init_harvest('test_harvest?'//NUL,harvest_sendline,LEN(harvest_sendline))
  ierr=set_harvest_verbose(1)

  ierr=set_harvest_payload_str(harvest_sendline,'str'//NUL,'F'//NUL)
  ierr=set_harvest_payload_int(harvest_sendline,'int'//NUL,5)
  ierr=set_harvest_payload_swt(harvest_sendline,'swt'//NUL,5)
  ierr=set_harvest_payload_flt(harvest_sendline,'flt'//NUL,5.5)
  ierr=set_harvest_payload_dbl(harvest_sendline,'dbl'//NUL,5.5D+0)
  ierr=set_harvest_payload_bol(harvest_sendline,'bol'//NUL,.True.)
  ierr=set_harvest_payload_bol(harvest_sendline,'+ctrl'//NUL,.True.)
  ierr=set_harvest_payload_nam(harvest_sendline,'nam'//NUL,namelist_str)

  ierr=set_harvest_host('localhost')
  ierr=harvest_send(harvest_sendline)

end program f_call_c

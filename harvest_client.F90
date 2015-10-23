program havest_clientF
  IMPLICIT NONE
  INCLUDE 'harvest_lib.inc' !this is not necessary if INCLUDE NONE is not there
  CHARACTER(LEN=65507) :: harvest_sendline
  CHARACTER  NUL
  PARAMETER (NUL = CHAR(0))

  CHARACTER(LEN=50000) :: namelist_str
  CHARACTER(LEN=10) hello
  INTEGER :: i1, i2, i3, ierr
  REAL :: r1, r2, r3, arr1(2,4)
  REAL, DIMENSION(10) :: F
  double precision, DIMENSION(10) :: D
  NAMELIST/inputs/i1, i2, i3, r1, r2, r3, hello, arr1

  F = (/ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 /)
  D = (/ 1D0, 2D0, 3D0, 4D0, 5D0, 6D0, 7D0, 8D0, 9D0, 1D1 /)

  i1 = 1
  i2 = 2
  i3 = 3
  r1 = 1.0
  r2 = 2.0
  r3 = 3.0
  arr1=0.0
  arr1(1,1) = 1.0
  arr1(2,1) = 2.0
  arr1(1,2) = 3.0
  arr1(2,2) = 4.0
  hello = 'hello'

#ifndef __INTEL_COMPILER

  write(namelist_str,nml=inputs)
  write(namelist_str,*) TRIM(namelist_str),NUL
  
#endif

  ierr=init_harvest('test_harvest'//NUL,harvest_sendline,LEN(harvest_sendline))
  ierr=set_harvest_verbose(1)
  ierr=set_harvest_protocol('UDP'//NUL)

  ierr=set_harvest_payload_str(harvest_sendline,'str'//NUL,'F'//NUL)
  ierr=set_harvest_payload_int(harvest_sendline,'int'//NUL,5)
  ierr=set_harvest_payload_swt(harvest_sendline,'swt'//NUL,5)
  ierr=set_harvest_payload_flt(harvest_sendline,'flt'//NUL,5.5)
  ierr=set_harvest_payload_dbl(harvest_sendline,'dbl'//NUL,5.5D0)
  ierr=set_harvest_payload_bol(harvest_sendline,'bol'//NUL,.True.)
  ierr=set_harvest_payload_bol(harvest_sendline,'+ctrl'//NUL,.True.)
  ierr=set_harvest_payload_flt_array(harvest_sendline,'farr'//NUL,F,SIZE(F))
  ierr=set_harvest_payload_dbl_array(harvest_sendline,'darr'//NUL,D,SIZE(D))
#ifndef __INTEL_COMPILER
  ierr=set_harvest_payload_nam(harvest_sendline,'nam'//NUL,namelist_str)
#endif

  ierr=harvest_send(harvest_sendline)

end program havest_clientF

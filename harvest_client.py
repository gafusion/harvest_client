#!/usr/bin/env python

from harvest_lib import *
from numpy.random import *

if False:
    data={}
    data['str']='PY'
    data['int']=5
    data['swt']=5
    data['flt']=5.8
    data['dbl']=5.5
    data['bol']=True
    data['+ctrl']=0.6
    data['_tag']=''

    for k in range(100):
        #data['+ctrl'+str(k)]=randn()
        data['dbl']=randn()
        data['flt']=randn()*10
        harvest_send(data,'test_harvest?',verbose=True)

else:
    data=harvest_nc('eped.nc',verbose=True)
    harvest_send(data,'test_harvest?',verbose=True)
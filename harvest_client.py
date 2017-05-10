#!/usr/bin/env python

from harvest_lib import *
from numpy.random import *

if True:
    data={}
    data['str']='PY'
    data['int']=5
    data['swt']=5
    data['flt']=5.8
    data['dbl']=5.5
    data['bol']=True
    data['+ctrl']=0.6
    data['_tag']='test'

    for k in range(3):
        #data['+ctrl'+str(k)]=randn()
        data['dbl']=randn()
        data['flt']=randn()*10
        harvest_send(data,'test_harvest',verbose=True,host='localhost',protocol='TCP',port=41000)

else:
    data=harvest_nc('eped.nc',verbose=True)
    harvest_send(data,'test_harvest',verbose=True,protocol='TCP',host='localhost')
#!/usr/bin/env python

def _data_2_message(payload):
    import numpy
    import re
    def formatter(data):
        data=('%g'%data)
        if '.' in data:
            data=data.lstrip('0')
        data=re.sub('e\-0+','e-',data)
        data=re.sub('e\+0+','e+',data)
        return data
    def compress(tmps):
        return tmps
        tmpsc=[]
        c=-1
        kold=tmps[0]
        for k in tmps+[tmps[-1]+' ']:
            if kold==k:
                c+=1
            else:
                if c==0:
                    tmpsc.append(kold)
                else:
                    tmpsc.append(str(c+1)+'*'+kold)
                kold=k
                c=0
        return tmpsc

    message=[]
    for what in payload.keys():
        data=payload[what]
        if isinstance(data,bool):
            tp='b'
            data=str(int(data))
        elif isinstance(data,(list,tuple,numpy.ndarray)):
            tp='a'
            data=re.sub(' ','','['+','.join(compress(map(formatter,numpy.atleast_1d(data).flatten().tolist())))+']' )
        elif numpy.array(data).dtype.kind=='i':
            tp='i'
            data=str(data)
        elif numpy.array(data).dtype.kind=='f':
            tp='f'
            data=formatter(data)
        elif isinstance(data,basestring):
            tp='s'
            data=repr(data.strip())
        else:
            raise(Exception('%s objects of type %s are not supported'%(what,type(data))))
        message.append(tp+'@'+what+'='+data)

    return '|'.join(message)

def harvest_send(payload, table='test_harvest', host=None, port=None, verbose=None):
    '''
    Function to send data to the harvesting server

    :param payload: dictionary

    :param table: table where to put the data

    :param host: harvesting server address
    If None take value from `HARVEST_HOST` environemental variable, or use default `gadb-harvest.ddns.net` if not set.

    :param port: port the harvesting server is listening on.
    If None take value from `HARVEST_PORT` environemental variable, or use default `0` if not set.

    :param verbose: print harvest message to screen
    If None take value from `HARVEST_VERBOSE` environemental variable, or use default `False` if not set.

    :return: tuple with used (host, port, message)
    '''
    import os,socket,copy,random

    version=3

    if host is None:
        host='gadb-harvest.ddns.net'
        if 'HARVEST_HOST' in os.environ:
            host=os.environ['HARVEST_HOST']

    if port is None:
        port=32000
        if 'HARVEST_PORT' in os.environ:
            port=int(os.environ['HARVEST_PORT'])

    if verbose is None:
        verbose=int('0')
        if 'HARVEST_VERBOSE' in os.environ:
            verbose=int(os.environ['HARVEST_VERBOSE'])

    payload=copy.deepcopy(payload)
    payload['_user']=os.environ['USER']
    payload['_hostname']=socket.gethostname()
    payload['_workdir']=os.getcwd()

    MTU=1400
    message = "%d:%s:%s"%(version,table,_data_2_message(payload))

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    if len(message)<MTU:
        sock.sendto(message, (host,port))
        if verbose:
            print("%s:%d -[%3.3f]-> %s"%(host,port,len(message)*1./MTU,message))
    else:
        split_message=[message[x:x+MTU] for x in range(0,len(message),MTU)]
        ID=random.randint(0,999999)
        for k,message in enumerate(split_message):
            message = "&%d&%d&%d&%s"%(ID,k,len(split_message),message)
            sock.sendto(message, (host,port))
            if verbose:
                print("%s:%d -[%3.3f]-> %s"%(host,port,len(message)*1./MTU,message))

    return (host,port,message)

def harvest_nc(filename, entries=None, verbose=False):
    '''
    Function that returns data contained in a NetCDF3 file to be sent by harvest_send

    :param filename: NetCDF3 file

    :param entries: subset of variables to loof for in the NetCDF file

    :param verbose: print payload

    :return: payload dictionary
    '''
    import os,netCDF4

    payload={}
    payload['harvest_filename']=os.path.abspath(filename)

    nc = netCDF4.Dataset(filename,'r',format='NETCDF3_CLASSIC')
    if entries is None:
        entries=nc.variables.keys()
    for entry in entries:
        if entry in nc.variables.keys():
            try:
                value=nc.variables[entry].getValue()[0]
            except Exception:
                value=nc.variables[entry][:]
            if len(value)==1:
                payload[entry]=value[0]
            else:
                payload[entry]=value
            if verbose:
                print(str(entry), value[0])
    nc.close()

    return payload
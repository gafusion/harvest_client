#!/usr/bin/env python

def _data_2_message(payload):
    import numpy

    message=[]
    for what in payload.keys():
        data=payload[what]
        if isinstance(data,bool):
            tp='b'
            data=int(data)
        elif numpy.array(data).dtype.kind=='i':
            tp='i'
        elif numpy.array(data).dtype.kind=='f':
            tp='f'
        elif isinstance(data,(list,tuple,numpy.ndarray)):
            tp='a'
            data=numpy.atleast_1d(data).flatten().tolist()
        elif isinstance(data,basestring):
            tp='s'
            data=data.strip()
        else:
            raise(Exception('%s objects of type %s are not supported'%(what,type(data))))
        message.append(tp+'@'+what+'='+repr(data))

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
    import os,socket,copy

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

    message = "%d:%s:"%(version,table) + _data_2_message(payload)

    if verbose:
        print("%s:%d --> %s"%(host,port,message))

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(message, (host,port))

    return (host,port,message)

def harvest_nc(filename, entries=None, verbose=False):
    '''
    Function that returns 0d data contained in a netcdf file to be sent by harvest_send

    :param filename: nectdf3 file

    :param entries: subset of variables to loof for in the NetCDF file

    :param verbose: print payload

    :return: payload
    '''
    import netCDF4
    
    nc = netCDF4.Dataset(filename,'r',format='NETCDF3_CLASSIC')

    payload={}

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
                if verbose:
                    print(str(entry), value[0])

    nc.close()

    return payload
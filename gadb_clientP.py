#!/usr/bin/env python

def harvest_send(payload, table='test_omfit', host=None, port=None, verbose=None):
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

    version=2

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

    message = ["%d:%s:"%(version,table)]
    for what in payload.keys():
        data=payload[what]
        if isinstance(payload[what],bool):
            tp='b'
            data=int(data)
        elif isinstance(payload[what],int):
            tp='i'
        elif isinstance(payload[what],float):
            tp='f'
        else:
            tp='s'
        message.append(tp+'@'+what+'='+str(data))
    message=message[0]+','.join(message[1:])

    if verbose:
        print("%s:%d --> %s"%(host,port,message))

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(message, (host,port))

    return (host,port,message)

def harvest_nc(filename,table='test_omfit', entries=None, host=None, port=None, verbose=None):
    '''
    Function to send 0d data contained in a netcdf file to the harvesting server

    :param filename: nectdf3 file

    :param table: table where to put the data

    :param host: harvesting server address
    If None take value from `HARVEST_HOST` environemental variable, or use default `gadb-harvest.ddns.net` if not set.

    :param port: port the harvesting server is listening on.
    If None take value from `HARVEST_PORT` environemental variable, or use default `0` if not set.

    :param verbose: print harvest message to screen
    If None take value from `HARVEST_VERBOSE` environemental variable, or use default `False` if not set.

    :return: tuple with used (host, port, message)
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

    return harvest_send(payload, table=table, host=host, port=port, verbose=verbose)
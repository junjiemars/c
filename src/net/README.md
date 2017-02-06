# Networking

## Build on Linux
**getaddrinfo()** is a POSIX.1g extension and is not available in pure C99, 
so We need **-D_GNU_SOURCE** if **-std=c99** existings (see [c99 does not define getaddrinfo](https://github.com/droe/sslsplit/issues/2)).


## References


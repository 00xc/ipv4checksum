# ipv4checksum #
Fast Python 3 module to compute an [IPv4 checksum](https://tools.ietf.org/html/rfc1071#section-4).

### Setup ###
`$ git clone https://github.com/00xc/ipv4checksum.git`\
`$ cd ipv4checksum && pip3 install .`

### Usage ###
```Python
import ipv4checksum

data = b"Some random bytes"
print(hex(ipv4checksum.checksum(data)))
```
Result:\
`0xdba1`
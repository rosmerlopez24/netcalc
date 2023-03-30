# Netcalc - Network Calculator
It is a small program written in C++ as a tool for my use, and as a systems engineering student I also wanted to learn how to create my own tools.

# Usage
```bash
$ netcalc --help
Usage: netcalc [--help] [--version] address

Utility that calculates network address, netmask, network, broadcast, etc by given IP Address with CIRD Notation.

Positional arguments:
  address      	ip address with cird notation, example: 192.168.100.1/24 

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 

Written by Rosmer Lopez
```

```bash
$ netcalc 192.168.100.1/24
+-------------+------------------+-------------------------------------+
|   Address   | 192.168.100.1    | 11000000.10101000.01100100.00000001 |
+-------------+------------------+-------------------------------------+
|   Netmask   | 255.255.255.0    | 11111111.11111111.11111111.00000000 |
+-------------+------------------+-------------------------------------+
|   Network   | 192.168.100.0/24 | 11000000.10101000.01100100.00000000 |
+-------------+------------------+-------------------------------------+
|  Broadcast  | 192.168.100.255  | 11000000.10101000.01100100.11111111 |
+-------------+------------------+-------------------------------------+
| Start range | 192.168.100.1    | 11000000.10101000.01100100.00000001 |
+-------------+------------------+-------------------------------------+
|  End range  | 192.168.100.254  | 11000000.10101000.01100100.11111110 |
+-------------+------------------+-------------------------------------+
|    Hosts    | 254              |                                     |
+-------------+------------------+-------------------------------------+
```

# Librarys
This program makes use of the following third party libraries.
- [Argparse](https://github.com/p-ranav/argparse)
- [Asio](https://github.com/chriskohlhoff/asio)
- [Tabulate](https://github.com/p-ranav/tabulate)

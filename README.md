Simple-Web-Server [![Build Status](https://travis-ci.org/eidheim/Simple-Web-Server.svg?branch=master)](https://travis-ci.org/eidheim/Simple-Web-Server)
=================

A very simple, fast, multithreaded, platform independent HTTP and HTTPS server and client library implemented using C++11 and Boost.Asio. Created to be an easy way to make REST resources available from C++ applications. 

See https://github.com/eidheim/Simple-WebSocket-Server for an easy way to make WebSocket/WebSocket Secure endpoints in C++. Also, feel free to check out the new C++ IDE supporting C++11/14/17: https://github.com/cppit/jucipp. 

### Features

* Asynchronous request handling
* Thread pool if needed
* Platform independent
* HTTPS support
* HTTP persistent connection (for HTTP/1.1)
* Client supports chunked transfer encoding
* Timeouts, if any of Server::timeout_request and Server::timeout_content are >0 (default: Server::timeout_request=5 seconds, and Server::timeout_content=300 seconds)
* Simple way to add REST resources using regex for path, and anonymous functions

###Usage

See http_examples.cpp or https_examples.cpp for example usage. 

See particularly the JSON-POST (using Boost.PropertyTree) and the GET /match/[number] examples, which are most relevant.

### Dependencies

* Boost C++ libraries
* For HTTPS: OpenSSL libraries 

### Compile and run

Compile with a C++11 compliant compiler:
```
cmake .
make
```

#### HTTP

Run the server and client examples: `./http_examples`

Direct your favorite browser to for instance http://localhost:8080/

#### HTTPS

Before running the server, an RSA private key (server.key) and an SSL certificate (server.crt) must be created. Follow, for instance, the instructions given here (for a self-signed certificate): http://www.akadia.com/services/ssh_test_certificate.html

Run the server and client examples: `./https_examples`

Direct your favorite browser to for instance https://localhost:8080/

## AWS Install
```
#boost:
sudo apt-get install libboost-all-dev

#ssl:
sudo apt-get install libssl-dev

#C++: (gcc doesn't handle C++ on Ubuntu by default)
sudo apt-get install gcc g++

#cmake: (was already installed - so remove and install)
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get remove cmake
sudo apt-get install cmake
sudo apt-get upgrade

#clone the repo:
git clone https://github.com/tzaffi/Simple-Web-Server.git

#compile with cmake and make:
cd Simple-Web-Server
cmake .
make

#make a local log directory (for the Ubuntu branch):
mkdir ~/log

#run the binary:
./jsonEchoAndLog &

#view the logs
cd ..
ls log
```


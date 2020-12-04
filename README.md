# Energy Grid of Things - Distributed Control System

## Debian Buster (OS)_
The requirements are:

* CMake 3.16 or better;
* A C++11 compatible compiler
* Boost Libraries
* Git

```bash
sudo apt-get update -y \
  && apt-get install -y build-essential wget git cmake pkg-config libboost-all-dev libssl-dev libmodbus-dev \
  && mkdir ~/temp
cd ~/temp && wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz \
  && tar -xf cmake-3.18.4.tar.gz \
  && cd cmake-3.18.4 && ./boostrap && make && sudo make install
sudo rm -rf ~/temp
```

To configure (must be done first):

```bash
mkdir ~/Dev && cd ~/Dev && git clone https://github.com/EGoT-DCS-SunSpec-Modbus/EGoT-DCS
cd EGoT-DCS && cmake -S . -B build
```

To build:

```bash
cmake --build build
```

To test:

```bash
./build/tests/all-tests
```

To run:

```bash
./build/src/app
```
## Docker
If you wish to develop on a different system that has docker installed I have provided a dockerfile to setup the same development environment within a container. 

To build:
``` bash
docker build -f Dockerfile.buster -t egot-dcs .
```

To run tests:

```bash
docker container run -i egot-dcs
```

To run app:

```bash
docker container run -i egot-dcs ./build/src/app
```

To run and attach terminal for troubleshooting:

```bash
docker container run -it egot-dcs /bin/bash
```

To cleanup all docker containers, images, and volumnes that are unused:

```bash
docker system prune -a
```

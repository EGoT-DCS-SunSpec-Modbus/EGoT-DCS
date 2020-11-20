# SunSpec-ModBus

## Debian Buster (OS)_
The requirements are:

* CMake 3.16 or better;
* A C++11 compatible compiler
* Boost Libraries
* Git

```bash
sudo apt-get update -y \
  && apt-get install -y build-essential git cmake libboost-all-dev libssl-dev \
  && mkdir ~/temp
cd ~/temp && wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz \
  && tar -xf cmake-3.18.4.tar.gz \
  && cd cmake-3.18.4 && ./boostrap && make && sudo make install
cd ~/temp && git clone https://github.com/apache/xerces-c && cd xerces-c \
  && cmake -S . -B build && cmake --build build && make -C build && sudo make -C build install
sudo rm -rf ~/temp
```

To configure (must be done first):

```bash
mkdir ~/Dev && cd ~/Dev && git clone https://github.com/psu-powerlab/cpp-seed
cd cpp-seed && cmake -S . -B build
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
docker build -f Dockerfile.buster -t cppseed .
```

To run tests:

```bash
docker container run -i cppseed
```

To run app:

```bash
docker container run -i cppseed ./build/src/app
```

To run and attach terminal for troubleshooting:

```bash
docker container run -it cppseed /bin/bash
```

To cleanup all docker containers, images, and volumnes that are unused:

```bash
docker system prune -a
```

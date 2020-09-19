# simple-distributed-system

```
A simple simulation of a distributed system with three nodes passing messages using
Google Protocol Buffers and libzmq. We assume that the nodes are on different machines,
but for the sake of this demo, we are only using a localhost.
```

### Compile and build instructions.

```
mkdir build
cd build
cmake ..
cmake --build .
./demo
```

### Dependencies

```
libzmq
Google Protobuf
```

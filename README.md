# simple-distributed-system
A simple simulation of a distributed system with three nodes passing messages using
Google Protocol Buffers. We assume that the nodes are on different machines, but for
the sake of this demo, we are only using a localhost.

Compile and build instructions.

[1] mkdir build
[2] cd build
[3] cmake ..
[4] cmake --build .
[5] execute demo e.g ./demo

Make sure you have all the dependencies needed.
[1] libzmq
[2] Google Protobuf compiler

#include <iostream>
#include <zmq.h>
#include <cassert>
#include <unistd.h>

int main()
{
    std::cout << "Server node" << std::endl;

    void *ctx = zmq_ctx_new();
    void *rep = zmq_socket(ctx, ZMQ_REP); // socket to wait for requestor node
    void *db = zmq_socket(ctx, ZMQ_REQ); // socket to connect to database node

    assert(zmq_bind(rep, "tcp://*:5600") == 0); // bind listener socket

    zmq_connect(db, "tcp://localhost:5601"); // connect to database node

    for(;;)
    {
        char buffer[256] = {0};
        zmq_recv(rep, buffer, 256, 0);

        std::cout << "Sending to database..." << std::endl;
        sleep(1); // simulate working
        // send the msg from requestor node to database node
        zmq_send(db, buffer, 256, 0);

        char msg[16] = {0};
        zmq_recv(db, msg, 16, 0);
        std::cout << msg << std::endl;

        zmq_send(rep, msg, 16, 0); // send response back to requestor node
    }

    zmq_close(rep);
    zmq_close(db);
    zmq_ctx_destroy(ctx);

    return 0;
}

#include <zmq.h>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include "proto/person.pb.h"

int main()
{
    std::cout << "Database node" << std::endl;

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    void *ctx = zmq_ctx_new();
    void *db = zmq_socket(ctx, ZMQ_REP);
    assert(zmq_bind(db, "tcp://*:5601") == 0);

    for(;;)
    {
        char buffer[256] = {0};
        zmq_recv(db, buffer, 256, 0);
        std::cout << "Processing entry:" << std::endl;

        sleep(1); // simulate doing some work
        const std::string input(buffer);
        person::Person person;
        person.ParseFromString(input);

        std::cout << person.last_name() << std::endl;
        std::cout << person.first_name() << std::endl;
        std::cout << person.middle_name() << std::endl;

        zmq_send(db, "Added to db", 11, 0);
    }

    zmq_close(db);
    zmq_ctx_destroy(ctx);

    return 0;
}

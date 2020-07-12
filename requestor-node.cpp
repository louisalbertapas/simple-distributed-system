#include <zmq.h>
#include <string>
#include <iostream>
#include "proto/person.pb.h"

int main()
{
    std::cout << "Requestor node" << std::endl;

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    void *ctx = zmq_ctx_new();
    void *req = zmq_socket(ctx, ZMQ_REQ);
    zmq_connect(req, "tcp://localhost:5600");

    for(;;)
    {
        person::Person p;
        std::cout << "Input person details..." << std::endl;

        std::cout << "Enter last name: ";
        std::string input;
        getline(std::cin, input);
        p.set_last_name(input);

        input = "";
        std::cout << "Enter first name: ";
        getline(std::cin, input);
        p.set_first_name(input);

        input = "";
        std::cout << "Enter middle name(optional): ";
        getline(std::cin, input);
        if (!input.empty())
        {
            p.set_middle_name(input);
        }

        std::string serialized;
        p.SerializeToString(&serialized);

        std::cout << "Sending person details..." << std::endl;
        zmq_send(req, serialized.c_str(), serialized.length(), 0);

        char buffer[16] = {0};
        zmq_recv(req, buffer, 16, 0);
        std::cout << buffer << std::endl;
    }

    zmq_close(req);
    zmq_ctx_destroy(ctx);

    return 0;
}

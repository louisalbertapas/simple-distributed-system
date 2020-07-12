include_directories(${PROTOBUF_INCLUDE_DOR})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER person.proto)
add_library(proto ${PROTO_SRC} ${PROTO_HEADER})

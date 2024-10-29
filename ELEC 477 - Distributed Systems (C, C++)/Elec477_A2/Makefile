
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CXX=g++
CXXFLAGS=-std=c++2a -g -pthread -g
LDFLAGS= -lprotobuf -pthread -lgdbm
endif
ifeq ($(UNAME_S),Darwin)
CXXFLAGS=-std=c++20 -g -pthread -g
CXX=c++
LDFLAGS= -lprotobuf -pthread
endif

OBJS=main.o network.o E477KV.pb.o dumpHex.o kvserver.o kvservice.o kvclient1.o kvclientstub.o

all: bin/assign1
bin/assign1:  $(OBJS)
	$(CXX) -g -o bin/assign1 $(OBJS)  $(LDFLAGS)
	

main.o:  E477KV.pb.h

E477KV.pb.h E477KV.pb.cc: E477KV.proto
	protoc --cpp_out=. E477KV.proto

kvclient1.o: E477KV.pb.h kvclient1.hpp KVrpc.h kvclientstub.hpp network.hpp
kclientvstub.o: kvclientstub.hpp network.hpp

kvservice.o: kvservice.hpp E477KV.pb.h network.hpp #E477.h
kvserver.o: kvserver.hpp network.hpp kvservice.hpp

# support files
network.o: network.hpp dumpHex.hpp
dumpHex.o: dumpHex.hpp


clean:
	rm bin/* *.o E477KV.pb.h E477KV.pb.cc

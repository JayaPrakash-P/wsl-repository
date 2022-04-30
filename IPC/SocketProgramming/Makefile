CXX:=g++
LD_FLAGS:=-pthread

CLIENT:=SocketClient
SERVER:=SocketServer

all : $(CLIENT) $(SERVER)
	$(info Making all with $^)

% : %.cc
	$(CXX) $^ $(LD_FLAGS) -o $@

clean : $(CLIENT) $(SERVER)
	rm -rf $^ *.o

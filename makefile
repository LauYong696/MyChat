CXX = gcc
LFLAGS = -lpthread -lrt -lncurses
TARGET = chat_server 
OBJ = main.o server_socket.o server_thread.o ncurse.o
CXXFLAGS = -g -c 

$(TARGET): $(OBJ)
	$(CXX) -g -o $(TARGET) $(OBJ) $(LFLAGS)

$(OBJ): %.o : %.c
	$(CXX) -g -c $< -o $@

clean:
	-rm $(TARGET) *.o

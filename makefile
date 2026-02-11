CC=g++
CFLAGS= -g -std=c++17 -Wall 
INCLUDES= -I../dragonfly/include -I/opt/homebrew/include -I/usr/local/include
LDFLAGS= -L../dragonfly/lib -ldragonfly -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

COMMON_SRC= NetworkManager.cpp EventNetwork.cpp Sentry.cpp

SERVER_SRC= server.cpp yakserver.cpp

CLIENT_SRC= chat.cpp ServerEntry.cpp NameEntry.cpp Input.cpp yakclient.cpp

COMMON_OBJ=$(COMMON_SRC:.cpp=.o)
SERVER_OBJ=$(SERVER_SRC:.cpp=.o)
CLIENT_OBJ=$(CLIENT_SRC:.cpp=.o)

all: chat-server chat-client

chat-server: $(COMMON_OBJ) $(SERVER_OBJ)
	$(CC) $(COMMON_OBJ) $(SERVER_OBJ) -o $@ $(LDFLAGS)

chat-client: $(COMMON_OBJ) $(CLIENT_OBJ)
	$(CC) $(COMMON_OBJ) $(CLIENT_OBJ) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o chat-server chat-client core *.log
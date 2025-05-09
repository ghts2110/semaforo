# Nome do executável
TARGET = simulacao_transito

# Compilador
CC = clang

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11

# Bibliotecas
LIBS = -lpthread

# Arquivos fonte
SRCS = simulacao_transito.c

# Regra principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Limpa arquivos gerados
clean:
	rm -f $(TARGET)

# Nom de l'exécutable final
TARGET = snake_battle

# Compilateur
CC = gcc

# Options de compilation (Warnings, Debug, Standard C99)
CFLAGS = -Wall -Wextra -std=c99 -O2

# Bibliothèques à lier (Raylib et dépendances système)
# Sur Linux, on ajoute généralement -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Liste des fichiers sources
SRCS = projet.c Arbre.c Case.c

# Génération automatique de la liste des fichiers objets (.o)
OBJS = $(SRCS:.c=.o)

# Règle par défaut : compile le projet
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Règle pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour recompiler proprement
re: clean all

.PHONY: all clean re
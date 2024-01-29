# Declare the variables
CC = g++
CFLAGS = -std=c++11

# File names
EXEC = assn4.exe
SOURCES = Image.cc SharedPtr_image_test.cc
OBJECTS = $(SOURCES:.cc=.o)

# The main target
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

# To obtain object files
%.o: %.cc
	$(CC) -c $(CFLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)


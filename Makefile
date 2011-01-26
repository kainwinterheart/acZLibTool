CXX = g++

CXXFLAGS =	-lz
LDFLAGS =	$(CXXFLAGS)

OBJS =		main.o zlibber.o

LIBS =		

TARGET =	build/acZLibTool

$(TARGET):	$(OBJS)
	mkdir -p build
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(LDFLAGS)
	rm -f $(OBJS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

install:
	mkdir -p /usr/bin
	mv $(TARGET) /usr/bin/
CC = g++
RM = rm -f
CPPFLAGS = -lGL -lSDL2 -L/usr/local -std=c++11

ODIR=obj
OBJS= $(ODIR)/shield.o $(ODIR)/badguy.o $(ODIR)/goodguy.o $(ODIR)/bullet.o $(ODIR)/leveldesigner.o $(ODIR)/quaternion.o $(ODIR)/quaternionlib.o

EXEDIR=bin

all: $(EXEDIR)/quaternion

$(ODIR)/%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@ $(CPPFLAGS)

$(EXEDIR)/quaternion: $(OBJS)
	$(CC) $^ -o $@ $(CPPFLAGS)

clean:
	$(RM) *.o $(ODIR)/*.o $(EXEDIR)/quaternion

SRCDIR := src
INCDIR := include
BUILDDIR := build
ASSETSDIR := assets

all: $(BUILDDIR)/main.out

# Build the final executable
$(BUILDDIR)/main.out: $(BUILDDIR)/main.o \
                      $(BUILDDIR)/carte.o \
                      $(BUILDDIR)/parcelle.o \
                      $(BUILDDIR)/za.o \
                      $(BUILDDIR)/zau.o \
                      $(BUILDDIR)/zn.o \
                      $(BUILDDIR)/zu.o | $(BUILDDIR)
	g++ -o $@ $^

# Build main.o
$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/point2d.hpp $(INCDIR)/polygone.hpp $(INCDIR)/parcelle.hpp $(INCDIR)/za.hpp $(INCDIR)/zau.hpp $(INCDIR)/zn.hpp $(INCDIR)/zu.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/main.cpp -o $(BUILDDIR)/main.o

# Build carte.o
$(BUILDDIR)/carte.o: $(SRCDIR)/carte.cpp $(INCDIR)/carte.hpp $(INCDIR)/parcelle.hpp $(INCDIR)/za.hpp $(INCDIR)/zau.hpp $(INCDIR)/zn.hpp $(INCDIR)/zu.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/carte.cpp -o $(BUILDDIR)/carte.o

# Build parcelle.o
$(BUILDDIR)/parcelle.o: $(SRCDIR)/parcelle.cpp $(INCDIR)/parcelle.hpp $(INCDIR)/polygone.hpp $(INCDIR)/point2d.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/parcelle.cpp -o $(BUILDDIR)/parcelle.o

# Build za.o
$(BUILDDIR)/za.o: $(SRCDIR)/za.cpp $(INCDIR)/za.hpp $(INCDIR)/zn.hpp $(INCDIR)/parcelle.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/za.cpp -o $(BUILDDIR)/za.o

# Build zau.o
$(BUILDDIR)/zau.o: $(SRCDIR)/zau.cpp $(INCDIR)/zau.hpp $(INCDIR)/constructible.hpp $(INCDIR)/parcelle.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/zau.cpp -o $(BUILDDIR)/zau.o

# Build zn.o
$(BUILDDIR)/zn.o: $(SRCDIR)/zn.cpp $(INCDIR)/zn.hpp $(INCDIR)/parcelle.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/zn.cpp -o $(BUILDDIR)/zn.o

# Build zu.o
$(BUILDDIR)/zu.o: $(SRCDIR)/zu.cpp $(INCDIR)/zu.hpp $(INCDIR)/constructible.hpp $(INCDIR)/parcelle.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/zu.cpp -o $(BUILDDIR)/zu.o

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rfv $(BUILDDIR)
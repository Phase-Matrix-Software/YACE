CPPS=$(wildcard *.cpp)
OBJDIR=build
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CPPS))
CFLAGS+= -std=c++11 -Wall -fPIC
LFLAGS+= -shared

ifeq ($(OS),Windows_NT)
	OBJDIR=build/windows
	OUT=$(OBJDIR)/YACE.dll
else
	OBJDIR=build/linux
	OUT=$(OBJDIR)/libYACE.so
endif

.PHONY: all clean

all: $(OBJDIR) $(OUT)

clean:
	rm -rf $(OBJDIR)

$(OUT): $(OBJS)
	$(CXX) $(LFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

# vim: ai:ts=8:sw=8:tw=0:noet:

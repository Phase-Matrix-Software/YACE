CPPS=$(wildcard *.cpp)
OBJDIR=build
OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CPPS))
CFLAGS+= -Wall -fPIC
LFLAGS+= -shared
OUT=$(OBJDIR)/libYACE.so

.PHONY: all

all: $(OBJDIR) $(OUT)

clean:
	rm -rf $(OBJDIR)

$(OUT): $(OBJS)
	$(CXX) $(LFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir $(OBJDIR)


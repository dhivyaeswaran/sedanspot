#  Written based on the original by Hilton Lipschitz on 2015-09-01.
# Makefile currently tested on MacOS.

UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
	CC := clang++ -arch x86_64
else
	CC := g++
endif

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
BOOSTDIR := /usr/local/Cellar/boost/1.67.0_1
# Targets
EXECUTABLE := SedanSpot
TARGET := $(TARGETDIR)/$(EXECUTABLE)

# Code Lists
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Shared Compiler Flags
CFLAGS := -c
INC := -I /usr/local/include -I $(BOOSTDIR)/include
LIB := -L /usr/local/lib -L $(BOOSTDIR)/lib -lboost_program_options

ifeq ($(UNAME_S),Linux)
	CFLAGS += -std=gnu++11 -O3 # -fPIC

	# PostgreSQL Special
	PG_VER := 9.3
	INC += -I /usr/pgsql-$(PG_VER)/include
	LIB += -L /usr/pgsql-$(PG_VER)/lib
else
  CFLAGS += -std=c++11 -stdlib=libc++ -O3
endif

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "  Linking $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGETDIR) example/output.csv

test: $(TARGET)
	./$(TARGET) --input example/input.csv --sample-size 500 > example/output.csv
	@echo 'Anomaly scores written to example/output.csv.'

.PHONY: clean

.PHONY: default help objects ising temp_ramp histogram all clean
CC = gcc

LD = $(CC)

SOURCE_C = metropolis.c lattice.c       #$(wildcard *.c)
OBJECTS_C = metropolis_c.o lattice_c.o  #$(patsubst %.c, %_c.o, $(SOURCE_C))

CFLAGS = -std=gnu99 -lm
ISING = ../bin/ising.e
TEMPRAMP = ../bin/temp_ramp.e
HISTOGRAM = ../bin/histogram.e

ISING_O = ising_c.o
TEMPRAMP_O = temp_ramp_c.o
HISTOGRAM_O = histogram_c.o

default: help

help:
	@echo "\
Options:\n\n\
  make objects:       compiler makes objects for every *.c\n\
  make ising:         compiler makes executable for basic ising run\n\
  make temp_ramp      compiler makes executable for temperature ramp ising\n\
  make histogram	  compiler makes executable for temperature ramp with state data saving\n\
  make all:           build all previous\n\
  make clean:         delete output files\n\
  make help:          display this help"

objects: $(OBJECTS_C) $(ISING_O) $(TEMPRAMP_O) $(HISTOGRAM_O)

all: objects ising temp_ramp histogram

%_c.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

ising: $(OBJECTS_C) $(ISING_O)
	$(LD) $^ -o $(ISING) -lm

temp_ramp: $(OBJECTS_C) $(TEMPRAMP_O)
	$(LD) $^ -o $(TEMPRAMP) -lm

histogram : $(OBJECTS_C) $(HISTOGRAM_O)
	$(LD) $^ -o $(HISTOGRAM) -lm

clean:
	rm -rfv $(OBJECTS_C) $(ISING) $(TEMPRAMP) $(HISTOGRAM) $(ISING_O) $(TEMP_RAMP_O) $(HISTOGRAM_O)

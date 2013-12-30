SOPTS = --static-library --debug-build

all:
	scons -Q $(SOPTS) all

clean:
	scons -Q -c all $(SOPTS) 

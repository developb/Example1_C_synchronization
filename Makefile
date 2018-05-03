

CFLAGS:=

ifeq ($(DEBUG),1)
	CFLAGS+= -DDEBUG
endif

SOURCES:= *.c

sem:
	gcc $(CFLAGS) $(SOURCES) -o sem  -lpthread
clean:
	-rm -f ./sem

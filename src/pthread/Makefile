#P=pthreads
#objects=string_utilities.o
## To use Glib mutexes, some systems will require both glib-2.0 and gthread-2.0.
#CFLAGS=`pkg-config --cflags glib-2.0` -g -Wall -std=gnu99 -O3 -pthread
#LDLIBS=`pkg-config --libs glib-2.0` -pthread
#
#$(P): $(objects)

pthread_binout := $(bin_path)pthread$(bin_ext)

pthread: $(pthread_binout)

pthread_lflags += `pkg-config --cflags glib-2.0`
pthread_lflags += `pkg-config --libs glib-2.0`
pthread_lflags += $(INCS) $(LFLAGS) $(LDLIBS) -lpthread

$(pthread_binout): $(src_path)pthreads.c $(src_path)string_utilities.c
	$(CC) $(pthread_lflags) $^ $(bin_out)$@

pthread_test: pthread
	$(pthread_binout)

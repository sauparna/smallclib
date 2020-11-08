SRC := 	kalgorithm.c 	\
		kstack.c		\
		ktree.c			\
		klist.c

PRODUCT := libsmallc.a

CC := clang
CFLAGS := -std=c99 -Wall -D_POSIX_C_SOURCE=200112L
CFLAGS_DEBUG := -O0 -g -DDEBUG
CFLGAS_RELEASE := -O3 -DNDEBUG
CFLAGS_ASAN := -O1 -g -DDEBUG -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
CFLAGS_GCOV := -O0 -g -DDEBUG -fprofile-arcs -ftest-coverage
LDFLAGS := -flto -fuse-ld=lld -lm

ifeq ($(DEBUG),1)
  CFLAGS := $(CFLAGS_DEBUG) $(CFLAGS)
else ifeq ($(ASAN),1)
  CFLAGS := $(CFLAGS_ASAN) $(CFLAGS)
  LDFLAGS := $(LDFLAGS) -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
else ifeq ($(GCOV),1)
  CFLAGS := $(CFLAGS_GCOV) $(CFLAGS)
  LDFLAGS := $(LDFLAGS) -fprofile-arcs -ftest-coverage
else
  CFLAGS := $(CFLAGS_RELEASE) $(CFLAGS)
endif

all:	$(PRODUCT)

clean::
	rm -f $(OBJ) $(PRODUCT) \
        $(addsuffix .gcda, $(basename $(SRC))) \
        $(addsuffix .gcno, $(basename $(SRC))) \
        $(addsuffix .gcov, $(SRC) fasttime.h)

OBJ = $(addsuffix .o, $(basename $(SRC)))

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PRODUCT): $(OBJ)
	ar rs $@ $^

.PHONY:	all clean

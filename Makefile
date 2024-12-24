MODULES = curiox
EXTENSION = curiox 
DATA = curiox--0.0.1.sql

OBJS = $(addprefix build/, curiox.o)
PG_CPPFLAGS += -I$(srcdir)/include

PG_CONFIG = /usr/local/pgsql/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
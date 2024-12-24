MODULES = curiox
EXTENSION = curiox 
DATA = curiox--0.0.1.sql

PG_CONFIG = /usr/local/pgsql/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
#pragma once

#include "postgres.h"
#include "fmgr.h"
#include "access/tableam.h"
#include "access/heapam.h"
#include "nodes/execnodes.h"
#include "catalog/index.h"
#include "commands/vacuum.h"
#include "utils/builtins.h"
#include "executor/tuptable.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Column {
  int value;
};

struct Row {
  struct Column* columns;
  size_t ncolumns;
};

#define MAX_ROWS 100
struct Table {
  char* name;
  struct Row* rows;
  size_t nrows;
};

#define MAX_TABLES 100
struct Database {
  struct Table* tables;
  size_t ntables;
};

struct Database* database;

static void get_table(struct Table** table, Relation relation) {
  char* this_name = NameStr(relation->rd_rel->relname);
  for (size_t i = 0; i < database->ntables; i++) {
    if (strcmp(database->tables[i].name, this_name) == 0) {
      *table = &database->tables[i];
      return;
    }
  }
}

#ifdef __cplusplus
}
#endif
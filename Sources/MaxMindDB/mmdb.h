//
//  mmdb.h
//  CSSH
//
//  Created by 费三量 on 2025/1/19.
//

#ifndef mmdb_h
#define mmdb_h

#include "maxminddb-compat-util.h"
#include "maxminddb.h"
#include <stdlib.h>

MMDB_s *mmdb_open(const char *filename);
void mmdb_close(MMDB_s *db);
char *mmdb_lookup_iso_code(MMDB_s *db, const char *ip);
MMDB_metadata_s *mmdb_metadata(MMDB_s *db);

#endif /* mmdb_h */

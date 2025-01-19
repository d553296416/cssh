//
//  mmdb.c
//  CSSH
//
//  Created by 费三量 on 2025/1/19.
//

#include "mmdb.h"

MMDB_s *mmdb_open(const char *filename)
{
    MMDB_s *mmdb;
    mmdb = malloc(sizeof(MMDB_s));
    int status = MMDB_open(filename, MMDB_MODE_MMAP, mmdb);
    if (status != MMDB_SUCCESS)
    {
        return NULL;
    }
    return mmdb;
}

void mmdb_close(MMDB_s *db)
{
    if (db)
    {
        MMDB_close(db);
        free(db);
    }
}
char *mmdb_lookup_iso_code(MMDB_s *db, const char *ip)
{
    if (!db)
    {
        return NULL;
    }
    int gai_error, mmdb_error;
    MMDB_lookup_result_s result = MMDB_lookup_string(db, ip, &gai_error, &mmdb_error);
    if (MMDB_SUCCESS != gai_error)
    {
        goto end;
    }

    if (MMDB_SUCCESS != mmdb_error)
    {
        goto end;
    }
    MMDB_entry_data_s iso_code;
    char *isoCode;

    int status = MMDB_get_value(&result.entry, &iso_code, "country", "iso_code", NULL);
    if (MMDB_SUCCESS == status)
    {
        goto ok;
    }
    status = MMDB_get_value(&result.entry, &iso_code, "represented_country", "iso_code", NULL);
    if (MMDB_SUCCESS == status)
    {
        goto ok;
    }
    status = MMDB_get_value(&result.entry, &iso_code, "registered_country", "iso_code", NULL);
    if (MMDB_SUCCESS == status)
    {
        goto ok;
    }
    status = MMDB_get_value(&result.entry, &iso_code, "subdivisions", "iso_code", NULL);
    if (MMDB_SUCCESS == status)
    {
        goto ok;
    }
    goto end;
ok:
    if (!iso_code.has_data || iso_code.type != MMDB_DATA_TYPE_UTF8_STRING)
    {
        goto end;
    }
    isoCode = mmdb_strndup(iso_code.utf8_string, iso_code.data_size);

    if (!isoCode)
    {
        goto end;
    }

    return isoCode;

end:
    return NULL;
}
MMDB_metadata_s *mmdb_metadata(MMDB_s *db)
{
    if (!db)
    {
        return NULL;
    }
    return &db->metadata;
}

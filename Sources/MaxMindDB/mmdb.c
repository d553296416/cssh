// mmdb.c
// Copyright (c) 2025 ssh2.app
// Created by admin@ssh2.app 2025/1/19.

#include "mmdb.h"

/**
 * @brief Opens a MaxMindDB database file.
 *
 * This function allocates memory for an MMDB_s structure and attempts to open
 * the specified MaxMindDB database file in memory-mapped mode.
 *
 * @param filename The path to the MaxMindDB database file to open.
 * @return A pointer to an MMDB_s structure if the file is successfully opened,
 *         or NULL if there is an error.
 */
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

/**
 * @brief Closes the MaxMindDB database and frees the associated memory.
 *
 * This function closes the MaxMindDB database pointed to by the given
 * MMDB_s structure and frees the memory allocated for the structure.
 *
 * @param db A pointer to the MMDB_s structure representing the database
 *           to be closed. If the pointer is NULL, the function does nothing.
 */
void mmdb_close(MMDB_s *db)
{
    if (db)
    {
        MMDB_close(db);
        free(db);
    }
}

/**
 * @brief Looks up the ISO code for a given IP address in the MaxMind database.
 *
 * This function queries the MaxMind database to find the ISO code associated with the provided IP address.
 * It checks multiple fields in the database entry to find the ISO code, including "country", "represented_country",
 * "registered_country", and "subdivisions".
 *
 * @param db A pointer to the MMDB_s structure representing the MaxMind database.
 * @param ip A string containing the IP address to look up.
 * @return A dynamically allocated string containing the ISO code if found, or NULL if not found or an error occurred.
 *         The caller is responsible for freeing the returned string.
 */
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

/**
 * @brief Retrieves the metadata from a MaxMindDB database.
 *
 * This function returns a pointer to the metadata structure of the given
 * MaxMindDB database. If the provided database pointer is NULL, the function
 * returns NULL.
 *
 * @param db A pointer to an MMDB_s structure representing the MaxMindDB database.
 * @return A pointer to an MMDB_metadata_s structure containing the metadata,
 *         or NULL if the provided database pointer is NULL.
 */
MMDB_metadata_s *mmdb_metadata(MMDB_s *db)
{
    if (!db)
    {
        return NULL;
    }
    return &db->metadata;
}

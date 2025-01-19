// mmdb.h
// Copyright (c) 2025 ssh2.app
// Created by admin@ssh2.app 2025/1/19.

#ifndef mmdb_h
#define mmdb_h

#include "maxminddb-compat-util.h"
#include "maxminddb.h"
#include <stdlib.h>

/**
 * @brief Opens a MaxMindDB database file.
 *
 * This function opens a MaxMindDB database file specified by the given filename.
 *
 * @param filename The path to the MaxMindDB database file to be opened.
 * @return A pointer to an MMDB_s structure representing the opened database, or NULL if the file could not be opened.
 */
MMDB_s *mmdb_open(const char *filename);
/**
 * @brief Closes the MaxMindDB database.
 *
 * This function closes the given MaxMindDB database and releases any resources
 * associated with it.
 *
 * @param db A pointer to the MMDB_s structure representing the database to be closed.
 */
void mmdb_close(MMDB_s *db);
/**
 * @brief Looks up the ISO code for a given IP address in the MaxMind database.
 *
 * This function takes a MaxMind database and an IP address as input, and returns
 * the corresponding ISO code as a string. The ISO code is typically a two-letter
 * country code.
 *
 * @param db A pointer to the MaxMind database structure.
 * @param ip A string representing the IP address to look up.
 * @return A string containing the ISO code for the given IP address. If the lookup
 *         fails, the function may return NULL.
 */
char *mmdb_lookup_iso_code(MMDB_s *db, const char *ip);
/**
 * @brief Retrieves the metadata from a MaxMindDB database.
 *
 * This function returns a pointer to the metadata structure of the given
 * MaxMindDB database.
 *
 * @param db A pointer to an MMDB_s structure representing the database.
 * @return A pointer to an MMDB_metadata_s structure containing the metadata.
 */
MMDB_metadata_s *mmdb_metadata(MMDB_s *db);

#endif /* mmdb_h */

// sshkey.h
// Copyright (c) 2024 ssh2.app
// Created by admin@ssh2.app 2024/8/26.

#ifndef sshkey_h
#define sshkey_h

#include <string.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

/**
 * @brief Extracts the ED25519 public key from the given EVP_PKEY structure.
 *
 * This function takes an EVP_PKEY structure containing an ED25519 key and
 * extracts the public key from it. The public key is returned as a
 * null-terminated string.
 *
 * @param pkey A pointer to an EVP_PKEY structure containing the ED25519 key.
 * @return A pointer to a null-terminated string containing the ED25519 public key.
 *         The caller is responsible for freeing the allocated memory.
 */
char *sshkey_ed25519_pub(EVP_PKEY *pkey);

/**
 * @brief Retrieves the RSA public key from the given EVP_PKEY structure.
 *
 * This function extracts the RSA public key from the provided EVP_PKEY
 * structure and returns it as a string.
 *
 * @param pkey A pointer to an EVP_PKEY structure containing the RSA key.
 * @return A string containing the RSA public key. The caller is responsible
 *         for freeing the returned string.
 */
char *sshkey_rsa_pub(EVP_PKEY *pkey);

/**
 * @brief Generates a public SSH key in the specified format.
 *
 * @param pkey A pointer to an EVP_PKEY structure containing the private key.
 * @param key_type A string specifying the type of the key (e.g., "rsa", "dsa", "ecdsa").
 * @return A pointer to a string containing the public key in the specified format.
 *         The caller is responsible for freeing the allocated memory.
 */
char *sshkey_pub(EVP_PKEY *pkey, const char *key_type);

#endif /* sshkey_h */

// sshkey.c
// Copyright (c) 2024 ssh2.app
// Created by admin@ssh2.app 2024/8/26.

#include "sshkey.h"

/**
 * Encodes the given data in base64 format.
 *
 * @param data The data to be encoded.
 * @param len The length of the data to be encoded.
 * @return A pointer to a null-terminated string containing the base64 encoded data.
 *         The caller is responsible for freeing the allocated memory.
 */
char *base64_encode(const unsigned char *data, int len)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    BIO_write(bio, data, len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *b64text = (char *)malloc(bufferPtr->length + 1);
    memcpy(b64text, bufferPtr->data, bufferPtr->length);
    b64text[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return b64text;
}

/**
 * @brief Writes a string to a BIO in SSH format.
 *
 * This function writes a string to a BIO (Basic Input/Output) object in the
 * format used by SSH (Secure Shell). The string is preceded by its length,
 * encoded as a 4-byte big-endian integer.
 *
 * @param bio A pointer to the BIO object where the string will be written.
 * @param str A pointer to the null-terminated string to be written.
 */
void write_ssh_string(BIO *bio, const char *str)
{
    uint32_t len = htonl(strlen(str));
    BIO_write(bio, &len, 4);
    BIO_write(bio, str, (int)strlen(str));
}

/**
 * @brief Writes a multi-precision integer (mpint) to a BIO stream.
 *
 * This function converts a BIGNUM to its binary representation and writes it
 * to the provided BIO stream in the SSH mpint format. If the most significant
 * bit of the first byte is set, an additional zero byte is prepended to ensure
 * the integer is interpreted as positive.
 *
 * @param bio A pointer to the BIO stream where the mpint will be written.
 * @param bn A pointer to the BIGNUM that will be written as an mpint.
 */
void write_ssh_mpint(BIO *bio, const BIGNUM *bn)
{
    int bytes_len = BN_num_bytes(bn);
    unsigned char *bytes = (unsigned char *)malloc(bytes_len);
    BN_bn2bin(bn, bytes);

    if (bytes[0] & 0x80)
    {
        uint32_t len = htonl(bytes_len + 1);
        BIO_write(bio, &len, 4);
        unsigned char zero = 0x00;
        BIO_write(bio, &zero, 1);
    }
    else
    {
        uint32_t len = htonl(bytes_len);
        BIO_write(bio, &len, 4);
    }

    BIO_write(bio, bytes, bytes_len);
    free(bytes);
}

/**
 * @brief Generates the public key string for the given private key and key type.
 *
 * This function takes an EVP_PKEY structure representing the private key and a string
 * representing the key type, and returns the corresponding public key string.
 *
 * @param pkey A pointer to an EVP_PKEY structure containing the private key.
 * @param key_type A string representing the type of the key. Supported values are "ssh-rsa" and "ssh-ed25519".
 * @return A string containing the public key if the key type is supported, or NULL if the key type is not supported.
 */
char *sshkey_pub(EVP_PKEY *pkey, const char *key_type)
{
    if (strcmp(key_type, "ssh-rsa") == 0)
    {
        return sshkey_rsa_pub(pkey);
    }
    else if (strcmp(key_type, "ssh-ed25519") == 0)
    {
        return sshkey_ed25519_pub(pkey);
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief Encodes a public key in SSH format and returns it as a base64 encoded string.
 *
 * This function takes a binary public key, its length, and the key type, and encodes it
 * into the SSH public key format. The resulting string is base64 encoded and returned
 * in the format "<key_type> <base64_encoded_key>\n".
 *
 * @param pubkey_bin A pointer to the binary public key.
 * @param pubkey_len The length of the binary public key.
 * @param key_type A string representing the type of the key (e.g., "ssh-rsa").
 * @return A pointer to the encoded public key string, or NULL if an error occurs.
 *
 * @note The caller is responsible for freeing the returned string.
 */
char *sshkey_encode(unsigned char *pubkey_bin, size_t pubkey_len, const char *key_type)
{
    unsigned char *ssh_format = NULL;
    char *encoded_pubkey = NULL;
    char *ssh_public_key = NULL;
    size_t ssh_format_len;
    uint32_t key_type_len = htonl(strlen(key_type));
    uint32_t pubkey_len_net = htonl(pubkey_len);
    ssh_format_len = 4 + strlen(key_type) + 4 + pubkey_len;

    ssh_format = malloc(ssh_format_len);
    if (!ssh_format)
    {
        return NULL;
    }

    memcpy(ssh_format, &key_type_len, 4);
    memcpy(ssh_format + 4, key_type, strlen(key_type));
    memcpy(ssh_format + 4 + strlen(key_type), &pubkey_len_net, 4);
    memcpy(ssh_format + 8 + strlen(key_type), pubkey_bin, pubkey_len);

    encoded_pubkey = base64_encode(ssh_format, (int)ssh_format_len);
    free(ssh_format);

    if (!encoded_pubkey)
    {
        return NULL;
    }

    ssh_public_key = (char *)malloc(strlen(key_type) + strlen(encoded_pubkey) + 2);
    if (ssh_public_key)
    {
        sprintf(ssh_public_key, "%s %s\n", key_type, encoded_pubkey);
    }

    free(encoded_pubkey);

    return ssh_public_key;
}

/**
 * Generates an SSH public key in the ssh-ed25519 format from the given EVP_PKEY.
 *
 * @param pkey A pointer to an EVP_PKEY structure containing the key.
 * @return A string containing the SSH public key in the ssh-ed25519 format, or NULL on failure.
 *
 * The caller is responsible for freeing the returned string.
 */
char *sshkey_ed25519_pub(EVP_PKEY *pkey)
{
    unsigned char *pubkey_bin = NULL;
    char *ssh_public_key = NULL;
    size_t pubkey_len;
    char *key_type = "ssh-ed25519";

    if (EVP_PKEY_get_raw_public_key(pkey, NULL, &pubkey_len) <= 0)
    {
        return NULL;
    }

    pubkey_bin = (unsigned char *)OPENSSL_malloc(pubkey_len);
    if (pubkey_bin == NULL)
    {
        return NULL;
    }

    if (EVP_PKEY_get_raw_public_key(pkey, pubkey_bin, &pubkey_len) <= 0)
    {
        OPENSSL_free(pubkey_bin);
        return NULL;
    }

    ssh_public_key = sshkey_encode(pubkey_bin, pubkey_len, key_type);
    if (ssh_public_key == NULL)
    {
        OPENSSL_free(pubkey_bin);
    }

    return ssh_public_key;
}

/**
 * Generates an SSH RSA public key in the OpenSSH format.
 *
 * @param pkey A pointer to an EVP_PKEY structure containing the RSA key.
 * @return A dynamically allocated string containing the SSH RSA public key in the format "ssh-rsa <base64-encoded-key>\n".
 *         The caller is responsible for freeing the returned string. Returns NULL on failure.
 *
 * The function extracts the RSA key parameters (n and e) from the provided EVP_PKEY structure,
 * encodes them in the SSH format, and then base64 encodes the result. The final string is
 * formatted as "ssh-rsa <base64-encoded-key>\n".
 *
 * The function performs the following steps:
 * 1. Extracts the RSA key parameters (n and e) from the EVP_PKEY.
 * 2. Writes the key type ("ssh-rsa") and the key parameters to a memory BIO.
 * 3. Base64 encodes the contents of the BIO.
 * 4. Formats the final SSH public key string.
 * 5. Cleans up allocated resources and returns the formatted string.
 *
 * If any step fails, the function performs cleanup and returns NULL.
 */
char *sshkey_rsa_pub(EVP_PKEY *pkey)
{
    BIGNUM *n = NULL, *e = NULL;
    char *ssh_public_key = NULL;
    char *key_type = "ssh-rsa";
    EVP_PKEY_get_bn_param(pkey, "n", &n);
    EVP_PKEY_get_bn_param(pkey, "e", &e);
    BIO *bio = BIO_new(BIO_s_mem());
    if (!bio)
    {
        return NULL;
    }
    write_ssh_string(bio, key_type);
    write_ssh_mpint(bio, e);
    write_ssh_mpint(bio, n);

    BUF_MEM *bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    char *b64_pub_key = base64_encode((unsigned char *)bufferPtr->data, (int)bufferPtr->length);
    if (!b64_pub_key)
    {
        goto cleanup;
    }
    size_t ssh_public_key_len = strlen(key_type) + strlen(b64_pub_key) + 2;
    ssh_public_key = (char *)malloc(ssh_public_key_len);
    if (!ssh_public_key)
    {
        goto cleanup;
    }

    snprintf(ssh_public_key, ssh_public_key_len, "%s %s\n", key_type, b64_pub_key);

cleanup:
    BIO_free(bio);
    free(b64_pub_key);

    return ssh_public_key;
}

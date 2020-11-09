/**
 * \file psa/crypto_values.h
 *
 * \brief PSA cryptography module: macros to build and analyze integer values.
 *
 * \note This file may not be included directly. Applications must
 * include psa/crypto.h. Drivers must include the appropriate driver
 * header file.
 *
 * This file contains portable definitions of macros to build and analyze
 * values of integral types that encode properties of cryptographic keys,
 * designations of cryptographic algorithms, and error codes returned by
 * the library.
 *
 * This header file only defines preprocessor macros.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef PSA_CRYPTO_VALUES_H
#define PSA_CRYPTO_VALUES_H

/** \defgroup error Error codes
 * @{
 */

/* PSA error codes */

/** The action was completed successfully. */
#define PSA_SUCCESS ((psa_status_t)0)

/** An error occurred that does not correspond to any defined
 * failure cause.
 *
 * Implementations may use this error code if none of the other standard
 * error codes are applicable. */
#define PSA_ERROR_GENERIC_ERROR         ((psa_status_t)-132)

/** The requested operation or a parameter is not supported
 * by this implementation.
 *
 * Implementations should return this error code when an enumeration
 * parameter such as a key type, algorithm, etc. is not recognized.
 * If a combination of parameters is recognized and identified as
 * not valid, return #PSA_ERROR_INVALID_ARGUMENT instead. */
#define PSA_ERROR_NOT_SUPPORTED         ((psa_status_t)-134)

/** The requested action is denied by a policy.
 *
 * Implementations should return this error code when the parameters
 * are recognized as valid and supported, and a policy explicitly
 * denies the requested operation.
 *
 * If a subset of the parameters of a function call identify a
 * forbidden operation, and another subset of the parameters are
 * not valid or not supported, it is unspecified whether the function
 * returns #PSA_ERROR_NOT_PERMITTED, #PSA_ERROR_NOT_SUPPORTED or
 * #PSA_ERROR_INVALID_ARGUMENT. */
#define PSA_ERROR_NOT_PERMITTED         ((psa_status_t)-133)

/** An output buffer is too small.
 *
 * Applications can call the \c PSA_xxx_SIZE macro listed in the function
 * description to determine a sufficient buffer size.
 *
 * Implementations should preferably return this error code only
 * in cases when performing the operation with a larger output
 * buffer would succeed. However implementations may return this
 * error if a function has invalid or unsupported parameters in addition
 * to the parameters that determine the necessary output buffer size. */
#define PSA_ERROR_BUFFER_TOO_SMALL      ((psa_status_t)-138)

/** Asking for an item that already exists
 *
 * Implementations should return this error, when attempting
 * to write an item (like a key) that already exists. */
#define PSA_ERROR_ALREADY_EXISTS        ((psa_status_t)-139)

/** Asking for an item that doesn't exist
 *
 * Implementations should return this error, if a requested item (like
 * a key) does not exist. */
#define PSA_ERROR_DOES_NOT_EXIST        ((psa_status_t)-140)

/** The requested action cannot be performed in the current state.
 *
 * Multipart operations return this error when one of the
 * functions is called out of sequence. Refer to the function
 * descriptions for permitted sequencing of functions.
 *
 * Implementations shall not return this error code to indicate
 * that a key either exists or not,
 * but shall instead return #PSA_ERROR_ALREADY_EXISTS or #PSA_ERROR_DOES_NOT_EXIST
 * as applicable.
 *
 * Implementations shall not return this error code to indicate that a
 * key identifier is invalid, but shall return #PSA_ERROR_INVALID_HANDLE
 * instead. */
#define PSA_ERROR_BAD_STATE             ((psa_status_t)-137)

/** The parameters passed to the function are invalid.
 *
 * Implementations may return this error any time a parameter or
 * combination of parameters are recognized as invalid.
 *
 * Implementations shall not return this error code to indicate that a
 * key identifier is invalid, but shall return #PSA_ERROR_INVALID_HANDLE
 * instead.
 */
#define PSA_ERROR_INVALID_ARGUMENT      ((psa_status_t)-135)

/** There is not enough runtime memory.
 *
 * If the action is carried out across multiple security realms, this
 * error can refer to available memory in any of the security realms. */
#define PSA_ERROR_INSUFFICIENT_MEMORY   ((psa_status_t)-141)

/** There is not enough persistent storage.
 *
 * Functions that modify the key storage return this error code if
 * there is insufficient storage space on the host media. In addition,
 * many functions that do not otherwise access storage may return this
 * error code if the implementation requires a mandatory log entry for
 * the requested action and the log storage space is full. */
#define PSA_ERROR_INSUFFICIENT_STORAGE  ((psa_status_t)-142)

/** There was a communication failure inside the implementation.
 *
 * This can indicate a communication failure between the application
 * and an external cryptoprocessor or between the cryptoprocessor and
 * an external volatile or persistent memory. A communication failure
 * may be transient or permanent depending on the cause.
 *
 * \warning If a function returns this error, it is undetermined
 * whether the requested action has completed or not. Implementations
 * should return #PSA_SUCCESS on successful completion whenever
 * possible, however functions may return #PSA_ERROR_COMMUNICATION_FAILURE
 * if the requested action was completed successfully in an external
 * cryptoprocessor but there was a breakdown of communication before
 * the cryptoprocessor could report the status to the application.
 */
#define PSA_ERROR_COMMUNICATION_FAILURE ((psa_status_t)-145)

/** There was a storage failure that may have led to data loss.
 *
 * This error indicates that some persistent storage is corrupted.
 * It should not be used for a corruption of volatile memory
 * (use #PSA_ERROR_CORRUPTION_DETECTED), for a communication error
 * between the cryptoprocessor and its external storage (use
 * #PSA_ERROR_COMMUNICATION_FAILURE), or when the storage is
 * in a valid state but is full (use #PSA_ERROR_INSUFFICIENT_STORAGE).
 *
 * Note that a storage failure does not indicate that any data that was
 * previously read is invalid. However this previously read data may no
 * longer be readable from storage.
 *
 * When a storage failure occurs, it is no longer possible to ensure
 * the global integrity of the keystore. Depending on the global
 * integrity guarantees offered by the implementation, access to other
 * data may or may not fail even if the data is still readable but
 * its integrity cannot be guaranteed.
 *
 * Implementations should only use this error code to report a
 * permanent storage corruption. However application writers should
 * keep in mind that transient errors while reading the storage may be
 * reported using this error code. */
#define PSA_ERROR_STORAGE_FAILURE       ((psa_status_t)-146)

/** A hardware failure was detected.
 *
 * A hardware failure may be transient or permanent depending on the
 * cause. */
#define PSA_ERROR_HARDWARE_FAILURE      ((psa_status_t)-147)

/** A tampering attempt was detected.
 *
 * If an application receives this error code, there is no guarantee
 * that previously accessed or computed data was correct and remains
 * confidential. Applications should not perform any security function
 * and should enter a safe failure state.
 *
 * Implementations may return this error code if they detect an invalid
 * state that cannot happen during normal operation and that indicates
 * that the implementation's security guarantees no longer hold. Depending
 * on the implementation architecture and on its security and safety goals,
 * the implementation may forcibly terminate the application.
 *
 * This error code is intended as a last resort when a security breach
 * is detected and it is unsure whether the keystore data is still
 * protected. Implementations shall only return this error code
 * to report an alarm from a tampering detector, to indicate that
 * the confidentiality of stored data can no longer be guaranteed,
 * or to indicate that the integrity of previously returned data is now
 * considered compromised. Implementations shall not use this error code
 * to indicate a hardware failure that merely makes it impossible to
 * perform the requested operation (use #PSA_ERROR_COMMUNICATION_FAILURE,
 * #PSA_ERROR_STORAGE_FAILURE, #PSA_ERROR_HARDWARE_FAILURE,
 * #PSA_ERROR_INSUFFICIENT_ENTROPY or other applicable error code
 * instead).
 *
 * This error indicates an attack against the application. Implementations
 * shall not return this error code as a consequence of the behavior of
 * the application itself. */
#define PSA_ERROR_CORRUPTION_DETECTED    ((psa_status_t)-151)

/** There is not enough entropy to generate random data needed
 * for the requested action.
 *
 * This error indicates a failure of a hardware random generator.
 * Application writers should note that this error can be returned not
 * only by functions whose purpose is to generate random data, such
 * as key, IV or nonce generation, but also by functions that execute
 * an algorithm with a randomized result, as well as functions that
 * use randomization of intermediate computations as a countermeasure
 * to certain attacks.
 *
 * Implementations should avoid returning this error after psa_crypto_init()
 * has succeeded. Implementations should generate sufficient
 * entropy during initialization and subsequently use a cryptographically
 * secure pseudorandom generator (PRNG). However implementations may return
 * this error at any time if a policy requires the PRNG to be reseeded
 * during normal operation. */
#define PSA_ERROR_INSUFFICIENT_ENTROPY  ((psa_status_t)-148)

/** The signature, MAC or hash is incorrect.
 *
 * Verification functions return this error if the verification
 * calculations completed successfully, and the value to be verified
 * was determined to be incorrect.
 *
 * If the value to verify has an invalid size, implementations may return
 * either #PSA_ERROR_INVALID_ARGUMENT or #PSA_ERROR_INVALID_SIGNATURE. */
#define PSA_ERROR_INVALID_SIGNATURE     ((psa_status_t)-149)

/** The decrypted padding is incorrect.
 *
 * \warning In some protocols, when decrypting data, it is essential that
 * the behavior of the application does not depend on whether the padding
 * is correct, down to precise timing. Applications should prefer
 * protocols that use authenticated encryption rather than plain
 * encryption. If the application must perform a decryption of
 * unauthenticated data, the application writer should take care not
 * to reveal whether the padding is invalid.
 *
 * Implementations should strive to make valid and invalid padding
 * as close as possible to indistinguishable to an external observer.
 * In particular, the timing of a decryption operation should not
 * depend on the validity of the padding. */
#define PSA_ERROR_INVALID_PADDING       ((psa_status_t)-150)

/** Return this error when there's insufficient data when attempting
 * to read from a resource. */
#define PSA_ERROR_INSUFFICIENT_DATA     ((psa_status_t)-143)

/** The key identifier is not valid. See also :ref:\`key-handles\`.
 */
#define PSA_ERROR_INVALID_HANDLE        ((psa_status_t)-136)

/** Stored data has been corrupted.
 *
 * This error indicates that some persistent storage has suffered corruption.
 * It does not indicate the following situations, which have specific error
 * codes:
 *
 * - A corruption of volatile memory - use #PSA_ERROR_CORRUPTION_DETECTED.
 * - A communication error between the cryptoprocessor and its external
 *   storage - use #PSA_ERROR_COMMUNICATION_FAILURE.
 * - When the storage is in a valid state but is full - use
 *   #PSA_ERROR_INSUFFICIENT_STORAGE.
 * - When the storage fails for other reasons - use
 *   #PSA_ERROR_STORAGE_FAILURE.
 * - When the stored data is not valid - use #PSA_ERROR_DATA_INVALID.
 *
 * \note A storage corruption does not indicate that any data that was
 * previously read is invalid. However this previously read data might no
 * longer be readable from storage.
 *
 * When a storage failure occurs, it is no longer possible to ensure the
 * global integrity of the keystore.
 */
#define PSA_ERROR_DATA_CORRUPT          ((psa_status_t)-152)

/**@}*/

/** \defgroup crypto_types Key and algorithm types
 * @{
 */

/** An invalid key type value.
 *
 * Zero is not the encoding of any key type.
 */
#define PSA_KEY_TYPE_NONE                           ((psa_key_type_t)0x0000)

/** Vendor-defined key type flag.
 *
 * Key types defined by this standard will never have the
 * #PSA_KEY_TYPE_VENDOR_FLAG bit set. Vendors who define additional key types
 * must use an encoding with the #PSA_KEY_TYPE_VENDOR_FLAG bit set and should
 * respect the bitwise structure used by standard encodings whenever practical.
 */
#define PSA_KEY_TYPE_VENDOR_FLAG                    ((psa_key_type_t)0x8000)

#define PSA_KEY_TYPE_CATEGORY_MASK                  ((psa_key_type_t)0x7000)
#define PSA_KEY_TYPE_CATEGORY_RAW                   ((psa_key_type_t)0x1000)
#define PSA_KEY_TYPE_CATEGORY_SYMMETRIC             ((psa_key_type_t)0x2000)
#define PSA_KEY_TYPE_CATEGORY_PUBLIC_KEY            ((psa_key_type_t)0x4000)
#define PSA_KEY_TYPE_CATEGORY_KEY_PAIR              ((psa_key_type_t)0x7000)

#define PSA_KEY_TYPE_CATEGORY_FLAG_PAIR             ((psa_key_type_t)0x3000)

/** Whether a key type is vendor-defined.
 *
 * See also #PSA_KEY_TYPE_VENDOR_FLAG.
 */
#define PSA_KEY_TYPE_IS_VENDOR_DEFINED(type) \
    (((type) & PSA_KEY_TYPE_VENDOR_FLAG) != 0)

/** Whether a key type is an unstructured array of bytes.
 *
 * This encompasses both symmetric keys and non-key data.
 */
#define PSA_KEY_TYPE_IS_UNSTRUCTURED(type) \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_RAW || \
     ((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_SYMMETRIC)

/** Whether a key type is asymmetric: either a key pair or a public key. */
#define PSA_KEY_TYPE_IS_ASYMMETRIC(type)                                \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK                               \
      & ~PSA_KEY_TYPE_CATEGORY_FLAG_PAIR) ==                            \
     PSA_KEY_TYPE_CATEGORY_PUBLIC_KEY)
/** Whether a key type is the public part of a key pair. */
#define PSA_KEY_TYPE_IS_PUBLIC_KEY(type)                                \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_PUBLIC_KEY)
/** Whether a key type is a key pair containing a private part and a public
 * part. */
#define PSA_KEY_TYPE_IS_KEY_PAIR(type)                                   \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_KEY_PAIR)
/** The key pair type corresponding to a public key type.
 *
 * You may also pass a key pair type as \p type, it will be left unchanged.
 *
 * \param type      A public key type or key pair type.
 *
 * \return          The corresponding key pair type.
 *                  If \p type is not a public key or a key pair,
 *                  the return value is undefined.
 */
#define PSA_KEY_TYPE_KEY_PAIR_OF_PUBLIC_KEY(type)        \
    ((type) | PSA_KEY_TYPE_CATEGORY_FLAG_PAIR)
/** The public key type corresponding to a key pair type.
 *
 * You may also pass a key pair type as \p type, it will be left unchanged.
 *
 * \param type      A public key type or key pair type.
 *
 * \return          The corresponding public key type.
 *                  If \p type is not a public key or a key pair,
 *                  the return value is undefined.
 */
#define PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type)        \
    ((type) & ~PSA_KEY_TYPE_CATEGORY_FLAG_PAIR)

/** Raw data.
 *
 * A "key" of this type cannot be used for any cryptographic operation.
 * Applications may use this type to store arbitrary data in the keystore. */
#define PSA_KEY_TYPE_RAW_DATA                       ((psa_key_type_t)0x1001)

/** HMAC key.
 *
 * The key policy determines which underlying hash algorithm the key can be
 * used for.
 *
 * HMAC keys should generally have the same size as the underlying hash.
 * This size can be calculated with #PSA_HASH_SIZE(\c alg) where
 * \c alg is the HMAC algorithm or the underlying hash algorithm. */
#define PSA_KEY_TYPE_HMAC                           ((psa_key_type_t)0x1100)

/** A secret for key derivation.
 *
 * The key policy determines which key derivation algorithm the key
 * can be used for.
 */
#define PSA_KEY_TYPE_DERIVE                         ((psa_key_type_t)0x1200)

/** Key for a cipher, AEAD or MAC algorithm based on the AES block cipher.
 *
 * The size of the key can be 16 bytes (AES-128), 24 bytes (AES-192) or
 * 32 bytes (AES-256).
 */
#define PSA_KEY_TYPE_AES                            ((psa_key_type_t)0x2400)

/** Key for a cipher or MAC algorithm based on DES or 3DES (Triple-DES).
 *
 * The size of the key can be 8 bytes (single DES), 16 bytes (2-key 3DES) or
 * 24 bytes (3-key 3DES).
 *
 * Note that single DES and 2-key 3DES are weak and strongly
 * deprecated and should only be used to decrypt legacy data. 3-key 3DES
 * is weak and deprecated and should only be used in legacy protocols.
 */
#define PSA_KEY_TYPE_DES                            ((psa_key_type_t)0x2301)

/** Key for a cipher, AEAD or MAC algorithm based on the
 * Camellia block cipher. */
#define PSA_KEY_TYPE_CAMELLIA                       ((psa_key_type_t)0x2403)

/** Key for the RC4 stream cipher.
 *
 * Note that RC4 is weak and deprecated and should only be used in
 * legacy protocols. */
#define PSA_KEY_TYPE_ARC4                           ((psa_key_type_t)0x2002)

/** Key for the ChaCha20 stream cipher or the Chacha20-Poly1305 AEAD algorithm.
 *
 * ChaCha20 and the ChaCha20_Poly1305 construction are defined in RFC 7539.
 *
 * Implementations must support 12-byte nonces, may support 8-byte nonces,
 * and should reject other sizes.
 */
#define PSA_KEY_TYPE_CHACHA20                       ((psa_key_type_t)0x2004)

/** RSA public key. */
#define PSA_KEY_TYPE_RSA_PUBLIC_KEY                 ((psa_key_type_t)0x4001)
/** RSA key pair (private and public key). */
#define PSA_KEY_TYPE_RSA_KEY_PAIR                   ((psa_key_type_t)0x7001)
/** Whether a key type is an RSA key (pair or public-only). */
#define PSA_KEY_TYPE_IS_RSA(type)                                       \
    (PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) == PSA_KEY_TYPE_RSA_PUBLIC_KEY)

#define PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE            ((psa_key_type_t)0x4100)
#define PSA_KEY_TYPE_ECC_KEY_PAIR_BASE              ((psa_key_type_t)0x7100)
#define PSA_KEY_TYPE_ECC_CURVE_MASK                 ((psa_key_type_t)0x00ff)
/** Elliptic curve key pair.
 *
 * \param curve     A value of type ::psa_ecc_family_t that
 *                  identifies the ECC curve to be used.
 */
#define PSA_KEY_TYPE_ECC_KEY_PAIR(curve)         \
    (PSA_KEY_TYPE_ECC_KEY_PAIR_BASE | (curve))
/** Elliptic curve public key.
 *
 * \param curve     A value of type ::psa_ecc_family_t that
 *                  identifies the ECC curve to be used.
 */
#define PSA_KEY_TYPE_ECC_PUBLIC_KEY(curve)              \
    (PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE | (curve))

/** Whether a key type is an elliptic curve key (pair or public-only). */
#define PSA_KEY_TYPE_IS_ECC(type)                                       \
    ((PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) &                        \
      ~PSA_KEY_TYPE_ECC_CURVE_MASK) == PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE)
/** Whether a key type is an elliptic curve key pair. */
#define PSA_KEY_TYPE_IS_ECC_KEY_PAIR(type)                               \
    (((type) & ~PSA_KEY_TYPE_ECC_CURVE_MASK) ==                         \
     PSA_KEY_TYPE_ECC_KEY_PAIR_BASE)
/** Whether a key type is an elliptic curve public key. */
#define PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(type)                            \
    (((type) & ~PSA_KEY_TYPE_ECC_CURVE_MASK) ==                         \
     PSA_KEY_TYPE_ECC_PUBLIC_KEY_BASE)

/** Extract the curve from an elliptic curve key type. */
#define PSA_KEY_TYPE_ECC_GET_FAMILY(type)                        \
    ((psa_ecc_family_t) (PSA_KEY_TYPE_IS_ECC(type) ?             \
                        ((type) & PSA_KEY_TYPE_ECC_CURVE_MASK) : \
                        0))

/** SEC Koblitz curves over prime fields.
 *
 * This family comprises the following curves:
 * secp192k1, secp224k1, secp256k1.
 * They are defined in _Standards for Efficient Cryptography_,
 * _SEC 2: Recommended Elliptic Curve Domain Parameters_.
 * https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECP_K1           ((psa_ecc_family_t) 0x17)

/** SEC random curves over prime fields.
 *
 * This family comprises the following curves:
 * secp192k1, secp224r1, secp256r1, secp384r1, secp521r1.
 * They are defined in _Standards for Efficient Cryptography_,
 * _SEC 2: Recommended Elliptic Curve Domain Parameters_.
 * https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECP_R1           ((psa_ecc_family_t) 0x12)
/* SECP160R2 (SEC2 v1, obsolete) */
#define PSA_ECC_FAMILY_SECP_R2           ((psa_ecc_family_t) 0x1b)

/** SEC Koblitz curves over binary fields.
 *
 * This family comprises the following curves:
 * sect163k1, sect233k1, sect239k1, sect283k1, sect409k1, sect571k1.
 * They are defined in _Standards for Efficient Cryptography_,
 * _SEC 2: Recommended Elliptic Curve Domain Parameters_.
 * https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECT_K1           ((psa_ecc_family_t) 0x27)

/** SEC random curves over binary fields.
 *
 * This family comprises the following curves:
 * sect163r1, sect233r1, sect283r1, sect409r1, sect571r1.
 * They are defined in _Standards for Efficient Cryptography_,
 * _SEC 2: Recommended Elliptic Curve Domain Parameters_.
 * https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECT_R1           ((psa_ecc_family_t) 0x22)

/** SEC additional random curves over binary fields.
 *
 * This family comprises the following curve:
 * sect163r2.
 * It is defined in _Standards for Efficient Cryptography_,
 * _SEC 2: Recommended Elliptic Curve Domain Parameters_.
 * https://www.secg.org/sec2-v2.pdf
 */
#define PSA_ECC_FAMILY_SECT_R2           ((psa_ecc_family_t) 0x2b)

/** Brainpool P random curves.
 *
 * This family comprises the following curves:
 * brainpoolP160r1, brainpoolP192r1, brainpoolP224r1, brainpoolP256r1,
 * brainpoolP320r1, brainpoolP384r1, brainpoolP512r1.
 * It is defined in RFC 5639.
 */
#define PSA_ECC_FAMILY_BRAINPOOL_P_R1    ((psa_ecc_family_t) 0x30)

/** Curve25519 and Curve448.
 *
 * This family comprises the following Montgomery curves:
 * - 255-bit: Bernstein et al.,
 *   _Curve25519: new Diffie-Hellman speed records_, LNCS 3958, 2006.
 *   The algorithm #PSA_ALG_ECDH performs X25519 when used with this curve.
 * - 448-bit: Hamburg,
 *   _Ed448-Goldilocks, a new elliptic curve_, NIST ECC Workshop, 2015.
 *   The algorithm #PSA_ALG_ECDH performs X448 when used with this curve.
 */
#define PSA_ECC_FAMILY_MONTGOMERY        ((psa_ecc_family_t) 0x41)

#define PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE             ((psa_key_type_t)0x4200)
#define PSA_KEY_TYPE_DH_KEY_PAIR_BASE               ((psa_key_type_t)0x7200)
#define PSA_KEY_TYPE_DH_GROUP_MASK                  ((psa_key_type_t)0x00ff)
/** Diffie-Hellman key pair.
 *
 * \param group     A value of type ::psa_dh_family_t that identifies the
 *                  Diffie-Hellman group to be used.
 */
#define PSA_KEY_TYPE_DH_KEY_PAIR(group)          \
    (PSA_KEY_TYPE_DH_KEY_PAIR_BASE | (group))
/** Diffie-Hellman public key.
 *
 * \param group     A value of type ::psa_dh_family_t that identifies the
 *                  Diffie-Hellman group to be used.
 */
#define PSA_KEY_TYPE_DH_PUBLIC_KEY(group)               \
    (PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE | (group))

/** Whether a key type is a Diffie-Hellman key (pair or public-only). */
#define PSA_KEY_TYPE_IS_DH(type)                                        \
    ((PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) &                        \
      ~PSA_KEY_TYPE_DH_GROUP_MASK) == PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE)
/** Whether a key type is a Diffie-Hellman key pair. */
#define PSA_KEY_TYPE_IS_DH_KEY_PAIR(type)                               \
    (((type) & ~PSA_KEY_TYPE_DH_GROUP_MASK) ==                         \
     PSA_KEY_TYPE_DH_KEY_PAIR_BASE)
/** Whether a key type is a Diffie-Hellman public key. */
#define PSA_KEY_TYPE_IS_DH_PUBLIC_KEY(type)                            \
    (((type) & ~PSA_KEY_TYPE_DH_GROUP_MASK) ==                         \
     PSA_KEY_TYPE_DH_PUBLIC_KEY_BASE)

/** Extract the group from a Diffie-Hellman key type. */
#define PSA_KEY_TYPE_DH_GET_FAMILY(type)                        \
    ((psa_dh_family_t) (PSA_KEY_TYPE_IS_DH(type) ?              \
                       ((type) & PSA_KEY_TYPE_DH_GROUP_MASK) :  \
                       0))

/** Diffie-Hellman groups defined in RFC 7919 Appendix A.
 *
 * This family includes groups with the following key sizes (in bits):
 * 2048, 3072, 4096, 6144, 8192. A given implementation may support
 * all of these sizes or only a subset.
 */
#define PSA_DH_FAMILY_RFC7919            ((psa_dh_family_t) 0x03)

#define PSA_GET_KEY_TYPE_BLOCK_SIZE_EXPONENT(type)      \
    (((type) >> 8) & 7)
/** The block size of a block cipher.
 *
 * \param type  A cipher key type (value of type #psa_key_type_t).
 *
 * \return      The block size for a block cipher, or 1 for a stream cipher.
 *              The return value is undefined if \p type is not a supported
 *              cipher key type.
 *
 * \note It is possible to build stream cipher algorithms on top of a block
 *       cipher, for example CTR mode (#PSA_ALG_CTR).
 *       This macro only takes the key type into account, so it cannot be
 *       used to determine the size of the data that #psa_cipher_update()
 *       might buffer for future processing in general.
 *
 * \note This macro returns a compile-time constant if its argument is one.
 *
 * \warning This macro may evaluate its argument multiple times.
 */
#define PSA_BLOCK_CIPHER_BLOCK_SIZE(type)            \
    (((type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_SYMMETRIC ? \
     1u << PSA_GET_KEY_TYPE_BLOCK_SIZE_EXPONENT(type) :                 \
     0u)

/** Vendor-defined algorithm flag.
 *
 * Algorithms defined by this standard will never have the #PSA_ALG_VENDOR_FLAG
 * bit set. Vendors who define additional algorithms must use an encoding with
 * the #PSA_ALG_VENDOR_FLAG bit set and should respect the bitwise structure
 * used by standard encodings whenever practical.
 */
#define PSA_ALG_VENDOR_FLAG                     ((psa_algorithm_t)0x80000000)

#define PSA_ALG_CATEGORY_MASK                   ((psa_algorithm_t)0x7f000000)
#define PSA_ALG_CATEGORY_HASH                   ((psa_algorithm_t)0x01000000)
#define PSA_ALG_CATEGORY_MAC                    ((psa_algorithm_t)0x02000000)
#define PSA_ALG_CATEGORY_CIPHER                 ((psa_algorithm_t)0x04000000)
#define PSA_ALG_CATEGORY_AEAD                   ((psa_algorithm_t)0x06000000)
#define PSA_ALG_CATEGORY_SIGN                   ((psa_algorithm_t)0x10000000)
#define PSA_ALG_CATEGORY_ASYMMETRIC_ENCRYPTION  ((psa_algorithm_t)0x12000000)
#define PSA_ALG_CATEGORY_KEY_DERIVATION         ((psa_algorithm_t)0x20000000)
#define PSA_ALG_CATEGORY_KEY_AGREEMENT          ((psa_algorithm_t)0x30000000)

/** Whether an algorithm is vendor-defined.
 *
 * See also #PSA_ALG_VENDOR_FLAG.
 */
#define PSA_ALG_IS_VENDOR_DEFINED(alg)                                  \
    (((alg) & PSA_ALG_VENDOR_FLAG) != 0)

/** Whether the specified algorithm is a hash algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a hash algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_HASH(alg)                                            \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_HASH)

/** Whether the specified algorithm is a MAC algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a MAC algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_MAC(alg)                                             \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_MAC)

/** Whether the specified algorithm is a symmetric cipher algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a symmetric cipher algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_CIPHER(alg)                                          \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_CIPHER)

/** Whether the specified algorithm is an authenticated encryption
 * with associated data (AEAD) algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is an AEAD algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_AEAD(alg)                                            \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_AEAD)

/** Whether the specified algorithm is an asymmetric signature algorithm,
 * also known as public-key signature algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is an asymmetric signature algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_SIGN(alg)                                            \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_SIGN)

/** Whether the specified algorithm is an asymmetric encryption algorithm,
 * also known as public-key encryption algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is an asymmetric encryption algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg)                           \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_ASYMMETRIC_ENCRYPTION)

/** Whether the specified algorithm is a key agreement algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a key agreement algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_KEY_AGREEMENT(alg)                                   \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_KEY_AGREEMENT)

/** Whether the specified algorithm is a key derivation algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a key derivation algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_KEY_DERIVATION(alg)                                  \
    (((alg) & PSA_ALG_CATEGORY_MASK) == PSA_ALG_CATEGORY_KEY_DERIVATION)

#define PSA_ALG_HASH_MASK                       ((psa_algorithm_t)0x000000ff)
/** MD2 */
#define PSA_ALG_MD2                             ((psa_algorithm_t)0x01000001)
/** MD4 */
#define PSA_ALG_MD4                             ((psa_algorithm_t)0x01000002)
/** MD5 */
#define PSA_ALG_MD5                             ((psa_algorithm_t)0x01000003)
/** PSA_ALG_RIPEMD160 */
#define PSA_ALG_RIPEMD160                       ((psa_algorithm_t)0x01000004)
/** SHA1 */
#define PSA_ALG_SHA_1                           ((psa_algorithm_t)0x01000005)
/** SHA2-224 */
#define PSA_ALG_SHA_224                         ((psa_algorithm_t)0x01000008)
/** SHA2-256 */
#define PSA_ALG_SHA_256                         ((psa_algorithm_t)0x01000009)
/** SHA2-384 */
#define PSA_ALG_SHA_384                         ((psa_algorithm_t)0x0100000a)
/** SHA2-512 */
#define PSA_ALG_SHA_512                         ((psa_algorithm_t)0x0100000b)
/** SHA2-512/224 */
#define PSA_ALG_SHA_512_224                     ((psa_algorithm_t)0x0100000c)
/** SHA2-512/256 */
#define PSA_ALG_SHA_512_256                     ((psa_algorithm_t)0x0100000d)
/** SHA3-224 */
#define PSA_ALG_SHA3_224                        ((psa_algorithm_t)0x01000010)
/** SHA3-256 */
#define PSA_ALG_SHA3_256                        ((psa_algorithm_t)0x01000011)
/** SHA3-384 */
#define PSA_ALG_SHA3_384                        ((psa_algorithm_t)0x01000012)
/** SHA3-512 */
#define PSA_ALG_SHA3_512                        ((psa_algorithm_t)0x01000013)

/** In a hash-and-sign algorithm policy, allow any hash algorithm.
 *
 * This value may be used to form the algorithm usage field of a policy
 * for a signature algorithm that is parametrized by a hash. The key
 * may then be used to perform operations using the same signature
 * algorithm parametrized with any supported hash.
 *
 * That is, suppose that `PSA_xxx_SIGNATURE` is one of the following macros:
 * - #PSA_ALG_RSA_PKCS1V15_SIGN, #PSA_ALG_RSA_PSS,
 * - #PSA_ALG_ECDSA, #PSA_ALG_DETERMINISTIC_ECDSA.
 * Then you may create and use a key as follows:
 * - Set the key usage field using #PSA_ALG_ANY_HASH, for example:
 *   ```
 *   psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_SIGN_HASH); // or VERIFY
 *   psa_set_key_algorithm(&attributes, PSA_xxx_SIGNATURE(PSA_ALG_ANY_HASH));
 *   ```
 * - Import or generate key material.
 * - Call psa_sign_hash() or psa_verify_hash(), passing
 *   an algorithm built from `PSA_xxx_SIGNATURE` and a specific hash. Each
 *   call to sign or verify a message may use a different hash.
 *   ```
 *   psa_sign_hash(key, PSA_xxx_SIGNATURE(PSA_ALG_SHA_256), ...);
 *   psa_sign_hash(key, PSA_xxx_SIGNATURE(PSA_ALG_SHA_512), ...);
 *   psa_sign_hash(key, PSA_xxx_SIGNATURE(PSA_ALG_SHA3_256), ...);
 *   ```
 *
 * This value may not be used to build other algorithms that are
 * parametrized over a hash. For any valid use of this macro to build
 * an algorithm \c alg, #PSA_ALG_IS_HASH_AND_SIGN(\c alg) is true.
 *
 * This value may not be used to build an algorithm specification to
 * perform an operation. It is only valid to build policies.
 */
#define PSA_ALG_ANY_HASH                        ((psa_algorithm_t)0x010000ff)

#define PSA_ALG_MAC_SUBCATEGORY_MASK            ((psa_algorithm_t)0x00c00000)
#define PSA_ALG_HMAC_BASE                       ((psa_algorithm_t)0x02800000)
/** Macro to build an HMAC algorithm.
 *
 * For example, #PSA_ALG_HMAC(#PSA_ALG_SHA_256) is HMAC-SHA-256.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *
 * \return              The corresponding HMAC algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_HMAC(hash_alg)                                  \
    (PSA_ALG_HMAC_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_HMAC_GET_HASH(hmac_alg)                             \
    (PSA_ALG_CATEGORY_HASH | ((hmac_alg) & PSA_ALG_HASH_MASK))

/** Whether the specified algorithm is an HMAC algorithm.
 *
 * HMAC is a family of MAC algorithms that are based on a hash function.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is an HMAC algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_HMAC(alg)                                            \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_MAC_SUBCATEGORY_MASK)) == \
     PSA_ALG_HMAC_BASE)

/* In the encoding of a MAC algorithm, the bits corresponding to
 * PSA_ALG_MAC_TRUNCATION_MASK encode the length to which the MAC is
 * truncated. As an exception, the value 0 means the untruncated algorithm,
 * whatever its length is. The length is encoded in 6 bits, so it can
 * reach up to 63; the largest MAC is 64 bytes so its trivial truncation
 * to full length is correctly encoded as 0 and any non-trivial truncation
 * is correctly encoded as a value between 1 and 63. */
#define PSA_ALG_MAC_TRUNCATION_MASK             ((psa_algorithm_t)0x00003f00)
#define PSA_MAC_TRUNCATION_OFFSET 8

/** Macro to build a truncated MAC algorithm.
 *
 * A truncated MAC algorithm is identical to the corresponding MAC
 * algorithm except that the MAC value for the truncated algorithm
 * consists of only the first \p mac_length bytes of the MAC value
 * for the untruncated algorithm.
 *
 * \note    This macro may allow constructing algorithm identifiers that
 *          are not valid, either because the specified length is larger
 *          than the untruncated MAC or because the specified length is
 *          smaller than permitted by the implementation.
 *
 * \note    It is implementation-defined whether a truncated MAC that
 *          is truncated to the same length as the MAC of the untruncated
 *          algorithm is considered identical to the untruncated algorithm
 *          for policy comparison purposes.
 *
 * \param mac_alg       A MAC algorithm identifier (value of type
 *                      #psa_algorithm_t such that #PSA_ALG_IS_MAC(\p alg)
 *                      is true). This may be a truncated or untruncated
 *                      MAC algorithm.
 * \param mac_length    Desired length of the truncated MAC in bytes.
 *                      This must be at most the full length of the MAC
 *                      and must be at least an implementation-specified
 *                      minimum. The implementation-specified minimum
 *                      shall not be zero.
 *
 * \return              The corresponding MAC algorithm with the specified
 *                      length.
 * \return              Unspecified if \p alg is not a supported
 *                      MAC algorithm or if \p mac_length is too small or
 *                      too large for the specified MAC algorithm.
 */
#define PSA_ALG_TRUNCATED_MAC(mac_alg, mac_length)                      \
    (((mac_alg) & ~PSA_ALG_MAC_TRUNCATION_MASK) |                       \
     ((mac_length) << PSA_MAC_TRUNCATION_OFFSET & PSA_ALG_MAC_TRUNCATION_MASK))

/** Macro to build the base MAC algorithm corresponding to a truncated
 * MAC algorithm.
 *
 * \param mac_alg       A MAC algorithm identifier (value of type
 *                      #psa_algorithm_t such that #PSA_ALG_IS_MAC(\p alg)
 *                      is true). This may be a truncated or untruncated
 *                      MAC algorithm.
 *
 * \return              The corresponding base MAC algorithm.
 * \return              Unspecified if \p alg is not a supported
 *                      MAC algorithm.
 */
#define PSA_ALG_FULL_LENGTH_MAC(mac_alg)        \
    ((mac_alg) & ~PSA_ALG_MAC_TRUNCATION_MASK)

/** Length to which a MAC algorithm is truncated.
 *
 * \param mac_alg       A MAC algorithm identifier (value of type
 *                      #psa_algorithm_t such that #PSA_ALG_IS_MAC(\p alg)
 *                      is true).
 *
 * \return              Length of the truncated MAC in bytes.
 * \return              0 if \p alg is a non-truncated MAC algorithm.
 * \return              Unspecified if \p alg is not a supported
 *                      MAC algorithm.
 */
#define PSA_MAC_TRUNCATED_LENGTH(mac_alg)                               \
    (((mac_alg) & PSA_ALG_MAC_TRUNCATION_MASK) >> PSA_MAC_TRUNCATION_OFFSET)

#define PSA_ALG_CIPHER_MAC_BASE                 ((psa_algorithm_t)0x02c00000)
/** The CBC-MAC construction over a block cipher
 *
 * \warning CBC-MAC is insecure in many cases.
 * A more secure mode, such as #PSA_ALG_CMAC, is recommended.
 */
#define PSA_ALG_CBC_MAC                         ((psa_algorithm_t)0x02c00001)
/** The CMAC construction over a block cipher */
#define PSA_ALG_CMAC                            ((psa_algorithm_t)0x02c00002)

/** Whether the specified algorithm is a MAC algorithm based on a block cipher.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a MAC algorithm based on a block cipher, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_BLOCK_CIPHER_MAC(alg)                                \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_MAC_SUBCATEGORY_MASK)) == \
     PSA_ALG_CIPHER_MAC_BASE)

#define PSA_ALG_CIPHER_STREAM_FLAG              ((psa_algorithm_t)0x00800000)
#define PSA_ALG_CIPHER_FROM_BLOCK_FLAG          ((psa_algorithm_t)0x00400000)

/** Whether the specified algorithm is a stream cipher.
 *
 * A stream cipher is a symmetric cipher that encrypts or decrypts messages
 * by applying a bitwise-xor with a stream of bytes that is generated
 * from a key.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a stream cipher algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier or if it is not a symmetric cipher algorithm.
 */
#define PSA_ALG_IS_STREAM_CIPHER(alg)            \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_CIPHER_STREAM_FLAG)) == \
        (PSA_ALG_CATEGORY_CIPHER | PSA_ALG_CIPHER_STREAM_FLAG))

/** The ARC4 stream cipher algorithm.
 */
#define PSA_ALG_ARC4                            ((psa_algorithm_t)0x04800001)

/** The ChaCha20 stream cipher.
 *
 * ChaCha20 is defined in RFC 7539.
 *
 * The nonce size for psa_cipher_set_iv() or psa_cipher_generate_iv()
 * must be 12.
 *
 * The initial block counter is always 0.
 *
 */
#define PSA_ALG_CHACHA20                        ((psa_algorithm_t)0x04800005)

/** The CTR stream cipher mode.
 *
 * CTR is a stream cipher which is built from a block cipher.
 * The underlying block cipher is determined by the key type.
 * For example, to use AES-128-CTR, use this algorithm with
 * a key of type #PSA_KEY_TYPE_AES and a length of 128 bits (16 bytes).
 */
#define PSA_ALG_CTR                             ((psa_algorithm_t)0x04c00001)

/** The CFB stream cipher mode.
 *
 * The underlying block cipher is determined by the key type.
 */
#define PSA_ALG_CFB                             ((psa_algorithm_t)0x04c00002)

/** The OFB stream cipher mode.
 *
 * The underlying block cipher is determined by the key type.
 */
#define PSA_ALG_OFB                             ((psa_algorithm_t)0x04c00003)

/** The XTS cipher mode.
 *
 * XTS is a cipher mode which is built from a block cipher. It requires at
 * least one full block of input, but beyond this minimum the input
 * does not need to be a whole number of blocks.
 */
#define PSA_ALG_XTS                             ((psa_algorithm_t)0x044000ff)

/** The Electronic Code Book (ECB) mode of a block cipher, with no padding.
 *
 * \warning ECB mode does not protect the confidentiality of the encrypted data
 * except in extremely narrow circumstances. It is recommended that applications
 * only use ECB if they need to construct an operating mode that the
 * implementation does not provide. Implementations are encouraged to provide
 * the modes that applications need in preference to supporting direct access
 * to ECB.
 *
 * The underlying block cipher is determined by the key type.
 *
 * This symmetric cipher mode can only be used with messages whose lengths are a
 * multiple of the block size of the chosen block cipher.
 *
 * ECB mode does not accept an initialization vector (IV). When using a
 * multi-part cipher operation with this algorithm, psa_cipher_generate_iv()
 * and psa_cipher_set_iv() must not be called.
 */
#define PSA_ALG_ECB_NO_PADDING                  ((psa_algorithm_t)0x04404400)

/** The CBC block cipher chaining mode, with no padding.
 *
 * The underlying block cipher is determined by the key type.
 *
 * This symmetric cipher mode can only be used with messages whose lengths
 * are whole number of blocks for the chosen block cipher.
 */
#define PSA_ALG_CBC_NO_PADDING                  ((psa_algorithm_t)0x04600100)

/** The CBC block cipher chaining mode with PKCS#7 padding.
 *
 * The underlying block cipher is determined by the key type.
 *
 * This is the padding method defined by PKCS#7 (RFC 2315) &sect;10.3.
 */
#define PSA_ALG_CBC_PKCS7                       ((psa_algorithm_t)0x04600101)

#define PSA_ALG_AEAD_FROM_BLOCK_FLAG            ((psa_algorithm_t)0x00400000)

/** Whether the specified algorithm is an AEAD mode on a block cipher.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is an AEAD algorithm which is an AEAD mode based on
 *         a block cipher, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_AEAD_ON_BLOCK_CIPHER(alg)    \
    (((alg) & (PSA_ALG_CATEGORY_MASK | PSA_ALG_AEAD_FROM_BLOCK_FLAG)) == \
     (PSA_ALG_CATEGORY_AEAD | PSA_ALG_AEAD_FROM_BLOCK_FLAG))

/** The CCM authenticated encryption algorithm.
 *
 * The underlying block cipher is determined by the key type.
 */
#define PSA_ALG_CCM                             ((psa_algorithm_t)0x06401001)

/** The GCM authenticated encryption algorithm.
 *
 * The underlying block cipher is determined by the key type.
 */
#define PSA_ALG_GCM                             ((psa_algorithm_t)0x06401002)

/** The Chacha20-Poly1305 AEAD algorithm.
 *
 * The ChaCha20_Poly1305 construction is defined in RFC 7539.
 *
 * Implementations must support 12-byte nonces, may support 8-byte nonces,
 * and should reject other sizes.
 *
 * Implementations must support 16-byte tags and should reject other sizes.
 */
#define PSA_ALG_CHACHA20_POLY1305               ((psa_algorithm_t)0x06001005)

/* In the encoding of a AEAD algorithm, the bits corresponding to
 * PSA_ALG_AEAD_TAG_LENGTH_MASK encode the length of the AEAD tag.
 * The constants for default lengths follow this encoding.
 */
#define PSA_ALG_AEAD_TAG_LENGTH_MASK            ((psa_algorithm_t)0x00003f00)
#define PSA_AEAD_TAG_LENGTH_OFFSET 8

/** Macro to build a shortened AEAD algorithm.
 *
 * A shortened AEAD algorithm is similar to the corresponding AEAD
 * algorithm, but has an authentication tag that consists of fewer bytes.
 * Depending on the algorithm, the tag length may affect the calculation
 * of the ciphertext.
 *
 * \param aead_alg      An AEAD algorithm identifier (value of type
 *                      #psa_algorithm_t such that #PSA_ALG_IS_AEAD(\p alg)
 *                      is true).
 * \param tag_length    Desired length of the authentication tag in bytes.
 *
 * \return              The corresponding AEAD algorithm with the specified
 *                      length.
 * \return              Unspecified if \p alg is not a supported
 *                      AEAD algorithm or if \p tag_length is not valid
 *                      for the specified AEAD algorithm.
 */
#define PSA_ALG_AEAD_WITH_TAG_LENGTH(aead_alg, tag_length)              \
    (((aead_alg) & ~PSA_ALG_AEAD_TAG_LENGTH_MASK) |                     \
     ((tag_length) << PSA_AEAD_TAG_LENGTH_OFFSET &                      \
      PSA_ALG_AEAD_TAG_LENGTH_MASK))

/** Calculate the corresponding AEAD algorithm with the default tag length.
 *
 * \param aead_alg      An AEAD algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_AEAD(\p alg) is true).
 *
 * \return              The corresponding AEAD algorithm with the default
 *                      tag length for that algorithm.
 */
#define PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH(aead_alg)                   \
    (                                                                    \
        PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, PSA_ALG_CCM) \
        PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, PSA_ALG_GCM) \
        PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, PSA_ALG_CHACHA20_POLY1305) \
        0)
#define PSA_ALG_AEAD_WITH_DEFAULT_TAG_LENGTH_CASE(aead_alg, ref)         \
    PSA_ALG_AEAD_WITH_TAG_LENGTH(aead_alg, 0) ==                         \
    PSA_ALG_AEAD_WITH_TAG_LENGTH(ref, 0) ?                               \
    ref :

#define PSA_ALG_RSA_PKCS1V15_SIGN_BASE          ((psa_algorithm_t)0x10020000)
/** RSA PKCS#1 v1.5 signature with hashing.
 *
 * This is the signature scheme defined by RFC 8017
 * (PKCS#1: RSA Cryptography Specifications) under the name
 * RSASSA-PKCS1-v1_5.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *                      This includes #PSA_ALG_ANY_HASH
 *                      when specifying the algorithm in a usage policy.
 *
 * \return              The corresponding RSA PKCS#1 v1.5 signature algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_RSA_PKCS1V15_SIGN(hash_alg)                             \
    (PSA_ALG_RSA_PKCS1V15_SIGN_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
/** Raw PKCS#1 v1.5 signature.
 *
 * The input to this algorithm is the DigestInfo structure used by
 * RFC 8017 (PKCS#1: RSA Cryptography Specifications), &sect;9.2
 * steps 3&ndash;6.
 */
#define PSA_ALG_RSA_PKCS1V15_SIGN_RAW PSA_ALG_RSA_PKCS1V15_SIGN_BASE
#define PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg)                               \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_RSA_PKCS1V15_SIGN_BASE)

#define PSA_ALG_RSA_PSS_BASE               ((psa_algorithm_t)0x10030000)
/** RSA PSS signature with hashing.
 *
 * This is the signature scheme defined by RFC 8017
 * (PKCS#1: RSA Cryptography Specifications) under the name
 * RSASSA-PSS, with the message generation function MGF1, and with
 * a salt length equal to the length of the hash. The specified
 * hash algorithm is used to hash the input message, to create the
 * salted hash, and for the mask generation.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *                      This includes #PSA_ALG_ANY_HASH
 *                      when specifying the algorithm in a usage policy.
 *
 * \return              The corresponding RSA PSS signature algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_RSA_PSS(hash_alg)                               \
    (PSA_ALG_RSA_PSS_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_IS_RSA_PSS(alg)                                 \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_RSA_PSS_BASE)

#define PSA_ALG_ECDSA_BASE                      ((psa_algorithm_t)0x10060000)
/** ECDSA signature with hashing.
 *
 * This is the ECDSA signature scheme defined by ANSI X9.62,
 * with a random per-message secret number (*k*).
 *
 * The representation of the signature as a byte string consists of
 * the concatentation of the signature values *r* and *s*. Each of
 * *r* and *s* is encoded as an *N*-octet string, where *N* is the length
 * of the base point of the curve in octets. Each value is represented
 * in big-endian order (most significant octet first).
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *                      This includes #PSA_ALG_ANY_HASH
 *                      when specifying the algorithm in a usage policy.
 *
 * \return              The corresponding ECDSA signature algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_ECDSA(hash_alg)                                 \
    (PSA_ALG_ECDSA_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
/** ECDSA signature without hashing.
 *
 * This is the same signature scheme as #PSA_ALG_ECDSA(), but
 * without specifying a hash algorithm. This algorithm may only be
 * used to sign or verify a sequence of bytes that should be an
 * already-calculated hash. Note that the input is padded with
 * zeros on the left or truncated on the left as required to fit
 * the curve size.
 */
#define PSA_ALG_ECDSA_ANY PSA_ALG_ECDSA_BASE
#define PSA_ALG_DETERMINISTIC_ECDSA_BASE        ((psa_algorithm_t)0x10070000)
/** Deterministic ECDSA signature with hashing.
 *
 * This is the deterministic ECDSA signature scheme defined by RFC 6979.
 *
 * The representation of a signature is the same as with #PSA_ALG_ECDSA().
 *
 * Note that when this algorithm is used for verification, signatures
 * made with randomized ECDSA (#PSA_ALG_ECDSA(\p hash_alg)) with the
 * same private key are accepted. In other words,
 * #PSA_ALG_DETERMINISTIC_ECDSA(\p hash_alg) differs from
 * #PSA_ALG_ECDSA(\p hash_alg) only for signature, not for verification.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *                      This includes #PSA_ALG_ANY_HASH
 *                      when specifying the algorithm in a usage policy.
 *
 * \return              The corresponding deterministic ECDSA signature
 *                      algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_DETERMINISTIC_ECDSA(hash_alg)                           \
    (PSA_ALG_DETERMINISTIC_ECDSA_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_ECDSA_DETERMINISTIC_FLAG        ((psa_algorithm_t)0x00010000)
#define PSA_ALG_IS_ECDSA(alg)                                           \
    (((alg) & ~PSA_ALG_HASH_MASK & ~PSA_ALG_ECDSA_DETERMINISTIC_FLAG) ==  \
     PSA_ALG_ECDSA_BASE)
#define PSA_ALG_ECDSA_IS_DETERMINISTIC(alg)             \
    (((alg) & PSA_ALG_ECDSA_DETERMINISTIC_FLAG) != 0)
#define PSA_ALG_IS_DETERMINISTIC_ECDSA(alg)                             \
    (PSA_ALG_IS_ECDSA(alg) && PSA_ALG_ECDSA_IS_DETERMINISTIC(alg))
#define PSA_ALG_IS_RANDOMIZED_ECDSA(alg)                                \
    (PSA_ALG_IS_ECDSA(alg) && !PSA_ALG_ECDSA_IS_DETERMINISTIC(alg))

/** Whether the specified algorithm is a hash-and-sign algorithm.
 *
 * Hash-and-sign algorithms are asymmetric (public-key) signature algorithms
 * structured in two parts: first the calculation of a hash in a way that
 * does not depend on the key, then the calculation of a signature from the
 * hash value and the key.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a hash-and-sign algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_HASH_AND_SIGN(alg)                                   \
    (PSA_ALG_IS_RSA_PSS(alg) || PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) ||    \
     PSA_ALG_IS_ECDSA(alg))

/** Get the hash used by a hash-and-sign signature algorithm.
 *
 * A hash-and-sign algorithm is a signature algorithm which is
 * composed of two phases: first a hashing phase which does not use
 * the key and produces a hash of the input message, then a signing
 * phase which only uses the hash and the key and not the message
 * itself.
 *
 * \param alg   A signature algorithm (\c PSA_ALG_XXX value such that
 *              #PSA_ALG_IS_SIGN(\p alg) is true).
 *
 * \return      The underlying hash algorithm if \p alg is a hash-and-sign
 *              algorithm.
 * \return      0 if \p alg is a signature algorithm that does not
 *              follow the hash-and-sign structure.
 * \return      Unspecified if \p alg is not a signature algorithm or
 *              if it is not supported by the implementation.
 */
#define PSA_ALG_SIGN_GET_HASH(alg)                                     \
    (PSA_ALG_IS_HASH_AND_SIGN(alg) ?                                   \
     ((alg) & PSA_ALG_HASH_MASK) == 0 ? /*"raw" algorithm*/ 0 :        \
     ((alg) & PSA_ALG_HASH_MASK) | PSA_ALG_CATEGORY_HASH :             \
     0)

/** RSA PKCS#1 v1.5 encryption.
 */
#define PSA_ALG_RSA_PKCS1V15_CRYPT              ((psa_algorithm_t)0x12020000)

#define PSA_ALG_RSA_OAEP_BASE                   ((psa_algorithm_t)0x12030000)
/** RSA OAEP encryption.
 *
 * This is the encryption scheme defined by RFC 8017
 * (PKCS#1: RSA Cryptography Specifications) under the name
 * RSAES-OAEP, with the message generation function MGF1.
 *
 * \param hash_alg      The hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true) to use
 *                      for MGF1.
 *
 * \return              The corresponding RSA OAEP encryption algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_RSA_OAEP(hash_alg)                              \
    (PSA_ALG_RSA_OAEP_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
#define PSA_ALG_IS_RSA_OAEP(alg)                                \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_RSA_OAEP_BASE)
#define PSA_ALG_RSA_OAEP_GET_HASH(alg)                          \
    (PSA_ALG_IS_RSA_OAEP(alg) ?                                 \
     ((alg) & PSA_ALG_HASH_MASK) | PSA_ALG_CATEGORY_HASH :      \
     0)

#define PSA_ALG_HKDF_BASE                       ((psa_algorithm_t)0x20000100)
/** Macro to build an HKDF algorithm.
 *
 * For example, `PSA_ALG_HKDF(PSA_ALG_SHA256)` is HKDF using HMAC-SHA-256.
 *
 * This key derivation algorithm uses the following inputs:
 * - #PSA_KEY_DERIVATION_INPUT_SALT is the salt used in the "extract" step.
 *   It is optional; if omitted, the derivation uses an empty salt.
 * - #PSA_KEY_DERIVATION_INPUT_SECRET is the secret key used in the "extract" step.
 * - #PSA_KEY_DERIVATION_INPUT_INFO is the info string used in the "expand" step.
 * You must pass #PSA_KEY_DERIVATION_INPUT_SALT before #PSA_KEY_DERIVATION_INPUT_SECRET.
 * You may pass #PSA_KEY_DERIVATION_INPUT_INFO at any time after steup and before
 * starting to generate output.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *
 * \return              The corresponding HKDF algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_HKDF(hash_alg)                                  \
    (PSA_ALG_HKDF_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))
/** Whether the specified algorithm is an HKDF algorithm.
 *
 * HKDF is a family of key derivation algorithms that are based on a hash
 * function and the HMAC construction.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \c alg is an HKDF algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \c alg is not a supported
 *         key derivation algorithm identifier.
 */
#define PSA_ALG_IS_HKDF(alg)                            \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_HKDF_BASE)
#define PSA_ALG_HKDF_GET_HASH(hkdf_alg)                         \
    (PSA_ALG_CATEGORY_HASH | ((hkdf_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_TLS12_PRF_BASE                  ((psa_algorithm_t)0x20000200)
/** Macro to build a TLS-1.2 PRF algorithm.
 *
 * TLS 1.2 uses a custom pseudorandom function (PRF) for key schedule,
 * specified in Section 5 of RFC 5246. It is based on HMAC and can be
 * used with either SHA-256 or SHA-384.
 *
 * This key derivation algorithm uses the following inputs, which must be
 * passed in the order given here:
 * - #PSA_KEY_DERIVATION_INPUT_SEED is the seed.
 * - #PSA_KEY_DERIVATION_INPUT_SECRET is the secret key.
 * - #PSA_KEY_DERIVATION_INPUT_LABEL is the label.
 *
 * For the application to TLS-1.2 key expansion, the seed is the
 * concatenation of ServerHello.Random + ClientHello.Random,
 * and the label is "key expansion".
 *
 * For example, `PSA_ALG_TLS12_PRF(PSA_ALG_SHA256)` represents the
 * TLS 1.2 PRF using HMAC-SHA-256.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *
 * \return              The corresponding TLS-1.2 PRF algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_TLS12_PRF(hash_alg)                                  \
    (PSA_ALG_TLS12_PRF_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))

/** Whether the specified algorithm is a TLS-1.2 PRF algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \c alg is a TLS-1.2 PRF algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \c alg is not a supported
 *         key derivation algorithm identifier.
 */
#define PSA_ALG_IS_TLS12_PRF(alg)                                    \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_TLS12_PRF_BASE)
#define PSA_ALG_TLS12_PRF_GET_HASH(hkdf_alg)                         \
    (PSA_ALG_CATEGORY_HASH | ((hkdf_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_TLS12_PSK_TO_MS_BASE            ((psa_algorithm_t)0x20000300)
/** Macro to build a TLS-1.2 PSK-to-MasterSecret algorithm.
 *
 * In a pure-PSK handshake in TLS 1.2, the master secret is derived
 * from the PreSharedKey (PSK) through the application of padding
 * (RFC 4279, Section 2) and the TLS-1.2 PRF (RFC 5246, Section 5).
 * The latter is based on HMAC and can be used with either SHA-256
 * or SHA-384.
 *
 * This key derivation algorithm uses the following inputs, which must be
 * passed in the order given here:
 * - #PSA_KEY_DERIVATION_INPUT_SEED is the seed.
 * - #PSA_KEY_DERIVATION_INPUT_SECRET is the secret key.
 * - #PSA_KEY_DERIVATION_INPUT_LABEL is the label.
 *
 * For the application to TLS-1.2, the seed (which is
 * forwarded to the TLS-1.2 PRF) is the concatenation of the
 * ClientHello.Random + ServerHello.Random,
 * and the label is "master secret" or "extended master secret".
 *
 * For example, `PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA256)` represents the
 * TLS-1.2 PSK to MasterSecret derivation PRF using HMAC-SHA-256.
 *
 * \param hash_alg      A hash algorithm (\c PSA_ALG_XXX value such that
 *                      #PSA_ALG_IS_HASH(\p hash_alg) is true).
 *
 * \return              The corresponding TLS-1.2 PSK to MS algorithm.
 * \return              Unspecified if \p hash_alg is not a supported
 *                      hash algorithm.
 */
#define PSA_ALG_TLS12_PSK_TO_MS(hash_alg)                                  \
    (PSA_ALG_TLS12_PSK_TO_MS_BASE | ((hash_alg) & PSA_ALG_HASH_MASK))

/** Whether the specified algorithm is a TLS-1.2 PSK to MS algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \c alg is a TLS-1.2 PSK to MS algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \c alg is not a supported
 *         key derivation algorithm identifier.
 */
#define PSA_ALG_IS_TLS12_PSK_TO_MS(alg)                                    \
    (((alg) & ~PSA_ALG_HASH_MASK) == PSA_ALG_TLS12_PSK_TO_MS_BASE)
#define PSA_ALG_TLS12_PSK_TO_MS_GET_HASH(hkdf_alg)                         \
    (PSA_ALG_CATEGORY_HASH | ((hkdf_alg) & PSA_ALG_HASH_MASK))

#define PSA_ALG_KEY_DERIVATION_MASK             ((psa_algorithm_t)0x0803ffff)
#define PSA_ALG_KEY_AGREEMENT_MASK              ((psa_algorithm_t)0x10fc0000)

/** Macro to build a combined algorithm that chains a key agreement with
 * a key derivation.
 *
 * \param ka_alg        A key agreement algorithm (\c PSA_ALG_XXX value such
 *                      that #PSA_ALG_IS_KEY_AGREEMENT(\p ka_alg) is true).
 * \param kdf_alg       A key derivation algorithm (\c PSA_ALG_XXX value such
 *                      that #PSA_ALG_IS_KEY_DERIVATION(\p kdf_alg) is true).
 *
 * \return              The corresponding key agreement and derivation
 *                      algorithm.
 * \return              Unspecified if \p ka_alg is not a supported
 *                      key agreement algorithm or \p kdf_alg is not a
 *                      supported key derivation algorithm.
 */
#define PSA_ALG_KEY_AGREEMENT(ka_alg, kdf_alg)  \
    ((ka_alg) | (kdf_alg))

#define PSA_ALG_KEY_AGREEMENT_GET_KDF(alg)                              \
    (((alg) & PSA_ALG_KEY_DERIVATION_MASK) | PSA_ALG_CATEGORY_KEY_DERIVATION)

#define PSA_ALG_KEY_AGREEMENT_GET_BASE(alg)                             \
    (((alg) & PSA_ALG_KEY_AGREEMENT_MASK) | PSA_ALG_CATEGORY_KEY_AGREEMENT)

/** Whether the specified algorithm is a raw key agreement algorithm.
 *
 * A raw key agreement algorithm is one that does not specify
 * a key derivation function.
 * Usually, raw key agreement algorithms are constructed directly with
 * a \c PSA_ALG_xxx macro while non-raw key agreement algorithms are
 * constructed with #PSA_ALG_KEY_AGREEMENT().
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \p alg is a raw key agreement algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \p alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_RAW_KEY_AGREEMENT(alg)                               \
    (PSA_ALG_IS_KEY_AGREEMENT(alg) &&                                   \
     PSA_ALG_KEY_AGREEMENT_GET_KDF(alg) == PSA_ALG_CATEGORY_KEY_DERIVATION)

#define PSA_ALG_IS_KEY_DERIVATION_OR_AGREEMENT(alg)     \
    ((PSA_ALG_IS_KEY_DERIVATION(alg) || PSA_ALG_IS_KEY_AGREEMENT(alg)))

/** The finite-field Diffie-Hellman (DH) key agreement algorithm.
 *
 * The shared secret produced by key agreement is
 * `g^{ab}` in big-endian format.
 * It is `ceiling(m / 8)` bytes long where `m` is the size of the prime `p`
 * in bits.
 */
#define PSA_ALG_FFDH                            ((psa_algorithm_t)0x30100000)

/** Whether the specified algorithm is a finite field Diffie-Hellman algorithm.
 *
 * This includes the raw finite field Diffie-Hellman algorithm as well as
 * finite-field Diffie-Hellman followed by any supporter key derivation
 * algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \c alg is a finite field Diffie-Hellman algorithm, 0 otherwise.
 *         This macro may return either 0 or 1 if \c alg is not a supported
 *         key agreement algorithm identifier.
 */
#define PSA_ALG_IS_FFDH(alg) \
    (PSA_ALG_KEY_AGREEMENT_GET_BASE(alg) == PSA_ALG_FFDH)

/** The elliptic curve Diffie-Hellman (ECDH) key agreement algorithm.
 *
 * The shared secret produced by key agreement is the x-coordinate of
 * the shared secret point. It is always `ceiling(m / 8)` bytes long where
 * `m` is the bit size associated with the curve, i.e. the bit size of the
 * order of the curve's coordinate field. When `m` is not a multiple of 8,
 * the byte containing the most significant bit of the shared secret
 * is padded with zero bits. The byte order is either little-endian
 * or big-endian depending on the curve type.
 *
 * - For Montgomery curves (curve types `PSA_ECC_FAMILY_CURVEXXX`),
 *   the shared secret is the x-coordinate of `d_A Q_B = d_B Q_A`
 *   in little-endian byte order.
 *   The bit size is 448 for Curve448 and 255 for Curve25519.
 * - For Weierstrass curves over prime fields (curve types
 *   `PSA_ECC_FAMILY_SECPXXX` and `PSA_ECC_FAMILY_BRAINPOOL_PXXX`),
 *   the shared secret is the x-coordinate of `d_A Q_B = d_B Q_A`
 *   in big-endian byte order.
 *   The bit size is `m = ceiling(log_2(p))` for the field `F_p`.
 * - For Weierstrass curves over binary fields (curve types
 *   `PSA_ECC_FAMILY_SECTXXX`),
 *   the shared secret is the x-coordinate of `d_A Q_B = d_B Q_A`
 *   in big-endian byte order.
 *   The bit size is `m` for the field `F_{2^m}`.
 */
#define PSA_ALG_ECDH                            ((psa_algorithm_t)0x30200000)

/** Whether the specified algorithm is an elliptic curve Diffie-Hellman
 * algorithm.
 *
 * This includes the raw elliptic curve Diffie-Hellman algorithm as well as
 * elliptic curve Diffie-Hellman followed by any supporter key derivation
 * algorithm.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \c alg is an elliptic curve Diffie-Hellman algorithm,
 *         0 otherwise.
 *         This macro may return either 0 or 1 if \c alg is not a supported
 *         key agreement algorithm identifier.
 */
#define PSA_ALG_IS_ECDH(alg) \
    (PSA_ALG_KEY_AGREEMENT_GET_BASE(alg) == PSA_ALG_ECDH)

/** Whether the specified algorithm encoding is a wildcard.
 *
 * Wildcard values may only be used to set the usage algorithm field in
 * a policy, not to perform an operation.
 *
 * \param alg An algorithm identifier (value of type #psa_algorithm_t).
 *
 * \return 1 if \c alg is a wildcard algorithm encoding.
 * \return 0 if \c alg is a non-wildcard algorithm encoding (suitable for
 *         an operation).
 * \return This macro may return either 0 or 1 if \c alg is not a supported
 *         algorithm identifier.
 */
#define PSA_ALG_IS_WILDCARD(alg)                        \
    (PSA_ALG_IS_HASH_AND_SIGN(alg) ?                    \
     PSA_ALG_SIGN_GET_HASH(alg) == PSA_ALG_ANY_HASH :   \
     (alg) == PSA_ALG_ANY_HASH)

/**@}*/

/** \defgroup key_lifetimes Key lifetimes
 * @{
 */

/** The default lifetime for volatile keys.
 *
 * A volatile key only exists as long as the identifier to it is not destroyed.
 * The key material is guaranteed to be erased on a power reset.
 *
 * A key with this lifetime is typically stored in the RAM area of the
 * PSA Crypto subsystem. However this is an implementation choice.
 * If an implementation stores data about the key in a non-volatile memory,
 * it must release all the resources associated with the key and erase the
 * key material if the calling application terminates.
 */
#define PSA_KEY_LIFETIME_VOLATILE               ((psa_key_lifetime_t)0x00000000)

/** The default lifetime for persistent keys.
 *
 * A persistent key remains in storage until it is explicitly destroyed or
 * until the corresponding storage area is wiped. This specification does
 * not define any mechanism to wipe a storage area, but implementations may
 * provide their own mechanism (for example to perform a factory reset,
 * to prepare for device refurbishment, or to uninstall an application).
 *
 * This lifetime value is the default storage area for the calling
 * application. Implementations may offer other storage areas designated
 * by other lifetime values as implementation-specific extensions.
 * See ::psa_key_lifetime_t for more information.
 */
#define PSA_KEY_LIFETIME_PERSISTENT             ((psa_key_lifetime_t)0x00000001)

/** The persistence level of volatile keys.
 *
 * See ::psa_key_persistence_t for more information.
 */
#define PSA_KEY_PERSISTENCE_VOLATILE            ((psa_key_persistence_t)0x00)

/** The default persistence level for persistent keys.
 *
 * See ::psa_key_persistence_t for more information.
 */
#define PSA_KEY_PERSISTENCE_DEFAULT             ((psa_key_persistence_t)0x01)

/** A persistence level indicating that a key is never destroyed.
 *
 * See ::psa_key_persistence_t for more information.
 */
#define PSA_KEY_PERSISTENCE_READ_ONLY           ((psa_key_persistence_t)0xff)

#define PSA_KEY_LIFETIME_GET_PERSISTENCE(lifetime)      \
    ((psa_key_persistence_t)((lifetime) & 0x000000ff))

#define PSA_KEY_LIFETIME_GET_LOCATION(lifetime)      \
    ((psa_key_location_t)((lifetime) >> 8))

/** Whether a key lifetime indicates that the key is volatile.
 *
 * A volatile key is automatically destroyed by the implementation when
 * the application instance terminates. In particular, a volatile key
 * is automatically destroyed on a power reset of the device.
 *
 * A key that is not volatile is persistent. Persistent keys are
 * preserved until the application explicitly destroys them or until an
 * implementation-specific device management event occurs (for example,
 * a factory reset).
 *
 * \param lifetime      The lifetime value to query (value of type
 *                      ::psa_key_lifetime_t).
 *
 * \return \c 1 if the key is volatile, otherwise \c 0.
 */
#define PSA_KEY_LIFETIME_IS_VOLATILE(lifetime)  \
    (PSA_KEY_LIFETIME_GET_PERSISTENCE(lifetime) == \
     PSA_KEY_PERSISTENCE_VOLATILE)

/** Construct a lifetime from a persistence level and a location.
 *
 * \param persistence   The persistence level
 *                      (value of type ::psa_key_persistence_t).
 * \param location      The location indicator
 *                      (value of type ::psa_key_location_t).
 *
 * \return The constructed lifetime value.
 */
#define PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(persistence, location) \
    ((location) << 8 | (persistence))

/** The local storage area for persistent keys.
 *
 * This storage area is available on all systems that can store persistent
 * keys without delegating the storage to a third-party cryptoprocessor.
 *
 * See ::psa_key_location_t for more information.
 */
#define PSA_KEY_LOCATION_LOCAL_STORAGE          ((psa_key_location_t)0x000000)

#define PSA_KEY_LOCATION_VENDOR_FLAG            ((psa_key_location_t)0x800000)

/** The minimum value for a key identifier chosen by the application.
 */
#define PSA_KEY_ID_USER_MIN                     ((psa_key_id_t)0x00000001)
/** The maximum value for a key identifier chosen by the application.
 */
#define PSA_KEY_ID_USER_MAX                     ((psa_key_id_t)0x3fffffff)
/** The minimum value for a key identifier chosen by the implementation.
 */
#define PSA_KEY_ID_VENDOR_MIN                   ((psa_key_id_t)0x40000000)
/** The maximum value for a key identifier chosen by the implementation.
 */
#define PSA_KEY_ID_VENDOR_MAX                   ((psa_key_id_t)0x7fffffff)


#if !defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)

#define MBEDTLS_SVC_KEY_ID_INIT ( (psa_key_id_t)0 )
#define MBEDTLS_SVC_KEY_ID_GET_KEY_ID( id ) ( id )
#define MBEDTLS_SVC_KEY_ID_GET_OWNER_ID( id ) ( 0 )

/** Utility to initialize a key identifier at runtime.
 *
 * \param unused  Unused parameter.
 * \param key_id  Identifier of the key.
 */
static inline mbedtls_svc_key_id_t mbedtls_svc_key_id_make(
    unsigned int unused, psa_key_id_t key_id )
{
    (void)unused;

    return( key_id );
}

/** Compare two key identifiers.
 *
 * \param id1 First key identifier.
 * \param id2 Second key identifier.
 *
 * \return Non-zero if the two key identifier are equal, zero otherwise.
 */
static inline int mbedtls_svc_key_id_equal( mbedtls_svc_key_id_t id1,
                                            mbedtls_svc_key_id_t id2 )
{
    return( id1 == id2 );
}

/** Check whether a key identifier is null.
 *
 * \param key Key identifier.
 *
 * \return Non-zero if the key identifier is null, zero otherwise.
 */
static inline int mbedtls_svc_key_id_is_null( mbedtls_svc_key_id_t key )
{
    return( key == 0 );
}

#else /* MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */

#define MBEDTLS_SVC_KEY_ID_INIT ( (mbedtls_svc_key_id_t){ 0, 0 } )
#define MBEDTLS_SVC_KEY_ID_GET_KEY_ID( id ) ( ( id ).key_id )
#define MBEDTLS_SVC_KEY_ID_GET_OWNER_ID( id ) ( ( id ).owner )

/** Utility to initialize a key identifier at runtime.
 *
 * \param owner_id Identifier of the key owner.
 * \param key_id   Identifier of the key.
 */
static inline mbedtls_svc_key_id_t mbedtls_svc_key_id_make(
    mbedtls_key_owner_id_t owner_id, psa_key_id_t key_id )
{
    return( (mbedtls_svc_key_id_t){ .key_id = key_id,
                                    .owner = owner_id } );
}

/** Compare two key identifiers.
 *
 * \param id1 First key identifier.
 * \param id2 Second key identifier.
 *
 * \return Non-zero if the two key identifier are equal, zero otherwise.
 */
static inline int mbedtls_svc_key_id_equal( mbedtls_svc_key_id_t id1,
                                            mbedtls_svc_key_id_t id2 )
{
    return( ( id1.key_id == id2.key_id ) &&
            mbedtls_key_owner_id_equal( id1.owner, id2.owner ) );
}

/** Check whether a key identifier is null.
 *
 * \param key Key identifier.
 *
 * \return Non-zero if the key identifier is null, zero otherwise.
 */
static inline int mbedtls_svc_key_id_is_null( mbedtls_svc_key_id_t key )
{
    return( ( key.key_id == 0 ) && ( key.owner == 0 ) );
}

#endif /* !MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER */

/**@}*/

/** \defgroup policy Key policies
 * @{
 */

/** Whether the key may be exported.
 *
 * A public key or the public part of a key pair may always be exported
 * regardless of the value of this permission flag.
 *
 * If a key does not have export permission, implementations shall not
 * allow the key to be exported in plain form from the cryptoprocessor,
 * whether through psa_export_key() or through a proprietary interface.
 * The key may however be exportable in a wrapped form, i.e. in a form
 * where it is encrypted by another key.
 */
#define PSA_KEY_USAGE_EXPORT                    ((psa_key_usage_t)0x00000001)

/** Whether the key may be copied.
 *
 * This flag allows the use of psa_copy_key() to make a copy of the key
 * with the same policy or a more restrictive policy.
 *
 * For lifetimes for which the key is located in a secure element which
 * enforce the non-exportability of keys, copying a key outside the secure
 * element also requires the usage flag #PSA_KEY_USAGE_EXPORT.
 * Copying the key inside the secure element is permitted with just
 * #PSA_KEY_USAGE_COPY if the secure element supports it.
 * For keys with the lifetime #PSA_KEY_LIFETIME_VOLATILE or
 * #PSA_KEY_LIFETIME_PERSISTENT, the usage flag #PSA_KEY_USAGE_COPY
 * is sufficient to permit the copy.
 */
#define PSA_KEY_USAGE_COPY                      ((psa_key_usage_t)0x00000002)

/** Whether the key may be used to encrypt a message.
 *
 * This flag allows the key to be used for a symmetric encryption operation,
 * for an AEAD encryption-and-authentication operation,
 * or for an asymmetric encryption operation,
 * if otherwise permitted by the key's type and policy.
 *
 * For a key pair, this concerns the public key.
 */
#define PSA_KEY_USAGE_ENCRYPT                   ((psa_key_usage_t)0x00000100)

/** Whether the key may be used to decrypt a message.
 *
 * This flag allows the key to be used for a symmetric decryption operation,
 * for an AEAD decryption-and-verification operation,
 * or for an asymmetric decryption operation,
 * if otherwise permitted by the key's type and policy.
 *
 * For a key pair, this concerns the private key.
 */
#define PSA_KEY_USAGE_DECRYPT                   ((psa_key_usage_t)0x00000200)

/** Whether the key may be used to sign a message.
 *
 * This flag allows the key to be used for a MAC calculation operation
 * or for an asymmetric signature operation,
 * if otherwise permitted by the key's type and policy.
 *
 * For a key pair, this concerns the private key.
 */
#define PSA_KEY_USAGE_SIGN_HASH                 ((psa_key_usage_t)0x00000400)

/** Whether the key may be used to verify a message signature.
 *
 * This flag allows the key to be used for a MAC verification operation
 * or for an asymmetric signature verification operation,
 * if otherwise permitted by by the key's type and policy.
 *
 * For a key pair, this concerns the public key.
 */
#define PSA_KEY_USAGE_VERIFY_HASH               ((psa_key_usage_t)0x00000800)

/** Whether the key may be used to derive other keys.
 */
#define PSA_KEY_USAGE_DERIVE                    ((psa_key_usage_t)0x00001000)

/**@}*/

/** \defgroup derivation Key derivation
 * @{
 */

/** A secret input for key derivation.
 *
 * This should be a key of type #PSA_KEY_TYPE_DERIVE
 * (passed to psa_key_derivation_input_key())
 * or the shared secret resulting from a key agreement
 * (obtained via psa_key_derivation_key_agreement()).
 *
 * The secret can also be a direct input (passed to
 * key_derivation_input_bytes()). In this case, the derivation operation
 * may not be used to derive keys: the operation will only allow
 * psa_key_derivation_output_bytes(), not psa_key_derivation_output_key().
 */
#define PSA_KEY_DERIVATION_INPUT_SECRET     ((psa_key_derivation_step_t)0x0101)

/** A label for key derivation.
 *
 * This should be a direct input.
 * It can also be a key of type #PSA_KEY_TYPE_RAW_DATA.
 */
#define PSA_KEY_DERIVATION_INPUT_LABEL      ((psa_key_derivation_step_t)0x0201)

/** A salt for key derivation.
 *
 * This should be a direct input.
 * It can also be a key of type #PSA_KEY_TYPE_RAW_DATA.
 */
#define PSA_KEY_DERIVATION_INPUT_SALT       ((psa_key_derivation_step_t)0x0202)

/** An information string for key derivation.
 *
 * This should be a direct input.
 * It can also be a key of type #PSA_KEY_TYPE_RAW_DATA.
 */
#define PSA_KEY_DERIVATION_INPUT_INFO       ((psa_key_derivation_step_t)0x0203)

/** A seed for key derivation.
 *
 * This should be a direct input.
 * It can also be a key of type #PSA_KEY_TYPE_RAW_DATA.
 */
#define PSA_KEY_DERIVATION_INPUT_SEED       ((psa_key_derivation_step_t)0x0204)

/**@}*/

#endif /* PSA_CRYPTO_VALUES_H */

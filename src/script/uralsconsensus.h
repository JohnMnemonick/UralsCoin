// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers 
// Copyright (c) 2015-2017 The Dash developers 
// Copyright (c) 2015-2017 The URALS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef URALS_URALSCONSENSUS_H
#define URALS_URALSCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_URALS_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/urals-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBURALSCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define URALSCONSENSUS_API_VER 1

typedef enum uralsconsensus_error_t
{
    uralsconsensus_ERR_OK = 0,
    uralsconsensus_ERR_TX_INDEX,
    uralsconsensus_ERR_TX_SIZE_MISMATCH,
    uralsconsensus_ERR_TX_DESERIALIZE,
    uralsconsensus_ERR_AMOUNT_REQUIRED,
    uralsconsensus_ERR_INVALID_FLAGS,
} uralsconsensus_error;

/** Script verification flags */
enum
{
    uralsconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    uralsconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    uralsconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    uralsconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    uralsconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    uralsconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    uralsconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    uralsconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = uralsconsensus_SCRIPT_FLAGS_VERIFY_P2SH | uralsconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               uralsconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | uralsconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               uralsconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | uralsconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int uralsconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, uralsconsensus_error* err);

EXPORT_SYMBOL int uralsconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, uralsconsensus_error* err);

EXPORT_SYMBOL unsigned int uralsconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // URALS_URALSCONSENSUS_H

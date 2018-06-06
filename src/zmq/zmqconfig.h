// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2018 The URALS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef URALS_ZMQ_ZMQCONFIG_H
#define URALS_ZMQ_ZMQCONFIG_H

#if defined(HAVE_CONFIG_H)
#include "config/urals-config.h"
#endif

#include <stdarg.h>
#include <string>

#if ENABLE_ZMQ
#include <zmq.h>
#endif

#include "primitives/block.h"
#include "primitives/transaction.h"

void zmqError(const char *str);

#endif // URALS_ZMQ_ZMQCONFIG_H

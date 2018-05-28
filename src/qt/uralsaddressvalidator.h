// Copyright (c) 2011-2014 The URALS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef URALS_QT_URALSADDRESSVALIDATOR_H
#define URALS_QT_URALSADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class UralsAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit UralsAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** URALS address widget validator, checks for a valid urals address.
 */
class UralsAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit UralsAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // URALS_QT_URALSADDRESSVALIDATOR_H

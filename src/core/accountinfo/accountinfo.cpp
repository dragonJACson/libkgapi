/*
 * This file is part of LibKGAPI library
 *
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "accountinfo.h"
#include "utils_p.h"

#include <QJsonDocument>

#include <QVariantMap>

using namespace KGAPI2;


class Q_DECL_HIDDEN AccountInfo::Private
{
public:
    Private();
    Private(const Private &other);
    ~Private();

    QString id;
    QString email;
    QString name;
    QString givenName;
    QString familyName;

    QString birthday;
    QString gender;

    QString link;
    QString locale;
    QString timezone;

    bool verifiedEmail;

    QString pictureUrl;
};

AccountInfo::Private::Private():
    verifiedEmail(false)
{
}

AccountInfo::Private::Private(const Private &other):
    id(other.id),
    email(other.email),
    name(other.name),
    givenName(other.givenName),
    familyName(other.familyName),
    birthday(other.birthday),
    gender(other.gender),
    link(other.link),
    locale(other.locale),
    timezone(other.timezone),
    verifiedEmail(other.verifiedEmail),
    pictureUrl(other.pictureUrl)
{
}

AccountInfo::Private::~Private()
{
}

AccountInfo::AccountInfo():
    Object(),
    d(new Private)
{
}

AccountInfo::AccountInfo(const AccountInfo &other):
    Object(other),
    d(new Private(*(other.d)))
{
}

AccountInfo::~AccountInfo()
{
    delete d;
}

bool AccountInfo::operator==(const AccountInfo &other) const
{
    if (!Object::operator==(other)) {
        return false;
    }
    GAPI_COMPARE(id)
    GAPI_COMPARE(email)
    GAPI_COMPARE(name)
    GAPI_COMPARE(givenName)
    GAPI_COMPARE(familyName)
    GAPI_COMPARE(birthday)
    GAPI_COMPARE(gender)
    GAPI_COMPARE(link)
    GAPI_COMPARE(locale)
    GAPI_COMPARE(timezone)
    GAPI_COMPARE(verifiedEmail)
    GAPI_COMPARE(pictureUrl)
    return true;
}

void AccountInfo::setId(const QString &id)
{
    d->id = id;
}

QString AccountInfo::id() const
{
    return d->id;
}

void AccountInfo::setEmail(const QString &email)
{
    d->email = email;
}

QString AccountInfo::email() const
{
    return d->email;
}

void AccountInfo::setName(const QString &name)
{
    d->name = name;
}

QString AccountInfo::name() const
{
    return d->name;
}

void AccountInfo::setGivenName(const QString &givenName)
{
    d->givenName = givenName;
}

QString AccountInfo::givenName() const
{
    return d->givenName;
}

void AccountInfo::setFamilyName(const QString &familyName)
{
    d->familyName = familyName;
}

QString AccountInfo::familyName() const
{
    return d->familyName;
}

void AccountInfo::setBirthday(const QString &birthday)
{
    d->birthday = birthday;
}

QString AccountInfo::birthday() const
{
    return d->birthday;
}

void AccountInfo::setGender(const QString &gender)
{
    d->gender = gender;
}

QString AccountInfo::gender() const
{
    return d->gender;
}

void AccountInfo::setLink(const QString &link)
{
    d->link = link;
}

QString AccountInfo::link() const
{
    return d->link;
}

void AccountInfo::setLocale(const QString &locale)
{
    d->locale = locale;
}

QString AccountInfo::locale() const
{
    return d->locale;
}

void AccountInfo::setTimezone(const QString &timezone)
{
    d->timezone = timezone;
}

QString AccountInfo::timezone() const
{
    return d->timezone;
}

void AccountInfo::setVerifiedEmail(const bool verifiedEmail)
{
    d->verifiedEmail = verifiedEmail;
}

bool AccountInfo::verifiedEmail() const
{
    return d->verifiedEmail;
}

void AccountInfo::setPhotoUrl(const QString &url)
{
    d->pictureUrl = url;
}

QString AccountInfo::photoUrl() const
{
    return d->pictureUrl;
}

AccountInfoPtr AccountInfo::fromJSON(const QByteArray& jsonData)
{
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (document.isNull()) {
        return AccountInfoPtr();
    }

    QVariantMap data;
    data = document.toVariant().toMap();

    AccountInfoPtr accountInfo(new AccountInfo);
    accountInfo->setId(data.value(QStringLiteral("id")).toString());
    accountInfo->setEmail(data.value(QStringLiteral("email")).toString());
    accountInfo->setName(data.value(QStringLiteral("name")).toString());
    accountInfo->setGivenName(data.value(QStringLiteral("given_name")).toString());
    accountInfo->setFamilyName(data.value(QStringLiteral("family_name")).toString());
    accountInfo->setBirthday(data.value(QStringLiteral("birthday")).toString());
    accountInfo->setGender(data.value(QStringLiteral("gender")).toString());
    accountInfo->setLink(data.value(QStringLiteral("link")).toString());
    accountInfo->setLocale(data.value(QStringLiteral("locale")).toString());
    accountInfo->setTimezone(data.value(QStringLiteral("timezone")).toString());
    accountInfo->setPhotoUrl(data.value(QStringLiteral("picture")).toString());
    accountInfo->setVerifiedEmail(data.value(QStringLiteral("verified_email")).toBool());

    return accountInfo;
}

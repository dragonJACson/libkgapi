/*
    Copyright (C) 2012 - 2018  Daniel Vrátil <dvratil@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBKGAPI2_CONTACTSSERVICE_H
#define LIBKGAPI2_CONTACTSSERVICE_H

#include "types.h"
#include "kgapicontacts_export.h"

#include <QUrl>

namespace KGAPI2
{

/**
 * @brief Additional methods for implementing support for Google Contacts service
 *
 * You should never need to use these methods, unless implementing your own Job
 *
 * There are no methods to serialize objects into JSON, because Google Contacts
 * API only supports XML for writing.
 */
namespace ContactsService
{

    /**
     * @brief Parses JSON data into Contact object
     *
     * @param jsonData
     */
    KGAPICONTACTS_EXPORT ContactPtr JSONToContact(const QByteArray& jsonData);

    /**
     * @brief Parses JSON data into ContactsGroup object
     *
     * @param jsonData
     */
    KGAPICONTACTS_EXPORT ContactsGroupPtr JSONToContactsGroup(const QByteArray& jsonData);

    /**
     * @brief Parses JSON feed into list of ContactsGroups or Events.
     *
     * @param jsonFeed
     * @param feedData The structure will be filled with additional data
     */
    KGAPICONTACTS_EXPORT ObjectsList parseJSONFeed(const QByteArray& jsonFeed, FeedData& feedData);

    /**
     * @brief Parses XML data into Contact object
     *
     * @param xmlData
     */
    KGAPICONTACTS_EXPORT ContactPtr XMLToContact(const QByteArray& xmlData);

    /**
     * @brief Serializes a Contact object into XML
     *
     * @param contact
     */
    KGAPICONTACTS_EXPORT QByteArray contactToXML(const ContactPtr& contact);

    /**
     * @brief Parses XML data into ContactsGroup object
     *
     * @param xmlData
     */
    KGAPICONTACTS_EXPORT ContactsGroupPtr XMLToContactsGroup(const QByteArray& xmlData);

    /**
     * @brief Serializes a ContactsGroup object into XML
     *
     * @param group
     */
    KGAPICONTACTS_EXPORT QByteArray contactsGroupToXML(const ContactsGroupPtr& group);

    /**
     * @brief Supported API version
     */
    KGAPICONTACTS_EXPORT QString APIVersion();

    /**
     * @brief Returns URL for creating contacts
     *
     * @param user User. "default" or user@gmail.com}
     */
    KGAPICONTACTS_EXPORT QUrl createContactUrl(const QString &user);

    /**
     * @brief Returns URL for fetching all contacts in addressbook
     *
     * @param user User. "default" or user@gmail.com
     * @param showDeleted Whether to fetch deleted contacts placeholders as well
     */
    KGAPICONTACTS_EXPORT QUrl fetchAllContactsUrl(const QString &user, bool showDeleted);

    /**
     * @brief Returns URL for fetching specific contact
     *
     * @param user User. "default" or user@gmail.com
     * @param contactID ID of contact to fetch
     */
    KGAPICONTACTS_EXPORT QUrl fetchContactUrl(const QString &user, const QString &contactID);

    /**
     * @brief Returns URL for updating a single contact
     *
     * @param user User. "default" or user@gmail.com
     * @param contactID ID of contact to update
     */
    KGAPICONTACTS_EXPORT QUrl updateContactUrl(const QString &user, const QString &contactID);

    /**
     * @brief Returns URL for removing a single contact
     *
     * @param user User. "default" or user@gmail.com
     * @param contactID ID of contact to remove
     */
    KGAPICONTACTS_EXPORT QUrl removeContactUrl(const QString &user, const QString &contactID);

    /**
     * Returns URL for KGAPI::Request::FetchAll requests.
     *
     * @param user User ("default" or user@gmail.com) in whose addressbook to look.
     */
    KGAPICONTACTS_EXPORT QUrl fetchAllGroupsUrl(const QString &user);

    /**
     * @brief Returns URL for fetching all contacts groups
     *
     * @param user User ("default" or user@gmail.com) in whose addressbook to look
     * @param groupId ID of group of which to fetch all data.
     */
    KGAPICONTACTS_EXPORT QUrl fetchGroupUrl(const QString &user, const QString &groupId);

    /**
     * @brief Returns URL for creating a new contacts group
     *
     * @param user User (user@gmail.com) in whose addressbook to create a group.
     */
    KGAPICONTACTS_EXPORT QUrl createGroupUrl(const QString &user);

    /**
     * @brief Returns URL for updating a single contacts group
     *
     * @param user User (user@gmail.com)) in whose addressbook to look
     * @param groupId ID of group to update.
     */
    KGAPICONTACTS_EXPORT QUrl updateGroupUrl(const QString &user, const QString &groupId);

    /**
     * @brief Returns URL for removing a single contacts group
     *
     * @param user User (user@gmail.com) in whose addressbook to look
     * @param groupId ID of group to delete
     */
    KGAPICONTACTS_EXPORT QUrl removeGroupUrl(const QString &user, const QString &groupId);

    /**
     * @brief Returns URL for modifying photo.
     *
     * Send a GET request to fetch the photo, PUT to change it and DELETE to
     * remove it.
     *
     * @param user User (user@gmail.com) in whose addressbook to lok
     * @param contactId ID of contacts whose photo to update
     */
    KGAPICONTACTS_EXPORT QUrl photoUrl(const QString &user, const QString &contactId);

} // namespace ContactsService

} // namespace KGAPI

#endif // LIBKGAPI2_CONTACTSSERVICE_H

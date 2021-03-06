/*
 * Copyright (C) 2014  Daniel Vrátil <dvratil@redhat.com>
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

#include "pagefetchjob.h"
#include "bloggerservice.h"
#include "page.h"
#include "utils.h"
#include "account.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

using namespace KGAPI2;
using namespace KGAPI2::Blogger;

class Q_DECL_HIDDEN PageFetchJob::Private
{
  public:
    Private(const QString &blogId,
            const QString &pageId);

    QString blogId;
    QString pageId;

    bool fetchContent;
    StatusFilters statusFilter;
};

PageFetchJob::Private::Private(const QString &blogId_,
                               const QString &pageId_)
    : blogId(blogId_)
    , pageId(pageId_)
    , fetchContent(true)
    , statusFilter(All)
{
}

PageFetchJob::PageFetchJob(const QString &blogId,
                           const AccountPtr &account,
                           QObject *parent)
    : FetchJob(account, parent)
    , d(new Private(blogId, QString()))
{
}

PageFetchJob::PageFetchJob(const QString &blogId,
                           const QString &pageId,
                           const AccountPtr &account,
                           QObject *parent)
    : FetchJob(account, parent)
    , d(new Private(blogId, pageId))
{
}

PageFetchJob::~PageFetchJob()
{
    delete d;
}

bool PageFetchJob::fetchContent() const
{
    return d->fetchContent;
}

void PageFetchJob::setFetchContent(bool fetchContent)
{
    d->fetchContent = fetchContent;
}

PageFetchJob::StatusFilters PageFetchJob::statusFilter() const
{
    return d->statusFilter;
}

void PageFetchJob::setStatusFilter(StatusFilters status)
{
    d->statusFilter = status;
}

void PageFetchJob::start()
{
    QUrl url = BloggerService::fetchPageUrl(d->blogId, d->pageId);
    QUrlQuery query(url);
    query.addQueryItem(QStringLiteral("fetchBodies"), Utils::bool2Str(d->fetchContent));
    if (d->statusFilter & Draft) {
        query.addQueryItem(QStringLiteral("status"), QStringLiteral("draft"));
    }
    if (d->statusFilter & Imported) {
        query.addQueryItem(QStringLiteral("status"), QStringLiteral("imported"));
    }
    if (d->statusFilter & Live) {
        query.addQueryItem(QStringLiteral("status"), QStringLiteral("live"));
    }
    if (account()) {
        query.addQueryItem(QStringLiteral("view"), QStringLiteral("ADMIN"));
    }
    url.setQuery(query);
    QNetworkRequest request(url);
    if (account()) {
        request.setRawHeader("Authorization", "Bearer " + account()->accessToken().toLatin1());
    }
    enqueueRequest(request);
}

ObjectsList PageFetchJob::handleReplyWithItems(const QNetworkReply *reply, const QByteArray &rawData)
{
    ObjectsList items;

    const QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    ContentType ct = Utils::stringToContentType(contentType);
    if (ct == KGAPI2::JSON) {
        if (d->pageId.isEmpty()) {
            items =  Page::fromJSONFeed(rawData);
        } else {
            items << Page::fromJSON(rawData);
        }
    } else {
        setError(KGAPI2::InvalidResponse);
        setErrorString(tr("Invalid response content type"));
        emitFinished();
        return items;
    }

    emitFinished();
    return items;
}



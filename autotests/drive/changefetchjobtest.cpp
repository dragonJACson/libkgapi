/*
 * Copyright (C) 2018  Daniel Vrátil <dvratil@kde.org>
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

#include <QObject>
#include <QTest>

#include "fakenetworkaccessmanagerfactory.h"
#include "testutils.h"
#include "drivetestutils.h"

#include "types.h"
#include "changefetchjob.h"
#include "change.h"
#include "account.h"

using namespace KGAPI2;

Q_DECLARE_METATYPE(QList<FakeNetworkAccessManager::Scenario>)
Q_DECLARE_METATYPE(KGAPI2::Drive::ChangesList)

class ChangeFetchJobTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase()
    {
        NetworkAccessManagerFactory::setFactory(new FakeNetworkAccessManagerFactory);
    }

    void testFetchAll()
    {
        FakeNetworkAccessManagerFactory::get()->setScenarios({
            scenarioFromFile(QFINDTESTDATA("data/changes_fetch_page1_request.txt"),
                             QFINDTESTDATA("data/changes_fetch_page1_response.txt")),
            scenarioFromFile(QFINDTESTDATA("data/changes_fetch_page2_request.txt"),
                             QFINDTESTDATA("data/changes_fetch_page2_response.txt"))
        });
        const Drive::ChangesList changes = {
            changeFromFile(QFINDTESTDATA("data/change1.json")),
            changeFromFile(QFINDTESTDATA("data/change2.json"))
        };

        auto account = AccountPtr::create(QStringLiteral("MockAccount"), QStringLiteral("MockToken"));
        auto job = new Drive::ChangeFetchJob(account);
        QVERIFY(execJob(job));
        const auto items = job->items();
        QCOMPARE(items.count(), changes.count());
        for (int i = 0; i < changes.count(); ++i) {
            const auto returnedChange =  items.at(i).dynamicCast<Drive::Change>();
            const auto expectedChange = changes.at(i);
            QVERIFY(returnedChange);
            QCOMPARE(*returnedChange, *expectedChange);
        }
    }

    void testFetchSingle()
    {
        FakeNetworkAccessManagerFactory::get()->setScenarios({
            scenarioFromFile(QFINDTESTDATA("data/change1_fetch_request.txt"),
                             QFINDTESTDATA("data/change1_fetch_response.txt"))

        });
        const auto change = changeFromFile(QFINDTESTDATA("data/change1.json"));

        auto account = AccountPtr::create(QStringLiteral("MockAccount"), QStringLiteral("MockToken"));
        auto job = new Drive::ChangeFetchJob(QString::number(change->id()), account);
        QVERIFY(execJob(job));
        const auto items = job->items();
        QCOMPARE(items.count(), 1);
        const auto returnedChange =  items.at(0).dynamicCast<Drive::Change>();
        QVERIFY(returnedChange);
        QCOMPARE(*returnedChange, *change);
    }
};

QTEST_GUILESS_MAIN(ChangeFetchJobTest)

#include "changefetchjobtest.moc"






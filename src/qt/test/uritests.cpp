// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 10000);

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 10010000);

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?amount=100&label=Wikipedia Example"));

    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));

    QVERIFY(rv.amount == 1000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?message=Wikipedia Example Address", &rv));
    printf("%s",rv.address.toLatin1().data());
    QVERIFY(rv.address == QString("CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("litecoincash:CKfokwkxV3U64sRqZkJ62a3LXmsuFWnNns?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}

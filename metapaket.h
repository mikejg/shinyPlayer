#ifndef METAPAKET_H
#define METAPAKET_H

#include <QString>

struct MetaPaket
{
    bool isEmpty;

    QString interpret;
    QString album;
    QString title;

    QString url;
    QString coverUrl;
    int points;
    int urlkey;
    int lastPlayed;
};

#endif // METAPAKET_H

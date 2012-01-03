#ifndef PLAY_ENGINE_H
#define PLAY_ENGINE_H

#include <QObject>

#include <phonon/phononnamespace.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/audiodataoutput.h>

#include "metapaket.h"

using namespace Phonon;

class Play_Engine : public QObject
{
    Q_OBJECT

private:
    MediaObject* m_media;
    AudioOutput* output;
    AudioDataOutput* dataout;
    MetaPaket currentMP;

public:
    Play_Engine(QObject* parent = 0);

    void play(MetaPaket mp);
    void play(QString s);

    QString coverUrl() { return currentMP.coverUrl; }
    MetaPaket getMetaPaket() { return currentMP; }

public slots:
    void pause();

signals:
    void finished();
    void dataReady(const QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >&);
};

#endif // PLAY_ENGINE_H

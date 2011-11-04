#ifndef PLAY_ENGINE_H
#define PLAY_ENGINE_H

#include <QObject>

#include <phonon/phononnamespace.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

using namespace Phonon;

class Play_Engine : public QObject
{
    Q_OBJECT

private:
    MediaObject* m_media;
    AudioOutput* output;

public:
    Play_Engine(QObject* parent = 0);

    void play(QString path);

public slots:
    void pause();

signals:
    void finished();
};

#endif // PLAY_ENGINE_H

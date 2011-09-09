#include "play_engine.h"

Play_Engine::Play_Engine(QObject* parent) : QObject(parent)
{
    m_media = new MediaObject(this);
    output = new AudioOutput(Phonon::MusicCategory, this);
    createPath(m_media, output);
}

void Play_Engine::play(QString path)
{
    MediaSource source(path);
    m_media->setCurrentSource(source);

    m_media->play();
}

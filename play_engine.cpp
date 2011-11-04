#include "play_engine.h"

Play_Engine::Play_Engine(QObject* parent) : QObject(parent)
{
    m_media = new MediaObject(this);
    output = new AudioOutput(Phonon::MusicCategory, this);
    createPath(m_media, output);

    connect(m_media, SIGNAL(finished()), this, SIGNAL(finished()));
}

void Play_Engine::pause()
{
    if(m_media->state() == PlayingState)
    {
        m_media->pause();
        return;
    }

    if(m_media->state() == PausedState)
    {
        m_media->play();
        return;
    }
}

void Play_Engine::play(QString path)
{
    m_media->stop();

    MediaSource source(path);
    m_media->setCurrentSource(source);

    m_media->play();
}

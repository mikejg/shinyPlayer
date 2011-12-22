#include "play_engine.h"
#include <QDebug>

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

void Play_Engine::play(MetaPaket mp)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << mp.url;

    currentMP = mp;
    m_media->stop();

    MediaSource source(mp.url);
    m_media->setCurrentSource(source);

    m_media->play();
}

void Play_Engine::play(QString s)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << s;
    m_media->stop();

    MediaSource source(s);
    m_media->setCurrentSource(source);

    m_media->play();
}

// Qt.
#include <QDebug>
#include <QMutexLocker>

// Project.
#include "imageworker.h"

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::ImageWorker( QObject* parent )
///
/// \brief  Constructor.
///
/// \param  The object's parent.
////////////////////////////////////////////////////////////////////////////////
ImageWorker::ImageWorker( QObject* parent )
    : QThread( parent )
    , m_enableCT( true )
    , m_stopped( false )
{

}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::enableCT()
///
/// \brief  Enables CT and disables US image generation.
////////////////////////////////////////////////////////////////////////////////
void ImageWorker::enableCT()
{
    qDebug() << QString( "[ImageWorker::enableCT] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    m_enableCT = true;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::enableUS()
///
/// \brief  Enables US and disables CT image generation.
////////////////////////////////////////////////////////////////////////////////
void ImageWorker::enableUS()
{
    qDebug() << QString( "[ImageWorker::enableUS] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    m_enableCT = false;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::isEnabledCT()
///
/// \brief  Checks whether CT images will be generated.
///
/// \return Returns true if CT images will be generated, otherwise false.
////////////////////////////////////////////////////////////////////////////////
bool ImageWorker::isEnabledCT()
{
    return m_enableCT;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::isEnabledUS()
///
/// \brief  Checks whether US images will be generated.
///
/// \return Returns true if US images will be generated, otherwise false.
////////////////////////////////////////////////////////////////////////////////
bool ImageWorker::isEnabledUS()
{
    return !m_enableCT;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::stop()
///
/// \brief  Stops the worker by ensuring the run() function exits.
////////////////////////////////////////////////////////////////////////////////
void ImageWorker::stop()
{
    qDebug() << QString( "[ImageWorker::stop] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    m_stopped = true;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::isStopped()
///
/// \brief  Checks whether the worker has been stopped.
///
/// \return Returns true if the worker has been stopped, otherwise false.
////////////////////////////////////////////////////////////////////////////////
bool ImageWorker::isStopped()
{
    return m_stopped;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageWorker::run()
///
/// \brief  The thread's main activity loop.
////////////////////////////////////////////////////////////////////////////////
void ImageWorker::run()
{
    qDebug() << QString( "[ImageWorker::run] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    // Allow the loop to keep running when this thread starts.
    // This run method will exit when stop() is called.
    m_stopped = false;

    while( !m_stopped )
    {
        // Signal that an image has been requested so the freeze timer can be started.
        emit waiting();

        // Gets the image using the given implementation.
        generateImage();
    }
}

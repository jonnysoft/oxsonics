// Qt.
#include <QDebug>
#include <QImage>
#include <QTimer>

// Project.
#include "imageprovider.h"
#include "imageworker.h"

// Statics.
const int ImageProvider::HARDWARE_TIMEOUT_MS = 2000;
const int ImageProvider::MAX_IMAGES_SAVED = 20;

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProvider::ImageProvider( ImageWorker& worker, QObject* parent )
///
/// \brief  Constructor.
///
/// \param  The injected image worker will contain the implementation to
///         generate images.
/// \param  The object's parent.
////////////////////////////////////////////////////////////////////////////////
ImageProvider::ImageProvider( ImageWorker& worker, QObject* parent )
    : QObject( parent )
    , m_timer( new QTimer() )
    , m_timerThread( new QThread() )
    , m_worker( worker )
{
    // Set up the timeout interval of 2s.
    m_timer->setInterval( HARDWARE_TIMEOUT_MS );
    m_timer->setSingleShot( true );

    // Move the timer to a separate thread so it doesn't block the main application
    // since QTimer's will run in the main event loop.
    m_timer->moveToThread( m_timerThread );
    m_timerThread->start();

    // Connect the timeout signal to handle hardware timeouts.
    // The direct connection ensures the timeout is processed in the timer's thread
    // rather than the main event loop's thread.
    connect( m_timer, &QTimer::timeout, this, &ImageProvider::onTimeout, Qt::DirectConnection );

    // Connect worker signals to handle new images and timeouts.
    connect( &m_worker, &ImageWorker::newImage, this, &ImageProvider::onNewImage );
    connect( &m_worker, &ImageWorker::timeout,  this, &ImageProvider::onTimeout );

    // QTimer has overloaded start() so we need to use a slightly messy syntax to ensure the correct slot is called.
    connect( &m_worker, &ImageWorker::waiting, m_timer, static_cast<void ( QTimer::* )()> ( &QTimer::start ) );

    // Connect threads finished signal so app can be closed cleanly.
    connect( &m_worker,     &QThread::finished, this, &ImageProvider::onThreadsFinished );
    connect( m_timerThread, &QThread::finished, this, &ImageProvider::onThreadsFinished );
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProvider::start()
///
/// \brief  Starts the image generation.
////////////////////////////////////////////////////////////////////////////////
void ImageProvider::start()
{
    qDebug() << QString( "[ImageProvider::start] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    // Start the worker thread.
    m_worker.start();
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProvider::onNewImage( QImage* image )
///
/// \brief  Handles a new image being generated.
///
/// \param  The new image.
////////////////////////////////////////////////////////////////////////////////
void ImageProvider::onNewImage( QImage* image )
{
    qDebug() << QString( "[ImageProvider::onNewImage] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    static unsigned int id = 0;

    // Only save a maximum number of images in the scope of this exercise.
    // Normally, this limit wouldn't be applied.
    if ( id < MAX_IMAGES_SAVED )
    {
        image->save( QString( "file_%1.png").arg( id ), "PNG" );

        ++id;
    }

    delete image;
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProvider::onTimeout()
///
/// \brief  Handles timeouts.
////////////////////////////////////////////////////////////////////////////////
void ImageProvider::onTimeout()
{
    qDebug() << QString( "[ImageProvider::onTimeout] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    // If there's a hardware timeout then assume something has gone wrong so stop
    // all threads to prevent any more images being requested.
    m_worker.stop();
    m_timer->stop();
    m_timerThread->quit();
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProvider::onThreadsFinished()
///
/// \brief  Handles when threads have finished.
////////////////////////////////////////////////////////////////////////////////
void ImageProvider::onThreadsFinished()
{
    qDebug() << QString( "[ImageProvider::onThreadsFinished] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    // Wait until all threads have finished.
    if ( !m_worker.isRunning() &&
         !m_timerThread->isRunning() )
    {
        // Signal image generation has finished so the application can close.
        emit finished();
    }
}

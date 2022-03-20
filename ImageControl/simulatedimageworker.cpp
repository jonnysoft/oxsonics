// Qt.
#include <QDebug>
#include <QImage>
#include <QMutexLocker>
#include <QRandomGenerator>

// Project.
#include "simulatedimageworker.h"

////////////////////////////////////////////////////////////////////////////////
/// \fn     SimulatedImageWorker::SimulatedImageWorker( QObject* parent )
///
/// \brief  Constructor.
///
/// \param  The object's parent.
////////////////////////////////////////////////////////////////////////////////
SimulatedImageWorker::SimulatedImageWorker( QObject* parent )
    : ImageWorker( parent )
{

}

////////////////////////////////////////////////////////////////////////////////
/// \fn     SimulatedImageWorker::generateImage()
///
/// \brief  Simulates image generation using the following fixed pattern:
///             * 10 cycles of no images.
///             * 10 images generated in less than 2 seconds.
///             * 10 images generated in more than 2 seconds.
///             * 1 timeout.
////////////////////////////////////////////////////////////////////////////////
void SimulatedImageWorker::generateImage()
{
    qDebug() << QString( "[SimulatedImageWorker::generateImage] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    // Simulate image generation following the above pattern.
    static int cycle = 0;

    if ( cycle < 10 )
    {
        qDebug() << QString( "[SimulatedImageWorker::generateImage] Simulating no image." );
        // Do nothing for the first 10 cycles.
    }
    else if ( cycle < 30 )
    {
        // Sleep for the appropriate amount of time.
        if ( cycle < 20 )
        {
            qDebug() << QString( "[SimulatedImageWorker::generateImage] Simulating fast image generation." );
            sleep( 1 );
        }
        else
        {
            qDebug() << QString( "[SimulatedImageWorker::generateImage] Simulating slow image generation." );
            sleep( 2 );
        }

        // Create the image.
        QImage* image = new QImage( 100, 100, QImage::Format_ARGB32 );
        QColor colour( QRandomGenerator::global()->bounded( 256 ),
                       QRandomGenerator::global()->bounded( 256 ),
                       QRandomGenerator::global()->bounded( 256 ) );

        image->fill( colour );

        // Notify listeners of the new image.
        emit newImage( image );
    }
    else
    {
        qDebug() << QString( "[SimulatedImageWorker::generateImage] Simulating known timeout." );

        emit timeout();
    }

    // Reset the cycle.
    if ( ++cycle > 30 )
    {
        cycle = 0;
    }
}

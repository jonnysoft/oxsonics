// Qt.
#include <QDebug>
#include <QImage>
#include <QMutexLocker>

// Project.
#include "clibimageworker.h"

extern "C"
{
    // This is the c-based library that needs to be added.
    #include "clib.h"
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     CLibImageWorker::CLibImageWorker( QObject* parent )
///
/// \brief  Constructor.
///
/// \param  The object's parent.
////////////////////////////////////////////////////////////////////////////////
CLibImageWorker::CLibImageWorker( QObject* parent )
    : ImageWorker( parent )
{

}

////////////////////////////////////////////////////////////////////////////////
/// \fn     CLibImageWorker::generateImage()
///
/// \brief  Generates the image using the existing C-based library.
////////////////////////////////////////////////////////////////////////////////
void CLibImageWorker::generateImage()
{
    qDebug() << QString( "[CLibImageWorker::generateImage] [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    QMutexLocker locker( &m_mutex );

    // Allocate image memory.
    // NOTE: Need to specify the correct array size here.
    unsigned int size = 100 * 100;
    double* data = new double[size];

    ERROR_TYPE result = getImage( m_enableCT
                                    ? IMAGE_TYPE::CT
                                    : IMAGE_TYPE::US,
                                  data );

    // Check the result and emit the appropriate signal if necessary.
    switch( result )
    {
        case ERROR_TYPE::OK:
        {
            // Create QImage from the raw data.
            // NOTE: The cast here may be inaccurate, this will need to be checked.
            QImage* image = new QImage( ( uchar* ) data, 100, 100, QImage::Format_ARGB32 );

            emit newImage( image );
            break;
        }

        case ERROR_TYPE::TIMEOUT:
        {
            // Image generation timed out.
            emit timeout();
            break;
        }

        default:
        {
            // Do nothing, no image was available.
            break;
        }
    }
}

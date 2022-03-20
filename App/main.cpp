// Qt.
#include <QCoreApplication>
#include <QDebug>
#include <QObject>

// Project.
#include "../ImageControl/clibimageworker.h"
#include "../ImageControl/imageprovider.h"
#include "../ImageControl/simulatedimageworker.h"

////////////////////////////////////////////////////////////////////////////////
/// \brief  Application entry point.
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    QCoreApplication app( argc, argv );

    qDebug() << QString( "[main] Starting application... [0x%1]" ).arg( ( int ) QThread::currentThreadId(), 0, 16 );

    // Create the C-based worker implementation.
//    CLibImageWorker worker;
//    worker.enableUS();

    // Create the simualated image generation worker implementation.
    SimulatedImageWorker worker;
    worker.enableUS();

    // Create the image provider.
    ImageProvider imageProvider( worker );
    imageProvider.start();

    // Allow image provider to decide when to quit the application.
    QObject::connect( &imageProvider, &ImageProvider::finished, &app, QCoreApplication::quit );

    return app.exec();
}

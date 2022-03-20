// Qt.
#include <QCoreApplication>
#include <QtTest/QtTest>

// Project.
#include "../ImageControlTest/tst_imageprovider.h"

////////////////////////////////////////////////////////////////////////////////
/// \brief  Application entry point.
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    // A GUI application is required for the event system.
    QCoreApplication app( argc, argv );

    QTest::qExec( new ImageProviderTest() );

    return 0;
}

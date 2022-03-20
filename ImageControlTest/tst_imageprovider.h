#ifndef TST_IMAGEPROVIDER_H
#define TST_IMAGEPROVIDER_H

// Qt.
#include <QObject>

// Project.
#include "mocks/mockimageworker.h"
class ImageProvider;

////////////////////////////////////////////////////////////////////////////////
/// \class  Unit tests for the ImageProvider class.
////////////////////////////////////////////////////////////////////////////////
class ImageProviderTest : public QObject
{
    Q_OBJECT

public:
    explicit ImageProviderTest( QObject* parent = nullptr );

private slots:

    // Test initialisation.
    void init();
    void initTestCase();

    // Tests.
    void testSignals();
    void testStart();
    void testNewImage();

    // Test cleanup.
    void cleanup();
    void cleanupTestCase();

private:
    ImageProvider* m_imageProvider;         ///< Class under test.
    MockImageWorker* m_mockImageWorker;     ///< Mock image worker.
};

#endif // TST_IMAGEPROVIDER_H

// Qt.
#include <QtTest/QtTest>

// Project.
#include "../ImageControl/imageprovider.h"
#include "tst_imageprovider.h"

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::ImageProviderTest()
///
/// \brief  Constructor.
///
/// \param  Parent.
////////////////////////////////////////////////////////////////////////////////
ImageProviderTest::ImageProviderTest( QObject* parent )
    : QObject( parent )
{
    // Create any mocks.
    m_mockImageWorker = new MockImageWorker();

    // Create the class under test.
    m_imageProvider = new ImageProvider( *m_mockImageWorker );
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::init()
///
/// \brief  Initialises the test case, called before every test.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::init()
{

}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::initTestCase()
///
/// \brief  Initialises the test case, called once before the test run.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::initTestCase()
{

}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::testSignals()
///
/// \brief  Tests that the relevant signals exist.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::testSignals()
{
    QVERIFY( QObject::connect( m_imageProvider, &ImageProvider::finished, [] () {} ) );
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::testStart()
///
/// \brief  Tests that starting the image provider starts the image worker thread.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::testStart()
{
    // Start the image provider.
    m_imageProvider->start();

    QVERIFY( m_imageProvider->m_worker.isRunning() );
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::testNewImage()
///
/// \brief  Tests that new images are passed correctly and then deleted.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::testNewImage()
{
    // Mock a new image being created.
    m_mockImageWorker->m_mockImage = new QImage( 111, 222, QImage::Format_ARGB32 );
    m_mockImageWorker->doNewImage();

    // If the image worker is connected correctly then the mock image should have been
    // passed to the image provider in the newImage signal and saved.
    // We can then load the saved image using the expected filename and it should
    // exist.
    QImage image;
    image.load( QString( "file_0.png"), "PNG" );

    // Verify some of the image properties match.
    QVERIFY( image.width() == 111 );
    QVERIFY( image.height() == 222 );
    QVERIFY( image.format() == QImage::Format_ARGB32 );
}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::cleanup()
///
/// \brief  Cleans up the test case, called after every test function.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::cleanup()
{

}

////////////////////////////////////////////////////////////////////////////////
/// \fn     ImageProviderTest::cleanupTestCase()
///
/// \brief  Cleans up the test case, called at the end of the test run.
////////////////////////////////////////////////////////////////////////////////
void ImageProviderTest::cleanupTestCase()
{
    delete m_imageProvider;
}

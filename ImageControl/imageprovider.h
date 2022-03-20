#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

// Qt.
#include <QMutex>
#include <QThread>

class QImage;
class QThread;
class QTimer;

// Project.
class ImageWorker;

////////////////////////////////////////////////////////////////////////////////
/// \class  The image provider.
///
/// \brief  This will provide images using the implementation contained within
///         the injected worker thread.
////////////////////////////////////////////////////////////////////////////////
class ImageProvider : public QObject
{
    Q_OBJECT

public:
    // Structure.
    explicit ImageProvider( ImageWorker& worker, QObject* parent = nullptr );

    // Control.
    void start();

    // Statics.
    static const int HARDWARE_TIMEOUT_MS;       ///< Hardware freeze timeout interval (ms).
    static const int MAX_IMAGES_SAVED;          ///< The maximum number of images that will be saved.

    // Friendship.
    friend class ImageProviderTest;

signals:
    void finished();

protected slots:
    void onNewImage( QImage* image );
    void onTimeout();
    void onThreadsFinished();

protected:
    QTimer* m_timer;                ///< Additional timer to check for hardware freezes.
    QThread* m_timerThread;         ///< Thread for the timer to prevent blocking the main event loop.
    QMutex m_mutex;                 ///< Protects member access across threads.
    ImageWorker& m_worker;          ///< Worker that will generate images.
};

#endif // IMAGEPROVIDER_H

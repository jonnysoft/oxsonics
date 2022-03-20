#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H

// Qt.
#include <QMutex>
#include <QThread>

class QImage;

////////////////////////////////////////////////////////////////////////////////
/// \class  The image worker abstract class.
///
/// \brief  The image worker runs continuously in a separate thread and checks
///         signals when new images are available or errors occur.
////////////////////////////////////////////////////////////////////////////////
class ImageWorker : public QThread
{
    Q_OBJECT

public:
    // Structure.
    explicit ImageWorker( QObject* parent = nullptr );

    // Data.
    virtual void generateImage() = 0;

    // Modes.
    void enableCT();
    void enableUS();
    bool isEnabledCT();
    bool isEnabledUS();

    // Operation.
    void stop();
    bool isStopped();

    // Friendship.
    friend class ImageWorkerTest;

signals:
    void waiting();                     ///< An image has been requested and is currently waiting.
    void newImage( QImage* image );     ///< New image has been obtained.
    void timeout();                     ///< Image request timed out.

protected:
    // Threads.
    virtual void run();

    // NOTE: Ideally, I'd like to use the enum here but the enums provided in the c library need to
    // be moved to a seperate header file so they can be used without causing conflicts with the
    // getImage() function.
    // The other alternative is to redefine the enum here but that's duplicating code.
    // This solution is the simplest and allows the same configuration without modifying the
    // existing libraries.
    bool m_enableCT;        ///< CT images will be generated if true, otherwise US images will be generated.
    bool m_stopped;         ///< Indicates whether the thread should be running.

    QMutex m_mutex;         ///< Protects member access across threads.
};

#endif // IMAGEWORKER_H

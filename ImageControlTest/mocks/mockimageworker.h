#ifndef MOCKIMAGEWORKER_H
#define MOCKIMAGEWORKER_H

// Qt.
class QImage;

// Project.
#include "../../ImageControl/imageworker.h"

////////////////////////////////////////////////////////////////////////////////
/// \class  A mock image worker.
///
/// \brief  The image worker runs continuously in a separate thread and checks
///         signals when new images are available or errors occur.
////////////////////////////////////////////////////////////////////////////////
class MockImageWorker : public ImageWorker
{
public:
    explicit MockImageWorker( QObject* parent = nullptr );

    // Data.
    virtual void generateImage();

    // Signals.
    void doWaiting();
    void doNewImage();
    void doTimeout();

    QImage* m_mockImage;
};

#endif // MOCKIMAGEWORKER_H

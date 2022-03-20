#ifndef CLIBIMAGEWORKER_H
#define CLIBIMAGEWORKER_H

// Project.
#include "imageworker.h"

////////////////////////////////////////////////////////////////////////////////
/// \class  The c- based image generator.
///
/// \brief  The image worker runs continuously in a separate thread and checks
///         signals when new images are available or errors occur.
////////////////////////////////////////////////////////////////////////////////
class CLibImageWorker : public ImageWorker
{
    Q_OBJECT

public:
    // Structure.
    explicit CLibImageWorker( QObject* parent = nullptr );

    // Data.
    virtual void generateImage();

    // Friendship.
    friend class CLibImageWorkerTest;
};

#endif // CLIBIMAGEWORKER_H

#ifndef SIMULATEDIMAGEWORKER_H
#define SIMULATEDIMAGEWORKER_H

// Project.
#include "imageworker.h"

////////////////////////////////////////////////////////////////////////////////
/// \class  Simualtes image generation.
///
/// \brief  The image worker runs continuously in a separate thread and checks
///         signals when new images are available or errors occur.
////////////////////////////////////////////////////////////////////////////////
class SimulatedImageWorker : public ImageWorker
{
public:
    // Structure.
    explicit SimulatedImageWorker( QObject* parent = nullptr );

    // Data.
    virtual void generateImage();

    // Friendship.
    friend class SimulatedImageWorkerTest;
};

#endif // SIMULATEDIMAGEWORKER_H

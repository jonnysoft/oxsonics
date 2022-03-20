#ifndef CLIB_H
#define CLIB_H

////////////////////////////////////////////////////////////////////////////////
/// \class  Defines the state of the images.
///             * OK - An image was available and provided.
///             * EMPTY - No image was available.
///             * TIMEOUT - The hardware timed out whilst getting the image.
////////////////////////////////////////////////////////////////////////////////
enum ERROR_TYPE
{
    OK,
    EMPTY,
    TIMEOUT
};

////////////////////////////////////////////////////////////////////////////////
/// \enum   Defines the type of images.
///             * US - Ultrasound.
///             * CT - Computed tomography.
////////////////////////////////////////////////////////////////////////////////
enum IMAGE_TYPE
{
    US,
    CT
};

////////////////////////////////////////////////////////////////////////////////
/// \fn     getImage( IMAGE_TYPE type, double* image )
///
/// \brief  Gets an image from the hardware if one is available.
///
/// \param  The image type to get.
/// \param  The pointer to the raw data.
///
/// \return The result of the image generation.
////////////////////////////////////////////////////////////////////////////////
ERROR_TYPE getImage( IMAGE_TYPE type, double* image )
{
    (void) type;
    (void) image;

    return ERROR_TYPE::EMPTY;
}

#endif // CLIB_H

OxSonics Technical Test
Jon-Paul Murrow

Please find my attempt at the OxSonics technical test.
I have assumed that images will be 100x100 pixels and ARGB 32 bit format.
For simplicity I have not created proper libraries as I felt this goes beyond the scope of the task.
As a result, the files within those liraries are built with the application but show how I would create
separate modules for them.

Please feel free to ask any questions. My email is jon-paul.murrow@jonnysoft.co.uk

Kindest regards

JP

----------------------------------------
File system
----------------------------------------
The repository contains the following folders:

App - The main runnable application.
ImageControl - Library containing the image generation files.
ImageControlTest - Library containing unit tests for the ImageControl library.
UnitTests - Runnable unit test application.

----------------------------------------
Problem
----------------------------------------
Essentially, there were three problems:
1) How to handling multi-threading to prevent getImage() from stalling the application.
2) How to detect a hardware freeze.
3) How to structure and test the code.

----------------------------------------
Solution
----------------------------------------
There should be sufficient comments in the code to explain my intentions but essentially, the ImageProvider is the main 
entry point to the application. You simply provide an implementation and inject it into the constuctor of ImageProvider.
Since I do not have the source for the C image library, I've injected a simulated image generation.

1) Allow the getImage() function to be called from inside it's own thread so that it doesn't block the main GUI thread.
Sub-classing QThread can be used for this and signals and slots are used to ensure the right code is called from the right thread.

2) A separate QTimer is re-started before getImage is called. This also needs to be run in it's own thread since, by deafult,
it would be run in the GUI thread this blocking it. Once triggered, the ImageProvider is able to detect a problem and act
accordingly (in this example, by closing the app).

3) An abstract class ImageWorker is used so that different implementations can be used. This is particularly useful for 
simulating and unit testing, both of which have been demonstrated here. I would have liked to extend the unit tests 
to use QSignalSpy and mock QTimer.

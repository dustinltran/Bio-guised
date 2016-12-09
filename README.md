# Bio-guised
* IMPORTANT: This is for Windows platform only!

DESCRIPTION: Application to create a multilevel security on a windows platform.

AUTHORS: Sam Rucker, Dustin Tran, Daniel Trebe

Parts Required:
  * Ardunio Uno Rev. 3
  * Breadboard
  * TTL Fingerprint Scanner
  * 560 ohm resistor
  * 1k ohm resistor
  * wires

Setup/Install
  Easy way:
  1.  Download zip file.
  2.  Extract the files.
  3.  Navigate into the folder "Bio-guised".
  4.  Run "Bio-guised.exe"
  5.  (Only if steps 1-4 are not enough) download and install Visual C++ Redistributable 2015:   https://www.microsoft.com/en-us/download/details.aspx?id=48145
  6.  (Only if steps 1-4 are not enough) retry step 4.
  
Harder way:
  1.  Install Qt: https://www.qt.io/
  2.  Download zip file.
  3.  Extract the files.
  4.  Navigate to "senior-project/Bio-guised"
  5.  Open the file Bio-guised.pro which is a Qt Project file.
  6.  Press: CTRL + R or click on the topmost big plain green arrow in the bottom left corner to run.
  7.  (If strange errors occure) Click on build at the top then do a "Clean All", "Run qmake", and finally do a "Build All"
  8.  Retry step 6.

Running Bio-guised (As of 4/22/2016)
  1.  After Setup/install steps you will be greeted with the registration window.
  2.  Clicking on a button in the top section will open up a another window to set the desired fingerprint into the slot. (currently only the left most button is connected and the back button is not setup so just close the window)
  3.  Clicking on the "Register" button will lead you to the home window.
  4.  Clicking on the "Add File" button will allow you to browse through your files until you select a file you wish to store.
  5.  Once selecting the desired file the explorer will close and the file will be moved to the bioguised-testfolder located in the same directory as "Bio-guised.exe".

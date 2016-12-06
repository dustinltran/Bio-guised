# Bio-guised
* Repo URL: https://github.com/dustinltran/Bio-guised
* IMPORTANT: This is for Windows platform only!
* DISCLAIMER: for testing purposes, Bio-guised will launch registration screen but will not function after without the required hardware (fingerprint scanner)

DESCRIPTION: Application add multilevel security on a windows platform.

AUTHORS: Sam Rucker, Dustin Tran, Daniel Trebe

Parts Required:
  * Ardunio Uno Rev. 3
  * Breadboard
  * Adafruit Fingerprint Scanner
  * Wires

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

Running Bio-guised (As of 12/5/2016)
  1.  After Setup/install steps you will be greeted with the registration window.
  2.  Clicking on a button indicating which fingerprint you want to register in the top section will open up a another window to set the desired fingerprint into the slot.
  3.  When ready to read in appropriate fingerprint using the scanner, press the “Register Fingerprint” button on the pop up.  The fingerprint scanner will light up red when ready to read in fingerprint.  Press finger against illuminated optical reader until the red light goes out.  The light will then illuminate again, prompting you to read in the same finger print one more time for validation.  Only one fingerprint needs to be registered, but steps 2-3 may be repeated for up to 10 fingers.
  4.  When satisfied with print registration, press the “Register” button on the main window to lead into the home window.
  5.  Clicking on the "Add File" button will open a file navigation window allowing you to choose a file to be hidden using the application.  Clicking on the "Add Folder" button brings up a file navigation window that allows the user to choose an entire directory of files to add to the application.
  6.  When done selecting the desired file the explorer will close and the file will be moved to the bioguised-testfolder located in the same directory as “Bio-guised.exe".
  7.  To make the data added to the application inaccessable to others, the application can be closed manually using the close button, or it will automattically close when the USB scanner device is disconnected, encrypting and obfuscation the data until your identity is verified using the scanner next time.


This is an Video game with GUI developed based on OpenGL Framework

Developer: Chen Chongsong from Nanyang Technological University


Environment Requirement: MacOSX + Xcode

  // If your program is having trouble finding the Assets directory,
  // open the main.cpp file,
  // replace the string literal with a full path name to the directory,
  // e.g., "Z:/CS32/IceMan/Assets" or "/Users/fred/cs32/IceMan/Assets"

Project Website:
http://www.solomonlrussell.com/summer17/cs32/
(Click “Project4 spec”)

===========================================================================

Mac OS X: You'll need to have XQuartz and freeGLUT installed to run the program.

1. Install XQuartz:
Click the download link http://xquartz.org/ , open the downloaded .dmg file, double-click on XQuartz.pkg, and follow the installation instructions.
Log out and log back in again.
To verify the installation, open a Terminal window and run the command echo $DISPLAY. That should produce one line of output that ends with org.macosforge.xquartz:0.

2. Install freeGLUT. You have two options:

Option 1: Install the MacPorts package manager (https://guide.macports.org/). Select the appropriate installation links and install the package:
	MacPorts-2.4.0-10.12-Sierra.pkg https://distfiles.macports.org/MacPorts/MacPorts-2.4.0-10.12-Sierra.pkg
	MacPorts-2.4.0-10.11-ElCapitan.pkg https://distfiles.macports.org/MacPorts/MacPorts-2.4.0-10.11-ElCapitan.pkg
	MacPorts-2.4.0-10.10-Yosemite.pkg https://distfiles.macports.org/MacPorts/MacPorts-2.4.0-10.10-Yosemite.pkg
	MacPorts-2.4.0-10.9-Mavericks.pkg https://distfiles.macports.org/MacPorts/MacPorts-2.4.0-10.9-Mavericks.pkg
	MacPorts-2.4.0-10.8-MountainLion.pkg https://distfiles.macports.org/MacPorts/MacPorts-2.4.0-10.8-MountainLion.pkg
To verify the installation, open a new Terminal window and run the command port version. That should produce the output Version: 2.3.4. In that new Terminal window, run the command sudo port install freeglut, which will prompt you for your password to authorize installation. A lot of output will be produced. To verify the installation, run the command port installed freeglut. 
When some people run sudo port install freeglut, the response is Error: Port freeglut not found and the installation fails. That's probably because you are behind the a firewall. Bypassing the firewall (perhaps by creating a hotspot with your phone) may do the trick. You might also need to run sudo port selfupdate, but that step is probably not necessary.

Option 2: Install the homebrew package manager (http://brew.sh/). Then run the command brew install homebrew/x11/freeglut.

3. Open the folder “IceMan_Executable”. In that folder is a file named INSTRUCTION.txt that tells you how to launch the program.
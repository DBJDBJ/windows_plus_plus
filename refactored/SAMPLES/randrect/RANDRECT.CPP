//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: RANDRECT.CPP
//
// RANDRECT adapted for Windows++ from orignal program by 
// Charles Petzold in "Programming Windows" Chapter 12.

#include "../prefix.h"

MyApp myApp; // instantiate one and only app

class RandRect final : public WPMainWin {
public:
	RandRect()					{ createWin("Windows++ Random Rectangles"); }
	BOOL doIdle();				// virtual function called during idle loop
};

void MyApp::main()
{
	mainWin = new RandRect;
	run();
}

BOOL RandRect::doIdle()
{
	WPRect win = this;
	WPRect box(rand() % win.width(), rand() % win.height(),
		rand() % win.width(), rand() % win.height());
	box.normalize();		// normalize (no negative width, ht)

	WPWinDC dc = this;
	dc.setBrush( RGB(rand()&255, rand()&255, rand()&255) );
	dc.rectangle(box);

	::Sleep(1000); // DBJ: otherwise it is too fast on modern year 2022 machines

	return TRUE;			// tell Windows++ to do idle loop
}

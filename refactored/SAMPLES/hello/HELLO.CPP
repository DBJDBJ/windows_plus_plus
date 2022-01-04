// 2022 Refactoring by dbj at dbj dot org
//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: HELLO.CPP
//

#include "../prefix.h"

MyApp myApp;

class HelloWin : public WPMainWin {
public:
	HelloWin() { createWin("Hello2022"); }
	void paint(WPPaintDC &pdc) {
		WPRect clientArea = this;
		pdc.drawText(clientArea, "Hello, Windows++ 2022",
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
};

void MyApp::main()
{
	mainWin = new HelloWin;
	run();
}

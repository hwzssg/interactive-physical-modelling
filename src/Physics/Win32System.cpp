
/* -------------------------------------------------
  
 @Filename  : Win32System.cpp
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: Class implementation.

 ------------------------------------------------- */

#include "Win32System.h"

// Constructor & Deconstrucor
Win32System::Win32System()
	: m_pWindow(new Win32Window()), 
	  m_pInput(new Win32Driver()),
	  m_Type(WINDOWED),
	  m_Quit(FALSE)
{
}

Win32System::~Win32System()
{
	SAFE_RELEASE(m_pWindow);
	SAFE_RELEASE(m_pInput);
}

// Member Functions
bool Win32System::WindowRunning() 
{
	return(m_pWindow->onUpdate());
}

void Win32System::Initialise()
{
	// Initialise the window & opengl
	m_pWindow->Initialise();
	m_pWindow->Display(m_Type);
	m_pWindow->EnableOpenGL();

	// Initialise input
	HWND Handle = m_pWindow->GetHandle();
	m_pInput->Initialise(&Handle);

	// And glew
	GLenum error = glewInit();
	if(error != GLEW_OK) 
	{
		printf("Error: %s\n", glewGetErrorString(error));
		system("pause");
	}
}

void Win32System::SwapWindowBuffers()
{
	SwapBuffers(GetDC(m_pWindow->GetHandle()));
}

void Win32System::onUpdate()
{
	m_pWindow->onUpdate();
	m_pInput->onUpdate();
}

// Get & Set Functions
void Win32System::setWindowType(Type type)
{
	this->m_Type = type;
}

void Win32System::setWindowTraits(CHAR * c, Region s)
{
	m_pWindow->setTraits(c, s.x, s.y, s.w, s.h);
}

Win32Window * Win32System::getWindow()
{
	return m_pWindow;
}
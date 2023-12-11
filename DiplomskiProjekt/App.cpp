#include "App.h"


wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Face recognition");

	mainFrame->SetClientSize(400, 300);
	mainFrame->Center();

	mainFrame->Show();
	return true;
}
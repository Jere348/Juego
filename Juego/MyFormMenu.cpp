#include "MyFormMenu.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    TrabajoFinal2025::MyForm^ form = gcnew TrabajoFinal2025::MyForm();
    Application::Run(form);
}
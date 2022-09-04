#include "devices.h"
#include "main_form.h"

using namespace jimo_sdr;

soapy::devices soapy_devices;

int main()
{
    main_form form1;
    form1.show();
    form1.show_source_dlg();
    xtd::forms::application::run(form1);
    return EXIT_SUCCESS;
}
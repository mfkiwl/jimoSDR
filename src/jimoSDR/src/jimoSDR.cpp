#include <xtd/xtd>

using namespace xtd;
using namespace xtd::forms;

class jimo_form : public form
{
    public:
        jimo_form() {
        }
};

int main()
{
    jimo_form form1 {};
    application::run(form1);
    return EXIT_SUCCESS;
}
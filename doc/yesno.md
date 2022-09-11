# Yes/No
There is an yesno API for libtermg in `libtermg/yesno.hpp`.
```
#include <libtermg/yesno.hpp>
```
Available function is:
```
bool nc_yesno(const std::string text, const std::string title="")
bool nc_yesno(const std::vector<std::string> text, const std::string title="")
```
*text* is required argument. *title* is optional argument and his default parameter is nothing.
*title* is name of your menu, *text* - your text.
`nc_yesno()` returns *True* if you select **Yes** and *False* if you select **No**

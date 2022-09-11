# Title
There is an title API for libtermg in `libtermg/title.hpp`.
```
#include <libtermg/select.hpp>
```
Available function is:
```
void nc_title(const std::string text, const std::string title="")
void nc_title(const std::vector<std::string> text, const std::string title="")
```
*text* is required argument. *title* is optional argument and his default parameter is nothing.
*title* is name of your menu, *text* - your text.

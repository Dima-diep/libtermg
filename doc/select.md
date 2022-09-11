# Select
There is an selection API for libtermg in `libtermg/select.hpp`.
```
#include <libtermg/select.hpp>
```
Available function is:
```
unsigned int selectmenu(const std::string title, const std::vector<std::string> menus, const selectsetup setup, const unsigned int pos)
```
*title* and *menus* are required arguments. *pos* is optional argument and his default parameter is 6.
*title* is name of your menu, *menus* - your variants of selection, *pos* - length of selection menu (how many selection can be seen at one time).
`selectmenu()` return count of selection (started from 0)

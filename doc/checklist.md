# Checklist
There is an checklist API for libtermg in `libtermg/checklist.hpp`.
```
#include <libtermg/checklist.hpp>
```
Available function is:
```
std::vector<unsigned int> checklist(const std::string title, const std::vector<std::string> menus, const selectsetup setup, const unsigned int pos)
```
*title* and *menus* are required arguments. *pos* is optional argument and his default parameter is 6.
*title* is name of your menu, *menus* - your variants of selection, *pos* - length of selection menu (how many selection can be seen at one time).
`checklist()` return vector of counts of selection (started from 1)

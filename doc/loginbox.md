# LoginBox
There is an loginbox API in `libtermg/loginbox.hpp`
```
#include <libtermg/loginbox.hpp>
```
Available function is:
```
reg loginbox(const std::string title="", const unsigned int len=10)
```
There is 2 optional arguments - *title* and *length* (default value is 10)

This function returns `struct reg` which contains login and password:
```
struct reg {
    std::string login, password;
};
```

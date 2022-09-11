# PasswordBox
There is a password API for libtermg in `libtermg/passwordbox.hpp`
```
#include <libtermg/passwordbox.hpp>
```
There is a function:
```
std::string passwdbox(const std::string title="", const unsigned int len=10)
```
which returns password.
*title* and *len* are optional arguments.

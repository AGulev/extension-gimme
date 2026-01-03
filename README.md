# Gimme Defold value

A tiny extension that contains functions to convert Defold types into different values.

---

This is a tiny extension that helps read errors from release builds to better understand what's going on.  
Just add the following snippet to your game code and run the debug build:

```lua
    local pls_gimme = require("extension-gimme.pls_gimme")
    local err_str = [["DEFOLD:ERROR:GAMEOBJECT: Instance '<unknown:2403139543084994936>' could not be found when dispatching message '<unknown:1470838101223322218>' sent from game:<unknown:2403139543084994936>#<unknown:3368041780547566206>\n"]]
    local unhashed_err = pls_gimme.error_message(err_str)
    print(err_str, "\n->\n", unhashed_err)
```

```txt
DEBUG:SCRIPT: "DEFOLD:ERROR:GAMEOBJECT: Instance '<unknown:2403139543084994936>' could not be found when dispatching message '<unknown:1470838101223322218>' sent from game:<unknown:2403139543084994936>#<unknown:3368041780547566206>\n"	
->
"DEFOLD:ERROR:GAMEOBJECT: Instance '/go' could not be found when dispatching message 'disable' sent from game:/go#<unknown:3368041780547566206>\n"

```
⚠️ You should understand that there is no magic. This module just takes values from a `ReverseHashTable` which exists in the debug build.  
If a value was hashed during the debug build session, it will be retrieved and converted into a string. If not, it will remain as "<unknown:*>".  
So, run this script with that in mind. In practice, that usually means you should run it during the gameplay process.  
I typically add a breakpoint somewhere and use "eval" from the editor.

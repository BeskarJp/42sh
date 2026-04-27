# 42sh

TCSH-like Shell made in EPITECH.

--- 

## Description

Conclusion of minishell 1 and 2, 42sh is a full recreation of the TCSH Shell, including various features, ranging from basic commands (like ls or echo), builtin commands (such as cd and setenv) and even redirections (for exemple: "|", ">" or even ">>"), the full list of major 42sh features can be found below:

* **MAJOR FEATURES** :
    * `inhibitors`
    * `globbings`
    * `job control`
    * `backticks`
    * `parentheses`
    * `variables`
    * `special variables`
    * `history`
    * `aliases`
    * `line edition`
    * `scripting`

---

 ## Usage

First, you have to build it as an executable:
```bash
make
```

This will create a binary named "42sh", then you just have to execute the binary like this:
```bash
./42sh
```

and you're ready to go!

---

## Error Handling

The 42sh will return the same value as the TCSH shell, exemple:
> **Exemple :** a segmentation fault will exit with the code 139, or the shell command ls will return 0 upon success.

---

## Notes

- This projet was written in **C**.
- This project is absolutely **NOT** for sale.
- Beware EPITECH students, any attempt of stealing the code will result in a -42.

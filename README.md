# 42sh - EPITECH Project

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

This project is licensed under the [MIT License](LICENSE).

> Complete command interpreter based on the **TCSH** shell architecture, developed as part of Epitech's Unix System Programming module.

## Description

**42sh** is the culmination of EPITECH's Minishell cycle. This project consists of creating a robust shell capable of handling complex command execution, variable manipulation, process control (Job Control), and an advanced interactive user interface.

The main objective is **stability** and compliance with the reference shell behavior: `tcsh`.

---

## 🛠️ Features

### Fundamentals

* **Standard Execution**: System commands with PATH handling.
* **Pipes & Redirections**:
* Pipes (`|`) for chaining.
* Single and double input/output redirections (`>`, `>>`, `<`, `<<`).


* **Separators & Logic**: `;`, `&&`, `||`.
* **Subshells**: Command grouping via `( )`.

### Advanced Management

* **Job Control**: Background task management (`&`), and built-ins `jobs`, `fg`, `bg`.
* **Variables**:
* Environment variables (`setenv`, `unsetenv`, `env`).
* Local variables (`set`, `unset`, `export`).
* Variable expansion via `$`.


* **Aliases & History**: Customizable alias system and command history navigation in a linked list (`!`).
* **Globbing**: Support for patterns `*`, `?`, `[ ]`.

### User Interface

* **Line Editing**: Interactive command-line editing (cursor movement, deletion, Raw mode management).
* **Inhibitors**: Handling of quotes and backslashes.

### Exclusive Bonuses

* **EpiClaude**: Integrated intelligent assistant for command help. Reuses command parsing, except that instead of executing the command, it interprets it.
* **Built-in Editor**: A visual text editor (Emacs style) in `ncurses` accessible via the `party-editor` or `emac` command.
* **Scripting**: Ability to interpret script files.

---

## Installation and Usage

### Prerequisites

* A C compiler
* The `ncurses` library (for the visual editor)

### Compilation

Generate the executable using the Makefile:

```bash
make

```

### Execution

```bash
./42sh

```

---

## Testing and Errors

The shell is designed to strictly match TCSH in terms of exit codes and error messages.

* **Exit Codes**: A `Segmentation Fault` will return `139`, for example.
* **Validation**: Unit tests can be run (if present) via:

```bash
make tests_run

```

---

## ⚠️ Important Notes

* **Language**: Written entirely in C.
* **EPITECH Warning**: This project is for educational use. Any attempt at plagiarism (copy-pasting) by an EPITECH student will be considered cheating.
---

*Project created by the 42sh team - 2026*

*Laouënan, Hugo, Joshua, Noa, Sylvain* - *Class of 2030 PGE*

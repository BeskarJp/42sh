/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Print Epi Claude
*/

#include "shell.h"

void print_header(shell_t *shell)
{
    char *username = user_of_shell(shell->copy_env);
    char welcome[128];

    my_printf("\033[H\033[J");
    my_printf("\n%s [#] %s EpiClaude Code %s version 42.sh",
        ORANGE, STYLE_BOLD, GREY);
    my_printf("\033[22m (For quit EpiClaude,");
    my_printf(" try 'exit' or 'quit' or 'close')\n\n");
    sprintf(welcome, "Hello %s ! I'm here for help you !\n", username);
    my_printf("%s ", RESET);
    ia_style_text_writer(welcome, SLOW);
    my_putchar('\n');
}

void print_explication_shell(void)
{
    const char *fileway = "./bonus/epiclaude/rdr_files/notions.rdr";
    char *line_in_file = NULL;
    struct stat sb;
    int fd = open(fileway, O_RDONLY);

    if (fd == -1 || stat(fileway, &sb) == -1) {
        ia_style_text_writer("\nSorry, I need my 'notions.rdr' file", SLOW);
        ia_style_text_writer(" ...\n\n", ULTRA_SLOW);
        return;
    }
    line_in_file = malloc(sizeof(char) * (sb.st_size + 1));
    if (line_in_file == NULL)
        return;
    if (read(fd, line_in_file, sb.st_size) >= 0)
        display_line_in_file(line_in_file, sb.st_size);
    free(line_in_file);
    close(fd);
}

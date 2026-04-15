/*
** EPITECH PROJECT, 2026
** exec_globbings_utils
** File description:
** exec_globbings_utlis for 42sh
*/

#include "shell.h"

/**
 * @brief Frees the array of matches up
 *
 * @param matches The array of matched strings to be freed.
 * @param i The index up to which the strings should be freed.
 */
static void free_matches_until(char **matches, size_t i)
{
    size_t j;

    for (j = 0; j < i; j++)
        free(matches[j]);
    free(matches);
}

/**
 * @brief Allocates and duplicates matched files from glob result
 *
 * @param gl Glob result structure
 */
static char **alloc_matches(glob_t *gl)
{
    char **matches;
    size_t i;

    matches = malloc(sizeof(char *) * (gl->gl_pathc + 1));
    if (!matches)
        return NULL;
    for (i = 0; i < gl->gl_pathc; i++) {
        matches[i] = my_strdup(gl->gl_pathv[i]);
        if (!matches[i]) {
            free_matches_until(matches, i);
            return NULL;
        }
    }
    matches[gl->gl_pathc] = NULL;
    return matches;
}

/**
 * @brief Collects all files matching a glob pattern
 *
 * @param pattern Glob pattern to match
 */
char **collect_matches(char *pattern)
{
    glob_t gl;
    char **matches;

    if (glob(pattern, GLOB_NOCHECK, NULL, &gl) != 0)
        return NULL;
    matches = alloc_matches(&gl);
    globfree(&gl);
    return matches;
}

/**
 * @brief Expands and appends the matched strings to the destination array of arguments
 *
 * @param matches The array of matched files to be added
 * @param exp The destination array that will store the expanded arguments
 * @param count A pointer to the current number of elements in the destination array
 * @param cap A pointer to the current capacity of the destination array
 * @return int. 0 on success or -1 if error
 */
static int expand_matches(char **matches, char ***exp, int *count, int *cap)
{
    int j;

    for (j = 0; matches[j]; j++) {
        if (append_match(exp, count, cap, matches[j]) == -1)
            return -1;
    }
    free(matches);
    return 0;
}

/**
 * @brief Processes a single argument by checking for globbing patterns
 *
 * @param arg The argument string to be processed and expanded
 * @param exp The destination array that will store the expanded arguments
 * @param count A pointer to the current number of elements in the destination array
 * @param cap A pointer to the current capacity of the destination array
 * @return int. 0 on success or -1 if error
 */
static int handle_arg(char *arg, char ***exp, int *count, int *cap)
{
    char **matches;
    char *copy;

    matches = NULL;
    if (is_globbing_pattern(arg))
        matches = collect_matches(arg);
    if (matches)
        return expand_matches(matches, exp, count, cap);
    copy = my_strdup(arg);
    if (!copy)
        return -1;
    return append_match(exp, count, cap, copy);
}

/**
 * @brief Expands all arguments, matching glob patterns to files
 *
 * @param args Original arguments
 * @param expanded Destination array for expanded arguments
 * @param count Pointer to result count
 * @param capacity Pointer to array capacity
 */
int expand_all_args(char **args, char **expanded, int *count, int *capacity)
{
    int i;

    for (i = 0; args[i]; i++) {
        if (handle_arg(args[i], &expanded, count, capacity) == -1)
            return -1;
    }
    return 0;
}

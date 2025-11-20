#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "libft.h"

// Mock or helper functions if needed

void test_validate_extension() {
    printf("Testing validate_extension...\n");
    if (validate_file_extension("map.cub") == 0) printf("  [PASS] map.cub\n"); else printf("  [FAIL] map.cub\n");
    if (validate_file_extension("map.txt") == -1) printf("  [PASS] map.txt\n"); else printf("  [FAIL] map.txt\n");
    if (validate_file_extension("cub") == -1) printf("  [PASS] cub\n"); else printf("  [FAIL] cub\n");
    if (validate_file_extension(".cub") == 0) printf("  [PASS] .cub (hidden file)\n"); else printf("  [FAIL] .cub\n");
    if (validate_file_extension("map.cub.txt") == -1) printf("  [PASS] map.cub.txt\n"); else printf("  [FAIL] map.cub.txt\n");
    if (validate_file_extension("map.txt.cub") == 0) printf("  [PASS] map.txt.cub\n"); else printf("  [FAIL] map.txt.cub\n");
}

void test_parse_color() {
    printf("Testing parse_color...\n");
    t_color c;
    // Note: parse_color modifies the string (strtok or similar) or just reads it?
    // Looking at the code, it seems to use ft_split or similar internally?
    // Wait, I saw parse_component but not parse_color implementation.
    // Let's assume it takes a string. I should pass a mutable string just in case.

    char s1[] = "255,255,255";
    if (parse_color(s1, &c) == 0 && c.r == 255 && c.g == 255 && c.b == 255)
        printf("  [PASS] 255,255,255\n");
    else
        printf("  [FAIL] 255,255,255 (ret=%d)\n", parse_color(s1, &c));

    char s2[] = "0,0,0";
    if (parse_color(s2, &c) == 0 && c.r == 0 && c.g == 0 && c.b == 0)
        printf("  [PASS] 0,0,0\n");
    else
        printf("  [FAIL] 0,0,0\n");

    char s3[] = "256,0,0";
    if (parse_color(s3, &c) != 0) printf("  [PASS] 256,0,0 (overflow)\n"); else printf("  [FAIL] 256,0,0\n");

    char s4[] = "-1,0,0";
    if (parse_color(s4, &c) != 0) printf("  [PASS] -1,0,0 (negative)\n"); else printf("  [FAIL] -1,0,0\n");

    char s5[] = "0,0";
    if (parse_color(s5, &c) != 0) printf("  [PASS] 0,0 (missing)\n"); else printf("  [FAIL] 0,0\n");
}

void test_validate_map_chars() {
    printf("Testing validate_map_chars...\n");
    t_map map;
    char *grid_valid[] = {"111", "101", "111", NULL};
    map.grid = grid_valid;
    map.height = 3;
    map.width = 3;
    if (validate_map_chars(&map) == 0) printf("  [PASS] valid grid\n"); else printf("  [FAIL] valid grid\n");

    char *grid_invalid[] = {"111", "1X1", "111", NULL};
    map.grid = grid_invalid;
    // X is valid if sprites are allowed (A-Z).
    // If validate_map_chars allows A-Z, then this should return 0.
    // But run_tester.sh expects failure for unknown symbol.
    // RESULT: It returns 0 (Allowed). This explains why run_tester.sh fails (it expects error).
    int ret = validate_map_chars(&map);
    if (ret == 0) printf("  [PASS] invalid grid (X) - ALLOWED by code\n");
    else printf("  [FAIL] invalid grid (X) - REJECTED by code (ret=%d)\n", ret);

    char *grid_really_invalid[] = {"111", "1?1", "111", NULL};
    map.grid = grid_really_invalid;
    if (validate_map_chars(&map) == -1) printf("  [PASS] really invalid grid (?)\n"); else printf("  [FAIL] really invalid grid (?)\n");
}

int main() {
    test_validate_extension();
    test_parse_color();
    test_validate_map_chars();
    return 0;
}

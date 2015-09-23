#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "common.h"
#include "highway.h"
#include "option.h"
#include "log.h"
#include "help.h"

void init_option(int argc, char **argv, hw_option *op)
{
    bool help = false;
    static int flag;

    static struct option longopts[] = {
        { "help",              no_argument,       NULL,  'h' },
        { "file-with-matches", no_argument,       NULL,  'l' },
        { "debug",             no_argument,       &flag, 1   },
        { "worker",            required_argument, &flag, 2   },
        { 0, 0, 0, 0 }
    };

    op->worker            = DEFAULT_WORKER;
    op->root_paths[0]     = ".";
    op->paths_count       = 1;
    op->file_with_matches = false;

    int ch;
    while ((ch = getopt_long(argc, argv, "hl", longopts, NULL)) != -1) {
        switch (ch) {
            case 0:
                switch (flag) {
                    case 1: /* --debug */
                        set_log_level(LOG_LEVEL_DEBUG);
                        break;
                    case 2: /* --worker */
                        op->worker = atoi(optarg);
                        break;
                }
                break;

            case 'h':
                usage();
                exit(0);
                break;

            case 'l':
                op->file_with_matches = true;
                break;

            case '?':
            default:
                usage();
                exit(1);
        }
    }

    if (argc == optind) {
        usage();
        exit(1);
    }

    op->pattern = argv[optind++];
    op->pattern_len = strlen(op->pattern);
    int paths_count = argc - optind;
    if (paths_count > 0) {
        for (int i = 0; i < paths_count && i < MAX_PATHS_COUNT; i++) {
            char *path = argv[optind + i];
            int len = strlen(path);
            if (path[len - 1] == '/') {
                path[len - 1] = '\0';
            }
            op->root_paths[i] = path;
        }
        op->paths_count = paths_count;
    }
}

#define NOB_IMPLEMENTATION

#include "nob.h"
#define BUILD_DIR "build/"
#define SRC_DIR "src/"

int main(int argc, char **argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra");
  nob_cmd_append(&cmd, "-o", BUILD_DIR"gol");
  nob_cmd_append(&cmd, SRC_DIR"main.c");
  nob_cmd_append(&cmd, SRC_DIR"draw.c");
  nob_cmd_append(&cmd, SRC_DIR"event.c");
  nob_cmd_append(&cmd, SRC_DIR"cells.c");
  nob_cmd_append(&cmd, "-lSDL3");
  if (!nob_cmd_run(&cmd)) return 1;
  return 0;
}

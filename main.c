#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define init_size 512



int main(){

	int allocated = init_size;

	char cmd[256], key[256], value[256];

	char **keys = malloc(allocated);
	if (!keys){
		perror("Failed to allocate memory!");
		return -1;
	}

	char **values = malloc(allocated);
	if (!values){
		perror("Failed to allocate memory!");	
		return -1;
  }

  int stored = 0;

  while (1) {

    printf("> ");
    fflush(stdout);

    scanf("%s %s %s", &cmd, &key, &value);
    if (cmd == "SET") {

      for (int i = 0; i < stored; i++) {
        if (key == keys[i]) {
          printf("Key already exists!\n");
          printf("Change another key\n");
          continue;
        }
      }

      if (stored == (sizeof(keys) / sizeof(keys[0]))) {
        allocated += init_size;
        char **tmp_mem = realloc(keys, allocated);
        if (!tmp_mem) {
          perror("Failed to allocate memory");
          return -1;
        }
        keys = tmp_mem;

        tmp_mem = realloc(values, allocated);
        if (!tmp_mem) {
          perror("Failed to allocate memory");
          return -1;
        }
        values = tmp_mem;
      }

      keys[stored] = malloc(strlen(key));
      strcpy(keys[stored], key);
      values[stored] = malloc(strlen(value));
      strcpy(values[stored], value);
    }
  }

  for (int j = 0; j < stored; j++) {
    free(keys[j]);
  }
  free(keys);
  return 0;
}

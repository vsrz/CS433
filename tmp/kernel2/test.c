#include <stdio.h>
#include <string.h>

int main() {
  char *url = "http://www.iota-six.co.uk";

  printf("%s\n", strstr(url, "iota-six"));
  printf("%s\n", strstr(url, "iota-6"));

  if(strstr(url, "iota-seven")==NULL) {
    printf("iota-seven not found in %s\n", url);
  }

  printf("Length of %s is %d\n", url, strlen(url));

  return 0;
}


#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#endif

#include <stdlib.h>

#ifdef _WIN32
#include <crtdbg.h>
#endif

#include <string.h>
#include <stdio.h>
#include <acb.h>

static void callback(uint32_t completed, uint32_t total, const char* name, bool result) {
  printf("%d / %d: %s, %s\n", completed, total, result ? "true" : "false", name);
}

int main() {
  acb* acbp = acb_open("./solo.acb");
  int res = acb_extract(acbp, "sub/solo", callback);
  acb_close(acbp);

  acbp = acb_open("./100071.acb");
  res = acb_extract(acbp, "sub/100071", callback);
  acb_close(acbp);
#ifdef _WIN32
  _CrtDumpMemoryLeaks();
#endif
  return res;
}

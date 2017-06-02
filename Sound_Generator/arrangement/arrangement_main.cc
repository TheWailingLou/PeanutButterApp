#include "arrangement_main.h"

namespace arrangement_main
{
  int num_of_unique_sections(int* arrangement, int total_sections)
  {
    int unique_sections = 0;
    for (int section=0; section<total_sections; section++)
    {
      if (arrangement[section] > unique_sections) {
        unique_sections = arrangement[section];
      }
    }
    return unique_sections;
  }
}

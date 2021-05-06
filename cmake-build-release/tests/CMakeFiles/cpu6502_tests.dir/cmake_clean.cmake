file(REMOVE_RECURSE
  "libcpu6502_tests.a"
  "libcpu6502_tests.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/cpu6502_tests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

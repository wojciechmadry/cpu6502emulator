file(REMOVE_RECURSE
  "libcpu6502.a"
  "libcpu6502.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/cpu6502.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

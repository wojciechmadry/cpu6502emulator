file(REMOVE_RECURSE
  "libcpu6502_registers.a"
  "libcpu6502_registers.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/cpu6502_registers.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

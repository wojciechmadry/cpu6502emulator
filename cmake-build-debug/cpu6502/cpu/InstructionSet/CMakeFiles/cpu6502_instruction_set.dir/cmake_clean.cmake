file(REMOVE_RECURSE
  "libcpu6502_instruction_set.a"
  "libcpu6502_instruction_set.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/cpu6502_instruction_set.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

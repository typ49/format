if(EXISTS "/home/juliengauthier410/l3/s6/programmation_Multi-Paradigme/projet_3/format/build/testFormatPrint[1]_tests.cmake")
  include("/home/juliengauthier410/l3/s6/programmation_Multi-Paradigme/projet_3/format/build/testFormatPrint[1]_tests.cmake")
else()
  add_test(testFormatPrint_NOT_BUILT testFormatPrint_NOT_BUILT)
endif()

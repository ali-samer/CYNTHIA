# the stb library had linking issues. This design ensures the library is statically linked once in cynthia executable
add_compile_definitions(STB_IMAGE_IMPLEMENTATION)
add_library(stb_image STATIC load.cpp)
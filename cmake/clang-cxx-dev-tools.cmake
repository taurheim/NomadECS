# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     *.cpp)
file(GLOB_RECURSE
	 ALL_CXX_HEADERS
	 *.h)

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT_EXE "clang-format")
if(CLANG_FORMAT_EXE)
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXE}
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
	${ALL_CXX_HEADERS}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY_EXE "clang-tidy")
if(CLANG_TIDY_EXE)
  add_custom_target(
    clang-tidy
    COMMAND ${CLANG_TIDY_EXE}
	-checks "*,-llvm-header-guard,-google-build-using-namespace,-clang-analyzer-alpha.clone.CloneChecker,-google-runtime-int,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-clang-analyzer-alpha.deadcode.UnreachableCode,-misc-use-after-move,-cppcoreguidelines-pro-type-vararg,-modernize-use-emplace,-cert-err60-cpp"
	-p "."
	-header-filter=.*
    ${ALL_CXX_SOURCE_FILES}
    )
endif()

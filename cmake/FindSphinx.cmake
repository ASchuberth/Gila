
if(WIN32)
set(PYTHON_ENVIRONMENT ${CMAKE_SOURCE_DIR}/.venv/Scripts/)
message("Python Environment: ${PYTHON_ENVIRONMENT}")
endif()

if(UNIX)
set(PYTHON_ENVIRONMENT ${CMAKE_SOURCE_DIR}/.venv/bin/)
message("Python Environment: ${PYTHON_ENVIRONMENT}")
endif()

#Look for an executable called sphinx-build
find_program(SPHINX_EXECUTABLE
             NAMES sphinx-build
             HINTS ${PYTHON_ENVIRONMENT}
             DOC "Path to sphinx-build executable")

include(FindPackageHandleStandardArgs)

#Handle standard arguments to find_package like REQUIRED and QUIET
find_package_handle_standard_args(Sphinx
                                  "Failed to find sphinx-build executable"
                                  SPHINX_EXECUTABLE)
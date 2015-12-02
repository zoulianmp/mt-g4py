# - Add Files
project(wp_module)

file(GLOB _TARGETSrc  "${PROJECT_SOURCE_DIR}/module/*.cc")
file(GLOB _PYFiles "*.py")

message("the source files: ${_TARGETSrc}")
message("the python files: ${_PYFiles}")


# library
set(_TARGET demo_wp)
add_library(
  ${_TARGET} SHARED
  
  ${_TARGETSrc}
)




set_target_properties(${_TARGET} PROPERTIES PREFIX "")
set_target_properties(${_TARGET} PROPERTIES OUTPUT_NAME ${_TARGET})
set_target_properties(${_TARGET} PROPERTIES SUFFIX ".so")

target_link_libraries (${_TARGET}
                       ${GEANT4_LIBRARIES_WITH_VIS} boost_python
                       ${PYTHON_LIBRARIES})

# install
install(TARGETS ${_TARGET} LIBRARY DESTINATION ${MODULES_INSTALL_DIR})

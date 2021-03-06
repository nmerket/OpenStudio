# generate the IddFactory files

add_custom_command(
  OUTPUT
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactoryFileIndex.hxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddEnums.hxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFieldEnums.hxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory.hxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory.cxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory_EnergyPlus.cxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory_OpenStudio.cxx"
  "${CMAKE_CURRENT_BINARY_DIR}/idd/IddFieldEnums.ixx"
  COMMAND GenerateIddFactory "--outdir=${CMAKE_CURRENT_BINARY_DIR}/idd" "EnergyPlus,${CMAKE_SOURCE_DIR}/resources/energyplus/ProposedEnergy+.idd" "${CMAKE_SOURCE_DIR}/resources/model/OpenStudio.idd"
  DEPENDS
  GenerateIddFactory
  "${CMAKE_SOURCE_DIR}/resources/energyplus/ProposedEnergy+.idd"
  "${CMAKE_SOURCE_DIR}/resources/model/OpenStudio.idd"
)


# include the generated files
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/idd/)

set(idd_src
  idd/mainpage.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactoryFileIndex.hxx
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddEnums.hxx
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFieldEnums.hxx
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory.hxx
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory.cxx
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory_EnergyPlus.cxx
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFactory_OpenStudio.cxx
  idd/IddField.hpp
  idd/IddField.cpp
  idd/IddField_Impl.hpp
  idd/IddFieldProperties.hpp
  idd/IddFieldProperties.cpp
  idd/IddFile.cpp
  idd/IddFile.hpp
  idd/IddFile_Impl.hpp
  idd/IddKey.cpp
  idd/IddKey.hpp
  idd/IddKeyProperties.hpp
  idd/IddKeyProperties.cpp
  idd/IddKey_Impl.hpp
  idd/IddObject.cpp
  idd/IddObject.hpp
  idd/IddObjectProperties.hpp
  idd/IddObjectProperties.cpp
  idd/IddObject_Impl.hpp
  idd/ExtensibleIndex.hpp
  idd/ExtensibleIndex.cpp
  idd/IddRegex.hpp
  idd/IddRegex.cpp
  idd/IddFileAndFactoryWrapper.hpp
  idd/IddFileAndFactoryWrapper.cpp
  idd/CommentRegex.hpp
  idd/CommentRegex.cpp
  idd/Comments.hpp
  idd/Comments.cpp
)

set(idd_test_src
  idd/Test/IddFixture.hpp
  idd/Test/IddFixture.cpp
  idd/Test/IddFile_GTest.cpp
  idd/Test/IddObject_GTest.cpp
  idd/Test/IddField_GTest.cpp
  idd/Test/IddKey_GTest.cpp
  idd/Test/IddRegex_GTest.cpp
  idd/Test/CommentRegex_GTest.cpp
  idd/Test/IddFactory_GTest.cpp
  idd/Test/IddFileAndFactoryWrapper_GTest.cpp
  idd/Test/IddEnums_GTest.cpp
)

set(idd_swig_src
  ${CMAKE_CURRENT_BINARY_DIR}/idd/IddFieldEnums.ixx
  idd/Idd.i
)

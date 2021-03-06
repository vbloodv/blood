cmake_minimum_required(VERSION 3.0)
#------------------------------------------------------------------------------
# PLATFORM LIST:
# |- WIN32
# |-- SYGWIN
# |-- MINGW
# |-- MSVC
# |--- STORE
# | UNIX
#------------------------------------------------------------------------------
include(assemble/cmake/parse.cmake)
include(assemble/cmake/submodule.cmake)
include(assemble/cmake/configuration.cmake)

set(project_name quaternion)
project(${project_name})
# _________________________________________ Options

option(ADDRESS_MODEL_64 "Build x64 platform"                              OFF)
option(STORE            "Create Windows 8.1 or more; Store application"   OFF)
option(BUILD_LIBRARY    "Switcher between library and executable"         OFF)

# _________________________________________ Use technology

option(USE_BOOST   "" OFF)
option(USE_CURL    "" OFF)
option(USE_OPENCV  "" OFF)
option(USE_OPENSSL "" OFF)
option(USE_DIRECTX "" OFF)
option(USE_OCULUS  "" OFF)

if(USE_BOOST)
	option(Boost_USE_STATIC_LIBS    "Set to ON to force the use of the static libraries."                                                  ON)
	option(Boost_USE_MULTITHREADED  "Set to OFF to use the non-multithreaded libraries                                         ('mt' tag)" ON)  
	option(Boost_USE_STATIC_RUNTIME "Set to ON or OFF to specify whether to use libraries linked statically to the C++ runtime ('s' tag) " ON)
	option(Boost_USE_DEBUG_RUNTIME  "Set to ON or OFF to specify whether to use libraries linked to the MS debug C++ runtime   ('g' tag) " OFF)

	set(Boost_components
		program_options
		filesystem
		date_time
		regex
		#lockfree # only boost 1.59
		#fusion
		#spirit
		system
		#thread
		chrono
	)
endif()

if(USE_DIRECTX)
	option(DirectX_9  "" OFF)
	option(DirectX_10 "" OFF)
	option(DirectX_11 "" ON)
endif()

# _________________________________________ Processing

submodule_fill_technology_list()
configuration_initialize_engine_paths()

configuration_project()
configuration_linking_flags()
configuration_project_types()

submodule_connect_external_projects()
submodule_set_include_directory()

parse_add_source_groups()

# _________________________________________ Processing

include_directories(${BLOOD_INCLUDE_DIR} ${BLOOD_ROOT}/include/ ${BLOOD_INCLUDES})
link_directories(${BLOOD_LIBRARIES})

add_library(blood STATIC ${BLOOD_SOURCES_FILES})
# _________________________________________ Create template project ${project_name}

file(GLOB PROJECT_CODE "${BLOOD_ROOT}/source/code/*.*")
source_group("" FILES ${PROJECT_CODE})
add_executable(${project_name} ${PROJECT_CODE})
submodule_link_dependence()

# _________________________________________ Set targets
set_target_properties(blood           PROPERTIES LINKER_LANGUAGE C++)
set_target_properties(${project_name} PROPERTIES LINKER_LANGUAGE C++)
target_link_libraries(${project_name} blood)

set(SOURCE2SDK_DIR ${EXTERN_DIR}/hl2sdk-cs2)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wno-error")

	add_compile_definitions(
		POSIX
		COMPILER_GCC
		PLATFORM_64BITS
	)

	set(SOURCE2SDK_LIB_DIRS
		${SOURCE2SDK_DIR}/lib/linux64
	)

	set(SOURCE2SDK_LIBS
		-l:interfaces.a
		-l:tier1.a
	)
elseif (WIN32)
	add_compile_definitions(
		COMPILER_MSVC64
		COMPILER_MSVC
		PLATFORM_64BITS
	)

	set(SOURCE2SDK_LIB_DIRS
		${SOURCE2SDK_DIR}/lib/public/win64
	)

	set(SOURCE2SDK_LIBS
		tier0
		tier1
		interfaces
	)
endif()

set(SOURCE2SDK_INCLUDE_DIRS
	${SOURCE2SDK_DIR}
	${SOURCE2SDK_DIR}/common
	${SOURCE2SDK_DIR}/public
	${SOURCE2SDK_DIR}/public/engine
	${SOURCE2SDK_DIR}/public/mathlib
	${SOURCE2SDK_DIR}/public/vstdlib
	${SOURCE2SDK_DIR}/public/tier0
	${SOURCE2SDK_DIR}/public/tier1
	${SOURCE2SDK_DIR}/public/game/server
	${SOURCE2SDK_DIR}/game/shared
)

add_library(Source2SDK INTERFACE)
target_link_directories(Source2SDK INTERFACE
	${SOURCE2SDK_LIB_DIRS}
)
target_link_libraries(Source2SDK INTERFACE
	${SOURCE2SDK_LIBS}
)
target_include_directories(Source2SDK INTERFACE
	${SOURCE2SDK_INCLUDE_DIRS}
)
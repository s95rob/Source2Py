set(METAMOD_DIR ${EXTERN_DIR}/metamod-source)

add_compile_definitions(META_IS_SOURCE2)

set(METAMOD_INCLUDE_DIRS
	${METAMOD_DIR}
	${METAMOD_DIR}/core
	${METAMOD_DIR}/core/provider
	${METAMOD_DIR}/core/provider/source
	${METAMOD_DIR}/core/provider/source2
	${METAMOD_DIR}/core/sourcehook
	${METAMOD_DIR}/loader
	${METAMOD_DIR}/public
	${METAMOD_DIR}/versionlib
	${METAMOD_DIR}/third_party/amtl
)

add_library(Metamod INTERFACE)
target_include_directories(Metamod INTERFACE
	${METAMOD_INCLUDE_DIRS}
)
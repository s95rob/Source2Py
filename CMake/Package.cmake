set(SOURCE2PY_PACKAGE_DIR ${BUILD_DIR}/Package/Source2Py)
set(SOURCE2PY_PACKAGE_RES_DIR ${SCRIPTS_DIR}/Resources)

add_custom_command(TARGET Source2Py POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "${SOURCE2PY_PACKAGE_DIR}"
	COMMAND ${CMAKE_COMMAND} -E make_directory "${SOURCE2PY_PACKAGE_DIR}/bin"
	COMMAND ${CMAKE_COMMAND} -E make_directory "${SOURCE2PY_PACKAGE_DIR}/plugins"
	
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Source2Py> "${SOURCE2PY_PACKAGE_DIR}/bin"
	COMMAND ${CMAKE_COMMAND} -E copy "${SOURCE2PY_PACKAGE_RES_DIR}/pyplugins.ini" "${SOURCE2PY_PACKAGE_DIR}"

	# Copy sample plugins to package directory
	COMMAND ${CMAKE_COMMAND} -E copy "${SAMPLE_PLUGINS_DIR}/SamplePlugin.py" "${SOURCE2PY_PACKAGE_DIR}/plugins"
)
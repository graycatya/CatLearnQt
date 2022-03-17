#--
# cmake 国际化处理
#--
function(build_linguisttools)
if(ARGN)
	#需要加载翻译工具
	find_package(Qt5LinguistTools REQUIRED)

	#set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})

	#get_source_file_property(output_location ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_LOCATION)
	#if(output_location)
	#    file(MAKE_DIRECTORY "${output_location}")
	#    set(qm "${output_location}/${qm}.qm")
	#else()
	#    set(qm "${CMAKE_CURRENT_BINARY_DIR}/${qm}.qm")
	#endif()

	find_program(LUPDATE_EXECUTABLE lupdate)
	find_program(LRELEASE_EXECUTABLE lrelease)

	foreach(_ts_file IN LISTS ARGN)

		execute_process(
			COMMAND ${LUPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${_ts_file})
		execute_process(
			COMMAND ${LRELEASE_EXECUTABLE} ${_ts_file})

	endforeach()
endif(ARGN)
endfunction(build_linguisttools)


#--
# 字符串处理方法
#--

# 声明Func，并采用作用域提升
# 功能: variable 变量数据后面拼接_static
function(load_name_static variable)
    set(LOAD_NAME ${PROJECT_NAME}_static)
	# 变量提升
	# ${variable} 被展开成 MESSAGE_THREE
	# ${${variable}} 被展开成 message_three 即 MESSAGE_THREE 的值
	# PARENT_SCOPE 指父作用域，是set方法的参数
    set(${variable} ${LOAD_NAME} PARENT_SCOPE)
endfunction(load_name_static)

#--
# 项目处理方法
#--

# 加载当前模块下的源文件，防止项目文件冲突
function(add_src_lib)
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CURPATH_DIR_LIB_SRCS)
	if(ARGN) 
		set(PROJECT_SOURCE)
		foreach(arg IN LISTS ARGN)
			set(PROJECT_SOURCE ${PROJECT_SOURCE}${arg})
	  	endforeach()
		add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS} ${PROJECT_SOURCE})
		add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS} ${PROJECT_SOURCE})
	else()
		add_library(${PROJECT_NAME} SHARED ${CURPATH_DIR_LIB_SRCS})
		add_library(${STATIC_NAME} STATIC ${CURPATH_DIR_LIB_SRCS})
	endif(ARGN)
endfunction()

# 获取当前目录下的源文件，并过滤指定的文件
# 用法: filtration_aux_source_directory(CURPATH_DIR_LIB_SRCS 
#										<filtration_file>
#										<filtration_file>
#										...)
function(filtration_aux_source_directory)
	if(ARGN)
		aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} TEMP_CURPATH_DIR_LIB_SRCS)
		if(ARGV1)
			set(LIST_FILE ${ARGN})
			list(REMOVE_ITEM LIST_FILE ${ARGV0})
			message(${LIST_FILE})
			foreach(arg IN LISTS LIST_FILE)
				list(REMOVE_ITEM TEMP_CURPATH_DIR_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
			endforeach()
		endif(ARGV1)
		set(${ARGV0} ${TEMP_CURPATH_DIR_LIB_SRCS} PARENT_SCOPE)
	endif(ARGN)
endfunction(filtration_aux_source_directory)


#--
# 链接库处理方法
#--

# 添加Windows链接库
function(link_win32_lib)
	if(WIN32 AND ARGN)
		foreach(arg IN LISTS ARGN)
			link_libraries(${arg})
		endforeach()
	endif(WIN32 AND ARGN)
endfunction(link_win32_lib)

# 添加apple链接库
function(link_apple_lib)
	if(APPLE AND ARGN)
		foreach(arg IN LISTS ARGN)
			link_libraries(${arg})
		endforeach()
	endif(APPLE AND ARGN)
endfunction(link_apple_lib)

# 添加unix链接库
function(link_unix_lib)
	if(UNIX AND ARGN AND (NOT ANDROID) AND (NOT APPLE))
		foreach(arg IN LISTS ARGN)
			link_libraries(${arg})
		endforeach()
	endif(UNIX AND ARGN AND (NOT ANDROID) AND (NOT APPLE))
endfunction(link_unix_lib)

function(find_unix_package)
	if(UNIX AND (NOT ANDROID) AND (NOT APPLE))
		if(ARGN)
			foreach(arg IN LISTS ARGN)
				find_package(Qt5 COMPONENTS ${arg} REQUIRED)
			endforeach()
		endif(ARGN)
	endif(UNIX AND (NOT ANDROID) AND (NOT APPLE))
endfunction(find_unix_package)

function(target_link_unix_libraries)
	if(UNIX)
		if(ARGN)
			foreach(arg IN LISTS ARGN)
				target_link_libraries(${PROJECTNAME} PRIVATE ${arg})
			endforeach()
		endif(ARGN)
	endif(UNIX)
endfunction(target_link_unix_libraries)

# 添加android链接库
function(link_android_lib)
	if(ANDROID AND ARGN)
		foreach(arg IN LISTS ARGN)
			link_libraries(${arg})
		endforeach()
	endif(ANDROID AND ARGN)
endfunction(link_android_lib)

#-------------------------------------
# android cmake error: No platform plugin, neither libqtforandroid.so 
# or libqtforandroidGL.so, included in package. Please include one.
# Qt 5.15 cmake 编译android库需要添加gui
function(find_android_gui)
	if(ANDROID)
		find_package(Qt5 COMPONENTS Gui REQUIRED)
	endif(ANDROID)
endfunction(find_android_gui)

function(target_link_android_gui PROJECTNAME)
	if(ANDROID)
		target_link_libraries(${PROJECTNAME} PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
	endif(ANDROID)
endfunction(target_link_android_gui)
#-------------------------------------

#--
# 头文件查找
#--

function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()


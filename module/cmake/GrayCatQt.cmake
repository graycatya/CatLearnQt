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
	if(UNIX AND ARGN AND (NOT ANDROID))
		foreach(arg IN LISTS ARGN)
			link_libraries(${arg})
		endforeach()
	endif(UNIX AND ARGN AND (NOT ANDROID))
endfunction(link_unix_lib)

function(find_unix_package)
	if(UNIX AND (NOT ANDROID) AND (NOT MACROS))
		if(ARGN)
			foreach(arg IN LISTS ARGN)
				find_package(Qt5 COMPONENTS ${arg} REQUIRED)
			endforeach()
		endif(ARGN)
	endif(UNIX AND (NOT ANDROID) AND (NOT MACROS))
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
		target_link_libraries(${PROJECTNAME} PRIVATE Qt5::Gui)
	endif(ANDROID)
endfunction(target_link_android_gui)
#-------------------------------------

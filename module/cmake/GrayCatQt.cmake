# 声明Func，并采用作用域提升
function(load_name_static variable)
    set(LOAD_NAME ${PROJECT_NAME}_static)
	# 变量提升
	# ${variable} 被展开成 MESSAGE_THREE
	# ${${variable}} 被展开成 message_three 即 MESSAGE_THREE 的值
	# PARENT_SCOPE 指父作用域，是set方法的参数
    set(${variable} ${LOAD_NAME} PARENT_SCOPE)
endfunction(load_name_static)

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


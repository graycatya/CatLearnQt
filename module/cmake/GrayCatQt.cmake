# 声明Func，并采用作用域提升
function(load_name_static variable)
    set(LOAD_NAME ${PROJECT_NAME}_static)
	# 变量提升
	# ${variable} 被展开成 MESSAGE_THREE
	# ${${variable}} 被展开成 message_three 即 MESSAGE_THREE 的值
	# PARENT_SCOPE 指父作用域，是set方法的参数
    set(${variable} ${LOAD_NAME} PARENT_SCOPE)
endfunction()



# 定义函数, 用于启用 sanitize
function(enable_sanitize target)
    message(STATUS "Enable sanitize for ${target}")

    set(_sanitize_compile_opt address)
    set(_sanitize_link_opt address)
    add_compile_definitions(_SANITIZE_ADDRESS)

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
            set(_sanitize_compile_opt leak)
            set(_sanitize_link_opt leak)

            add_compile_definitions(_SANITIZE_LEAK)
        endif()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
            unset(_sanitize_compile_opt)
            unset(_sanitize_link_opt)
        endif()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    endif()

    if (DEFINED _sanitize_compile_opt)
        target_compile_options(${target}
            PRIVATE -fsanitize=${_sanitize_compile_opt} -fsanitize-recover=${_sanitize_compile_opt}
        )
    endif()

    if (DEFINED _sanitize_link_opt)
        target_link_libraries(${target}
            PRIVATE -fsanitize=${_sanitize_link_opt}
        )
    endif()
endfunction(enable_sanitize target)
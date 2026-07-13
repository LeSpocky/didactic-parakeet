# SPDX-FileCopyrightText: 2026 Alexander Dahl <post@lespocky.de>
# SPDX-License-Identifier: BSD-2-Clause
cmake_minimum_required(VERSION 3.18)
project(didactic-parakeet)

include(CheckCCompilerFlag)

option(DP_ASAN "build with Asan" OFF)

message(STATUS "Target system: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Target processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "C compiler target: ${CMAKE_C_COMPILER_TARGET}")
message(STATUS "C compiler arch id: ${CMAKE_C_COMPILER_ARCHITECTURE_ID}")

set(DP_ASAN_FLAG "-fsanitize=address")
set(CMAKE_REQUIRED_FLAGS "${DP_ASAN_FLAG}")
check_c_compiler_flag("${DP_ASAN_FLAG}" DP_ASAN_DETECTED)
message("DP_ASAN_DETECTED: '${DP_ASAN_DETECTED}'")

set(DP_OMITFP_FLAG "-fno-omit-frame-pointer")
set(CMAKE_REQUIRED_FLAGS "${DP_OMITFP_FLAG}")
check_c_compiler_flag("${DP_OMITFP_FLAG}" DP_OMITFP_DETECTED)
message("DP_OMITFP_DETECTED: '${DP_OMITFP_DETECTED}'")


add_executable(didactic-parakeet
	main.c
)

if(DP_ASAN)
	if(NOT DP_ASAN_DETECTED OR NOT DP_OMITFP_DETECTED)
		message(SEND_ERROR "Asan requested but not supported!")
	endif()

	target_compile_options(didactic-parakeet
		PRIVATE
			"${DP_ASAN_FLAG}"
			"${DP_OMITFP_FLAG}"
	)
	target_link_libraries(didactic-parakeet
		PRIVATE
			"${DP_ASAN_FLAG}"
			"${DP_OMITFP_FLAG}"
	)
endif()

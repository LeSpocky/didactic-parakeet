# SPDX-FileCopyrightText: 2026 Alexander Dahl <post@lespocky.de>
# SPDX-License-Identifier: BSD-2-Clause
cmake_minimum_required(VERSION 3.18)
project(didactic-parakeet)

include(CheckCCompilerFlag)

option(DP_WITH_ASAN "build with Asan" OFF)
option(DP_WITH_ATOMIC "link against libatomic" OFF)

message(STATUS "Target system: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Target processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "C compiler target: ${CMAKE_C_COMPILER_TARGET}")
message(STATUS "C compiler arch id: ${CMAKE_C_COMPILER_ARCHITECTURE_ID}")

if(DP_WITH_ATOMIC)
	set(DP_LINK_OPTION "-latomic")
endif()

set(DP_ASAN_FLAG "-fsanitize=address")
set(CMAKE_REQUIRED_FLAGS "${DP_ASAN_FLAG}")
set(CMAKE_REQUIRED_LINK_OPTIONS "${DP_LINK_OPTION}")
check_c_compiler_flag("${DP_ASAN_FLAG}" DP_ASAN_DETECTED)
message("DP_ASAN_DETECTED: '${DP_ASAN_DETECTED}'")

set(DP_OMITFP_FLAG "-fno-omit-frame-pointer")
set(CMAKE_REQUIRED_FLAGS "${DP_OMITFP_FLAG}")
check_c_compiler_flag("${DP_OMITFP_FLAG}" DP_OMITFP_DETECTED)
message("DP_OMITFP_DETECTED: '${DP_OMITFP_DETECTED}'")

if(DP_WITH_ASAN AND (NOT DP_ASAN_DETECTED OR NOT DP_OMITFP_DETECTED))
	message(SEND_ERROR "Asan requested but not supported!")
endif()

add_executable(didactic-parakeet
	main.c
)

target_compile_options(didactic-parakeet
	PRIVATE
		$<$<BOOL:${DP_WITH_ASAN}>:${DP_ASAN_FLAG}>
		$<$<BOOL:${DP_WITH_ASAN}>:${DP_OMITFP_FLAG}>
)
target_link_libraries(didactic-parakeet
	PRIVATE
		$<$<BOOL:${DP_WITH_ASAN}>:${DP_ASAN_FLAG}>
		$<$<BOOL:${DP_WITH_ASAN}>:${DP_OMITFP_FLAG}>
		$<$<BOOL:${DP_ASAN_WITH_ATOMIC}>:${DP_LINK_OPTION}>
)

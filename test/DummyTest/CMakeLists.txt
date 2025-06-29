set(targetName DummyTest)
add_executable(${targetName})

set(tested_source
)
list(TRANSFORM tested_source PREPEND ${tested_src_dir}/)

target_sources(${targetName} PRIVATE
	./main.cpp
	./dummy.cpp

	${tested_source}
)

target_include_directories(${targetName} PUBLIC
	.
	${tested_include_dir}
)

target_link_libraries(${targetName}
	gtest
)

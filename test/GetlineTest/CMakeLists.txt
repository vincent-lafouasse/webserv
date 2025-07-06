set(targetName GetlineTest)
add_executable(${targetName})

set(tested_source
	IO/getline.cpp
	Option/Option.cpp
)
list(TRANSFORM tested_source PREPEND ${tested_src_dir}/)

target_sources(${targetName} PRIVATE
	./main.cpp
	./GetlineTest.cpp

	${tested_source}
)

target_include_directories(${targetName} PUBLIC
	.
	${tested_include_dir}
)

target_link_libraries(${targetName}
	gtest
)

-- cpp standard
set_languages("c++17")

-- Build Mode
add_rules("mode.debug", "mode.release")

-- toolchains requirements
add_requires("llvm")

-- requirements
add_requires("glfw3")
add_requires("glm")
add_requires("glad")
add_requires("assimp")
add_requires("tinygltf")

-- target(.exe)
target("BickRenderer")
    set_kind("binary")
    set_toolchains("llvm")
    add_includedirs("Source/Include")
    add_files("Source/Src/**.cpp")
    add_packages("glfw3", "glm","glad","assimp", "tinygltf")

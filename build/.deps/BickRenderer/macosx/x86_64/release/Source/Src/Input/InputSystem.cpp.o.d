{
    depfiles_gcc = "build/.objs/BickRenderer/macosx/x86_64/release/Source/Src/Input/__cpp_InputSystem.cpp.cpp:   Source/Src/Input/InputSystem.cpp Source/Include/Input/InputSystem.hpp   Source/Include/Common/Singleton.hpp Source/Include/Camera/Camera.hpp\
",
    values = {
        "/usr/local/Cellar/llvm/19.1.6/bin/clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-isysroot",
            "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.2.sdk",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++17",
            "-ISource/Include",
            "-isystem",
            "/usr/local/Cellar/glfw/3.4/include",
            "-isystem",
            "/usr/local/Cellar/glm/1.0.1/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/g/glad/v0.1.36/e6361778169149179bb154a87a3e8645/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/a/assimp/v5.4.3/70c2032c2cae4584891588798ee17240/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/m/minizip/v1.2.13/d1916a67b92342b78e85cd63eb5d6d72/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/m/minizip/v1.2.13/d1916a67b92342b78e85cd63eb5d6d72/include/minizip",
            "-isystem",
            "/Users/vanish/.xmake/packages/t/tinygltf/v2.9.3/c0a5094c611b4ceab086c57a7a5d6fba/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/n/nlohmann_json/v3.11.3/07dbd8c7f12347f583937915168be7dc/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/s/stb/2024.06.01/c5dad42a0d624f5a9cc4dce48178a35e/include",
            "-isystem",
            "/Users/vanish/.xmake/packages/s/stb/2024.06.01/c5dad42a0d624f5a9cc4dce48178a35e/include/stb",
            "-DNDEBUG"
        }
    },
    files = {
        "Source/Src/Input/InputSystem.cpp"
    }
}
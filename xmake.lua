-- cpp standard
set_languages("c++17")

-- Build Mode
add_rules("mode.debug", "mode.release")

-- toolchains requirements
add_requires("llvm")

-- requirements
add_requires("glfw")
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
    add_packages("glfw", "glm","glad","assimp", "tinygltf")
    
    -- 构建后复制资源文件
    after_build(function (target)
        import("core.project.config")
        
        -- 获取目标输出目录
        local targetdir = target:targetdir()
        
        -- 复制Assets文件夹
        local assets_src = path.join(os.projectdir(), "Assets")
        local assets_dst = path.join(targetdir, "Assets")
        if os.exists(assets_src) then
            os.rm(assets_dst)  -- 先删除旧的
            os.cp(assets_src, assets_dst)
            print("[xmake] 已复制Assets文件夹到: " .. assets_dst)
        else
            print("[xmake] 警告: 找不到Assets文件夹: " .. assets_src)
        end
        
        -- 复制着色器文件
        local shaders_src = path.join(os.projectdir(), "Source", "GLSL_Shaders")
        local shaders_dst = path.join(targetdir, "Shaders")
        if os.exists(shaders_src) then
            os.rm(shaders_dst)  -- 先删除旧的
            os.cp(shaders_src, shaders_dst)
            print("[xmake] 已复制Shaders文件夹到: " .. shaders_dst)
        else
            print("[xmake] 警告: 找不到GLSL_Shaders文件夹: " .. shaders_src)
        end
    end)
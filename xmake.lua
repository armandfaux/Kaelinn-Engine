add_rules("mode.debug", "mode.release")

add_requires("conan::sfml/2.6.1", {alias = "sfml"})
add_requires("conan::asio/1.28.2", {alias = "asio"})
add_requires("conan::boost/1.83.0", {alias = "boost"})
add_requires("conan::catch2/3.5.0", {alias = "catch2"})

local common_configuration = function()
    if is_plat("windows") then
        add_cxflags("-D_WIN32_WINNT=0x0A00")
    end
    set_languages("cxx17")
    set_warnings("all")
    set_targetdir("$(projectdir)")
end

-- R-Type engine
target("game-engine-test")
    common_configuration()
    set_kind("binary")
    add_files("src/engine/**/*.cpp", "src/games/rtype/*.cpp")
    add_headerfiles("src/engine/**/*.hpp")
    add_packages("sfml", "asio", "boost")

-- R-Type client
target("r-type_client")
    common_configuration()
    set_kind("binary")
    add_files("src/client/*.cpp", "src/engine/**/*.cpp")
    add_headerfiles("src/client/*.hpp", "src/engine/**/*.hpp")
    add_packages("sfml", "asio", "boost")

-- R-Type server
target("r-type_server")
    common_configuration()
    set_kind("binary")
    add_files("src/server/*.cpp", "src/engine/**/*.cpp")
    add_headerfiles("src/engine/**/*.hpp")
    add_packages("sfml", "asio", "boost")

-- Test Catch2
target("test-main")
    common_configuration()
    set_kind("binary")
    add_files("src/tests/main.cpp", "src/tests/catch-test.cpp")
    add_packages("catch2")
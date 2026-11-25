set_project("slk_defs1")
set_version("1.0.0")

-- Enforce C++23 standard
set_languages("cxx23")

-- Build modes (debug / release)
add_rules("mode.debug", "mode.release")

target("slk_defs1")
    -- Target kind: "static" (.a archive) or "shared" (.so library)
    set_kind("static")

    -- Library source files
    add_files("src/*.cpp")

    -- Public headers exposed so consumers can use #include "slk_defs1/..."
    add_headerfiles("include/(slk_defs1/*.hpp)")
    add_includedirs("include", {public = true})

-- Unit test executable (excluded from default build; run via `xmake test`)
target("slk_defs1_tests")
    set_kind("binary")
    set_default(false)
    add_deps("slk_defs1")
    add_files("tests/*.cpp")
    add_tests("unit")


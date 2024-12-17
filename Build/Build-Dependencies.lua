--- OUTPUT DIRS
OutputDirs = { }

OutputDirs[ "Solution" ] = "%{wks.location}/Solution/"
OutputDirs[ "Bin" ] = "%{wks.location}/bin/"
OutputDirs[ "BinInt" ] = "%{wks.location}/bin-int/"

--- THIRDPARTY LIBRARIES
IncludeDirs = { }

IncludeDirs[ "Glm" ] = "%{wks.location}/Thirdparty/glm/"
IncludeDirs[ "Libclang" ] = "%{wks.location}/Thirdparty/libclang/"
IncludeDirs[ "Spdlog" ] = "%{wks.location}/Thirdparty/spdlog/"
IncludeDirs[ "Yaml" ] = "%{wks.location}/Thirdparty/yaml-cpp/"
IncludeDirs[ "MicroTest" ] = "%{wks.location}/MicroTest/"
IncludeDirs[ "MicroCore" ] = "%{wks.location}/MicroCore/"

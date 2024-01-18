if (Test-Path build) {
    Remove-Item -Recurse -Force build
}

function usage {
    Write-Host "Usage: .\install\build.ps1 --game <game_name> [--linter <linter_name>] [--download] [--tests]"
    exit 1
}

if ($args.Length -eq 0) {
    usage
}

$game = ""
$linter = ""
$download = $false

$command="cmake .. '-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake' -DCMAKE_BUILD_TYPE=Release"

for ($i = 0; $i -lt $args.Length; $i++) {
    $arg = $args[$i]
    switch ($arg) {
        "--game" {
            $i++
            $game = $args[$i]
            $command += " -DENABLE_PROJECT=$game"
        }
        "--linter" {
            $i++
            $linter = $args[$i]
            $command += " -DACTIVATE_LINTER=$linter"
        }
        "--download" {
            $download = $true
        }
        "--tests" {
            $command += " -DENABLE_TESTS=True"
        }
        default {
            usage
        }
    }
}

if ($game -eq "") {
    usage
}

$processor_info = Get-WmiObject -Class Win32_Processor
$num_cores = $processor_info.NumberOfCores

Write-Host "Building with $num_cores cores"

conan profile detect --force
conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cd build
Invoke-Expression $command
cmake --build . --config Release -- /maxcpucount:$num_cores

if ($download) {
    cpack
}
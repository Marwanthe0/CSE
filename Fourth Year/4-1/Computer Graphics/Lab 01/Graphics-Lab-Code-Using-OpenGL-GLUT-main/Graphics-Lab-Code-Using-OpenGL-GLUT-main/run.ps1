param (
    [string]$Number
)

$experiments = @{
    "1"  = "1_DDA_line_drawing"
    "2"  = "2_Bresenham_line_drawing"
    "3"  = "3_Midpoint_circle_drawing"
    "4"  = "4_Circle_using_single_point"
    "5"  = "5_Midpoint_ellipse_drawing"
    "6"  = "6_Boundary_fill_algorithm"
    "7"  = "7_Flood_fill_algorithm"
    "8"  = "8_Basic_transformations_rectangle"
    "9"  = "9_Basic_transformations_triangle"
    "10" = "10_Composite_transformations_rectangle"
    "11" = "11_Composite_transformations_triangle"
    "12" = "12_Clip_rectangle"
    "13" = "13_Draw_line_within_rectangle"
    "14" = "14_Bezier_curve"
}

if (-not $Number) {
    Write-Host "===================================================" -ForegroundColor Cyan
    Write-Host "  OpenGL GLUT Lab Experiments Runner" -ForegroundColor Yellow
    Write-Host "===================================================" -ForegroundColor Cyan
    foreach ($k in 1..14) {
        $strK = "$k"
        Write-Host ("  [{0,2}] {1}" -f $k, $experiments[$strK])
    }
    Write-Host "===================================================" -ForegroundColor Cyan
    $Number = Read-Host "Enter experiment number (1-14)"
}

if (-not $experiments.ContainsKey($Number)) {
    Write-Host "[ERROR] Invalid experiment number: $Number" -ForegroundColor Red
    exit 1
}

$dir = $experiments[$Number]
$cppFile = Get-ChildItem -Path $dir -Filter "*.cpp" | Select-Object -First 1

if (-not $cppFile) {
    Write-Host "[ERROR] C++ file not found in $dir" -ForegroundColor Red
    exit 1
}

$exeFile = Join-Path $dir "$($cppFile.BaseName).exe"

Write-Host "[*] Compiling $($cppFile.Name)..." -ForegroundColor Cyan
& g++ $cppFile.FullName -o $exeFile -lfreeglut -lopengl32 -lglu32

if ($LASTEXITCODE -ne 0) {
    Write-Host "[ERROR] Compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host "[OK] Compilation successful! Launching..." -ForegroundColor Green
Start-Process -FilePath "cmd.exe" -ArgumentList "/c `"$exeFile & pause`""

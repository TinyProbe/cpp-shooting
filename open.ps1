$inc_files = ls ./inc/*.hpp
$src_files = ls ./src/*.cpp
$files = ""

for ($i = 0; $i -lt $inc_files.count; ++$i) {
  $files = $files + $inc_files[$i] + " "
  $files = $files + $src_files[$i] + " "
}

$files = $files -replace "C:\\Users\\137ad\\Projects\\desktop\\shooting\\", ""
$files = $files -split " "

nvim inc/shooting.h src/shooting.cc $files[0..($files.length - 2)]

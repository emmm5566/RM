cmake_minimum_required(VERSION 2.8)
project(course)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 定义所有目标名称（按顺序对应源文件）
set(TARGETS 
  EnableImage 
  EnableVideo 
  EnableCamera 
  BasicFunctions 
  ResizeAndCrop 
  DrawShapesAndText
  WarpImage
  ColorDetection
  ShapesDetection
  FaceDetection

  VirtualPaint
  ColorPicker
  DocumentScanner
  LicensePlateDetector
)

# 生成可执行文件
add_executable(EnableImage src/chapter1/EnableImage.cpp)
add_executable(EnableVideo src/chapter1/EnableVideo.cpp)
add_executable(EnableCamera src/chapter1/EnableCamera.cpp)
add_executable(BasicFunctions src/chapter2/BasicFunctions.cpp)
add_executable(ResizeAndCrop src/chapter3/ResizeAndCrop.cpp)
add_executable(DrawShapesAndText src/chapter4/DrawShapesAndText.cpp)
add_executable(WarpImage src/chapter5/WarpImage.cpp)
add_executable(ColorDetection src/chapter6/ColorDetection.cpp)
add_executable(ShapesDetection src/chapter7/ShapesDetection.cpp)
add_executable(FaceDetection src/chapter8/FaceDetection.cpp)

add_executable(VirtualPaint src/project1/VirtualPaint.cpp)
add_executable(ColorPicker src/project1/ColorPicker.cpp)
add_executable(DocumentScanner src/project2/DocumentScanner.cpp)
add_executable(LicensePlateDetector src/project3/LicensePlateDetector.cpp)

# 批量链接 OpenCV 库
foreach(target IN LISTS TARGETS)
  target_link_libraries(${target} PRIVATE ${OpenCV_LIBS}) 
endforeach()
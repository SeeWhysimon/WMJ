# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/simon/OPENCV/WMJ/Week2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/simon/OPENCV/WMJ/Week2/build

# Include any dependencies generated for this target.
include CMakeFiles/Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project.dir/flags.make

CMakeFiles/Project.dir/src/test.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/src/test.cpp.o: ../src/test.cpp
CMakeFiles/Project.dir/src/test.cpp.o: CMakeFiles/Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/simon/OPENCV/WMJ/Week2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project.dir/src/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Project.dir/src/test.cpp.o -MF CMakeFiles/Project.dir/src/test.cpp.o.d -o CMakeFiles/Project.dir/src/test.cpp.o -c /home/simon/OPENCV/WMJ/Week2/src/test.cpp

CMakeFiles/Project.dir/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/src/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/simon/OPENCV/WMJ/Week2/src/test.cpp > CMakeFiles/Project.dir/src/test.cpp.i

CMakeFiles/Project.dir/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/src/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/simon/OPENCV/WMJ/Week2/src/test.cpp -o CMakeFiles/Project.dir/src/test.cpp.s

CMakeFiles/Project.dir/src/Project.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/src/Project.cpp.o: ../src/Project.cpp
CMakeFiles/Project.dir/src/Project.cpp.o: CMakeFiles/Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/simon/OPENCV/WMJ/Week2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project.dir/src/Project.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Project.dir/src/Project.cpp.o -MF CMakeFiles/Project.dir/src/Project.cpp.o.d -o CMakeFiles/Project.dir/src/Project.cpp.o -c /home/simon/OPENCV/WMJ/Week2/src/Project.cpp

CMakeFiles/Project.dir/src/Project.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/src/Project.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/simon/OPENCV/WMJ/Week2/src/Project.cpp > CMakeFiles/Project.dir/src/Project.cpp.i

CMakeFiles/Project.dir/src/Project.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/src/Project.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/simon/OPENCV/WMJ/Week2/src/Project.cpp -o CMakeFiles/Project.dir/src/Project.cpp.s

# Object files for target Project
Project_OBJECTS = \
"CMakeFiles/Project.dir/src/test.cpp.o" \
"CMakeFiles/Project.dir/src/Project.cpp.o"

# External object files for target Project
Project_EXTERNAL_OBJECTS =

Project: CMakeFiles/Project.dir/src/test.cpp.o
Project: CMakeFiles/Project.dir/src/Project.cpp.o
Project: CMakeFiles/Project.dir/build.make
Project: /usr/local/lib/libopencv_gapi.so.4.8.0
Project: /usr/local/lib/libopencv_stitching.so.4.8.0
Project: /usr/local/lib/libopencv_aruco.so.4.8.0
Project: /usr/local/lib/libopencv_bgsegm.so.4.8.0
Project: /usr/local/lib/libopencv_bioinspired.so.4.8.0
Project: /usr/local/lib/libopencv_ccalib.so.4.8.0
Project: /usr/local/lib/libopencv_dnn_objdetect.so.4.8.0
Project: /usr/local/lib/libopencv_dnn_superres.so.4.8.0
Project: /usr/local/lib/libopencv_dpm.so.4.8.0
Project: /usr/local/lib/libopencv_face.so.4.8.0
Project: /usr/local/lib/libopencv_freetype.so.4.8.0
Project: /usr/local/lib/libopencv_fuzzy.so.4.8.0
Project: /usr/local/lib/libopencv_hfs.so.4.8.0
Project: /usr/local/lib/libopencv_img_hash.so.4.8.0
Project: /usr/local/lib/libopencv_intensity_transform.so.4.8.0
Project: /usr/local/lib/libopencv_line_descriptor.so.4.8.0
Project: /usr/local/lib/libopencv_mcc.so.4.8.0
Project: /usr/local/lib/libopencv_quality.so.4.8.0
Project: /usr/local/lib/libopencv_rapid.so.4.8.0
Project: /usr/local/lib/libopencv_reg.so.4.8.0
Project: /usr/local/lib/libopencv_rgbd.so.4.8.0
Project: /usr/local/lib/libopencv_saliency.so.4.8.0
Project: /usr/local/lib/libopencv_stereo.so.4.8.0
Project: /usr/local/lib/libopencv_structured_light.so.4.8.0
Project: /usr/local/lib/libopencv_superres.so.4.8.0
Project: /usr/local/lib/libopencv_surface_matching.so.4.8.0
Project: /usr/local/lib/libopencv_tracking.so.4.8.0
Project: /usr/local/lib/libopencv_videostab.so.4.8.0
Project: /usr/local/lib/libopencv_wechat_qrcode.so.4.8.0
Project: /usr/local/lib/libopencv_xfeatures2d.so.4.8.0
Project: /usr/local/lib/libopencv_xobjdetect.so.4.8.0
Project: /usr/local/lib/libopencv_xphoto.so.4.8.0
Project: /usr/local/lib/libopencv_shape.so.4.8.0
Project: /usr/local/lib/libopencv_highgui.so.4.8.0
Project: /usr/local/lib/libopencv_datasets.so.4.8.0
Project: /usr/local/lib/libopencv_plot.so.4.8.0
Project: /usr/local/lib/libopencv_text.so.4.8.0
Project: /usr/local/lib/libopencv_ml.so.4.8.0
Project: /usr/local/lib/libopencv_phase_unwrapping.so.4.8.0
Project: /usr/local/lib/libopencv_optflow.so.4.8.0
Project: /usr/local/lib/libopencv_ximgproc.so.4.8.0
Project: /usr/local/lib/libopencv_video.so.4.8.0
Project: /usr/local/lib/libopencv_videoio.so.4.8.0
Project: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
Project: /usr/local/lib/libopencv_objdetect.so.4.8.0
Project: /usr/local/lib/libopencv_calib3d.so.4.8.0
Project: /usr/local/lib/libopencv_dnn.so.4.8.0
Project: /usr/local/lib/libopencv_features2d.so.4.8.0
Project: /usr/local/lib/libopencv_flann.so.4.8.0
Project: /usr/local/lib/libopencv_photo.so.4.8.0
Project: /usr/local/lib/libopencv_imgproc.so.4.8.0
Project: /usr/local/lib/libopencv_core.so.4.8.0
Project: CMakeFiles/Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/simon/OPENCV/WMJ/Week2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project.dir/build: Project
.PHONY : CMakeFiles/Project.dir/build

CMakeFiles/Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project.dir/clean

CMakeFiles/Project.dir/depend:
	cd /home/simon/OPENCV/WMJ/Week2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/simon/OPENCV/WMJ/Week2 /home/simon/OPENCV/WMJ/Week2 /home/simon/OPENCV/WMJ/Week2/build /home/simon/OPENCV/WMJ/Week2/build /home/simon/OPENCV/WMJ/Week2/build/CMakeFiles/Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project.dir/depend


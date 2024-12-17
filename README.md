# MNIST Tflite-for-CPP

MAJOR SOURCE OF TENSORFLOW SETUP:

https://www.tensorflow.org/install/source

-----------------------------------------------------------------------------------------------------------------------------------------
BUILDING TENSORFLOW LIBRARY FOR LINUX:

INSTALL PYTHON:

sudo apt install python3-dev python3-pip

INSTALL PIP:

pip install -U pip

override the warning if necessary

-----------------------------------------------------------------------------------------------------------------------------------------

FOR THE NEXT STEP WE NEED TO TAKE CARE OF THE CONFIGURATION VERSIONS:

https://www.tensorflow.org/install/source#tested_build_configurations

![image](https://github.com/user-attachments/assets/96e7a666-253d-4509-8d4e-7e83e0197fc8)


-----------------------------------------------------------------------------------------------------------------------------------------

INSTALL BAZEL:

Bazel is tool to build software of any size ( at the end we want a shared library of 
tensorflow build)

https://github.com/bazelbuild/bazel/releases

After this add bazel to the PATH environment variable

-> sudo mv bazel-{version} /usr/local/bin/bazel

For checking

bazel --version

-----------------------------------------------------------------------------------------------------------------------------------------

INSTALL CLANG:

sudo apt-get update && sudo apt-get install -y llvm-17 clang-17  (again check for which version you want)

DOWNLOAD TENSORFLOW

* git clone https://github.com/tensorflow/tensorflow.git
* cd tensorflow
* ./configure

-----------------------------------------------------------------------------------------------------------------------------------------

BUILD TENSORFLOW:

bazel build //tensorflow/lite:libtensorflowlite.so

NOTE: The build takes a more than 3 hours for a mid-range pc with 4 cores.

You will find the "libtensorflowlite.so" in the below directory if the build is successfull

~/tensorflow/bazel-bin/tensorflow/lite    (We need to add this to our libs folder)

-----------------------------------------------------------------------------------------------------------------------------------------

NEXT YOU THE NECESSARY LIBRARY HEADERS FROM TFLITE

There is no default headers which are organized given by tensorflow we need extract it manually.

Maybe this page help for manual extraction -> https://www.thecodingnotebook.com/2019/11/cross-platform-object-detection-with.html

For this project I took the one which is already created by -> https://github.com/ValYouW/tflite-dist/releases

-----------------------------------------------------------------------------------------------------------------------------------------

MNIST MODEL:

The model was taken from 

https://github.com/frogermcs/MNIST-TFLite/blob/master/notebooks/mnist_model.tflite

-----------------------------------------------------------------------------------------------------------------------------------------

Install OPENCV for image reading:

Dependencies:

sudo apt install -y build-essential cmake git pkg-config

sudo apt install -y libjpeg-dev libtiff-dev libpng-dev

sudo apt install -y libavcodec-dev libavformat-dev libswscale-dev

sudo apt install -y libv4l-dev libxvidcore-dev libx264-dev

sudo apt install -y libgtk-3-dev libcanberra-gtk3-dev

sudo apt install -y libatlas-base-dev gfortran

sudo apt install -y python3-dev

OpenCV installation:

sudo apt install libopencv-dev

-----------------------------------------------------------------------------------------------------------------------------------------

FOR BUILDING THE PROJECT:

cd build

rm -rf *        -> (for a clean build)

cmake -DOpenCV_DIR=/usr/lib/x86_64-linux-gnu/cmake/opencv4 ..         -> (check the path of your OpenCV library) 

make

./TFLite

"WE ARE EXPECTING THE OUTPUT VALUE TO BE THE SAME AS THE IMAGE GIVEN AS THE INPUT"

-----------------------------------------------------------------------------------------------------------------------------------------


REFERENCES:

https://github.com/karthickai/tflite

https://www.thecodingnotebook.com/2019/11/cross-platform-object-detection-with.html

https://github.com/ValYouW/tflite-dist

https://github.com/frogermcs/MNIST-TFLite/blob/master/notebooks/mnist_model.tflite

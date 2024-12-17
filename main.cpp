#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/c/common.h"

// Helper function to load a binary model file
std::vector<char> LoadModelFile(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Failed to open model file");
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("Failed to read model file");
    }
    return buffer;
}

int main() {
    const std::string model_path = "../mnist_model.tflite";
    const std::string image_path = "../mnist_image.jpg";

    // Load model
    std::vector<char> model_data = LoadModelFile(model_path);
    auto model = tflite::FlatBufferModel::BuildFromBuffer(model_data.data(), model_data.size());
    if (!model) {
        std::cerr << "Failed to load model" << std::endl;
        return -1;
    }

    // Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);
    if (!interpreter) {
        std::cerr << "Failed to create interpreter" << std::endl;
        return -1;
    }

    // Allocate tensors
    if (interpreter->AllocateTensors() != kTfLiteOk) {
        std::cerr << "Failed to allocate tensors" << std::endl;
        return -1;
    }

    // Load image using OpenCV
    cv::Mat img = cv::imread(image_path, cv::IMREAD_GRAYSCALE); // Load as grayscale
    if (img.empty()) {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    // Preprocess the image
    int input_height = interpreter->tensor(interpreter->inputs()[0])->dims->data[1];
    int input_width = interpreter->tensor(interpreter->inputs()[0])->dims->data[2];

    // Resize image to 28x28
    cv::resize(img, img, cv::Size(input_width, input_height));

    // Normalize the image to [0, 1]
    img.convertTo(img, CV_32F, 1.0 / 255); // Convert to float and scale to [0, 1]

    // Flatten image into 1D array for model input
    float* input = interpreter->typed_input_tensor<float>(0);

    // Copy image data to input tensor
    std::memcpy(input, img.data, img.total() * img.elemSize());

    // Run inference
    if (interpreter->Invoke() != kTfLiteOk) {
        std::cerr << "Failed to invoke interpreter" << std::endl;
        return -1;
    }

    // Get output tensor
    float* output = interpreter->typed_output_tensor<float>(0);

    // Find the predicted digit (highest probability)
    int predicted_digit = std::distance(output, std::max_element(output, output + 10));

    // Print output
    std::cout << "Predicted Digit: " << predicted_digit << std::endl;

    return 0;
}


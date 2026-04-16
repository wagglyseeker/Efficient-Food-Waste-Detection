#  Efficient Food Waste Detection using Edge AI on NVIDIA Jetson

An intelligent edge AI system that detects and classifies food waste in real-time using computer vision and deep learning.  
The system leverages *MobileNetV2-based CNN, **OpenCV preprocessing, and **NVIDIA Jetson edge deployment* to enable low-latency, real-time waste monitoring.

---

##  Overview

This project presents a real-time food waste detection system designed to improve waste monitoring and analytics using edge AI.

The system captures food images, processes them using computer vision techniques, classifies them using a trained deep learning model, and combines visual data with weight measurements to estimate food waste.

By deploying the model on *NVIDIA Jetson*, the system performs inference locally, reducing latency and eliminating dependence on cloud-based processing.

---

##  Key Features

- Real-time *food classification* using deep learning
- Edge AI deployment on *NVIDIA Jetson*
- OpenCV-based *image preprocessing pipeline*
- Transfer learning using *MobileNetV2*
- Multi-sensor integration (camera + load cell)
- Low-latency local inference
- Real-time food waste measurement

---

##  System Architecture

The system consists of multiple integrated modules:

###  Image Acquisition Module

- Captures food images using camera input
- Processes live video frames
- Sends frames to preprocessing pipeline

---

###  Image Processing Module

- HSV-based color segmentation
- Gaussian filtering
- Morphological operations
- Region extraction and segmentation

These steps prepare images for accurate classification.

---

### 3️⃣ Classification Module

- MobileNetV2 CNN used for classification
- Transfer learning applied to improve performance
- Custom dense layers added
- Data augmentation improves generalization

The model classifies food items into predefined categories.

---

###  Sensor Integration Module

- Load-cell sensor measures food weight
- Combines classification output with weight data
- Enables real-time food waste estimation

---

###  Edge Deployment Module

- Model deployed on *NVIDIA Jetson*
- Local inference reduces latency
- Eliminates need for cloud processing

---

## Technologies Used

- Python
- OpenCV
- TensorFlow / Keras
- MobileNetV2
- Computer Vision
- Deep Learning
- Image Processing
- Edge AI (NVIDIA Jetson)
- Sensor Integration

---

##  Performance Highlights

- Achieved *~88% classification accuracy*
- Real-time inference on edge hardware
- Low-latency predictions
- Improved generalization using data augmentation
- Efficient image preprocessing pipeline

---

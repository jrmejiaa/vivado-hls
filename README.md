Sobel CPU Implementation
------------------------
This project is a simple Implementation of the Grayscale and Sobel Image Filters.

Dependencies
------------

* OpenCV 3.4.10

How to install Dependencies / Abhängigkeiten installieren
---------------------------
```shell script
git clone https://github.com/opencv/opencv.git
git checkout 3.4.10
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```


How to build / Build-Prozess
------------
```shell script
mkdir build
cd build
cmake ..
make
```

How to run / Ausführen
----------
Mit OpenCV für jpg-Bilder:

```shell script
./sobel_cpu ../resources/lena-color.jpg ../resources/filtered.jpg
```

Die Testbench zum Checken der Korrektheit von grayscale & sobel
```shell script
./sobel_tb <red.data> <green.data> <blue.data> <gray.data> <sobel.data>
```
This command will load the image '../resources/lena-color.jpg', apply a grayscale filter to it. Finally, the sobel filter is used to perform edge-detection.


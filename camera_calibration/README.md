# camera_calibration
Tool to calibrate a camera for use with LSD-SLAM.

## building
- create build-directory and cd into it:
  ``` bash
  mkdir build
  cd build
  ```

- cmake and build:
  ``` bash
  cmake ..
  make
  ```

## usage
Call the built application with an XML-config-file as parameter.
Use `sample_config.xml` as a starting point for your configuration.

# LightsOutChallenge
CS169 Group Project

## Instructions to test it out

1. Get boost python by running the next line (should work on any linux/debian machine)  
   Note: This command takes a very long time, only do this once
   ```bash
   make get_boost_python
   ```

2. Take note of your python3 minor version (over here it's python 3.6)  
   Note: Python 3.6.* all have minor version '6' for these purposes
    ```bash
   python3 --version
   ```

3. Run the below command:  
    Note: Substitute '8' with your python3 minor version number.  
    Note: Defaults to '6'  
    ```bash
    make PYTHON_MINOR_VERSION=8
    ```
4. Run the python modules with python3

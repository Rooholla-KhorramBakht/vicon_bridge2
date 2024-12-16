FROM ros:humble
# Add an argument for the entry point
SHELL ["/bin/bash", "-c"]
# Non-interactive installation
ENV DEBIAN_FRONTEND=noninteractive
# Install dependencies
RUN apt update && apt upgrade -y
RUN sudo apt install libboost-all-dev python3-pip -y 

# Install CycloneDDS
RUN git clone https://github.com/eclipse-cyclonedds/cyclonedds && \
    cd cyclonedds && mkdir build install && cd build && \ 
    cmake .. && \
    cmake --build . --config RelWithDebInfo --target install 

# Install cyclonedds-cxx
RUN git clone https://github.com/eclipse-cyclonedds/cyclonedds-cxx &&\
    cd cyclonedds-cxx && mkdir build install && cd build && \
    cmake  .. && \
    cmake --build . --target install
# Install cylconedds-python
RUN echo "export CYCLONEDDS_HOME=/usr/local" >> ~/.bashrc 
RUN echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib" >> ~/.bashrc 
ENV CYCLONEDDS_HOME=/usr/local
RUN pip3 install git+https://github.com/eclipse-cyclonedds/cyclonedds-python

RUN mkdir -p /home/vicon-ws/src
COPY ./vicon_bridge2 /home/vicon-ws/src/vicon_bridge2
COPY ./vicon_msgs /home/vicon-ws/src/vicon_msgs
# Compile the package
WORKDIR /home/vicon-ws
RUN . /opt/ros/humble/setup.bash && colcon build
RUN echo "source /home/vicon-ws/install/setup.bash" >> ~/.bashrc

RUN pip3 install scipy numpy
# Set the entry point
# ENTRYPOINT ["/bin/bash", "ros2 launch vicon_bridge2 vicon.launch.py"]

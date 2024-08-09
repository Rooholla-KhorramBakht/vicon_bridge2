FROM ros:foxy
# Add an argument for the entry point
ARG VICON_IP
SHELL ["/bin/bash", "-c"]
# Non-interactive installation
ENV DEBIAN_FRONTEND=noninteractive
# Install dependencies
RUN apt update && apt upgrade -y
RUN sudo apt install libboost1.71-all-dev -y
# Copy the vicon_bridge2 package into the home directory and install dependencies
RUN mkdir -p /home/vicon-ws/src
COPY ./vicon_bridge2 /home/vicon-ws/src/vicon_bridge2
COPY ./vicon_msgs /home/vicon-ws/src/vicon_msgs
# Compile the package
WORKDIR /home/vicon-ws
RUN . /opt/ros/foxy/setup.bash && colcon build --symlink-install
# Set the entry point to be the bash
ENTRYPOINT ["/bin/bash"]
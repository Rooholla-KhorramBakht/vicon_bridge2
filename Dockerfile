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
COPY ./vicon_bridge2 /home/vicon_bridge2
COPY DataStreamSDK_10.1 /home/DataStreamSDK_10.1
RUN cp /home/DataStreamSDK_10.1/libViconDataStreamSDK_CPP.so /usr/lib
RUN cp /home/DataStreamSDK_10.1/libboost_system-mt.so.1.58.0 /usr/lib
RUN cp /home/DataStreamSDK_10.1/libboost_thread-mt.so.1.58.0 /usr/lib
RUN cp /home/DataStreamSDK_10.1/libboost_timer-mt.so.1.58.0 /usr/lib
RUN cp /home/DataStreamSDK_10.1/libboost_chrono-mt.so.1.58.0 /usr/lib
RUN chmod 0755 /usr/lib/libViconDataStreamSDK_CPP.so /usr/lib/libboost_system-mt.so.1.58.0 /usr/lib/libboost_thread-mt.so.1.58.0 /usr/lib/libboost_timer-mt.so.1.58.0 /usr/lib/libboost_chrono-mt.so.1.58.0
RUN ldconfig
# Compile the package
WORKDIR /home/vicon_bridge2
RUN . /opt/ros/foxy/setup.bash && colcon build --symlink-install
# Set the entry point to be the bash
ENTRYPOINT ["/bin/bash"]
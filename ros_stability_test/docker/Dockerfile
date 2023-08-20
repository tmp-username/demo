FROM ros:eloquent

RUN apt-get update && apt-get install -y \
    vim \
    systemd \
    ethtool \
    linuxptp \
    openssh-server \
    ros-eloquent-launch* \
    ros-eloquent-rmw-opensplice-cpp \
    ros-eloquent-rmw-cyclonedds-cpp

RUN systemctl set-default multi-user.target

# Use this image to run a container with 'host' network that make ros2 nodes communicate sucessfully,
# update ssh port with 9922 to avoid confiliction with local host that ssh service exist
RUN sed -i 's/#Port 22/Port 9922/' /etc/ssh/sshd_config
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN echo 'root:docker' | chpasswd
RUN systemctl enable ssh.service

CMD ["/sbin/init"]

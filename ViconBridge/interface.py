import time
import numpy as np
from scipy.spatial.transform import Rotation as R

from cyclonedds.domain import DomainParticipant
from ViconBridge.msgs import Pose6D
from cyclonedds.topic import Topic

from cyclonedds.domain import DomainParticipant
from cyclonedds.topic import Topic
from cyclonedds.sub import DataReader
from cyclonedds.util import duration
from threading import Thread
import time

class ViconDDSListener():
    def __init__(
        self,
        object_name,
        spawn_thread = True,
        state_update_timeout = 0.1
    ):
        self.object_name = object_name
        self.topic_name = f'vicon/{object_name}/{object_name}'
        self.spawn_thread = spawn_thread
        self.state_update_timeout = state_update_timeout
        try:
            self.participant = DomainParticipant()
        except:
            raise Exception('Could not initialize the DDS communication. Is the interface name provided correctly?')
        
        self.vicon_topic = Topic(self.participant, self.topic_name, Pose6D)
        self.state_reader = DataReader(self.participant, self.vicon_topic)
        if self.spawn_thread:
            self.state_thread = Thread(target=self.state_update)
            self.running = True
            self.state_thread.start()

        self.state = None
        self.latest_stamp = time.time()

    def state_update(self):
        """
        Retrieve the state of the robot
        """
        while self.running:
            self.updateStateOnce()

    def updateStateOnce(self):
        for msg in self.state_reader.take_iter(timeout=duration(milliseconds=1.)):
            self.state = msg
            self.latest_stamp = time.time()

    def getState(self):
        if self.spawn_thread:
            if (time.time() - self.latest_stamp) < self.state_update_timeout:
                return self.state
            else:
                return None
        else: 
            self.updateStateOnce()
            if (time.time() - self.latest_stamp) < self.state_update_timeout:
                return self.state
            
    def getPose(self, vicon_stamp=False):
        state = self.getState()
        if state is not None:
            q = state.q
            t = state.t
            stamp_ns = state.stamp_nano_secs
            Rot = R.from_quat(q)
            pose = np.eye(4)
            pose[:3, :3] = Rot.as_dcm()
            pose[:3, 3] = t
            if vicon_stamp:
                return pose, stamp_ns
            else:
                return pose
        else:
            return None
        
    def close(self):
        self.running = False
        self.state_thread.join()
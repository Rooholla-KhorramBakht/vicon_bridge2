from ViconBridge import ViconDDSListener
import signal
import time

object_name = 'tool'
vicon = ViconDDSListener(object_name, spawn_thread=True)

while True:
    state = vicon.getState()
    if state is not None:
        print(state)
    else:
        print('No new state')
    time.sleep(0.1)
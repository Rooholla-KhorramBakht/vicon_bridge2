#include "vicon_bridge2/communicator.hpp"
#include "rclcpp/rclcpp.hpp"
#include <csignal>
#include "vicon_msgs/msg/marker.hpp"
#include "vicon_msgs/msg/markers.hpp"
using namespace ViconDataStreamSDK::CPP;

Communicator::Communicator() : Node("vicon")
{
    // get parameters
    this->declare_parameter<std::string>("hostname", "127.0.0.1");
    this->declare_parameter<int>("buffer_size", 200);
    this->declare_parameter<std::string>("namespace", "vicon");
    this->get_parameter("hostname", hostname);
    this->get_parameter("buffer_size", buffer_size);
    this->get_parameter("namespace", ns_name);
    std::string topic_name = ns_name + "/" + "markers";
    this->create_publisher<vicon_msgs::msg::Markers>(topic_name, 10);
}

bool Communicator::connect()
{
    // connect to server
    string msg = "Connecting to " + hostname + " ...";
    cout << msg << endl;
    int counter = 0;
    while (!vicon_client.IsConnected().Connected && rclcpp::ok())
    {
        bool ok = (vicon_client.Connect(hostname).Result == Result::Success);
        if (!ok)
        {
            counter++;
            msg = "Connect failed, reconnecting (" + std::to_string(counter) + ")...";
            cout << msg << endl;
            sleep(1);
        }
    }
    msg = "Connection successfully established with " + hostname;
    cout << msg << endl;

    // perform further initialization
    vicon_client.EnableSegmentData();
    vicon_client.EnableMarkerData();
    vicon_client.EnableUnlabeledMarkerData();
    vicon_client.EnableMarkerRayData();
    vicon_client.EnableDeviceData();
    vicon_client.EnableDebugData();

    vicon_client.SetStreamMode(StreamMode::ClientPull);
    vicon_client.SetBufferSize(buffer_size);

    msg = "Initialization complete";
    cout << msg << endl;

    return true;
}

bool Communicator::disconnect()
{
    if (!vicon_client.IsConnected().Connected)
        return true;
    sleep(1);
    vicon_client.DisableSegmentData();
    vicon_client.DisableMarkerData();
    vicon_client.DisableUnlabeledMarkerData();
    vicon_client.DisableDeviceData();
    vicon_client.DisableCentroidData();
    string msg = "Disconnecting from " + hostname + "...";
    cout << msg << endl;
    vicon_client.Disconnect();
    msg = "Successfully disconnected";
    cout << msg << endl;
    unlabeled_marker_data_enabled = false;
    if (!vicon_client.IsConnected().Connected)
        return true;
    return false;
}

void Communicator::get_frame()
{
    cout << "enabling unlabeled marker data" << endl;
    if (!unlabeled_marker_data_enabled)
    {
    vicon_client.EnableUnlabeledMarkerData();
    bool status =  vicon_client.IsUnlabeledMarkerDataEnabled().Enabled;
    if (!status)
        {
        cout << "Unlabeled marker data not enabled" << endl;
        }
    else
        {
        cout << "Unlabeled marker data enabled" << endl;
        unlabeled_marker_data_enabled = true;
        }
    }
    unsigned int n_markers = 0;
     // Get the current timestamp
    rclcpp::Time current_time = this->now();
    // Extract seconds and nanoseconds from the timestamp
    int64_t seconds = current_time.seconds();
    int32_t nanoseconds = current_time.nanoseconds();
    vicon_msgs::msg::Markers markers_msg;
    markers_msg.header.stamp.sec = seconds;
    markers_msg.header.stamp.nanosec = nanoseconds;

    // Count the number of subjects
    unsigned int SubjectCount = vicon_client.GetSubjectCount().SubjectCount;
    // Get labeled markers
    for (unsigned int SubjectIndex = 0; SubjectIndex < SubjectCount; ++SubjectIndex)
    {
    std::string this_subject_name = vicon_client.GetSubjectName(SubjectIndex).SubjectName;
    // Count the number of markers
    unsigned int num_subject_markers = vicon_client.GetMarkerCount(this_subject_name).MarkerCount;
    n_markers += num_subject_markers;
    //std::cout << "    Markers (" << MarkerCount << "):" << std::endl;
    for (unsigned int MarkerIndex = 0; MarkerIndex < num_subject_markers; ++MarkerIndex)
    {
        vicon_msgs::msg::Marker this_marker;
        this_marker.marker_name = vicon_client.GetMarkerName(this_subject_name, MarkerIndex).MarkerName;
        this_marker.subject_name = this_subject_name;
        this_marker.segment_name
            = vicon_client.GetMarkerParentName(this_subject_name, this_marker.marker_name).SegmentName;

        // Get the global marker translation
        Output_GetMarkerGlobalTranslation _Output_GetMarkerGlobalTranslation =
            vicon_client.GetMarkerGlobalTranslation(this_subject_name, this_marker.marker_name);

        this_marker.translation.x = _Output_GetMarkerGlobalTranslation.Translation[0];
        this_marker.translation.y = _Output_GetMarkerGlobalTranslation.Translation[1];
        this_marker.translation.z = _Output_GetMarkerGlobalTranslation.Translation[2];
        this_marker.occluded = _Output_GetMarkerGlobalTranslation.Occluded;

        markers_msg.markers.push_back(this_marker);
    }
    }
    // get unlabeled markers
    unsigned int UnlabeledMarkerCount = vicon_client.GetUnlabeledMarkerCount().MarkerCount;
    cout << "Unlabeled Markers (" << UnlabeledMarkerCount << "):" << std::endl;
    for (unsigned int UnlabeledMarkerIndex = 0; UnlabeledMarkerIndex < UnlabeledMarkerCount; ++UnlabeledMarkerIndex)
    {
        // Get the global marker translation
        Output_GetUnlabeledMarkerGlobalTranslation _Output_GetUnlabeledMarkerGlobalTranslation =
            vicon_client.GetUnlabeledMarkerGlobalTranslation(UnlabeledMarkerIndex);

        if (_Output_GetUnlabeledMarkerGlobalTranslation.Result == Result::Success)
        {
            vicon_msgs::msg::Marker this_marker;
            this_marker.translation.x = _Output_GetUnlabeledMarkerGlobalTranslation.Translation[0];
            this_marker.translation.y = _Output_GetUnlabeledMarkerGlobalTranslation.Translation[1];
            this_marker.translation.z = _Output_GetUnlabeledMarkerGlobalTranslation.Translation[2];
            this_marker.occluded = false; // unlabeled markers can't be occluded
            markers_msg.markers.push_back(this_marker);
        }
    }
    markers_publisher->publish(markers_msg);
    vicon_client.GetFrame();

    Output_GetFrameNumber frame_number = vicon_client.GetFrameNumber();

    unsigned int subject_count = vicon_client.GetSubjectCount().SubjectCount;

    map<string, Publisher>::iterator pub_it;

    for (unsigned int subject_index = 0; subject_index < subject_count; ++subject_index)
    {
        // get the subject name
        string subject_name = vicon_client.GetSubjectName(subject_index).SubjectName;

        // count the number of segments
        unsigned int segment_count = vicon_client.GetSegmentCount(subject_name).SegmentCount;

        for (unsigned int segment_index = 0; segment_index < segment_count; ++segment_index)
        {
            // get the segment name
            string segment_name = vicon_client.GetSegmentName(subject_name, segment_index).SegmentName;

            // get position of segment
            PositionStruct current_position;
            Output_GetSegmentGlobalTranslation trans =
                vicon_client.GetSegmentGlobalTranslation(subject_name, segment_name);
            Output_GetSegmentGlobalRotationQuaternion rot =
                vicon_client.GetSegmentGlobalRotationQuaternion(subject_name, segment_name);
            
            for (size_t i = 0; i < 4; i++)
            {
                if (i < 3)
                    current_position.translation[i] = trans.Translation[i];
                current_position.rotation[i] = rot.Rotation[i];
            }
            // current_position.rotation[3] = rot.Rotation[3];
            current_position.segment_name = segment_name;
            current_position.subject_name = subject_name;
            current_position.translation_type = "Global";
            current_position.frame_number = frame_number.FrameNumber;
            current_position.time_sec = seconds;
            current_position.time_nsec = nanoseconds;

            // send position to publisher
            boost::mutex::scoped_try_lock lock(mutex);

            if (lock.owns_lock())
            {
                // get publisher
                pub_it = pub_map.find(subject_name + "/" + segment_name);
                if (pub_it != pub_map.end())
                {
                    Publisher & pub = pub_it->second;

                    if (pub.is_ready)
                    {
                        pub.publish(current_position);
                    }
                }
                else
                {
                    // create publisher if not already available
                    lock.unlock();
                    create_publisher(subject_name, segment_name);
                }
            }
        }
    }
}

void Communicator::create_publisher(const string subject_name, const string segment_name)
{
    boost::thread(&Communicator::create_publisher_thread, this, subject_name, segment_name);
}

void Communicator::create_publisher_thread(const string subject_name, const string segment_name)
{
    std::string topic_name = ns_name + "/" + subject_name + "/" + segment_name;
    std::string key = subject_name + "/" + segment_name;

    string msg = "Creating publisher for segment " + segment_name + " from subject " + subject_name;
    cout << msg << endl;

    // create publisher
    boost::mutex::scoped_lock lock(mutex);
    pub_map.insert(std::map<std::string, Publisher>::value_type(key, Publisher(topic_name, this)));

    // we don't need the lock anymore, since rest is protected by is_ready
    lock.unlock();
}
void signalHandler(int signum) 
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // Perform cleanup
    rclcpp::shutdown();
    // Terminate program
    exit(signum);
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Communicator>();
    node->connect();

    while (rclcpp::ok()){
        node->get_frame();
    }

    node->disconnect();
    rclcpp::shutdown();
    return 0;
}
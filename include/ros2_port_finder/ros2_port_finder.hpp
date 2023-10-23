#ifndef ROS2_PORT_FINDER_HPP
#define ROS2_PORT_FINDER_HPP

#include <iostream>
#include <chrono>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <regex>

using namespace std;

class PortFinder
{
    private:

    protected:

    public:
        /**
         * @source https://github.com/furkansariyildiz/TUBITAK-USV/blob/master/port_finder.py
        */
        PortFinder();

        ~PortFinder();
        
        string commandExecute(const char* command);

        vector<string> listAllPorts(string serial_port_group);

        string findIDVendor(string port);

        string findIDVendorID(string port);

        string findIDModelID(string port);

        string findIDPath(string port);

        string findDeviceName(string port);

        string findPort(string serial_port_group, string id_vendor, string id_vendor_id, string id_model_id, string id_path);

        char _command_buffer[128];

        regex _serial_port_pattern;
        smatch _serial_port_matches;

        regex _serial_port_monitoring_pattern;
        smatch _serial_port_monitoring_matches;

        string::const_iterator _serial_port_regex_iterator_start, _serial_port_regex_iterator_end;

        vector<string> _splitted_all_ports;

        string _list_all_ports_command, _id_vendor_id_command, _id_vendor_command, _id_model_id_command, _id_path_command, _device_name_command = "";
        string _list_all_ports_command_result, _id_vendor_id_command_result, _id_vendor_command_result, _id_model_id_command_result, _id_path_command_result, _device_name_command_result = "";

        string _found_port_name = "";

};

#endif
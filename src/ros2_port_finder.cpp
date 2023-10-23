#include "ros2_port_finder.hpp"

using namespace std;

PortFinder::PortFinder()
{
    _serial_port_pattern = regex("\\n");

    _serial_port_monitoring_pattern = regex("=");
}



PortFinder::~PortFinder()
{

}



string PortFinder::commandExecute(const char* command)
{
    memset(_command_buffer, 0, 127);
    string command_result = "";

    FILE* pipe = popen(command, "r");
    if(!pipe) throw runtime_error("popen() function is failed!");
    try
    {
        while(fgets(_command_buffer, sizeof(_command_buffer), pipe) != NULL)
        {
            command_result = command_result + _command_buffer;
        }
    }
    catch(const std::exception& e)
    {
        cout << "Error: " << e.what() << endl;
        pclose(pipe);
        throw e;
    }
    pclose(pipe);

    return command_result;
}



// ls /dev/*
vector<string> PortFinder::listAllPorts(string serial_port_group)
{
    _list_all_ports_command = "ls -p " + serial_port_group + " | grep -v /"; 

    string _list_all_ports_command_result = commandExecute(_list_all_ports_command.c_str()); 

    std::sregex_token_iterator serial_ports_iterator_start(_list_all_ports_command_result.begin(), _list_all_ports_command_result.end(), _serial_port_pattern, -1);
    std::sregex_token_iterator serial_ports_iterator_end;

    for(std::sregex_token_iterator it = serial_ports_iterator_start; it != serial_ports_iterator_end; ++it)
    {
        _splitted_all_ports.push_back(serial_port_group + "/" + it->str());
    }

    return _splitted_all_ports;
}



string PortFinder::findIDVendor(string port)
{
    try
    {
        _id_vendor_command = "udevadm info --name " + port + " | grep -i ID_VENDOR=";
        _id_vendor_command_result = commandExecute(_id_vendor_command.c_str());

        if(_id_vendor_command_result != "")
        {
            sregex_token_iterator it{_id_vendor_command_result.begin(), _id_vendor_command_result.end(), _serial_port_monitoring_pattern, -1};
            vector<string> tokenized_id_vendor_command_result{it, {}};
            
            _id_vendor_command_result = tokenized_id_vendor_command_result[1];

            _id_vendor_command_result.erase(remove(_id_vendor_command_result.begin(), _id_vendor_command_result.end(), '\n'), _id_vendor_command_result.cend());
        }
    }
    catch(const std::exception& e)
    {
        _id_vendor_command_result = "";
    }

    return _id_vendor_command_result;
}



string PortFinder::findIDVendorID(string port)
{
    try
    {
        _id_vendor_id_command = "udevadm info --name " + port + " | grep -i ID_VENDOR_ID=";
        _id_vendor_id_command_result = commandExecute(_id_vendor_id_command.c_str());

        if(_id_vendor_id_command_result != "")
        {
            sregex_token_iterator it{_id_vendor_id_command_result.begin(), _id_vendor_id_command_result.end(), _serial_port_monitoring_pattern, -1};
            vector<string> tokenized_id_vendor_id_command_result{it, {}};

            _id_vendor_id_command_result = tokenized_id_vendor_id_command_result[1];

            _id_vendor_id_command_result.erase(remove(_id_vendor_id_command_result.begin(), _id_vendor_id_command_result.end(), '\n'), _id_vendor_id_command_result.cend());
        }
    }
    catch(const std::exception& e)
    {
        _id_vendor_id_command_result = "";
    }

    return _id_vendor_id_command_result;
}



string PortFinder::findIDModelID(string port)
{
    try
    {
        _id_model_id_command = "udevadm info --name " + port + " | grep -i ID_MODEL_ID=";
        _id_model_id_command_result = commandExecute(_id_model_id_command.c_str());

        if(_id_model_id_command_result != "")
        {
            sregex_token_iterator it{_id_model_id_command_result.begin(), _id_model_id_command_result.end(), _serial_port_monitoring_pattern, -1};
            vector<string> tokenized_id_model_id_command_result{it, {}};

            _id_model_id_command_result = tokenized_id_model_id_command_result[1];

            _id_model_id_command_result.erase(remove(_id_model_id_command_result.begin(), _id_model_id_command_result.end(), '\n'), _id_model_id_command_result.cend());
        }
    }
    catch(const std::exception& e)
    {
        _id_model_id_command_result = "";
    }

    return _id_model_id_command_result;
}



string PortFinder::findIDPath(string port)
{
    try
    {
        _id_path_command = "udevadm info --name " + port + " | grep -i ID_PATH=";
        _id_path_command_result = commandExecute(_id_path_command.c_str());

        if(_id_path_command_result != "")
        {
            sregex_token_iterator it{_id_path_command_result.begin(), _id_path_command_result.end(), _serial_port_monitoring_pattern, -1};
            vector<string> tokenized_id_path_command_result{it, {}};

            _id_path_command_result = tokenized_id_path_command_result[1];

            _id_path_command_result.erase(remove(_id_path_command_result.begin(), _id_path_command_result.end(), '\n'), _id_path_command_result.cend());
        }
    }
    catch(const std::exception& e)
    {
        _id_path_command_result = "";
    }
    
    return _id_path_command_result;
}



string PortFinder::findDeviceName(string port)
{
    _device_name_command = "udevadm info --name " + port + " | grep -i DEVNAME=";
    _device_name_command_result = commandExecute(_device_name_command.c_str());

        sregex_token_iterator it{_device_name_command_result.begin(), _device_name_command_result.end(), _serial_port_monitoring_pattern, -1};
        vector<string> tokenized_device_name_command_result{it, {}};

        _device_name_command_result = tokenized_device_name_command_result[1];

        _device_name_command_result.erase(remove(_device_name_command_result.begin(), _device_name_command_result.end(), '\n'), _device_name_command_result.cend());

    return _device_name_command_result;    
}



string PortFinder::findPort(string serial_port_group, string id_vendor, string id_vendor_id, string id_model_id, string id_path)
{
    listAllPorts(serial_port_group);

    for(auto &port : _splitted_all_ports)
    {
        if(findIDVendor(port) == id_vendor && findIDVendorID(port) == id_vendor_id && findIDModelID(port) == id_model_id && findIDPath(port) == id_path)
        {
            _found_port_name = findDeviceName(port);
            // break;
        }
    }
    return _found_port_name;
}


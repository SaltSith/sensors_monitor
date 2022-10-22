#pragma once

#include "protos_src/monitor.pb.h"

monitor_MonitorMsg *monitor_commander_hello_async(void);
monitor_MonitorMsg *monitor_commander_temperature_async(const float cpu_temperature, const float gpu_temperature);

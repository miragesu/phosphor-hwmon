#pragma once

#include "hwmonio.hpp"
#include "interface.hpp"
#include "sysfs.hpp"

#include <memory>

namespace hwmon
{

/**
 * @class FanPwm
 * @brief Target fan pwm control implementation
 * @details Derived FanPwmObject type that writes the target value to sysfs
 * which in turn sets the fan speed to that target value
 */
class FanPwm : public FanPwmObject
{
  public:
    /**
     * @brief Constructs FanPwm Object
     *
     * @param[in] io - HwmonIO
     * @param[in] devPath - The /sys/devices sysfs path
     * @param[in] id - The hwmon id
     * @param[in] bus - Dbus bus object
     * @param[in] objPath - Dbus object path
     * @param[in] defer - Dbus object registration defer
     */
    FanPwm(std::unique_ptr<hwmonio::HwmonIOInterface> io,
           const std::string& devPath, const std::string& id,
           sdbusplus::bus::bus& bus, const char* objPath, bool defer,
           uint64_t target) :
        FanPwmObject(bus, objPath, defer),
        id(id), ioAccess(std::move(io)), devPath(devPath)
    {
        FanPwmObject::target(target);
    }

    /**
     * @brief Set the value of target
     *
     * @return Value of target
     */
    uint64_t target(uint64_t value) override;

  private:
    /** @brief hwmon type */
    static constexpr auto type = "pwm";
    /** @brief hwmon id */
    std::string id;
    /** @brief Hwmon sysfs access. */
    std::unique_ptr<hwmonio::HwmonIOInterface> ioAccess;
    /** @brief Physical device path. */
    std::string devPath;
};

} // namespace hwmon

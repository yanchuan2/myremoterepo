#include "ExecutorImpl.hpp"
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (int i = 0; i < (int)commands.size(); i++) {
        // 转向功能
        if (commands[i] == 'L') {
            if (pose.heading == 'N') {
                pose.heading = 'W';
            } else if (pose.heading == 'E') {
                pose.heading = 'N';
            } else if (pose.heading == 'S') {
                pose.heading = 'E';
            } else if (pose.heading == 'W') {
                pose.heading = 'S';
            }
        }
        if (commands[i] == 'R') {
            if (pose.heading == 'N') {
                pose.heading = 'E';
            } else if (pose.heading == 'E') {
                pose.heading = 'S';
            } else if (pose.heading == 'S') {
                pose.heading = 'W';
            } else if (pose.heading == 'W') {
                pose.heading = 'N';
            }
        }
        // 前进功能
        if (commands[i] == 'M') {
            if (pose.heading == 'N') {
                pose.y = 1;
            } else if (pose.heading == 'E') {
                pose.x = 1;
            } else if (pose.heading == 'S') {
                pose.y = -1;
            } else if (pose.heading == 'W') {
                pose.x = -1;
            }
        }
    }
    return;
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas
// namespace adas
